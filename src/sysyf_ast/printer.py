from .ast import (
    Assembly,
    AssignStmt,
    BinaryExpr,
    BinaryOp,
    BlockStmt,
    BreakStmt,
    ContinueStmt,
    EmptyStmt,
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
from .visitor import ASTVisitor


class ASTPrinter(ASTVisitor):
    def __init__(self) -> None:
        super().__init__()
        self._indent = 0

    def indent(self) -> str:
        return self._indent * " "

    def inc_indent(self):
        self._indent += 4

    def dec_indent(self):
        self._indent -= 4

    def visit_Assembly(self, node: Assembly):
        return "\n".join(self.visit_GlobalDef(i) for i in node)

    def visit_VarDefStmt(self, node: VarDefStmt):
        ret_str = f"{'const ' if node.is_const else ''}{self.visit_Type(node.type)} {node.name}"
        if node.array_length is not None:
            ret_str += f"[{node.array_length}]"
            if node.init_vals is not None:
                init_vals_str = ", ".join(self.visit_Expr(i) for i in node.init_vals)
                ret_str += f" = {{{init_vals_str}}}"
        elif node.init_vals is not None:
            ret_str += f" = {self.visit_Expr(node.init_vals[0])}"
        return f"{self.indent()}{ret_str};"

    def visit_FuncDef(self, node: FuncDef):
        params_str = ", ".join(self.visit_FuncParam(i) for i in node.params)
        ret_str = f"{self.visit_Type(node.ret_type)} {node.name}({params_str})"
        return ret_str + f"\n{self.visit_BlockStmt(node.body)}"

    def visit_FuncParam(self, node: FuncParam):
        ret_str = f"{self.visit_Type(node.type)} {node.name}"
        if node.is_array:
            ret_str += "[]"
        return ret_str

    def visit_Int(self, node: int):
        return str(node)

    def visit_Float(self, node: float):
        return str(node)

    def visit_FuncCallExpr(self, node: FuncCallExpr):
        return f"{node.func_name}({', '.join(self.visit_Expr(i) for i in node.params)})"

    def visit_BinaryExpr(self, node: BinaryExpr):
        return f"({self.visit_Expr(node.lhs)} {self.visit_BinaryOp(node.op)} {self.visit_Expr(node.rhs)})"

    def visit_UnaryExpr(self, node: UnaryExpr):
        return f"({self.visit_UnaryOp(node.op)}{self.visit_Expr(node.exp)})"

    def visit_UnaryOp(self, node: UnaryOp):
        match node:
            case UnaryOp.POS:
                return "+"
            case UnaryOp.NEG:
                return "-"
            case UnaryOp.NOT:
                return "!"

    def visit_LVal(self, node: LVal):
        if node.array_idx is not None:
            return f"{node.name}[{self.visit_Expr(node.array_idx)}]"
        return f"{node.name}"

    def visit_BinaryOp(self, node: BinaryOp):
        match node:
            case BinaryOp.AND:
                return "&&"
            case BinaryOp.OR:
                return "||"
            case BinaryOp.EQ:
                return "=="
            case BinaryOp.NEQ:
                return "!="
            case BinaryOp.LT:
                return "<"
            case BinaryOp.LTE:
                return "<="
            case BinaryOp.GT:
                return ">"
            case BinaryOp.GTE:
                return ">="
            case BinaryOp.ADD:
                return "+"
            case BinaryOp.SUB:
                return "-"
            case BinaryOp.MUL:
                return "*"
            case BinaryOp.DIV:
                return "/"
            case BinaryOp.MOD:
                return "%"

    def visit_Type(self, node: Type):
        match node:
            case Type.INT:
                return "int"
            case Type.FLOAT:
                return "float"
            case Type.VOID:
                return "void"

    def visit_AssignStmt(self, node: AssignStmt):
        return f"{self.indent()}{self.visit_LVal(node.var)} = {self.visit_Expr(node.val)};"

    def visit_EmptyStmt(self, node: EmptyStmt):
        return f"{self.indent()};"

    def visit_ExpStmt(self, node: ExpStmt):
        return f"{self.indent()}{self.visit_Expr(node.exp)};"

    def visit_IfStmt(self, node: IfStmt):
        if_str = f"{self.indent()}if ({self.visit_Expr(node.cond)})\n"
        if isinstance(node.if_body, list):
            if_str += self.visit_Stmt(node.if_body)
        else:
            self.inc_indent()
            if_str += self.visit_Stmt(node.if_body)
            self.dec_indent()
        if node.else_body is not None:
            if_str += f"\n{self.indent()}else\n"
            if isinstance(node.else_body, list):
                if_str += self.visit_Stmt(node.else_body)
            else:
                self.inc_indent()
                if_str += self.visit_Stmt(node.else_body)
                self.dec_indent()
        return if_str

    def visit_WhileStmt(self, node: WhileStmt):
        while_str = f"{self.indent()}while ({self.visit_Expr(node.cond)})\n"
        if isinstance(node.body, list):
            while_str += self.visit_Stmt(node.body)
        else:
            self.inc_indent()
            while_str += self.visit_Stmt(node.body)
            self.dec_indent()
        return while_str

    def visit_BreakStmt(self, node: BreakStmt):
        return f"{self.indent()}break;"

    def visit_ContinueStmt(self, node: ContinueStmt):
        return f"{self.indent()}continue;"

    def visit_BlockStmt(self, node: BlockStmt):
        ret_str = f"{self.indent()}{{\n"
        self.inc_indent()
        ret_str += "\n".join(self.visit_Stmt(i) for i in node)
        self.dec_indent()
        ret_str += f"\n{self.indent()}}}"
        return ret_str

    def visit_ReturnStmt(self, node: ReturnStmt):
        if node.ret is not None:
            return f"{self.indent()}return {self.visit_Expr(node.ret)};"
        return f"{self.indent()}return;"
