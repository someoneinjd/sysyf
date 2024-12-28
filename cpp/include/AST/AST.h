#pragma once
#include <ostream>
#include <string>

#include "Box.hpp"
#include "TypeAlias.h"
#include "Union.hpp"

namespace sysyf {
namespace ast {

enum struct BinaryOp { OR, AND, EQ, NEQ, LT, LTE, GT, GTE, ADD, SUB, MUL, DIV, MOD };

enum struct UnaryOp { POS, NEG, NOT };

enum struct Type { INT, FLOAT, VOID };

using Expr =
    Union<int, float, Box<struct BinaryExpr>, Box<struct UnaryExpr>, Box<struct LVal>, Box<struct FuncCallExpr>>;

struct BinaryExpr {
    BinaryOp op;
    Expr lhs, rhs;
};

struct UnaryExpr {
    UnaryOp op;
    Expr expr;
};

struct LVal {
    std::string name;
    Opt<Expr> array_idx;
};

struct FuncCallExpr {
    std::string func_name;
    Vec<Expr> params;
};

struct AssignStmt {
    LVal var;
    Expr val;
};

struct ExprStmt {
    Expr expr;
};

struct EmptyStmt {};

struct VarDefStmt {
    bool is_const;
    Type type;
    std::string name;
    Opt<int> array_idx;
    Opt<Vec<Expr>> init_vals;
};

struct BreakStmt {};

struct ContinueStmt {};

struct ReturnStmt {
    Opt<Expr> ret_val;
};

using Stmt = Union<AssignStmt, ExprStmt, EmptyStmt, VarDefStmt, Box<struct IfStmt>, Box<struct WhileStmt>, BreakStmt,
                   ContinueStmt, ReturnStmt, Box<struct BlockStmt>>;

struct IfStmt {
    Expr cond;
    Stmt if_body;
    Opt<Stmt> else_body;
};

struct WhileStmt {
    Expr cond;
    Stmt while_body;
};

struct BlockStmt {
    Vec<Stmt> stmts;
};

struct FuncParam {
    std::string name;
    Type type;
    bool is_array;
};

struct FuncDef {
    Type ret_type;
    std::string name;
    Vec<FuncParam> params;
    BlockStmt body;
};

using GlobalDef = Union<VarDefStmt, FuncDef>;

struct Assembly {
    Vec<GlobalDef> defs;
};

std::ostream &operator<<(std::ostream &out, const BinaryOp op);
std::ostream &operator<<(std::ostream &out, const UnaryOp op);
std::ostream &operator<<(std::ostream &out, const Type op);

std::ostream &operator<<(std::ostream &out, const BinaryExpr &expr);
std::ostream &operator<<(std::ostream &out, const UnaryExpr &expr);
std::ostream &operator<<(std::ostream &out, const LVal &expr);
std::ostream &operator<<(std::ostream &out, const FuncCallExpr &expr);

std::ostream &operator<<(std::ostream &out, const AssignStmt &stmt);
std::ostream &operator<<(std::ostream &out, const ExprStmt &stmt);
std::ostream &operator<<(std::ostream &out, const EmptyStmt &stmt);
std::ostream &operator<<(std::ostream &out, const VarDefStmt &stmt);
std::ostream &operator<<(std::ostream &out, const IfStmt &stmt);
std::ostream &operator<<(std::ostream &out, const WhileStmt &stmt);
std::ostream &operator<<(std::ostream &out, const BreakStmt &stmt);
std::ostream &operator<<(std::ostream &out, const ContinueStmt &stmt);
std::ostream &operator<<(std::ostream &out, const ReturnStmt &stmt);
std::ostream &operator<<(std::ostream &out, const BlockStmt &stmt);

}  // namespace ast

}  // namespace sysyf
