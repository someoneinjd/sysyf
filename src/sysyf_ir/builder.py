from typing import Any, TypeGuard

import llvmlite.ir as ir

from sysyf_ast.ast import (
    Assembly,
    AssignStmt,
    BinaryExpr,
    BinaryOp,
    BlockStmt,
    EmptyStmt,
    Expr,
    ExpStmt,
    FuncCallExpr,
    FuncDef,
    FuncParam,
    LVal,
    ReturnStmt,
    Type,
    UnaryExpr,
    UnaryOp,
    VarDefStmt,
)
from sysyf_ast.visitor import ASTVisitor


def all_literals(vals: list[Expr]) -> TypeGuard[list[int | float]]:
    return all(isinstance(i, int | float) for i in vals)


class IRBuilder(ASTVisitor):
    def __init__(self) -> None:
        super().__init__()
        self._builder = ir.IRBuilder()
        self._module = ir.Module()
        self._var_sym_table: list[dict[str, ir.AllocaInstr | ir.GlobalVariable]] = [{}]
        self._return_block: ir.Block
        self._func_sym_table: dict[str, ir.Function] = {
            "getint": ir.Function(self._module, ir.FunctionType(ir.IntType(32), []), "get_int"),
            "getfloat": ir.Function(self._module, ir.FunctionType(ir.IntType(32), []), "get_float"),
            "getch": ir.Function(self._module, ir.FunctionType(ir.IntType(32), []), "get_char"),
            "getarray": ir.Function(
                self._module, ir.FunctionType(ir.IntType(32), [ir.PointerType(ir.IntType(32))]), "get_int_array"
            ),
            "putint": ir.Function(self._module, ir.FunctionType(ir.VoidType(), [ir.IntType(32)]), "put_int"),
            "putfloat": ir.Function(self._module, ir.FunctionType(ir.VoidType(), [ir.FloatType()]), "put_float"),
            "putch": ir.Function(self._module, ir.FunctionType(ir.VoidType(), [ir.IntType(32)]), "put_char"),
            "putarray": ir.Function(
                self._module,
                ir.FunctionType(ir.VoidType(), [ir.IntType(32), ir.PointerType(ir.IntType(32))]),
                "put_int_array",
            ),
        }

    def unify_type(self, lhs: Any, rhs: Any) -> tuple[ir.Value, ir.Value, bool]:
        is_float = True
        if lhs.type == ir.FloatType() and rhs.type != ir.FloatType():
            rhs = self._builder.sitofp(rhs, ir.FloatType())
        elif lhs.type != ir.FloatType() and rhs.type == ir.FloatType():
            lhs = self._builder.sitofp(lhs, ir.FloatType())
        elif lhs.type != ir.FloatType() and rhs.type != ir.FloatType():
            is_float = False
        return lhs, rhs, is_float

    def cast(self, exp, typ: ir.Type):
        if exp.type != typ:
            match typ:
                case ir.IntType():
                    return self._builder.fptosi(exp, typ)
                case ir.FloatType():
                    return self._builder.sitofp(exp, typ)
                case _:
                    raise TypeError(f"Unsupport type cast: from {exp.type} to {typ}")
        return exp

    def enter_scope(self):
        self._var_sym_table.append({})

    def exit_scope(self):
        self._var_sym_table.pop()

    def push_var(self, name: str, value: ir.AllocaInstr | ir.GlobalVariable):
        self._var_sym_table[-1][name] = value

    def push_func(self, name: str, value: ir.Function):
        self._func_sym_table[name] = value

    def find_var(self, name: str) -> ir.AllocaInstr | ir.GlobalVariable | None:
        for i in self._var_sym_table[::-1]:
            try:
                return i[name]
            except KeyError:
                continue

    def find_func(self, name: str) -> ir.Function | None:
        try:
            return self._func_sym_table[name]
        except KeyError:
            return None

    def visit_Assembly(self, node: Assembly):
        for def_ in node:
            match def_:
                case FuncDef(_):
                    self.visit_FuncDef(def_)
                case VarDefStmt(_):
                    self.visit_VarDefStmt(def_)
        print(self._module)
        return self._module.__repr__()

    def visit_VarDefStmt(self, node: VarDefStmt):
        match node.type:
            case Type.INT:
                typ = ir.IntType(32)
                elem_typ = typ
                if node.array_length is not None:
                    typ = ir.ArrayType(typ, node.array_length)
            case Type.FLOAT:
                typ = ir.FloatType()
                elem_typ = typ
                if node.array_length is not None:
                    typ = ir.ArrayType(typ, node.array_length)
            case Type.VOID:
                raise TypeError(f"variables cannot be void: {node.name}")
        if len(self._var_sym_table) == 1:
            global_var = ir.GlobalVariable(self._module, typ, node.name)
            if node.init_vals is not None:
                assert all_literals(node.init_vals), f"Global vars can only be initialized by literals: {node.name}"
                if node.array_length is not None:
                    init_val = [elem_typ(int(i) if elem_typ != ir.FloatType() else float(i)) for i in node.init_vals]
                    for _ in range(len(node.init_vals), node.array_length):
                        init_val.append(elem_typ(0))
                else:
                    init_val = int(node.init_vals[0]) if typ != ir.FloatType() else float(node.init_vals[0])
            else:
                init_val = [elem_typ(0) for _ in range(node.array_length)] if node.array_length is not None else 0
            global_var.initializer = typ(init_val)
            global_var.global_constant = node.is_const
            self.push_var(node.name, global_var)
        else:
            local_var = self._builder.alloca(typ)
            self.push_var(node.name, local_var)
            if node.init_vals is not None:
                if node.array_length is not None:
                    array_begin = self._builder.gep(local_var, [ir.IntType(32)(0), ir.IntType(32)(0)], True)
                    for i in node.init_vals:
                        val = self.visit_Expr(i)
                        self._builder.store(self.cast(val, elem_typ), array_begin)
                        array_begin = self._builder.gep(array_begin, [ir.IntType(32)(1)], True)
                else:
                    self._builder.store(self.cast(self.visit_Expr(node.init_vals[0]), typ), local_var)

    def visit_FuncDef(self, node: FuncDef):
        self.enter_scope()
        match node.ret_type:
            case Type.INT:
                ret_type = ir.IntType(32)
            case Type.FLOAT:
                ret_type = ir.FloatType()
            case Type.VOID:
                ret_type = ir.VoidType()
        func_type = ir.FunctionType(ret_type, [self.visit_FuncParam(i) for i in node.params])
        func = ir.Function(self._module, func_type, node.name)
        self.push_func(node.name, func)
        entry_block = func.append_basic_block("entry")
        self._return_block = func.append_basic_block("return")
        self._builder.position_at_end(entry_block)
        if ret_type != ir.VoidType():
            self.push_var("%retval", self._builder.alloca(ret_type))
        for param, arg in zip(node.params, func.args, strict=True):
            alloca_arg = self._builder.alloca(arg.type)
            self._builder.store(arg, alloca_arg)
            self.push_var(param.name, alloca_arg)
        for i in node.body:
            self.visit_Stmt(i)
            if self._builder.block.is_terminated:
                break
        if not entry_block.is_terminated:
            self._builder.position_at_end(entry_block)
            self._builder.branch(self._return_block)
        self._builder.position_at_end(self._return_block)
        if ret_type != ir.VoidType():
            self._builder.ret(self._builder.load(self.find_var("%retval")))
        else:
            self._builder.ret_void()
        self.exit_scope()

    def visit_FuncParam(self, node: FuncParam):
        typ = ir.IntType(32) if node.type == Type.INT else ir.FloatType()
        if node.is_array:
            typ = ir.PointerType(typ)
        return typ

    def visit_BlockStmt(self, node: BlockStmt):
        self.enter_scope()
        for i in node:
            self.visit_Stmt(i)
            if self._builder.block.is_terminated:
                break
        self.exit_scope()

    def visit_EmptyStmt(self, node: EmptyStmt) -> Any:
        return

    def visit_ExpStmt(self, node: ExpStmt) -> Any:
        self.visit_Expr(node.exp)

    def visit_AssignStmt(self, node: AssignStmt) -> Any:
        lval = self.visit_LVal(node.var, True)
        self._builder.store(self.cast(self.visit_Expr(node.val), lval.type.pointee), lval)

    def visit_ReturnStmt(self, node: ReturnStmt) -> Any:
        ret_val_ptr = self.find_var("%retval")
        if node.ret is not None and ret_val_ptr is not None:
            self._builder.store(self.cast(self.visit_Expr(node.ret), ret_val_ptr.type.pointee), ret_val_ptr)
        self._builder.branch(self._return_block)

    def visit_Int(self, node: int):
        return ir.IntType(32)(node)

    def visit_Float(self, node: float):
        return ir.FloatType()(node)

    def visit_LVal(self, node: LVal, require_address=False) -> Any:
        ptr = self.find_var(node.name)
        if ptr is None:
            raise NameError(f"variable {node.name} not found in current scope")
        if node.array_idx is not None:
            index = self.visit_Expr(node.array_idx)
            ptr = (
                self._builder.gep(ptr, [index], True)
                if ptr.type.pointee.is_pointer
                else self._builder.gep(ptr, [ir.IntType(32)(0), index], True)
            )
        return ptr if require_address else self._builder.load(ptr)

    def visit_BinaryExpr(self, node: BinaryExpr) -> Any:  # ir.Value:
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

    def visit_CmpExpr(self, op: str, lhs, rhs, is_float: bool) -> Any:
        cmp = self._builder.fcmp_ordered(op, lhs, rhs) if is_float else self._builder.icmp_signed(op, lhs, rhs)
        return self._builder.zext(cmp, ir.IntType(32))

    def visit_UnaryExpr(self, node: UnaryExpr) -> Any:
        exp = self.visit_Expr(node.exp)
        is_float = exp.type == ir.FloatType()
        match node.op:
            case UnaryOp.POS:
                return exp
            case UnaryOp.NEG:
                return self._builder.fneg(exp) if is_float else self._builder.neg(exp)
            case UnaryOp.NOT:
                if exp.type == ir.FloatType():
                    cmp = self._builder.fcmp_ordered("!=", exp, ir.FloatType()(0.0))
                else:
                    cmp = self._builder.icmp_signed("!=", exp, ir.IntType(32)(0))
                return self._builder.zext(cmp, ir.IntType(32))

    def visit_FuncCallExpr(self, node: FuncCallExpr) -> Any:
        func = self.find_func(node.func_name)
        if func is None:
            raise NameError(f"Not defined function: {node.func_name}")
        call_param = []
        for rparam, fparm in zip(node.params, func.args, strict=True):
            if fparm.type.is_pointer:
                assert isinstance(rparam, LVal)
                ptr = self.visit_LVal(rparam, True)
                if isinstance(ptr.type.pointee, ir.ArrayType):
                    call_param.append(self._builder.gep(ptr, [ir.IntType(32)(0), ir.IntType(32)(0)]))
                else:
                    call_param.append(ptr)
            else:
                call_param.append(self.cast(self.visit_Expr(rparam), fparm.type))
        return self._builder.call(func, call_param)
