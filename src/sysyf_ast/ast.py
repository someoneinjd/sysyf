from dataclasses import dataclass
from enum import Enum
from typing import Optional, TypeAlias


class BinaryOp(Enum):
    LT = 0
    LTE = 1
    GT = 2
    GTE = 3
    EQ = 4
    NEQ = 5
    AND = 6
    OR = 7
    ADD = 8
    SUB = 9
    MUL = 10
    DIV = 11
    MOD = 12


class UnaryOp(Enum):
    POS = 0
    NEG = 1
    NOT = 2


class Type(Enum):
    INT = 0
    FLOAT = 1
    VOID = 2


@dataclass
class BinaryExpr:
    op: BinaryOp
    lhs: "Expr"
    rhs: "Expr"


@dataclass
class UnaryExpr:
    op: UnaryOp
    exp: "Expr"


@dataclass
class LVal:
    name: str
    array_idx: Optional["Expr"]


@dataclass
class FuncCallExpr:
    func_name: str
    params: list["Expr"]


Expr: TypeAlias = BinaryExpr | UnaryExpr | LVal | FuncCallExpr | int | float


@dataclass
class ReturnStmt:
    ret: Expr | None


@dataclass
class BreakStmt:
    pass


@dataclass
class ContinueStmt:
    pass


@dataclass
class WhileStmt:
    cond: Expr
    body: "Stmt"


@dataclass
class IfStmt:
    cond: Expr
    if_body: "Stmt"
    else_body: Optional["Stmt"]


@dataclass
class ExpStmt:
    exp: Expr


@dataclass
class EmptyStmt:
    pass


@dataclass
class AssignStmt:
    var: LVal
    val: Expr


@dataclass
class VarDefStmt:
    is_const: bool
    type: Type
    name: str
    array_length: int | None
    init_vals: list[Expr] | None


BlockStmt: TypeAlias = list["Stmt"]
Stmt: TypeAlias = (
    ReturnStmt
    | BreakStmt
    | ContinueStmt
    | WhileStmt
    | IfStmt
    | BlockStmt
    | ExpStmt
    | EmptyStmt
    | VarDefStmt
    | AssignStmt
)


@dataclass
class FuncParam:
    name: str
    type: Type
    is_array: bool


@dataclass
class FuncDef:
    ret_type: Type
    name: str
    params: list[FuncParam]
    body: BlockStmt


GlobalDef: TypeAlias = FuncDef | VarDefStmt

Assembly: TypeAlias = list[GlobalDef]
