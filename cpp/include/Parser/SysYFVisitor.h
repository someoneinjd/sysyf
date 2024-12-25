
// Generated from SysYF.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SysYFParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SysYFParser.
 */
class  SysYFVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SysYFParser.
   */
    virtual std::any visitComp_unit(SysYFParser::Comp_unitContext *context) = 0;

    virtual std::any visitGlobal_def(SysYFParser::Global_defContext *context) = 0;

    virtual std::any visitConst_decl(SysYFParser::Const_declContext *context) = 0;

    virtual std::any visitBtype(SysYFParser::BtypeContext *context) = 0;

    virtual std::any visitConst_def(SysYFParser::Const_defContext *context) = 0;

    virtual std::any visitConst_init_val(SysYFParser::Const_init_valContext *context) = 0;

    virtual std::any visitVar_decl(SysYFParser::Var_declContext *context) = 0;

    virtual std::any visitVar_def(SysYFParser::Var_defContext *context) = 0;

    virtual std::any visitInit_val(SysYFParser::Init_valContext *context) = 0;

    virtual std::any visitFunc_def(SysYFParser::Func_defContext *context) = 0;

    virtual std::any visitFunc_fparam(SysYFParser::Func_fparamContext *context) = 0;

    virtual std::any visitBlock(SysYFParser::BlockContext *context) = 0;

    virtual std::any visitBlock_item(SysYFParser::Block_itemContext *context) = 0;

    virtual std::any visitStmt(SysYFParser::StmtContext *context) = 0;

    virtual std::any visitAssign_stmt(SysYFParser::Assign_stmtContext *context) = 0;

    virtual std::any visitEmpty_stmt(SysYFParser::Empty_stmtContext *context) = 0;

    virtual std::any visitExp_stmt(SysYFParser::Exp_stmtContext *context) = 0;

    virtual std::any visitIf_stmt(SysYFParser::If_stmtContext *context) = 0;

    virtual std::any visitWhile_stmt(SysYFParser::While_stmtContext *context) = 0;

    virtual std::any visitBreak_stmt(SysYFParser::Break_stmtContext *context) = 0;

    virtual std::any visitContinue_stmt(SysYFParser::Continue_stmtContext *context) = 0;

    virtual std::any visitReturn_stmt(SysYFParser::Return_stmtContext *context) = 0;

    virtual std::any visitCond_exp(SysYFParser::Cond_expContext *context) = 0;

    virtual std::any visitExp(SysYFParser::ExpContext *context) = 0;

    virtual std::any visitFunc_call(SysYFParser::Func_callContext *context) = 0;

    virtual std::any visitLval(SysYFParser::LvalContext *context) = 0;

    virtual std::any visitIdent(SysYFParser::IdentContext *context) = 0;

    virtual std::any visitNumber(SysYFParser::NumberContext *context) = 0;


};

