#include "ASTBuilder.h"

#include <cassert>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include "AST.h"
#include "Any.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ast {

antlrcpp::Any ASTBuilder::visitComp_unit(SysYFParser::Comp_unitContext *context) {
    Assembly ret{};
    for (auto *def : context->global_def()) {
        visit(def);
        if (val_.is<Vec<VarDefStmt>>()) {
            for (auto &var_def : *val_.as<Vec<VarDefStmt>>()) {
                ret.defs.emplace_back(std::move(var_def));
            }
        } else {
            ret.defs.emplace_back(std::move(*val_.as<GlobalDef>()));
        }
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitGlobal_def(SysYFParser::Global_defContext *context) {
    if (context->func_def()) {
        visit(context->func_def());
    } else if (context->var_decl()) {
        visit(context->var_decl());
    } else if (context->const_decl()) {
        visit(context->const_decl());
    }
    return {};
}
antlrcpp::Any ASTBuilder::visitConst_decl(SysYFParser::Const_declContext *context) {
    visit(context->btype());
    auto var_type = *val_.as<Type>();
    Vec<VarDefStmt> ret;
    for (auto *def : context->const_def()) {
        visit(def);
        ret.emplace_back(std::move(*val_.as<Stmt>()->as<VarDefStmt>()));
        ret.back().type = var_type;
        ret.back().is_const = true;
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitBtype(SysYFParser::BtypeContext *context) {
    if (context->INT_T())
        val_ = Type::INT;
    else if (context->FLOAT_T())
        val_ = Type::FLOAT;
    return {};
}
antlrcpp::Any ASTBuilder::visitConst_def(SysYFParser::Const_defContext *context) {
    VarDefStmt ret;
    visit(context->ident());
    ret.name = std::move(*val_.as<std::string>());
    if (context->INT()) {
        auto str = context->INT()->getText();
        if (str[0] == '0') {
            if (str[1] == 'x' || str[1] == 'X') {
                ret.array_idx = std::stoi(str, nullptr, 16);
            } else {
                ret.array_idx = std::stoi(str, nullptr, 8);
            }
        } else {
            ret.array_idx = std::stoi(str);
        }
    }
    ret.init_vals = Vec<Box<Expr>>{};
    for (auto *expr : context->const_init_val()->exp()) {
        visit(expr);
        if (auto *int_val = val_.as<Expr>()->as<int>()) {
            ret.init_vals->emplace_back(*int_val);
        } else if (auto *float_val = val_.as<Expr>()->as<float>()) {
            ret.init_vals->emplace_back(*float_val);
        } else {
            assert(false);
        }
    }
    val_ = Stmt{std::move(ret)};
    return {};
}
antlrcpp::Any ASTBuilder::visitConst_init_val(SysYFParser::Const_init_valContext *) { return {}; }
antlrcpp::Any ASTBuilder::visitVar_decl(SysYFParser::Var_declContext *context) {
    visit(context->btype());
    auto var_type = *val_.as<Type>();
    Vec<VarDefStmt> ret;
    for (auto *def : context->var_def()) {
        visit(def);
        ret.emplace_back(std::move(*val_.as<Stmt>()->as<VarDefStmt>()));
        ret.back().type = var_type;
        ret.back().is_const = false;
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitVar_def(SysYFParser::Var_defContext *context) {
    VarDefStmt ret;
    visit(context->ident());
    ret.name = std::move(*val_.as<std::string>());
    if (context->INT()) {
        auto str = context->INT()->getText();
        if (str[0] == '0') {
            if (str[1] == 'x' || str[1] == 'X') {
                ret.array_idx = std::stoi(str, nullptr, 16);
            } else {
                ret.array_idx = std::stoi(str, nullptr, 8);
            }
        } else {
            ret.array_idx = std::stoi(str);
        }
    }
    if (context->init_val()) {
        ret.init_vals = Vec<Box<Expr>>{};
        for (auto *expr : context->init_val()->exp()) {
            visit(expr);
            ret.init_vals->emplace_back(std::move(*val_.as<Expr>()));
        }
    }
    val_ = Stmt{std::move(ret)};
    return {};
}
antlrcpp::Any ASTBuilder::visitInit_val(SysYFParser::Init_valContext *) { return {}; }
antlrcpp::Any ASTBuilder::visitFunc_def(SysYFParser::Func_defContext *context) {
    FuncDef ret;
    visit(context->ident());
    ret.name = std::move(*val_.as<std::string>());
    if (context->btype()) {
        visit(context->btype());
        ret.ret_type = *val_.as<Type>();
    }
    if (context->VOID_T()) ret.ret_type = Type::VOID;
    for (auto *fparam : context->func_fparam()) {
        visit(fparam);
        ret.params.emplace_back(std::move(*val_.as<FuncParam>()));
    }
    visit(context->block());
    ret.body = std::move(*val_.as<Stmt>()->as<BlockStmt>());
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitFunc_fparam(SysYFParser::Func_fparamContext *context) {
    FuncParam ret;
    ret.is_array = context->LBRACKET() && context->RBRACKET();
    visit(context->ident());
    ret.name = std::move(*val_.as<std::string>());
    visit(context->btype());
    ret.type = *val_.as<Type>();
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitBlock(SysYFParser::BlockContext *context) {
    BlockStmt ret;
    for (auto *stmt : context->block_item()) {
        visit(stmt);
        if (val_.is<Vec<VarDefStmt>>()) {
            for (auto &var_def : *val_.as<Vec<VarDefStmt>>()) {
                ret.stmts.emplace_back(std::move(var_def));
            }
        } else {
            ret.stmts.emplace_back(std::move(*val_.as<Stmt>()));
        }
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitBlock_item(SysYFParser::Block_itemContext *context) {
    if (context->const_decl())
        visit(context->const_decl());
    else if (context->var_decl())
        visit(context->var_decl());
    else if (context->stmt())
        visit(context->stmt());
    return {};
}
antlrcpp::Any ASTBuilder::visitStmt(SysYFParser::StmtContext *context) {
    if (context->block())
        visit(context->block());
    else if (context->assign_stmt())
        visit(context->assign_stmt());
    else if (context->while_stmt())
        visit(context->while_stmt());
    else if (context->if_stmt())
        visit(context->if_stmt());
    else if (context->break_stmt())
        visit(context->break_stmt());
    else if (context->continue_stmt())
        visit(context->continue_stmt());
    else if (context->exp_stmt())
        visit(context->exp_stmt());
    else if (context->empty_stmt())
        visit(context->empty_stmt());
    else if (context->return_stmt())
        visit(context->return_stmt());
    return {};
}
antlrcpp::Any ASTBuilder::visitAssign_stmt(SysYFParser::Assign_stmtContext *context) {
    AssignStmt ret;
    visit(context->lval());
    ret.var = std::move(*val_.as<Expr>()->as<LVal>());
    visit(context->exp());
    ret.val = std::move(*val_.as<Expr>());
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitEmpty_stmt(SysYFParser::Empty_stmtContext *) {
    val_ = EmptyStmt{};
    return {};
}
antlrcpp::Any ASTBuilder::visitExp_stmt(SysYFParser::Exp_stmtContext *context) {
    visit(context->exp());
    val_ = ExprStmt{std::move(*val_.as<Expr>())};
    return {};
}
antlrcpp::Any ASTBuilder::visitIf_stmt(SysYFParser::If_stmtContext *context) {
    IfStmt ret;
    visit(context->cond_exp());
    ret.cond = std::move(*val_.as<Expr>());
    visit(context->stmt(0));
    ret.if_body = std::move(*val_.as<Stmt>());
    if (context->stmt().size() == 2) {
        visit(context->stmt(1));
        ret.else_body = std::move(*val_.as<Stmt>());
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitWhile_stmt(SysYFParser::While_stmtContext *context) {
    WhileStmt ret;
    visit(context->cond_exp());
    ret.cond = std::move(*val_.as<Expr>());
    visit(context->stmt());
    ret.while_body = std::move(*val_.as<Stmt>());
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitBreak_stmt(SysYFParser::Break_stmtContext *) {
    val_ = BreakStmt{};
    return {};
}
antlrcpp::Any ASTBuilder::visitContinue_stmt(SysYFParser::Continue_stmtContext *) {
    val_ = ContinueStmt{};
    return {};
}
antlrcpp::Any ASTBuilder::visitReturn_stmt(SysYFParser::Return_stmtContext *context) {
    ReturnStmt ret{};
    if (context->exp()) {
        visit(context->exp());
        ret.ret_val = std::move(*val_.as<Expr>());
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitExp(SysYFParser::ExpContext *context) {
    if (context->lval()) {
        visit(context->lval());
    } else if (context->number()) {
        visit(context->number());
    } else if (context->func_call()) {
        visit(context->func_call());
    } else if (context->exp().size() == 1) {
        UnaryExpr ret;
        visit(context->exp(0));
        if (context->PLUS())
            ret.op = UnaryOp::POS;
        else if (context->MINUS())
            ret.op = UnaryOp::NEG;
        else if (context->NOT())
            ret.op = UnaryOp::NOT;
        else
            return {};
        if (ret.op == UnaryOp::NEG) {
            if (const auto *int_val = val_.as<Expr>()->as<int>()) {
                auto val = -(*int_val);
                val_ = val;
                return {};
            }
            if (const auto *float_val = val_.as<Expr>()->as<float>()) {
                auto val = -(*float_val);
                val_ = val;
                return {};
            }
        }
        ret.expr = std::move(*val_.as<Expr>());
        val_ = std::move(ret);
    } else if (context->exp().size() == 2) {
        BinaryExpr ret;
        visit(context->exp(0));
        ret.lhs = std::move(*val_.as<Expr>());
        visit(context->exp(1));
        ret.rhs = std::move(*val_.as<Expr>());
        if (context->PLUS()) ret.op = BinaryOp::ADD;
        if (context->MINUS()) ret.op = BinaryOp::SUB;
        if (context->MUL()) ret.op = BinaryOp::MUL;
        if (context->DIV()) ret.op = BinaryOp::DIV;
        if (context->MOD()) ret.op = BinaryOp::MOD;
        val_ = std::move(ret);
    }
    return {};
}
antlrcpp::Any ASTBuilder::visitCond_exp(SysYFParser::Cond_expContext *context) {
    if (context->exp()) {
        visit(context->exp());
    } else {
        BinaryExpr ret;
        visit(context->cond_exp(0));
        ret.lhs = std::move(*val_.as<Expr>());
        visit(context->cond_exp(1));
        ret.rhs = std::move(*val_.as<Expr>());
        if (context->EQ()) ret.op = BinaryOp::EQ;
        if (context->NEQ()) ret.op = BinaryOp::NEQ;
        if (context->LT()) ret.op = BinaryOp::LT;
        if (context->LTE()) ret.op = BinaryOp::LTE;
        if (context->GT()) ret.op = BinaryOp::GT;
        if (context->GTE()) ret.op = BinaryOp::GTE;
        if (context->LOR()) ret.op = BinaryOp::OR;
        if (context->LAND()) ret.op = BinaryOp::AND;
        val_ = std::move(ret);
    }
    return {};
}
antlrcpp::Any ASTBuilder::visitFunc_call(SysYFParser::Func_callContext *context) {
    FuncCallExpr ret;
    visit(context->ident());
    ret.func_name = std::move(*val_.as<std::string>());
    for (auto *rparam : context->exp()) {
        visit(rparam);
        ret.params.emplace_back(std::move(*val_.as<Expr>()));
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitLval(SysYFParser::LvalContext *context) {
    visit(context->ident());
    LVal ret{std::move(*val_.as<std::string>()), std::nullopt};
    if (context->exp()) {
        visit(context->exp());
        ret.array_idx = std::move(*val_.as<Expr>());
    }
    val_ = std::move(ret);
    return {};
}
antlrcpp::Any ASTBuilder::visitNumber(SysYFParser::NumberContext *context) {
    if (context->INT()) {
        auto str = context->INT()->getText();
        if (str[0] == '0') {
            if (str[1] == 'x' || str[1] == 'X')
                val_ = static_cast<int>(std::stol(str, nullptr, 16));
            else
                val_ = static_cast<int>(std::stol(str, nullptr, 8));
        } else {
            val_ = static_cast<int>(std::stol(str));
        }
    } else if (context->FLOAT()) {
        auto str = context->FLOAT()->getText();
        val_ = std::stof(str);
    }
    return {};
}
antlrcpp::Any ASTBuilder::visitIdent(SysYFParser::IdentContext *context) {
    val_ = context->NAME()->getText();
    return {};
}
}  // namespace ast
}  // namespace sysyf
