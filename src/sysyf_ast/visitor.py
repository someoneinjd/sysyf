from typing import Any

from .ast import (
    Assembly,
    AssignStmt,
    BinaryExpr,
    BlockStmt,
    BreakStmt,
    ContinueStmt,
    EmptyStmt,
    Expr,
    ExpStmt,
    FuncCallExpr,
    FuncDef,
    FuncParam,
    GlobalDef,
    IfStmt,
    LVal,
    ReturnStmt,
    Stmt,
    Type,
    UnaryExpr,
    VarDefStmt,
    WhileStmt,
)


class ASTVisitor:
    def __init__(self) -> None:
        pass

    def visit_Assembly(self, node: Assembly) -> Any:
        pass

    def visit_AssignStmt(self, node: AssignStmt) -> Any:
        pass

    def visit_BinaryExpr(self, node: BinaryExpr) -> Any:
        pass

    def visit_BlockStmt(self, node: BlockStmt) -> Any:
        pass

    def visit_BreakStmt(self, node: BreakStmt) -> Any:
        pass

    def visit_ContinueStmt(self, node: ContinueStmt) -> Any:
        pass

    def visit_EmptyStmt(self, node: EmptyStmt) -> Any:
        pass

    def visit_Expr(self, node: Expr) -> Any:
        match node:
            case BinaryExpr(_):
                return self.visit_BinaryExpr(node)
            case UnaryExpr(_):
                return self.visit_UnaryExpr(node)
            case LVal(_):
                return self.visit_LVal(node)
            case FuncCallExpr(_):
                return self.visit_FuncCallExpr(node)
            case int(_):
                return self.visit_Int(node)
            case float(_):
                return self.visit_Float(node)

    def visit_ExpStmt(self, node: ExpStmt) -> Any:
        pass

    def visit_Int(self, node: int) -> Any:
        pass

    def visit_Float(self, node: float) -> Any:
        pass

    def visit_FuncCallExpr(self, node: FuncCallExpr) -> Any:
        pass

    def visit_FuncDef(self, node: FuncDef) -> Any:
        pass

    def visit_FuncParam(self, node: FuncParam) -> Any:
        pass

    def visit_GlobalDef(self, node: GlobalDef) -> Any:
        match node:
            case FuncDef(_):
                return self.visit_FuncDef(node)
            case VarDefStmt(_):
                return self.visit_VarDefStmt(node)

    def visit_IfStmt(self, node: IfStmt) -> Any:
        pass

    def visit_LVal(self, node: LVal) -> Any:
        pass

    def visit_ReturnStmt(self, node: ReturnStmt) -> Any:
        pass

    def visit_Stmt(self, node: Stmt) -> Any:
        match node:
            case ReturnStmt(_):
                return self.visit_ReturnStmt(node)
            case BreakStmt():
                return self.visit_BreakStmt(node)
            case ContinueStmt():
                return self.visit_ContinueStmt(node)
            case WhileStmt(_):
                return self.visit_WhileStmt(node)
            case IfStmt(_):
                return self.visit_IfStmt(node)
            case [*other]:
                return self.visit_BlockStmt(other)
            case ExpStmt(_):
                return self.visit_ExpStmt(node)
            case EmptyStmt():
                return self.visit_EmptyStmt(node)
            case VarDefStmt(_):
                return self.visit_VarDefStmt(node)
            case AssignStmt(_):
                return self.visit_AssignStmt(node)

    def visit_Type(self, node: Type) -> Any:
        pass

    def visit_UnaryExpr(self, node: UnaryExpr) -> Any:
        pass

    def visit_VarDefStmt(self, node: VarDefStmt) -> Any:
        pass

    def visit_WhileStmt(self, node: WhileStmt) -> Any:
        pass
