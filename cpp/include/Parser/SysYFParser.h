
// Generated from SysYF.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  SysYFParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    VOID_T = 15, INT_T = 16, FLOAT_T = 17, PLUS = 18, MINUS = 19, MUL = 20, 
    DIV = 21, MOD = 22, LOR = 23, LAND = 24, EQ = 25, NEQ = 26, LT = 27, 
    LTE = 28, GT = 29, GTE = 30, NOT = 31, LBRACKET = 32, RBRACKET = 33, 
    NAME = 34, INT = 35, FLOAT = 36, C_COMMENT = 37, CPP_COMMENT = 38, WS = 39
  };

  enum {
    RuleComp_unit = 0, RuleGlobal_def = 1, RuleConst_decl = 2, RuleBtype = 3, 
    RuleConst_def = 4, RuleConst_init_val = 5, RuleVar_decl = 6, RuleVar_def = 7, 
    RuleInit_val = 8, RuleFunc_def = 9, RuleFunc_fparam = 10, RuleBlock = 11, 
    RuleBlock_item = 12, RuleStmt = 13, RuleAssign_stmt = 14, RuleEmpty_stmt = 15, 
    RuleExp_stmt = 16, RuleIf_stmt = 17, RuleWhile_stmt = 18, RuleBreak_stmt = 19, 
    RuleContinue_stmt = 20, RuleReturn_stmt = 21, RuleCond_exp = 22, RuleExp = 23, 
    RuleFunc_call = 24, RuleLval = 25, RuleIdent = 26, RuleNumber = 27
  };

  explicit SysYFParser(antlr4::TokenStream *input);

  SysYFParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SysYFParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class Comp_unitContext;
  class Global_defContext;
  class Const_declContext;
  class BtypeContext;
  class Const_defContext;
  class Const_init_valContext;
  class Var_declContext;
  class Var_defContext;
  class Init_valContext;
  class Func_defContext;
  class Func_fparamContext;
  class BlockContext;
  class Block_itemContext;
  class StmtContext;
  class Assign_stmtContext;
  class Empty_stmtContext;
  class Exp_stmtContext;
  class If_stmtContext;
  class While_stmtContext;
  class Break_stmtContext;
  class Continue_stmtContext;
  class Return_stmtContext;
  class Cond_expContext;
  class ExpContext;
  class Func_callContext;
  class LvalContext;
  class IdentContext;
  class NumberContext; 

  class  Comp_unitContext : public antlr4::ParserRuleContext {
  public:
    Comp_unitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Global_defContext *> global_def();
    Global_defContext* global_def(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Comp_unitContext* comp_unit();

  class  Global_defContext : public antlr4::ParserRuleContext {
  public:
    Global_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_declContext *const_decl();
    Var_declContext *var_decl();
    Func_defContext *func_def();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_defContext* global_def();

  class  Const_declContext : public antlr4::ParserRuleContext {
  public:
    Const_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BtypeContext *btype();
    std::vector<Const_defContext *> const_def();
    Const_defContext* const_def(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_declContext* const_decl();

  class  BtypeContext : public antlr4::ParserRuleContext {
  public:
    BtypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_T();
    antlr4::tree::TerminalNode *FLOAT_T();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BtypeContext* btype();

  class  Const_defContext : public antlr4::ParserRuleContext {
  public:
    Const_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    Const_init_valContext *const_init_val();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_defContext* const_def();

  class  Const_init_valContext : public antlr4::ParserRuleContext {
  public:
    Const_init_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_init_valContext* const_init_val();

  class  Var_declContext : public antlr4::ParserRuleContext {
  public:
    Var_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BtypeContext *btype();
    std::vector<Var_defContext *> var_def();
    Var_defContext* var_def(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Var_declContext* var_decl();

  class  Var_defContext : public antlr4::ParserRuleContext {
  public:
    Var_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    Init_valContext *init_val();
    antlr4::tree::TerminalNode *INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Var_defContext* var_def();

  class  Init_valContext : public antlr4::ParserRuleContext {
  public:
    Init_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Init_valContext* init_val();

  class  Func_defContext : public antlr4::ParserRuleContext {
  public:
    Func_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BtypeContext *btype();
    IdentContext *ident();
    BlockContext *block();
    std::vector<Func_fparamContext *> func_fparam();
    Func_fparamContext* func_fparam(size_t i);
    antlr4::tree::TerminalNode *VOID_T();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_defContext* func_def();

  class  Func_fparamContext : public antlr4::ParserRuleContext {
  public:
    Func_fparamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BtypeContext *btype();
    IdentContext *ident();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_fparamContext* func_fparam();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Block_itemContext *> block_item();
    Block_itemContext* block_item(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  Block_itemContext : public antlr4::ParserRuleContext {
  public:
    Block_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_declContext *const_decl();
    Var_declContext *var_decl();
    StmtContext *stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Block_itemContext* block_item();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Assign_stmtContext *assign_stmt();
    Empty_stmtContext *empty_stmt();
    Exp_stmtContext *exp_stmt();
    BlockContext *block();
    If_stmtContext *if_stmt();
    While_stmtContext *while_stmt();
    Break_stmtContext *break_stmt();
    Continue_stmtContext *continue_stmt();
    Return_stmtContext *return_stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmtContext* stmt();

  class  Assign_stmtContext : public antlr4::ParserRuleContext {
  public:
    Assign_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LvalContext *lval();
    ExpContext *exp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_stmtContext* assign_stmt();

  class  Empty_stmtContext : public antlr4::ParserRuleContext {
  public:
    Empty_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Empty_stmtContext* empty_stmt();

  class  Exp_stmtContext : public antlr4::ParserRuleContext {
  public:
    Exp_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Exp_stmtContext* exp_stmt();

  class  If_stmtContext : public antlr4::ParserRuleContext {
  public:
    If_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Cond_expContext *cond_exp();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_stmtContext* if_stmt();

  class  While_stmtContext : public antlr4::ParserRuleContext {
  public:
    While_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Cond_expContext *cond_exp();
    StmtContext *stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  While_stmtContext* while_stmt();

  class  Break_stmtContext : public antlr4::ParserRuleContext {
  public:
    Break_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Break_stmtContext* break_stmt();

  class  Continue_stmtContext : public antlr4::ParserRuleContext {
  public:
    Continue_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Continue_stmtContext* continue_stmt();

  class  Return_stmtContext : public antlr4::ParserRuleContext {
  public:
    Return_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Return_stmtContext* return_stmt();

  class  Cond_expContext : public antlr4::ParserRuleContext {
  public:
    Cond_expContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();
    std::vector<Cond_expContext *> cond_exp();
    Cond_expContext* cond_exp(size_t i);
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LTE();
    antlr4::tree::TerminalNode *GTE();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *LAND();
    antlr4::tree::TerminalNode *LOR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cond_expContext* cond_exp();
  Cond_expContext* cond_exp(int precedence);
  class  ExpContext : public antlr4::ParserRuleContext {
  public:
    ExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *NOT();
    LvalContext *lval();
    NumberContext *number();
    Func_callContext *func_call();
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpContext* exp();
  ExpContext* exp(int precedence);
  class  Func_callContext : public antlr4::ParserRuleContext {
  public:
    Func_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    std::vector<ExpContext *> exp();
    ExpContext* exp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Func_callContext* func_call();

  class  LvalContext : public antlr4::ParserRuleContext {
  public:
    LvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentContext *ident();
    antlr4::tree::TerminalNode *LBRACKET();
    ExpContext *exp();
    antlr4::tree::TerminalNode *RBRACKET();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LvalContext* lval();

  class  IdentContext : public antlr4::ParserRuleContext {
  public:
    IdentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentContext* ident();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *FLOAT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumberContext* number();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool cond_expSempred(Cond_expContext *_localctx, size_t predicateIndex);
  bool expSempred(ExpContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

