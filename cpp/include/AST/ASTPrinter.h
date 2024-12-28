#pragma once
#include <cstddef>
#include <string>

#include "AST.h"
#include "ASTVisitor.hpp"

namespace sysyf {
namespace ast {

struct ASTPrinter : public ASTVisitor<ASTPrinter> {
    using ASTVisitor<ASTPrinter>::visit;
    std::string visit(const int &expr);
    std::string visit(const float &expr);
    std::string visit(const UnaryExpr &expr);
    std::string visit(const BinaryExpr &expr);
    std::string visit(const LVal &expr);
    std::string visit(const FuncCallExpr &expr);

    std::string visit(const AssignStmt &stmt);
    std::string visit(const ExprStmt &stmt);
    std::string visit(const EmptyStmt &stmt);
    std::string visit(const VarDefStmt &stmt);
    std::string visit(const IfStmt &stmt);
    std::string visit(const BlockStmt &stmt);
    std::string visit(const WhileStmt &stmt);
    std::string visit(const BreakStmt &stmt);
    std::string visit(const ContinueStmt &stmt);
    std::string visit(const ReturnStmt &stmt);
    std::string visit(const FuncDef &stmt);
    std::string visit(const FuncParam &stmt);
    std::string visit(const Assembly &stmt);

  private:
    std::size_t indent_ = 0;
    void inc_indent() { indent_ += 2; }
    void dec_indent() { indent_ -= 2; }
    std::string indent() const { return std::string(indent_, ' '); }
};
}  // namespace ast
}  // namespace sysyf
