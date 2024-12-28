#include "ASTPrinter.h"

#include <cstddef>
#include <sstream>
#include <string>

#include "AST.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ast {

std::string ASTPrinter::visit(const int &expr) { return std::to_string(expr); }
std::string ASTPrinter::visit(const float &expr) { return std::to_string(expr); }
std::string ASTPrinter::visit(const UnaryExpr &expr) {
    std::stringstream out{};
    out << expr.op;
    if (const auto *bin_expr = expr.expr.as<BinaryExpr>())
        out << "(" << visit(*bin_expr) << ")";
    else
        out << visit(expr.expr);
    return out.str();
}
std::string ASTPrinter::visit(const BinaryExpr &expr) {
    constexpr static std::array<int, 13> priority{{0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4}};
    std::stringstream out{};
    if (const auto *lhs_expr = expr.lhs.as<BinaryExpr>()) {
        if (priority[(int)lhs_expr->op] < priority[(int)expr.op])
            out << "(" << visit(*lhs_expr) << ")";
        else
            out << visit(*lhs_expr);
    } else {
        out << visit(expr.lhs);
    }
    out << " " << expr.op << " ";
    if (const auto *rhs_expr = expr.rhs.as<BinaryExpr>()) {
        if (priority[(int)rhs_expr->op] < priority[(int)expr.op])
            out << "(" << visit(*rhs_expr) << ")";
        else
            out << visit(*rhs_expr);
    } else {
        out << visit(expr.rhs);
    }
    return out.str();
}
std::string ASTPrinter::visit(const LVal &expr) {
    std::stringstream out{};
    out << expr.name;
    if (expr.array_idx) out << "[" << visit(*expr.array_idx) << "]";
    return out.str();
}
std::string ASTPrinter::visit(const FuncCallExpr &expr) {
    std::stringstream out{};
    out << expr.func_name << "(";
    if (not expr.params.empty()) {
        out << visit(expr.params[0]);
        for (std::size_t i = 1; i < expr.params.size(); i++) out << ", " << visit(expr.params[i]);
    }
    out << ")";
    return out.str();
}

std::string ASTPrinter::visit(const AssignStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << visit(stmt.var) << " = " << visit(stmt.val) << ";";
    return out.str();
}
std::string ASTPrinter::visit(const ExprStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << visit(stmt.expr) << ";";
    return out.str();
}
std::string ASTPrinter::visit(const EmptyStmt &) { return this->indent() + ";"; }
std::string ASTPrinter::visit(const VarDefStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << (stmt.is_const ? "const " : "") << stmt.type << " " << stmt.name;
    if (stmt.array_idx) out << "[" << *stmt.array_idx << "]";
    if (stmt.init_vals) {
        if (stmt.array_idx) {
            out << " = {";
            if (not stmt.init_vals->empty()) out << visit((*stmt.init_vals)[0]);
            for (std::size_t i = 1; i < stmt.init_vals->size(); i++) out << ", " << visit((*stmt.init_vals)[i]);
            out << "}";
        } else {
            out << " = " << visit((*stmt.init_vals)[0]);
        }
    }
    out << ";";
    return out.str();
}
std::string ASTPrinter::visit(const IfStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << "if (" << visit(stmt.cond) << ") {\n";
    this->inc_indent();
    if (const auto *if_body = stmt.if_body.as<BlockStmt>()) {
        for (const auto &i : if_body->stmts) out << visit(i) << "\n";
    } else {
        out << visit(stmt.if_body) << "\n";
    }
    this->dec_indent();
    out << this->indent() << "}";
    if (stmt.else_body) {
        out << " else {\n";
        this->inc_indent();
        if (const auto *else_body = stmt.else_body->as<BlockStmt>()) {
            for (const auto &i : else_body->stmts) out << visit(i) << "\n";
        } else {
            out << visit(*stmt.else_body) << "\n";
        }
        this->dec_indent();
        out << this->indent() << "}";
    }
    return out.str();
}
std::string ASTPrinter::visit(const BlockStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << "{\n";
    this->inc_indent();
    for (const auto &i : stmt.stmts) out << visit(i) << "\n";
    this->dec_indent();
    out << this->indent() << "}";
    return out.str();
}
std::string ASTPrinter::visit(const WhileStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << "while (" << visit(stmt.cond) << ") {\n";
    this->inc_indent();
    if (const auto *body = stmt.while_body.as<BlockStmt>()) {
        for (const auto &i : body->stmts) out << visit(i) << "\n";
    } else {
        out << visit(stmt.while_body) << "\n";
    }
    this->dec_indent();
    out << this->indent() << "}";
    return out.str();
}
std::string ASTPrinter::visit(const BreakStmt &) { return this->indent() + "break;"; }
std::string ASTPrinter::visit(const ContinueStmt &) { return this->indent() + "continue;"; }
std::string ASTPrinter::visit(const ReturnStmt &stmt) {
    std::stringstream out{};
    out << this->indent() << "return";
    if (stmt.ret_val) out << " " << visit(*stmt.ret_val);
    out << ";";
    return out.str();
}
std::string ASTPrinter::visit(const FuncDef &stmt) {
    std::stringstream out{};
    out << stmt.ret_type << " " << stmt.name << "(";
    if (not stmt.params.empty()) out << visit(stmt.params[0]);
    for (std::size_t i = 1; i < stmt.params.size(); i++) out << ", " << visit(stmt.params[i]);
    out << ") {\n";
    this->inc_indent();
    for (const auto &i : stmt.body.stmts) out << visit(i) << "\n";
    this->dec_indent();
    out << "}";
    return out.str();
}
std::string ASTPrinter::visit(const FuncParam &stmt) {
    std::stringstream out{};
    out << stmt.type << " " << stmt.name;
    if (stmt.is_array) out << "[]";
    return out.str();
}
std::string ASTPrinter::visit(const Assembly &stmt) {
    std::stringstream out{};
    for (const auto &i : stmt.defs) out << visit(i) << "\n";
    return out.str();
}

}  // namespace ast
}  // namespace sysyf
