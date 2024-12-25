#pragma once

#include "ASTVisitor.hpp"
#include "BasicBlock.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "InstBuilder.h"
#include "Instruction.h"
#include "Module.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Union.hpp"

namespace sysyf {
namespace ir {

const Type VOID = VoidType{};
const Type INT = IntType{32};
const Type BOOL = IntType{1};
const Type FLOAT = FloatType{};

class IRBuilder : public ast::ASTVisitor<IRBuilder> {
  public:
    using ASTVisitor<IRBuilder>::visit;
    IRBuilder(RefPtr<Module> m) : module_{m}, builder_{m}, vars_{{}}, funcs_{} {
        funcs_ = {{"getint", Function::new_(module_, FunctionType{INT, {}}, "get_int")},
                  {"getfloat", Function::new_(module_, FunctionType{FLOAT, {}}, "get_float")},
                  {"getch", Function::new_(module_, FunctionType{INT, {}}, "get_char")},
                  {"getarray", Function::new_(module_, FunctionType{INT, {Type{PointerType{INT}}}}, "get_int_array")},

                  {"putint", Function::new_(module_, FunctionType{VOID, {INT}}, "put_int")},
                  {"putfloat", Function::new_(module_, FunctionType{VOID, {FLOAT}}, "put_float")},
                  {"putch", Function::new_(module_, FunctionType{VOID, {INT}}, "put_char")},
                  {"putarray", Function::new_(module_, FunctionType{VOID, {INT, Type{PointerType{INT}}}}, "put_int_array")}};
    }
    RefPtr<Value> find_var(const std::string &name) const {
        for (auto iter = vars_.rbegin(); iter != vars_.rend(); iter++)
            if (auto result = iter->find(name); result != iter->end()) return result->second;
        return nullptr;
    }
    RefPtr<Function> find_func(const std::string &name) const {
        auto result = funcs_.find(name);
        return result == funcs_.end() ? nullptr : result->second;
    }
    void push_var(std::string name, RefPtr<Value> val) { vars_.back()[name] = val; }
    void push_func(std::string name, RefPtr<Function> val) { funcs_[name] = val; }
    void enter_scope() { vars_.emplace_back(); }
    void exit_scope() { vars_.pop_back(); }
    auto unify_type(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        auto is_float = true;
        if (lhs->type().is<FloatType>() && not rhs->type().is<FloatType>())
            rhs = builder_.sitofp(rhs, lhs->type());
        else if (not lhs->type().is<FloatType>() && rhs->type().is<FloatType>())
            lhs = builder_.sitofp(lhs, rhs->type());
        else if (not lhs->type().is<FloatType>() && not rhs->type().is<FloatType>())
            is_float = false;
        return std::tuple{lhs, rhs, is_float};
    }
    RefPtr<Value> cast(RefPtr<Value> exp, const Type &target_type) {
        if (exp->type() != target_type) {
            if (target_type == INT) return builder_.fptosi(exp, target_type);
            if (target_type == BOOL)
                return exp->type().is<FloatType>() ? builder_.fcmp(FCmpType::ONE, exp, builder_.const_(0.0))
                                                   : builder_.icmp(ICmpType::NE, exp, builder_.const_(0));
            if (target_type.is<FloatType>()) return builder_.sitofp(exp, target_type);
        }
        return exp;
    }
    RefPtr<Value> visit(RefPtr<const int> expr);
    RefPtr<Value> visit(RefPtr<const float> expr);
    RefPtr<Value> visit(RefPtr<const ast::UnaryExpr> expr);
    RefPtr<Value> visit(RefPtr<const ast::BinaryExpr> expr);
    RefPtr<Value> visit(RefPtr<const ast::LVal> expr, bool require_address = false);
    RefPtr<Value> visit(RefPtr<const ast::FuncCallExpr> expr);

    void visit(RefPtr<const ast::AssignStmt> stmt);
    void visit(RefPtr<const ast::ExprStmt> stmt);
    void visit(RefPtr<const ast::EmptyStmt> stmt);
    void visit(RefPtr<const ast::VarDefStmt> stmt);
    void visit(RefPtr<const ast::IfStmt> stmt);
    void visit(RefPtr<const ast::BlockStmt> stmt);
    void visit(RefPtr<const ast::WhileStmt> stmt);
    void visit(RefPtr<const ast::BreakStmt> stmt);
    void visit(RefPtr<const ast::ContinueStmt> stmt);
    void visit(RefPtr<const ast::ReturnStmt> stmt);
    void visit(RefPtr<const ast::FuncDef> stmt);
    Type visit(RefPtr<const ast::FuncParam> stmt);
    void visit(RefPtr<const ast::Assembly> stmt);

  private:
    RefPtr<Module> module_;
    RefPtr<BasicBlock> ret_block_ = nullptr, while_cond_block_ = nullptr, while_next_block_ = nullptr;
    InstBuilder builder_;
    Vec<Map<std::string, RefPtr<Value>>> vars_;
    Map<std::string, RefPtr<Function>> funcs_;
};
}  // namespace ir

}  // namespace sysyf
