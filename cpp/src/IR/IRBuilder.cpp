#include "IRBuilder.h"

#include <cstddef>
#include <type_traits>

#include "AST.h"
#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "InstBuilder.h"
#include "Instruction.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Utils.hpp"

#define with(i) if (const auto &_ = i; true)

namespace sysyf {
namespace ir {

constexpr static auto INT = IntType{32};
constexpr static auto VOID = VoidType{};
constexpr static auto FLOAT = FloatType{};
constexpr static auto BOOL = IntType{1};

class Scope {
  public:
    Scope(RefPtr<IRBuilder> parent) : parent_{parent} { parent_->enter_scope(); }
    ~Scope() { parent_->exit_scope(); }

  private:
    RefPtr<IRBuilder> parent_;
};

class IfThen {
  public:
    IfThen(RefPtr<InstBuilder> parent, RefPtr<Value> cond) : builder_{parent} {
        auto *bbif = builder_->function()->append_basic_block(builder_->block()->name() + ".if");
        bbend_ = builder_->function()->append_basic_block(builder_->block()->name() + ".endif");
        builder_->branch(cond, bbif, bbend_);
        builder_->position_at_end(bbif);
    }
    ~IfThen() {
        if (not builder_->terminated()) builder_->branch(bbend_);
        builder_->position_at_end(bbend_);
    }

  private:
    RefPtr<InstBuilder> builder_;
    RefPtr<BasicBlock> bbend_;
};

RefPtr<Value> IRBuilder::visit(const int &expr) { return builder_.const_(expr); }
RefPtr<Value> IRBuilder::visit(const float &expr) { return builder_.const_(expr); }
RefPtr<Value> IRBuilder::visit(const ast::UnaryExpr &expr) {
    auto *val = visit(expr.expr);
    switch (expr.op) {
        case ast::UnaryOp::POS: return val;
        case ast::UnaryOp::NEG: return val->type().is<IntType>() ? builder_.neg(val) : builder_.fneg(val);
        case ast::UnaryOp::NOT:
            return builder_.zext(val->type().is<IntType>() ? builder_.icmp(ICmpType::EQ, val, builder_.const_(0))
                                                           : builder_.fcmp(FCmpType::OEQ, val, builder_.const_(0.0)),
                                 INT);
        default: unreachable();
    }
}

template <typename T>
RefPtr<Value> visit_cmp(T op, InstBuilder &builder, RefPtr<Value> lhs, RefPtr<Value> rhs) {
    if constexpr (std::is_same_v<T, ICmpType>)
        return builder.zext(builder.icmp(op, lhs, rhs), INT);
    else
        return builder.zext(builder.fcmp(op, lhs, rhs), INT);
}

RefPtr<Value> IRBuilder::visit(const ast::BinaryExpr &expr) {
    if (expr.op != ast::BinaryOp::AND && expr.op != ast::BinaryOp::OR) {
        /* In C++, value computations and side effects of the initialization of every parameter in a function call are
         * indeterminately sequenced. So `unify_type(visit(expr.lhs), visit(expr.rhs))` is wrong as `rhs` may be visited
         * before `lhs`.
         */
        auto *lhs_old = visit(expr.lhs);
        auto *rhs_old = visit(expr.rhs);
        auto [lhs, rhs, is_float] = unify_type(lhs_old, rhs_old);
        switch (expr.op) {
            case ast::BinaryOp::ADD: return is_float ? builder_.fadd(lhs, rhs) : builder_.add(lhs, rhs);
            case ast::BinaryOp::SUB: return is_float ? builder_.fsub(lhs, rhs) : builder_.sub(lhs, rhs);
            case ast::BinaryOp::MUL: return is_float ? builder_.fmul(lhs, rhs) : builder_.mul(lhs, rhs);
            case ast::BinaryOp::DIV: return is_float ? builder_.fdiv(lhs, rhs) : builder_.sdiv(lhs, rhs);
            case ast::BinaryOp::MOD: return builder_.srem(lhs, rhs);
            case ast::BinaryOp::EQ:
                return is_float ? visit_cmp(FCmpType::OEQ, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::EQ, builder_, lhs, rhs);
            case ast::BinaryOp::NEQ:
                return is_float ? visit_cmp(FCmpType::ONE, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::NE, builder_, lhs, rhs);
            case ast::BinaryOp::LT:
                return is_float ? visit_cmp(FCmpType::OLT, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::SLT, builder_, lhs, rhs);
            case ast::BinaryOp::LTE:
                return is_float ? visit_cmp(FCmpType::OLE, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::SLE, builder_, lhs, rhs);
            case ast::BinaryOp::GT:
                return is_float ? visit_cmp(FCmpType::OGT, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::SGT, builder_, lhs, rhs);
            case ast::BinaryOp::GTE:
                return is_float ? visit_cmp(FCmpType::OGE, builder_, lhs, rhs)
                                : visit_cmp(ICmpType::SGE, builder_, lhs, rhs);
            default: unreachable();
        }
    } else if (expr.op == ast::BinaryOp::AND) {
        auto *lhs = cast(visit(expr.lhs), BOOL);
        auto *cond = builder_.alloca_(INT);
        builder_.store(builder_.const_(0), cond);
        with(IfThen(&builder_, lhs)) builder_.store(cast(visit(expr.rhs), INT), cond);
        return builder_.load(cond);
    } else {
        auto *lhs = visit(expr.lhs);
        auto *cond = builder_.alloca_(INT);
        builder_.store(builder_.const_(1), cond);
        if (lhs->type().is<FloatType>())
            lhs = builder_.fcmp(FCmpType::OEQ, lhs, builder_.const_(0.0));
        else
            lhs = builder_.icmp(ICmpType::EQ, lhs, builder_.const_(0));
        with(IfThen(&builder_, lhs)) builder_.store(cast(visit(expr.rhs), INT), cond);
        return builder_.load(cond);
    }
}

RefPtr<Value> IRBuilder::visit(const ast::LVal &expr, bool require_address) {
    auto *ptr = find_var(expr.name);
    if (expr.array_idx) {
        auto *index = visit(*expr.array_idx);
        if (ptr->type().as<PointerType>()->pointee.is<PointerType>())
            ptr = builder_.gep(builder_.load(ptr), {index});
        else
            ptr = builder_.gep(ptr, {builder_.const_(0), index});
    }
    return require_address ? ptr : builder_.load(ptr);
}

RefPtr<Value> IRBuilder::visit(const ast::FuncCallExpr &expr) {
    auto *func = find_func(expr.func_name);
    Vec<RefPtr<Value>> call_params{};
    call_params.reserve(expr.params.size());

    for (std::size_t i = 0; i < expr.params.size(); i++) {
        auto &fparam = func->arg(i);
        auto &rparam = expr.params[i];
        if (fparam.type().is<PointerType>()) {
            auto *ptr = visit(*rparam.as<ast::LVal>(), true);
            if (ptr->type().as<PointerType>()->pointee.is<ArrayType>())
                call_params.push_back(builder_.gep(ptr, {builder_.const_(0), builder_.const_(0)}));
            else
                call_params.push_back(builder_.load(ptr));
        } else {
            call_params.push_back(cast(visit(rparam), fparam.type()));
        }
    }
    return builder_.call(func, call_params);
}

void IRBuilder::visit(const ast::AssignStmt &stmt) {
    auto *lval = visit(stmt.var, true);
    builder_.store(cast(visit(stmt.val), lval->type().as<PointerType>()->pointee), lval);
}

void IRBuilder::visit(const ast::ExprStmt &stmt) { visit(stmt.expr); }
void IRBuilder::visit(const ast::EmptyStmt &) {}

void IRBuilder::visit(const ast::VarDefStmt &stmt) {
    Type elem_type, type;
    switch (stmt.type) {
        case ast::Type::INT:
            type = INT;
            elem_type = INT;
            break;
        case ast::Type::FLOAT:
            type = FLOAT;
            elem_type = FLOAT;
            break;
        default: unreachable();
    }
    if (stmt.array_idx) type = ArrayType{static_cast<unsigned>(*stmt.array_idx), std::move(type)};
    if (vars_.size() == 1) {
        RefPtr<Constant> init_val = nullptr;
        if (stmt.init_vals) {
            if (stmt.array_idx && not stmt.init_vals->empty()) {
                auto &init_vals = *stmt.init_vals;
                if (elem_type.is<FloatType>()) {
                    Vec<float> vals(*stmt.array_idx, 0.0);
                    for (std::size_t i = 0; i < init_vals.size(); i++)
                        vals[i] = init_vals[i].is<int>() ? static_cast<float>(*init_vals[i].as<int>())
                                                         : *init_vals[i].as<float>();
                    init_val = builder_.const_(vals);
                } else {
                    Vec<int> vals(*stmt.array_idx, 0);
                    for (std::size_t i = 0; i < init_vals.size(); i++)
                        vals[i] = init_vals[i].is<int>() ? *init_vals[i].as<int>()
                                                         : static_cast<int>(*init_vals[i].as<float>());
                    init_val = builder_.const_(vals);
                }
            } else if (not stmt.array_idx) {
                if (const int *int_val = stmt.init_vals->begin()->as<int>())
                    init_val =
                        type.is<IntType>() ? builder_.const_(*int_val) : builder_.const_(static_cast<float>(*int_val));
                else if (const float *float_val = stmt.init_vals->begin()->as<float>())
                    init_val = type.is<IntType>() ? builder_.const_(static_cast<int>(*float_val))
                                                  : builder_.const_(*float_val);
            }
        }
        auto *global_var = GlobalVariable::new_(module_, std::move(type), stmt.name, stmt.is_const, init_val);
        push_var(stmt.name, global_var);
    } else {
        auto *local_var = builder_.alloca_(type);
        push_var(stmt.name, local_var);
        if (stmt.init_vals) {
            if (stmt.array_idx) {
                auto *array_begin = builder_.gep(local_var, {builder_.const_(0), builder_.const_(0)});
                for (const auto &i : *stmt.init_vals) {
                    builder_.store(cast(visit(i), elem_type), array_begin);
                    array_begin = builder_.gep(array_begin, {builder_.const_(1)});
                }
                for (auto i = stmt.init_vals->size(); i < static_cast<std::size_t>(*stmt.array_idx); i++) {
                    builder_.store(elem_type.is<FloatType>() ? builder_.const_(0.0) : builder_.const_(0), array_begin);
                    array_begin = builder_.gep(array_begin, {builder_.const_(1)});
                }
            } else {
                builder_.store(cast(visit(*stmt.init_vals->begin()), type), local_var);
            }
        }
    }
}
void IRBuilder::visit(const ast::IfStmt &stmt) {
    auto *cond = cast(visit(stmt.cond), BOOL);
    if (stmt.else_body) {
        auto *bbif = builder_.function()->append_basic_block(builder_.block()->name() + ".if");
        auto *bbelse = builder_.function()->append_basic_block(builder_.block()->name() + ".else");
        auto *bbend = builder_.function()->append_basic_block(builder_.block()->name() + ".endif");
        builder_.branch(cond, bbif, bbelse);

        builder_.position_at_end(bbif);
        with(Scope(this)) visit(stmt.if_body);
        if (not builder_.terminated()) builder_.branch(bbend);

        builder_.position_at_end(bbelse);
        with(Scope(this)) visit(*stmt.else_body);
        if (not builder_.terminated()) builder_.branch(bbend);

        builder_.position_at_end(bbend);
    } else {
        with(IfThen(&builder_, cond)) with(Scope(this)) visit(stmt.if_body);
    }
}

void IRBuilder::visit(const ast::BlockStmt &stmt) {
    with(Scope(this)) {
        for (const auto &i : stmt.stmts) {
            visit(i);
            if (builder_.terminated()) break;
        }
    }
}

void IRBuilder::visit(const ast::WhileStmt &stmt) {
    while_cond_block_ = builder_.function()->append_basic_block(builder_.block()->name() + ".whilecond");
    auto *while_body = builder_.function()->append_basic_block(builder_.block()->name() + ".whilebody");
    while_next_block_ = builder_.function()->append_basic_block(builder_.block()->name() + ".endwhile");
    builder_.branch(while_cond_block_);
    builder_.position_at_end(while_cond_block_);
    builder_.branch(cast(visit(stmt.cond), BOOL), while_body, while_next_block_);
    builder_.position_at_end(while_body);
    with(Scope{this}) {
        if (auto *block = stmt.while_body.as<ast::BlockStmt>()) {
            for (auto &i : block->stmts) {
                auto *old_while_cond_block = while_cond_block_;
                auto *old_while_next_block = while_next_block_;
                visit(i);
                while_cond_block_ = old_while_cond_block;
                while_next_block_ = old_while_next_block;
                if (builder_.terminated()) break;
            }
        } else {
            auto *old_while_cond_block = while_cond_block_;
            auto *old_while_next_block = while_next_block_;
            visit(stmt.while_body);
            while_cond_block_ = old_while_cond_block;
            while_next_block_ = old_while_next_block;
        }
    }
    if (not builder_.terminated()) builder_.branch(while_cond_block_);
    builder_.position_at_end(while_next_block_);
}
void IRBuilder::visit(const ast::BreakStmt &) { builder_.branch(while_next_block_); }
void IRBuilder::visit(const ast::ContinueStmt &) { builder_.branch(while_cond_block_); }
void IRBuilder::visit(const ast::ReturnStmt &stmt) {
    if (auto *ret_val_ptr = find_var("%retval"))
        builder_.store(cast(visit(*stmt.ret_val), ret_val_ptr->type().as<PointerType>()->pointee), ret_val_ptr);
    builder_.branch(ret_block_);
}

void IRBuilder::visit(const ast::FuncDef &stmt) {
    with(Scope(this)) {
        Type ret_type;
        switch (stmt.ret_type) {
            case ast::Type::INT: ret_type = INT; break;
            case ast::Type::FLOAT: ret_type = FLOAT; break;
            case ast::Type::VOID: ret_type = VOID; break;
        }
        FunctionType func_type{std::move(ret_type), {}};
        for (const auto &arg : stmt.params) func_type.arg_types.emplace_back(visit(arg));
        auto *func = Function::new_(module_, std::move(func_type), stmt.name);
        push_func(stmt.name, func);
        builder_.position_at_end(func->append_basic_block("entry"));
        ret_block_ = func->append_basic_block("return");

        if (stmt.ret_type != ast::Type::VOID) push_var("%retval", builder_.alloca_(func->ret_type()));
        for (std::size_t i = 0; i < stmt.params.size(); i++) {
            auto *alloca_arg = builder_.alloca_(func->arg(i).type());
            builder_.store(&func->arg(i), alloca_arg);
            push_var(stmt.params[i].name, alloca_arg);
        }
        for (const auto &i : stmt.body.stmts) {
            visit(i);
            if (builder_.terminated()) break;
        }
        if (not builder_.terminated()) builder_.branch(ret_block_);
        builder_.position_at_end(ret_block_);
        if (stmt.ret_type != ast::Type::VOID)
            builder_.ret(builder_.load(find_var("%retval")));
        else
            builder_.ret();
    }
}

Type IRBuilder::visit(const ast::FuncParam &stmt) {
    auto type = stmt.type == ast::Type::INT ? Type{INT} : Type{FLOAT};
    if (stmt.is_array) return PointerType{std::move(type)};
    return type;
}

void IRBuilder::visit(const ast::Assembly &stmt) {
    for (const auto &def : stmt.defs) visit(def);
}

}  // namespace ir
}  // namespace sysyf
