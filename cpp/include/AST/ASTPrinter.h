#pragma once
#include <cstddef>
#include <string>

#include "AST.h"
#include "ASTVisitor.hpp"
#include "TypeAlias.h"

namespace sysyf {
namespace ast {

struct ASTPrinter : public ASTVisitor<ASTPrinter> {
    using ASTVisitor<ASTPrinter>::visit;
    std::string visit(RefPtr<const int> expr);
    std::string visit(RefPtr<const float> expr);
    std::string visit(RefPtr<const UnaryExpr> expr);
    std::string visit(RefPtr<const BinaryExpr> expr);
    std::string visit(RefPtr<const LVal> expr);
    std::string visit(RefPtr<const FuncCallExpr> expr);

    std::string visit(RefPtr<const AssignStmt> stmt);
    std::string visit(RefPtr<const ExprStmt> stmt);
    std::string visit(RefPtr<const EmptyStmt> stmt);
    std::string visit(RefPtr<const VarDefStmt> stmt);
    std::string visit(RefPtr<const IfStmt> stmt);
    std::string visit(RefPtr<const BlockStmt> stmt);
    std::string visit(RefPtr<const WhileStmt> stmt);
    std::string visit(RefPtr<const BreakStmt> stmt);
    std::string visit(RefPtr<const ContinueStmt> stmt);
    std::string visit(RefPtr<const ReturnStmt> stmt);
    std::string visit(RefPtr<const FuncDef> stmt);
    std::string visit(RefPtr<const FuncParam> stmt);
    std::string visit(RefPtr<const Assembly> stmt);

  private:
    std::size_t indent_ = 0;
    void inc_indent() { indent_ += 2; }
    void dec_indent() { indent_ -= 2; }
    std::string indent() const { return std::string(indent_, ' '); }
};
}  // namespace ast
}  // namespace sysyf
