#pragma once
#include <cassert>
#include <type_traits>

#include "AST.h"
#include "TypeAlias.h"

namespace sysyf {
namespace detail {
template <typename SubClass, typename Node, typename = void>
struct have_visitor_for : std::false_type {};

template <typename SubClass, typename Node>
struct have_visitor_for<SubClass, Node,
                        std::void_t<decltype(std::declval<SubClass>().visit(std::declval<RefPtr<const Node>>()))>>
    : std::true_type {};

template <typename SubClass, typename Node>
constexpr static bool have_visitor_for_v = have_visitor_for<SubClass, Node>::value;
}  // namespace detail
namespace ast {

template <typename SubClass>
struct ASTVisitor {
    constexpr ASTVisitor() noexcept {
        static_assert(detail::have_visitor_for_v<SubClass, int>,
                      "No visit function overloaded for RefPtr<const int> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, float>,
                      "No visit function overloaded for RefPtr<const float> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, BinaryExpr>,
                      "No visit function overloaded for RefPtr<const BinaryExpr> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, UnaryExpr>,
                      "No visit function overloaded for RefPtr<const UnaryExpr> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, LVal>,
                      "No visit function overloaded for RefPtr<const LVal> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, FuncCallExpr>,
                      "No visit function overloaded for RefPtr<const FuncCallExpr> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, AssignStmt>,
                      "No visit function overloaded for RefPtr<const AssignStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, ExprStmt>,
                      "No visit function overloaded for RefPtr<const ExprStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, EmptyStmt>,
                      "No visit function overloaded for RefPtr<const EmptyStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, VarDefStmt>,
                      "No visit function overloaded for RefPtr<const VarDefStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, IfStmt>,
                      "No visit function overloaded for RefPtr<const IfStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, BlockStmt>,
                      "No visit function overloaded for RefPtr<const BlockStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, WhileStmt>,
                      "No visit function overloaded for RefPtr<const WhileStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, BreakStmt>,
                      "No visit function overloaded for RefPtr<const BreakStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, ContinueStmt>,
                      "No visit function overloaded for RefPtr<const ContinueStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, ReturnStmt>,
                      "No visit function overloaded for RefPtr<const ReturnStmt> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, FuncDef>,
                      "No visit function overloaded for RefPtr<const FuncDef> is defined");
        static_assert(detail::have_visitor_for_v<SubClass, VarDefStmt>,
                      "No visit function overloaded for RefPtr<const VarDefStmt> is defined");
    }
    auto visit(RefPtr<const Expr> expr) {
        switch (expr->index()) {
            case 0: return static_cast<SubClass *>(this)->visit(expr->as<int>());
            case 1: return static_cast<SubClass *>(this)->visit(expr->as<float>());
            case 2: return static_cast<SubClass *>(this)->visit(expr->as<BinaryExpr>());
            case 3: return static_cast<SubClass *>(this)->visit(expr->as<UnaryExpr>());
            case 4: return static_cast<SubClass *>(this)->visit(expr->as<LVal>());
            case 5: return static_cast<SubClass *>(this)->visit(expr->as<FuncCallExpr>());
            default: assert(false && "Unreachable");
        }
    };

    auto visit(RefPtr<const Stmt> stmt) {
        switch (stmt->index()) {
            case 0: return static_cast<SubClass *>(this)->visit(stmt->as<AssignStmt>());
            case 1: return static_cast<SubClass *>(this)->visit(stmt->as<ExprStmt>());
            case 2: return static_cast<SubClass *>(this)->visit(stmt->as<EmptyStmt>());
            case 3: return static_cast<SubClass *>(this)->visit(stmt->as<VarDefStmt>());
            case 4: return static_cast<SubClass *>(this)->visit(stmt->as<IfStmt>());
            case 5: return static_cast<SubClass *>(this)->visit(stmt->as<WhileStmt>());
            case 6: return static_cast<SubClass *>(this)->visit(stmt->as<BreakStmt>());
            case 7: return static_cast<SubClass *>(this)->visit(stmt->as<ContinueStmt>());
            case 8: return static_cast<SubClass *>(this)->visit(stmt->as<ReturnStmt>());
            case 9: return static_cast<SubClass *>(this)->visit(stmt->as<BlockStmt>());
            default: assert(false && "Unreachable");
        }
    }

    auto visit(RefPtr<const GlobalDef> stmt) {
        switch (stmt->index()) {
            case 0: return static_cast<SubClass *>(this)->visit(stmt->as<VarDefStmt>());
            case 1: return static_cast<SubClass *>(this)->visit(stmt->as<FuncDef>());
            default: assert(false && "Unreachable");
        }
    }
};
}  // namespace ast
}  // namespace sysyf
