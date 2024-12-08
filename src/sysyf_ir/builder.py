import contextlib
from typing import Any, TypeGuard

import llvmlite.ir as ir

from sysyf_ast.ast import (
    Assembly,
    AssignStmt,
    BinaryExpr,
    BinaryOp,
    BlockStmt,
    BreakStmt,
    ContinueStmt,
    Expr,
    ExpStmt,
    FuncCallExpr,
    FuncDef,
    FuncParam,
    IfStmt,
    LVal,
    ReturnStmt,
    Type,
    UnaryExpr,
    UnaryOp,
    VarDefStmt,
    WhileStmt,
)
from sysyf_ast.visitor import ASTVisitor


def all_literals(vals: list[Expr]) -> TypeGuard[list[int | float]]:
    return all(isinstance(i, int | float) for i in vals)


INT = ir.IntType(32)
BOOL = ir.IntType(1)
VOID = ir.VoidType()
FLOAT = ir.FloatType()


class IRBuilder(ASTVisitor):
    def __init__(self) -> None:
        super().__init__()
        self._builder = ir.IRBuilder()
        self._module = ir.Module()
        self._var_sym_table: list[dict[str, ir.AllocaInstr | ir.GlobalVariable]] = [{}]
        self._return_block: ir.Block
        self._func_sym_table: dict[str, ir.Function] = {
            "getint": ir.Function(self._module, ir.FunctionType(INT, []), "get_int"),
            "getfloat": ir.Function(self._module, ir.FunctionType(INT, []), "get_float"),
            "getch": ir.Function(self._module, ir.FunctionType(INT, []), "get_char"),
            "getarray": ir.Function(self._module, ir.FunctionType(INT, [ir.PointerType(INT)]), "get_int_array"),
            "putint": ir.Function(self._module, ir.FunctionType(VOID, [INT]), "put_int"),
            "putfloat": ir.Function(self._module, ir.FunctionType(VOID, [FLOAT]), "put_float"),
            "putch": ir.Function(self._module, ir.FunctionType(VOID, [INT]), "put_char"),
            "putarray": ir.Function(
                self._module,
                ir.FunctionType(VOID, [INT, ir.PointerType(INT)]),
                "put_int_array",
            ),
            "memset": self._module.declare_intrinsic("llvm.memset", (ir.PointerType(ir.IntType(8)), ir.IntType(64))),
        }

    def unify_type(self, lhs: Any, rhs: Any) -> tuple[ir.Value, ir.Value, bool]:
        is_float = True
        if lhs.type == FLOAT and rhs.type != FLOAT:
            rhs = self._builder.sitofp(rhs, FLOAT)
        elif lhs.type != FLOAT and rhs.type == FLOAT:
            lhs = self._builder.sitofp(lhs, FLOAT)
        elif lhs.type != FLOAT and rhs.type != FLOAT:
            is_float = False
        return lhs, rhs, is_float

    def cast(self, exp, typ: ir.Type):
        if exp.type != typ:
            match typ:
                case ir.IntType() if typ.width == 32:
                    return self._builder.fptosi(exp, typ)
                case ir.IntType() if typ.width == 1 and exp.type == INT:
                    return self._builder.icmp_signed("!=", exp, INT(0))
                case ir.IntType() if typ.width == 1 and exp.type == FLOAT:
                    return self._builder.fcmp_ordered("!=", exp, FLOAT(0.0))
                case ir.FloatType():
                    return self._builder.sitofp(exp, typ)
                case _:
                    raise TypeError(f"Unsupport type cast: from {exp.type} to {typ}")
        return exp

    def is_terminated(self) -> bool:
        return self._builder.block.is_terminated

    @contextlib.contextmanager
    def scope(self):
        self._var_sym_table.append({})
        yield
        self._var_sym_table.pop()

    def push_var(self, name: str, value: ir.AllocaInstr | ir.GlobalVariable):
        self._var_sym_table[-1][name] = value

    def push_func(self, name: str, value: ir.Function):
        self._func_sym_table[name] = value

    def find_var(self, name: str) -> ir.AllocaInstr | ir.GlobalVariable | None:
        for i in self._var_sym_table[::-1]:
            if name in i:
                return i[name]

    def find_func(self, name: str) -> ir.Function | None:
        return self._func_sym_table.get(name)

    def visit_Assembly(self, node: Assembly):
        for def_ in node:
            match def_:
                case FuncDef(_):
                    self.visit_FuncDef(def_)
                case VarDefStmt(_):
                    self.visit_VarDefStmt(def_)
        return self._module.__repr__()

    def visit_VarDefStmt(self, node: VarDefStmt):
        match node.type:
            case Type.INT:
                typ = INT
                elem_typ = typ
                if node.array_length is not None:
                    typ = ir.ArrayType(typ, node.array_length)
            case Type.FLOAT:
                typ = FLOAT
                elem_typ = typ
                if node.array_length is not None:
                    typ = ir.ArrayType(typ, node.array_length)
            case Type.VOID:
                raise TypeError(f"variables cannot be void: {node.name}")
        if len(self._var_sym_table) == 1:
            global_var = ir.GlobalVariable(self._module, typ, node.name)
            if node.init_vals is not None:
                assert all_literals(node.init_vals), f"Global vars can only be initialized by literals: {node.name}"
                if node.array_length is not None and len(node.init_vals) != 0:
                    init_val = [elem_typ(int(i) if elem_typ != FLOAT else float(i)) for i in node.init_vals]
                    for _ in range(len(node.init_vals), node.array_length):
                        init_val.append(elem_typ(0))
                elif node.array_length is not None:
                    init_val = None
                else:
                    init_val = int(node.init_vals[0]) if typ != FLOAT else float(node.init_vals[0])
            else:
                init_val = None
            global_var.initializer = typ(init_val)
            global_var.global_constant = node.is_const
            self.push_var(node.name, global_var)
        else:
            local_var = self._builder.alloca(typ)
            self.push_var(node.name, local_var)
            if node.init_vals is not None:
                if node.array_length is not None:
                    array_begin = self._builder.gep(local_var, [INT(0), INT(0)], True)
                    for i in node.init_vals:
                        val = self.visit_Expr(i)
                        self._builder.store(self.cast(val, elem_typ), array_begin)
                        array_begin = self._builder.gep(array_begin, [INT(1)], True)
                    if len(node.init_vals) < node.array_length:
                        bytes_num = ir.IntType(64)((node.array_length - len(node.init_vals)) * 4)
                        bytes_begin = self._builder.bitcast(array_begin, ir.PointerType(ir.IntType(8)))
                        memset = self.find_func("memset")
                        self._builder.call(memset, (bytes_begin, ir.IntType(8)(0), bytes_num, BOOL(0)))
                else:
                    self._builder.store(self.cast(self.visit_Expr(node.init_vals[0]), typ), local_var)

    def visit_FuncDef(self, node: FuncDef):
        with self.scope():
            match node.ret_type:
                case Type.INT:
                    ret_type = INT
                case Type.FLOAT:
                    ret_type = FLOAT
                case Type.VOID:
                    ret_type = VOID
            func_type = ir.FunctionType(ret_type, [self.visit_FuncParam(i) for i in node.params])
            func = ir.Function(self._module, func_type, node.name)
            self.push_func(node.name, func)
            entry_block = func.append_basic_block("entry")
            self._return_block = func.append_basic_block("return")
            self._builder.position_at_end(entry_block)
            if ret_type != VOID:
                self.push_var("%retval", self._builder.alloca(ret_type))
            for param, arg in zip(node.params, func.args, strict=True):
                alloca_arg = self._builder.alloca(arg.type)
                self._builder.store(arg, alloca_arg)
                self.push_var(param.name, alloca_arg)
            for i in node.body:
                self.visit_Stmt(i)
                if self.is_terminated():
                    break
            if not self.is_terminated():
                self._builder.branch(self._return_block)
            self._builder.position_at_end(self._return_block)
            if ret_type != VOID:
                self._builder.ret(self._builder.load(self.find_var("%retval")))
            else:
                self._builder.ret_void()

    def visit_FuncParam(self, node: FuncParam):
        typ = INT if node.type == Type.INT else FLOAT
        if node.is_array:
            typ = ir.PointerType(typ)
        return typ

    def visit_BlockStmt(self, node: BlockStmt):
        with self.scope():
            for i in node:
                self.visit_Stmt(i)
                if self.is_terminated():
                    break

    def visit_ExpStmt(self, node: ExpStmt):
        self.visit_Expr(node.exp)

    def visit_AssignStmt(self, node: AssignStmt):
        lval = self.visit_LVal(node.var, True)
        self._builder.store(self.cast(self.visit_Expr(node.val), lval.type.pointee), lval)

    def visit_ReturnStmt(self, node: ReturnStmt):
        ret_val_ptr = self.find_var("%retval")
        if node.ret is not None and ret_val_ptr is not None:
            self._builder.store(self.cast(self.visit_Expr(node.ret), ret_val_ptr.type.pointee), ret_val_ptr)
        self._builder.branch(self._return_block)

    def visit_IfStmt(self, node: IfStmt):
        cond = self.cast(self.visit_Expr(node.cond), BOOL)
        if node.else_body is not None:
            with self._builder.if_else(cond) as (then, otherwise):
                with then, self.scope():
                    self.visit_Stmt(node.if_body)
                with otherwise, self.scope():
                    self.visit_Stmt(node.else_body)
        else:
            with self._builder.if_then(cond), self.scope():
                self.visit_Stmt(node.if_body)

    def visit_WhileStmt(self, node: WhileStmt):
        self._while_cond_block = self._builder.append_basic_block(self._builder.block.name + ".whilecond")
        while_body = self._builder.append_basic_block(self._builder.block.name + ".whilebody")
        self._while_next_block = self._builder.append_basic_block(self._builder.block.name + ".endwhile")
        self._builder.branch(self._while_cond_block)
        self._builder.position_at_end(self._while_cond_block)
        cond = self.cast(self.visit_Expr(node.cond), BOOL)
        self._builder.cbranch(cond, while_body, self._while_next_block)
        stmts = node.body if isinstance(node.body, list) else [node.body]
        self._builder.position_at_end(while_body)
        with self.scope():
            for stmt in stmts:
                old_cond_block = self._while_cond_block
                old_next_block = self._while_next_block
                self.visit_Stmt(stmt)
                self._while_cond_block = old_cond_block
                self._while_next_block = old_next_block
                if self.is_terminated():
                    break
            if not self.is_terminated():
                self._builder.branch(self._while_cond_block)
        self._builder.position_at_end(self._while_next_block)

    def visit_BreakStmt(self, node: BreakStmt):
        self._builder.branch(self._while_next_block)

    def visit_ContinueStmt(self, node: ContinueStmt):
        self._builder.branch(self._while_cond_block)

    def visit_Int(self, node: int):
        return INT(node)

    def visit_Float(self, node: float):
        return FLOAT(node)

    def visit_LVal(
        self, node: LVal, require_address=False
    ) -> ir.GEPInstr | ir.LoadInstr | ir.AllocaInstr | ir.GlobalVariable:
        ptr = self.find_var(node.name)
        if ptr is None:
            raise NameError(f"variable {node.name} not found in current scope")
        if node.array_idx is not None:
            index = self.visit_Expr(node.array_idx)
            if ptr.type.pointee.is_pointer:
                ptr = self._builder.gep(self._builder.load(ptr), [index], True)
            else:
                ptr = self._builder.gep(ptr, [INT(0), index], True)
        return ptr if require_address else self._builder.load(ptr)

    def visit_BinaryExpr(self, node: BinaryExpr) -> Any:  # ir.Value:
        if node.op not in [BinaryOp.OR, BinaryOp.AND]:
            lhs, rhs, is_float = self.unify_type(self.visit_Expr(node.lhs), self.visit_Expr(node.rhs))
            match node.op:
                case BinaryOp.ADD:
                    return self._builder.fadd(lhs, rhs) if is_float else self._builder.add(lhs, rhs)
                case BinaryOp.SUB:
                    return self._builder.fsub(lhs, rhs) if is_float else self._builder.sub(lhs, rhs)
                case BinaryOp.MUL:
                    return self._builder.fmul(lhs, rhs) if is_float else self._builder.mul(lhs, rhs)
                case BinaryOp.DIV:
                    return self._builder.fdiv(lhs, rhs) if is_float else self._builder.sdiv(lhs, rhs)
                case BinaryOp.MOD:
                    if is_float:
                        raise TypeError("Take modulo of floating point numbers")
                    return self._builder.srem(lhs, rhs)
                case BinaryOp.LT:
                    return self.visit_CmpExpr("<", lhs, rhs, is_float)
                case BinaryOp.LTE:
                    return self.visit_CmpExpr("<=", lhs, rhs, is_float)
                case BinaryOp.GT:
                    return self.visit_CmpExpr(">", lhs, rhs, is_float)
                case BinaryOp.GTE:
                    return self.visit_CmpExpr(">=", lhs, rhs, is_float)
                case BinaryOp.EQ:
                    return self.visit_CmpExpr("==", lhs, rhs, is_float)
                case BinaryOp.NEQ:
                    return self.visit_CmpExpr("!=", lhs, rhs, is_float)
        elif node.op == BinaryOp.OR:
            lhs = self.cast(self.visit_Expr(node.lhs), BOOL)
            cond = self._builder.alloca(INT)
            self._builder.store(INT(1), cond)
            with self._builder.if_then(self._builder.not_(lhs)):
                self._builder.store(self.cast(self.visit_Expr(node.rhs), INT), cond)
            return self._builder.load(cond)
        elif node.op == BinaryOp.AND:
            lhs = self.cast(self.visit_Expr(node.lhs), BOOL)
            cond = self._builder.alloca(INT)
            self._builder.store(INT(0), cond)
            with self._builder.if_then(lhs):
                self._builder.store(self.cast(self.visit_Expr(node.rhs), INT), cond)
            return self._builder.load(cond)

    def visit_CmpExpr(self, op: str, lhs, rhs, is_float: bool) -> Any:
        cmp = self._builder.fcmp_ordered(op, lhs, rhs) if is_float else self._builder.icmp_signed(op, lhs, rhs)
        return self._builder.zext(cmp, INT)

    def visit_UnaryExpr(self, node: UnaryExpr) -> Any:
        exp = self.visit_Expr(node.exp)
        is_float = exp.type == FLOAT
        match node.op:
            case UnaryOp.POS:
                return exp
            case UnaryOp.NEG:
                return self._builder.fneg(exp) if is_float else self._builder.neg(exp)
            case UnaryOp.NOT:
                if exp.type == FLOAT:
                    cmp = self._builder.fcmp_ordered("==", exp, FLOAT(0.0))
                else:
                    cmp = self._builder.icmp_signed("==", exp, INT(0))
                return self._builder.zext(cmp, INT)

    def visit_FuncCallExpr(self, node: FuncCallExpr) -> Any:
        func = self.find_func(node.func_name)
        if func is None:
            raise NameError(f"Not defined function: {node.func_name}")
        call_param = []
        for rparam, fparam in zip(node.params, func.args, strict=True):
            if fparam.type.is_pointer:
                assert isinstance(rparam, LVal)
                ptr = self.visit_LVal(rparam, True)
                if isinstance(ptr.type.pointee, ir.ArrayType):
                    call_param.append(self._builder.gep(ptr, [INT(0), INT(0)]))
                else:
                    call_param.append(self._builder.load(ptr))
            else:
                call_param.append(self.cast(self.visit_Expr(rparam), fparam.type))
        return self._builder.call(func, call_param)
