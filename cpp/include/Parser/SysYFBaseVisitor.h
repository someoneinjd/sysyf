
// Generated from SysYF.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SysYFVisitor.h"


/**
 * This class provides an empty implementation of SysYFVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SysYFBaseVisitor : public SysYFVisitor {
public:

  virtual std::any visitComp_unit(SysYFParser::Comp_unitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal_def(SysYFParser::Global_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConst_decl(SysYFParser::Const_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBtype(SysYFParser::BtypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConst_def(SysYFParser::Const_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConst_init_val(SysYFParser::Const_init_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar_decl(SysYFParser::Var_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar_def(SysYFParser::Var_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInit_val(SysYFParser::Init_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_def(SysYFParser::Func_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_fparam(SysYFParser::Func_fparamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(SysYFParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock_item(SysYFParser::Block_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(SysYFParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_stmt(SysYFParser::Assign_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmpty_stmt(SysYFParser::Empty_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExp_stmt(SysYFParser::Exp_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_stmt(SysYFParser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile_stmt(SysYFParser::While_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreak_stmt(SysYFParser::Break_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinue_stmt(SysYFParser::Continue_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn_stmt(SysYFParser::Return_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCond_exp(SysYFParser::Cond_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExp(SysYFParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_call(SysYFParser::Func_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLval(SysYFParser::LvalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdent(SysYFParser::IdentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(SysYFParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }


};

