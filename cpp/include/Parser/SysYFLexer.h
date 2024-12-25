
// Generated from SysYF.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  SysYFLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    VOID_T = 15, INT_T = 16, FLOAT_T = 17, PLUS = 18, MINUS = 19, MUL = 20, 
    DIV = 21, MOD = 22, LOR = 23, LAND = 24, EQ = 25, NEQ = 26, LT = 27, 
    LTE = 28, GT = 29, GTE = 30, NOT = 31, LBRACKET = 32, RBRACKET = 33, 
    NAME = 34, INT = 35, FLOAT = 36, C_COMMENT = 37, CPP_COMMENT = 38, WS = 39
  };

  explicit SysYFLexer(antlr4::CharStream *input);

  ~SysYFLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

