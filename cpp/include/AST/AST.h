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

struct BinaryExpr;
struct UnaryExpr;
struct LVal;
struct FuncCallExpr;

using Expr = Union<int, float, BinaryExpr, UnaryExpr, LVal, FuncCallExpr>;

struct BinaryExpr {
    BinaryOp op;
    Box<Expr> lhs, rhs;
};

struct UnaryExpr {
    UnaryOp op;
    Box<Expr> expr;
};

struct LVal {
    std::string name;
    Opt<Box<Expr>> array_idx;
};

struct FuncCallExpr {
    std::string func_name;
    Vec<Box<Expr>> params;
};

struct AssignStmt;
struct ExprStmt;
struct EmptyStmt;
struct VarDefStmt;
struct IfStmt;
struct WhileStmt;
struct BreakStmt;
struct ContinueStmt;
struct ReturnStmt;
struct BlockStmt;

using Stmt = Union<AssignStmt, ExprStmt, EmptyStmt, VarDefStmt, IfStmt, WhileStmt, BreakStmt, ContinueStmt, ReturnStmt,
                   BlockStmt>;

struct AssignStmt {
    Box<LVal> var;
    Box<Expr> val;
};

struct ExprStmt {
    Box<Expr> expr;
};

struct EmptyStmt {};

struct VarDefStmt {
    bool is_const;
    Type type;
    std::string name;
    Opt<int> array_idx;
    Opt<Vec<Box<Expr>>> init_vals;
};

struct IfStmt {
    Box<Expr> cond;
    Box<Stmt> if_body;
    Opt<Box<Stmt>> else_body;
};

struct WhileStmt {
    Box<Expr> cond;
    Box<Stmt> while_body;
};

struct BreakStmt {};

struct ContinueStmt {};

struct ReturnStmt {
    Opt<Box<Expr>> ret_val;
};

struct BlockStmt {
    Vec<Box<Stmt>> stmts;
};

struct FuncParam {
    std::string name;
    Type type;
    bool is_array;
};

struct FuncDef {
    Type ret_type;
    std::string name;
    Vec<Box<FuncParam>> params;
    Box<BlockStmt> body;
};

using GlobalDef = Union<VarDefStmt, FuncDef>;

struct Assembly {
    Vec<Box<GlobalDef>> defs;
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
