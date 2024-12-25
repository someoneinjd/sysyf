from itertools import batched

from sysyf_parser.sysyf_parser import Transformer

from .ast import (
    AssignStmt,
    BinaryExpr,
    BinaryOp,
    BreakStmt,
    ContinueStmt,
    EmptyStmt,
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


class ASTBuilder(Transformer):
    PLUS = str
    NAME = str
    PLUS = str
    MINUS = str
    MUL = str
    DIV = str
    MOD = str
    LOR = str
    LAND = str
    EQ = str
    NEQ = str
    LT = str
    LTE = str
    GT = str
    GTE = str
    NOT = str
    LBRACKET = str
    RBRACKET = str

    def start(self, comp_unit):
        return comp_unit[0]

    def comp_unit(self, defs: list):
        ret = []
        for i in defs:
            match i:
                case {"multi_var_decl": decls}:
                    ret.extend(decls)
                case _:
                    ret.append(i)
        return ret

    def stmt(self, stmt: list):
        return stmt[0]

    def block(self, stmts: list):
        ret = []
        for i in stmts:
            match i:
                case {"multi_var_decl": decls}:
                    ret.extend(decls)
                case _:
                    ret.append(i)
        return ret

    def block_item(self, ops: list):
        return ops[0]

    def if_stmt(self, ops: list):
        match ops:
            case [cond, if_body]:
                return IfStmt(cond, if_body, None)
            case [cond, if_body, else_body]:
                return IfStmt(cond, if_body, else_body)

    def while_stmt(self, ops: list):
        return WhileStmt(ops[0], ops[1])

    def assign_stmt(self, ops: list):
        return AssignStmt(ops[0], ops[1])

    def exp_stmt(self, ops: list):
        return ExpStmt(ops[0])

    def empty_stmt(self, _: list):
        return EmptyStmt()

    def func_def(self, ops: list):
        return FuncDef(ops[0], ops[1], ops[2:-1], ops[-1])

    def func_fparam(self, ops: list):
        match ops:
            case [param_type, param_name]:
                return FuncParam(param_name, param_type, False)
            case [param_type, param_name, "[", "]"]:
                return FuncParam(param_name, param_type, True)

    def break_stmt(self, _: list):
        return BreakStmt()

    def continue_stmt(self, _: list):
        return ContinueStmt()

    def return_stmt(self, ret: list):
        if len(ret) == 0:
            return ReturnStmt(None)
        return ReturnStmt(ret[0])

    def const_decl(self, ops: list):
        for var_def in ops[1:]:
            var_def.type = ops[0]
        return {"multi_var_decl": ops[1:]}

    def const_def(self, ops: list):
        match ops:
            case [name, init_vals]:
                return VarDefStmt(True, Type.INT, name, None, init_vals)
            case [name, "[", "]", init_vals]:
                return VarDefStmt(True, Type.INT, name, len(init_vals), init_vals)
            case [name, "[", length, "]", init_vals]:
                return VarDefStmt(True, Type.INT, name, length, init_vals)

    def const_init_val(self, ops: list):
        return ops

    def var_decl(self, ops: list):
        for var_def in ops[1:]:
            var_def.type = ops[0]
        return {"multi_var_decl": ops[1:]}

    def var_def(self, ops: list):
        match ops:
            case [name]:
                return VarDefStmt(False, Type.INT, name, None, None)
            case [name, "[", "]"]:
                return VarDefStmt(False, Type.INT, name, 0, None)
            case [name, "[", length, "]"]:
                return VarDefStmt(False, Type.INT, name, length, None)
            case [name, vals]:
                return VarDefStmt(False, Type.INT, name, None, vals)
            case [name, "[", "]", vals]:
                return VarDefStmt(False, Type.INT, name, len(vals), vals)
            case [name, "[", length, "]", vals]:
                return VarDefStmt(False, Type.INT, name, length, vals)

    def init_val(self, init_vals: list):
        return init_vals

    def cond(self, exps: list):
        return exps[0]

    def exp(self, exps: list):
        return exps[0]

    def lor_exp(self, ops: list):
        lhs: Expr = ops[0]
        for _, exp in batched(ops[1:], 2):
            lhs = BinaryExpr(BinaryOp.OR, lhs, exp)
        return lhs

    def land_exp(self, ops: list):
        lhs: Expr = ops[0]
        for _, exp in batched(ops[1:], 2):
            lhs = BinaryExpr(BinaryOp.AND, lhs, exp)
        return lhs

    def eq_exp(self, ops: list):
        lhs: Expr = ops[0]
        for op, exp in batched(ops[1:], 2):
            match op:
                case "==":
                    lhs = BinaryExpr(BinaryOp.EQ, lhs, exp)
                case "!=":
                    lhs = BinaryExpr(BinaryOp.NEQ, lhs, exp)
        return lhs

    def rel_exp(self, ops: list):
        lhs: Expr = ops[0]
        for op, exp in batched(ops[1:], 2):
            match op:
                case "<":
                    lhs = BinaryExpr(BinaryOp.LT, lhs, exp)
                case ">":
                    lhs = BinaryExpr(BinaryOp.GT, lhs, exp)
                case "<=":
                    lhs = BinaryExpr(BinaryOp.LTE, lhs, exp)
                case ">=":
                    lhs = BinaryExpr(BinaryOp.GTE, lhs, exp)
        return lhs

    def add_exp(self, ops: list):
        lhs: Expr = ops[0]
        for op, exp in batched(ops[1:], 2):
            match op:
                case "+":
                    lhs = BinaryExpr(BinaryOp.ADD, lhs, exp)
                case "-":
                    lhs = BinaryExpr(BinaryOp.SUB, lhs, exp)
        return lhs

    def mul_exp(self, ops: list):
        lhs: Expr = ops[0]
        for op, exp in batched(ops[1:], 2):
            match op:
                case "*":
                    lhs = BinaryExpr(BinaryOp.MUL, lhs, exp)
                case "/":
                    lhs = BinaryExpr(BinaryOp.DIV, lhs, exp)
                case "%":
                    lhs = BinaryExpr(BinaryOp.MOD, lhs, exp)
        return lhs

    def unary_exp(self, ops: list):
        match ops:
            case [exp]:
                return exp
            case ["+", exp]:
                return UnaryExpr(UnaryOp.POS, exp)
            case ["-", exp]:
                return UnaryExpr(UnaryOp.NEG, exp)
            case ["!", exp]:
                return UnaryExpr(UnaryOp.NOT, exp)

    def func_call(self, ops: list):
        return FuncCallExpr(ops[0], ops[1:])

    def lval(self, idents: list):
        match idents:
            case [name]:
                return LVal(name, None)
            case [name, idx]:
                return LVal(name, idx)

    def number(self, nums: list):
        return nums[0]

    def btype(self, types: list):
        return types[0]

    def ident(self, names: list):
        return names[0]

    def VOID_T(self, _: list):
        return Type.VOID

    def INT_T(self, _: list):
        return Type.INT

    def FLOAT_T(self, _: list):
        return Type.FLOAT

    def INT(self, int_literal: str):
        if int_literal.startswith(("0x", "0X", "-0x", "-0X", "+0x", "+0X")):
            return int(int_literal, 16)
        elif int_literal.startswith(("0", "-0", "+0")):
            return int(int_literal, 8)
        return int(int_literal)

    def FLOAT(self, fp_literal: str):
        return float(fp_literal)
