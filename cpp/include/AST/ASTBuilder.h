#pragma once

#include "AST.h"
#include "Any.h"
#include "SysYFBaseVisitor.h"

namespace sysyf {
namespace ast {

class ASTBuilder : public SysYFBaseVisitor {
    Union<Assembly, GlobalDef, Expr, Stmt, Vec<VarDefStmt>, Type, std::string, FuncParam> val_;

  public:
    antlrcpp::Any visitComp_unit(SysYFParser::Comp_unitContext *context) final;
    antlrcpp::Any visitGlobal_def(SysYFParser::Global_defContext *context) final;
    antlrcpp::Any visitConst_decl(SysYFParser::Const_declContext *context) final;
    antlrcpp::Any visitBtype(SysYFParser::BtypeContext *context) final;
    antlrcpp::Any visitConst_def(SysYFParser::Const_defContext *context) final;
    antlrcpp::Any visitConst_init_val(SysYFParser::Const_init_valContext *context) final;
    antlrcpp::Any visitVar_decl(SysYFParser::Var_declContext *context) final;
    antlrcpp::Any visitVar_def(SysYFParser::Var_defContext *context) final;
    antlrcpp::Any visitInit_val(SysYFParser::Init_valContext *context) final;
    antlrcpp::Any visitFunc_def(SysYFParser::Func_defContext *context) final;
    antlrcpp::Any visitFunc_fparam(SysYFParser::Func_fparamContext *context) final;
    antlrcpp::Any visitBlock(SysYFParser::BlockContext *context) final;
    antlrcpp::Any visitBlock_item(SysYFParser::Block_itemContext *context) final;
    antlrcpp::Any visitStmt(SysYFParser::StmtContext *context) final;
    antlrcpp::Any visitAssign_stmt(SysYFParser::Assign_stmtContext *context) final;
    antlrcpp::Any visitEmpty_stmt(SysYFParser::Empty_stmtContext *context) final;
    antlrcpp::Any visitExp_stmt(SysYFParser::Exp_stmtContext *context) final;
    antlrcpp::Any visitIf_stmt(SysYFParser::If_stmtContext *context) final;
    antlrcpp::Any visitWhile_stmt(SysYFParser::While_stmtContext *context) final;
    antlrcpp::Any visitBreak_stmt(SysYFParser::Break_stmtContext *context) final;
    antlrcpp::Any visitContinue_stmt(SysYFParser::Continue_stmtContext *context) final;
    antlrcpp::Any visitReturn_stmt(SysYFParser::Return_stmtContext *context) final;
    antlrcpp::Any visitExp(SysYFParser::ExpContext *context) final;
    antlrcpp::Any visitCond_exp(SysYFParser::Cond_expContext *ctx) final;
    antlrcpp::Any visitFunc_call(SysYFParser::Func_callContext *context) final;
    antlrcpp::Any visitLval(SysYFParser::LvalContext *context) final;
    antlrcpp::Any visitNumber(SysYFParser::NumberContext *context) final;
    antlrcpp::Any visitIdent(SysYFParser::IdentContext *context) final;
    Assembly build(antlr4::tree::ParseTree *ctx) {
        visit(ctx);
        return *val_.as<Assembly>();
    }
};
}  // namespace ast
}  // namespace sysyf
