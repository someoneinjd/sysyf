#include "AST.h"

#include "ASTPrinter.h"

namespace sysyf {
namespace ast {
std::ostream &operator<<(std::ostream &out, const BinaryOp op) {
    switch (op) {
        case BinaryOp::OR: out << "||"; break;
        case BinaryOp::AND: out << "&&"; break;
        case BinaryOp::LT: out << "<"; break;
        case BinaryOp::LTE: out << "<="; break;
        case BinaryOp::GT: out << ">"; break;
        case BinaryOp::GTE: out << ">="; break;
        case BinaryOp::EQ: out << "=="; break;
        case BinaryOp::NEQ: out << "!="; break;
        case BinaryOp::ADD: out << "+"; break;
        case BinaryOp::SUB: out << "-"; break;
        case BinaryOp::MUL: out << "*"; break;
        case BinaryOp::DIV: out << "/"; break;
        case BinaryOp::MOD: out << "%"; break;
    }
    return out;
}
std::ostream &operator<<(std::ostream &out, const UnaryOp op) {
    switch (op) {
        case UnaryOp::POS: out << "+"; break;
        case UnaryOp::NEG: out << "-"; break;
        case UnaryOp::NOT: out << "!"; break;
    }
    return out;
}
std::ostream &operator<<(std::ostream &out, const Type op) {
    switch (op) {
        case Type::INT: out << "int"; break;
        case Type::FLOAT: out << "float"; break;
        case Type::VOID: out << "void"; break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const BinaryExpr &expr) { return out << ASTPrinter{}.visit(&expr); }
std::ostream &operator<<(std::ostream &out, const UnaryExpr &expr) { return out << ASTPrinter{}.visit(&expr); }
std::ostream &operator<<(std::ostream &out, const LVal &expr) { return out << ASTPrinter{}.visit(&expr); }
std::ostream &operator<<(std::ostream &out, const FuncCallExpr &expr) { return out << ASTPrinter{}.visit(&expr); }

std::ostream &operator<<(std::ostream &out, const AssignStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const ExprStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const EmptyStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const VarDefStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const IfStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const WhileStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const BreakStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const ContinueStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const ReturnStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }
std::ostream &operator<<(std::ostream &out, const BlockStmt &stmt) { return out << ASTPrinter{}.visit(&stmt); }

}  // namespace ast
}  // namespace sysyf
