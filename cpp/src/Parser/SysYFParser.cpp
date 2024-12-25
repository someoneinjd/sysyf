
// Generated from SysYF.g4 by ANTLR 4.13.2


#include "SysYFVisitor.h"

#include "SysYFParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SysYFParserStaticData final {
  SysYFParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SysYFParserStaticData(const SysYFParserStaticData&) = delete;
  SysYFParserStaticData(SysYFParserStaticData&&) = delete;
  SysYFParserStaticData& operator=(const SysYFParserStaticData&) = delete;
  SysYFParserStaticData& operator=(SysYFParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysyfParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<SysYFParserStaticData> sysyfParserStaticData = nullptr;

void sysyfParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sysyfParserStaticData != nullptr) {
    return;
  }
#else
  assert(sysyfParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SysYFParserStaticData>(
    std::vector<std::string>{
      "comp_unit", "global_def", "const_decl", "btype", "const_def", "const_init_val", 
      "var_decl", "var_def", "init_val", "func_def", "func_fparam", "block", 
      "block_item", "stmt", "assign_stmt", "empty_stmt", "exp_stmt", "if_stmt", 
      "while_stmt", "break_stmt", "continue_stmt", "return_stmt", "cond_exp", 
      "exp", "func_call", "lval", "ident", "number"
    },
    std::vector<std::string>{
      "", "'const'", "','", "';'", "'='", "'{'", "'}'", "'('", "')'", "'if'", 
      "'else'", "'while'", "'break'", "'continue'", "'return'", "'void'", 
      "'int'", "'float'", "'+'", "'-'", "'*'", "'/'", "'%'", "'||'", "'&&'", 
      "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", "'!'", "'['", "']'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "VOID_T", 
      "INT_T", "FLOAT_T", "PLUS", "MINUS", "MUL", "DIV", "MOD", "LOR", "LAND", 
      "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "NOT", "LBRACKET", "RBRACKET", 
      "NAME", "INT", "FLOAT", "C_COMMENT", "CPP_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,319,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,4,
  	0,58,8,0,11,0,12,0,59,1,0,1,0,1,1,1,1,1,1,3,1,67,8,1,1,2,1,2,1,2,1,2,
  	1,2,5,2,74,8,2,10,2,12,2,77,9,2,1,2,1,2,1,3,1,3,1,4,1,4,1,4,3,4,86,8,
  	4,1,4,3,4,89,8,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,101,8,5,
  	10,5,12,5,104,9,5,1,5,1,5,3,5,108,8,5,1,6,1,6,1,6,1,6,5,6,114,8,6,10,
  	6,12,6,117,9,6,1,6,1,6,1,7,1,7,1,7,3,7,124,8,7,1,7,3,7,127,8,7,1,7,1,
  	7,3,7,131,8,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,140,8,8,10,8,12,8,143,9,
  	8,1,8,1,8,3,8,147,8,8,1,9,1,9,1,9,1,9,1,9,1,9,5,9,155,8,9,10,9,12,9,158,
  	9,9,3,9,160,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,171,8,9,10,9,
  	12,9,174,9,9,3,9,176,8,9,1,9,1,9,1,9,3,9,181,8,9,1,10,1,10,1,10,1,10,
  	3,10,187,8,10,1,11,1,11,5,11,191,8,11,10,11,12,11,194,9,11,1,11,1,11,
  	1,12,1,12,1,12,3,12,201,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,3,13,212,8,13,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,16,1,16,1,16,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,231,8,17,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,3,21,247,8,21,1,21,
  	1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,5,22,266,8,22,10,22,12,22,269,9,22,1,23,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,3,23,281,8,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	5,23,289,8,23,10,23,12,23,292,9,23,1,24,1,24,1,24,1,24,1,24,5,24,299,
  	8,24,10,24,12,24,302,9,24,3,24,304,8,24,1,24,1,24,1,25,1,25,1,25,1,25,
  	1,25,3,25,313,8,25,1,26,1,26,1,27,1,27,1,27,0,2,44,46,28,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,0,7,
  	1,0,16,17,1,0,27,30,1,0,25,26,2,0,18,19,31,31,1,0,20,22,1,0,18,19,1,0,
  	35,36,338,0,57,1,0,0,0,2,66,1,0,0,0,4,68,1,0,0,0,6,80,1,0,0,0,8,82,1,
  	0,0,0,10,107,1,0,0,0,12,109,1,0,0,0,14,120,1,0,0,0,16,146,1,0,0,0,18,
  	180,1,0,0,0,20,182,1,0,0,0,22,188,1,0,0,0,24,200,1,0,0,0,26,211,1,0,0,
  	0,28,213,1,0,0,0,30,218,1,0,0,0,32,220,1,0,0,0,34,223,1,0,0,0,36,232,
  	1,0,0,0,38,238,1,0,0,0,40,241,1,0,0,0,42,244,1,0,0,0,44,250,1,0,0,0,46,
  	280,1,0,0,0,48,293,1,0,0,0,50,307,1,0,0,0,52,314,1,0,0,0,54,316,1,0,0,
  	0,56,58,3,2,1,0,57,56,1,0,0,0,58,59,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,
  	0,60,61,1,0,0,0,61,62,5,0,0,1,62,1,1,0,0,0,63,67,3,4,2,0,64,67,3,12,6,
  	0,65,67,3,18,9,0,66,63,1,0,0,0,66,64,1,0,0,0,66,65,1,0,0,0,67,3,1,0,0,
  	0,68,69,5,1,0,0,69,70,3,6,3,0,70,75,3,8,4,0,71,72,5,2,0,0,72,74,3,8,4,
  	0,73,71,1,0,0,0,74,77,1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,76,78,1,0,0,
  	0,77,75,1,0,0,0,78,79,5,3,0,0,79,5,1,0,0,0,80,81,7,0,0,0,81,7,1,0,0,0,
  	82,88,3,52,26,0,83,85,5,32,0,0,84,86,5,35,0,0,85,84,1,0,0,0,85,86,1,0,
  	0,0,86,87,1,0,0,0,87,89,5,33,0,0,88,83,1,0,0,0,88,89,1,0,0,0,89,90,1,
  	0,0,0,90,91,5,4,0,0,91,92,3,10,5,0,92,9,1,0,0,0,93,108,3,46,23,0,94,95,
  	5,5,0,0,95,108,5,6,0,0,96,97,5,5,0,0,97,102,3,46,23,0,98,99,5,2,0,0,99,
  	101,3,46,23,0,100,98,1,0,0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,
  	1,0,0,0,103,105,1,0,0,0,104,102,1,0,0,0,105,106,5,6,0,0,106,108,1,0,0,
  	0,107,93,1,0,0,0,107,94,1,0,0,0,107,96,1,0,0,0,108,11,1,0,0,0,109,110,
  	3,6,3,0,110,115,3,14,7,0,111,112,5,2,0,0,112,114,3,14,7,0,113,111,1,0,
  	0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,116,1,0,0,0,116,118,1,0,0,0,117,
  	115,1,0,0,0,118,119,5,3,0,0,119,13,1,0,0,0,120,126,3,52,26,0,121,123,
  	5,32,0,0,122,124,5,35,0,0,123,122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,
  	0,0,125,127,5,33,0,0,126,121,1,0,0,0,126,127,1,0,0,0,127,130,1,0,0,0,
  	128,129,5,4,0,0,129,131,3,16,8,0,130,128,1,0,0,0,130,131,1,0,0,0,131,
  	15,1,0,0,0,132,147,3,46,23,0,133,134,5,5,0,0,134,147,5,6,0,0,135,136,
  	5,5,0,0,136,141,3,46,23,0,137,138,5,2,0,0,138,140,3,46,23,0,139,137,1,
  	0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,0,142,144,1,0,0,0,
  	143,141,1,0,0,0,144,145,5,6,0,0,145,147,1,0,0,0,146,132,1,0,0,0,146,133,
  	1,0,0,0,146,135,1,0,0,0,147,17,1,0,0,0,148,149,3,6,3,0,149,150,3,52,26,
  	0,150,159,5,7,0,0,151,156,3,20,10,0,152,153,5,2,0,0,153,155,3,20,10,0,
  	154,152,1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,156,157,1,0,0,0,157,160,
  	1,0,0,0,158,156,1,0,0,0,159,151,1,0,0,0,159,160,1,0,0,0,160,161,1,0,0,
  	0,161,162,5,8,0,0,162,163,3,22,11,0,163,181,1,0,0,0,164,165,5,15,0,0,
  	165,166,3,52,26,0,166,175,5,7,0,0,167,172,3,20,10,0,168,169,5,2,0,0,169,
  	171,3,20,10,0,170,168,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,172,173,
  	1,0,0,0,173,176,1,0,0,0,174,172,1,0,0,0,175,167,1,0,0,0,175,176,1,0,0,
  	0,176,177,1,0,0,0,177,178,5,8,0,0,178,179,3,22,11,0,179,181,1,0,0,0,180,
  	148,1,0,0,0,180,164,1,0,0,0,181,19,1,0,0,0,182,183,3,6,3,0,183,186,3,
  	52,26,0,184,185,5,32,0,0,185,187,5,33,0,0,186,184,1,0,0,0,186,187,1,0,
  	0,0,187,21,1,0,0,0,188,192,5,5,0,0,189,191,3,24,12,0,190,189,1,0,0,0,
  	191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,195,1,0,0,0,194,192,
  	1,0,0,0,195,196,5,6,0,0,196,23,1,0,0,0,197,201,3,4,2,0,198,201,3,12,6,
  	0,199,201,3,26,13,0,200,197,1,0,0,0,200,198,1,0,0,0,200,199,1,0,0,0,201,
  	25,1,0,0,0,202,212,3,28,14,0,203,212,3,30,15,0,204,212,3,32,16,0,205,
  	212,3,22,11,0,206,212,3,34,17,0,207,212,3,36,18,0,208,212,3,38,19,0,209,
  	212,3,40,20,0,210,212,3,42,21,0,211,202,1,0,0,0,211,203,1,0,0,0,211,204,
  	1,0,0,0,211,205,1,0,0,0,211,206,1,0,0,0,211,207,1,0,0,0,211,208,1,0,0,
  	0,211,209,1,0,0,0,211,210,1,0,0,0,212,27,1,0,0,0,213,214,3,50,25,0,214,
  	215,5,4,0,0,215,216,3,46,23,0,216,217,5,3,0,0,217,29,1,0,0,0,218,219,
  	5,3,0,0,219,31,1,0,0,0,220,221,3,46,23,0,221,222,5,3,0,0,222,33,1,0,0,
  	0,223,224,5,9,0,0,224,225,5,7,0,0,225,226,3,44,22,0,226,227,5,8,0,0,227,
  	230,3,26,13,0,228,229,5,10,0,0,229,231,3,26,13,0,230,228,1,0,0,0,230,
  	231,1,0,0,0,231,35,1,0,0,0,232,233,5,11,0,0,233,234,5,7,0,0,234,235,3,
  	44,22,0,235,236,5,8,0,0,236,237,3,26,13,0,237,37,1,0,0,0,238,239,5,12,
  	0,0,239,240,5,3,0,0,240,39,1,0,0,0,241,242,5,13,0,0,242,243,5,3,0,0,243,
  	41,1,0,0,0,244,246,5,14,0,0,245,247,3,46,23,0,246,245,1,0,0,0,246,247,
  	1,0,0,0,247,248,1,0,0,0,248,249,5,3,0,0,249,43,1,0,0,0,250,251,6,22,-1,
  	0,251,252,3,46,23,0,252,267,1,0,0,0,253,254,10,4,0,0,254,255,7,1,0,0,
  	255,266,3,44,22,5,256,257,10,3,0,0,257,258,7,2,0,0,258,266,3,44,22,4,
  	259,260,10,2,0,0,260,261,5,24,0,0,261,266,3,44,22,3,262,263,10,1,0,0,
  	263,264,5,23,0,0,264,266,3,44,22,2,265,253,1,0,0,0,265,256,1,0,0,0,265,
  	259,1,0,0,0,265,262,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,
  	0,0,0,268,45,1,0,0,0,269,267,1,0,0,0,270,271,6,23,-1,0,271,272,7,3,0,
  	0,272,281,3,46,23,7,273,281,3,50,25,0,274,281,3,54,27,0,275,281,3,48,
  	24,0,276,277,5,7,0,0,277,278,3,46,23,0,278,279,5,8,0,0,279,281,1,0,0,
  	0,280,270,1,0,0,0,280,273,1,0,0,0,280,274,1,0,0,0,280,275,1,0,0,0,280,
  	276,1,0,0,0,281,290,1,0,0,0,282,283,10,2,0,0,283,284,7,4,0,0,284,289,
  	3,46,23,3,285,286,10,1,0,0,286,287,7,5,0,0,287,289,3,46,23,2,288,282,
  	1,0,0,0,288,285,1,0,0,0,289,292,1,0,0,0,290,288,1,0,0,0,290,291,1,0,0,
  	0,291,47,1,0,0,0,292,290,1,0,0,0,293,294,3,52,26,0,294,303,5,7,0,0,295,
  	300,3,46,23,0,296,297,5,2,0,0,297,299,3,46,23,0,298,296,1,0,0,0,299,302,
  	1,0,0,0,300,298,1,0,0,0,300,301,1,0,0,0,301,304,1,0,0,0,302,300,1,0,0,
  	0,303,295,1,0,0,0,303,304,1,0,0,0,304,305,1,0,0,0,305,306,5,8,0,0,306,
  	49,1,0,0,0,307,312,3,52,26,0,308,309,5,32,0,0,309,310,3,46,23,0,310,311,
  	5,33,0,0,311,313,1,0,0,0,312,308,1,0,0,0,312,313,1,0,0,0,313,51,1,0,0,
  	0,314,315,5,34,0,0,315,53,1,0,0,0,316,317,7,6,0,0,317,55,1,0,0,0,32,59,
  	66,75,85,88,102,107,115,123,126,130,141,146,156,159,172,175,180,186,192,
  	200,211,230,246,265,267,280,288,290,300,303,312
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysyfParserStaticData = std::move(staticData);
}

}

SysYFParser::SysYFParser(TokenStream *input) : SysYFParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SysYFParser::SysYFParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SysYFParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sysyfParserStaticData->atn, sysyfParserStaticData->decisionToDFA, sysyfParserStaticData->sharedContextCache, options);
}

SysYFParser::~SysYFParser() {
  delete _interpreter;
}

const atn::ATN& SysYFParser::getATN() const {
  return *sysyfParserStaticData->atn;
}

std::string SysYFParser::getGrammarFileName() const {
  return "SysYF.g4";
}

const std::vector<std::string>& SysYFParser::getRuleNames() const {
  return sysyfParserStaticData->ruleNames;
}

const dfa::Vocabulary& SysYFParser::getVocabulary() const {
  return sysyfParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysYFParser::getSerializedATN() const {
  return sysyfParserStaticData->serializedATN;
}


//----------------- Comp_unitContext ------------------------------------------------------------------

SysYFParser::Comp_unitContext::Comp_unitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYFParser::Comp_unitContext::EOF() {
  return getToken(SysYFParser::EOF, 0);
}

std::vector<SysYFParser::Global_defContext *> SysYFParser::Comp_unitContext::global_def() {
  return getRuleContexts<SysYFParser::Global_defContext>();
}

SysYFParser::Global_defContext* SysYFParser::Comp_unitContext::global_def(size_t i) {
  return getRuleContext<SysYFParser::Global_defContext>(i);
}


size_t SysYFParser::Comp_unitContext::getRuleIndex() const {
  return SysYFParser::RuleComp_unit;
}


std::any SysYFParser::Comp_unitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitComp_unit(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Comp_unitContext* SysYFParser::comp_unit() {
  Comp_unitContext *_localctx = _tracker.createInstance<Comp_unitContext>(_ctx, getState());
  enterRule(_localctx, 0, SysYFParser::RuleComp_unit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(56);
      global_def();
      setState(59); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 229378) != 0));
    setState(61);
    match(SysYFParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_defContext ------------------------------------------------------------------

SysYFParser::Global_defContext::Global_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::Const_declContext* SysYFParser::Global_defContext::const_decl() {
  return getRuleContext<SysYFParser::Const_declContext>(0);
}

SysYFParser::Var_declContext* SysYFParser::Global_defContext::var_decl() {
  return getRuleContext<SysYFParser::Var_declContext>(0);
}

SysYFParser::Func_defContext* SysYFParser::Global_defContext::func_def() {
  return getRuleContext<SysYFParser::Func_defContext>(0);
}


size_t SysYFParser::Global_defContext::getRuleIndex() const {
  return SysYFParser::RuleGlobal_def;
}


std::any SysYFParser::Global_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitGlobal_def(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Global_defContext* SysYFParser::global_def() {
  Global_defContext *_localctx = _tracker.createInstance<Global_defContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYFParser::RuleGlobal_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(66);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(63);
      const_decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(64);
      var_decl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(65);
      func_def();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_declContext ------------------------------------------------------------------

SysYFParser::Const_declContext::Const_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::BtypeContext* SysYFParser::Const_declContext::btype() {
  return getRuleContext<SysYFParser::BtypeContext>(0);
}

std::vector<SysYFParser::Const_defContext *> SysYFParser::Const_declContext::const_def() {
  return getRuleContexts<SysYFParser::Const_defContext>();
}

SysYFParser::Const_defContext* SysYFParser::Const_declContext::const_def(size_t i) {
  return getRuleContext<SysYFParser::Const_defContext>(i);
}


size_t SysYFParser::Const_declContext::getRuleIndex() const {
  return SysYFParser::RuleConst_decl;
}


std::any SysYFParser::Const_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitConst_decl(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Const_declContext* SysYFParser::const_decl() {
  Const_declContext *_localctx = _tracker.createInstance<Const_declContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYFParser::RuleConst_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(SysYFParser::T__0);
    setState(69);
    btype();
    setState(70);
    const_def();
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYFParser::T__1) {
      setState(71);
      match(SysYFParser::T__1);
      setState(72);
      const_def();
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(78);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BtypeContext ------------------------------------------------------------------

SysYFParser::BtypeContext::BtypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYFParser::BtypeContext::INT_T() {
  return getToken(SysYFParser::INT_T, 0);
}

tree::TerminalNode* SysYFParser::BtypeContext::FLOAT_T() {
  return getToken(SysYFParser::FLOAT_T, 0);
}


size_t SysYFParser::BtypeContext::getRuleIndex() const {
  return SysYFParser::RuleBtype;
}


std::any SysYFParser::BtypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitBtype(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::BtypeContext* SysYFParser::btype() {
  BtypeContext *_localctx = _tracker.createInstance<BtypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYFParser::RuleBtype);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    _la = _input->LA(1);
    if (!(_la == SysYFParser::INT_T

    || _la == SysYFParser::FLOAT_T)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_defContext ------------------------------------------------------------------

SysYFParser::Const_defContext::Const_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::IdentContext* SysYFParser::Const_defContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

SysYFParser::Const_init_valContext* SysYFParser::Const_defContext::const_init_val() {
  return getRuleContext<SysYFParser::Const_init_valContext>(0);
}

tree::TerminalNode* SysYFParser::Const_defContext::LBRACKET() {
  return getToken(SysYFParser::LBRACKET, 0);
}

tree::TerminalNode* SysYFParser::Const_defContext::RBRACKET() {
  return getToken(SysYFParser::RBRACKET, 0);
}

tree::TerminalNode* SysYFParser::Const_defContext::INT() {
  return getToken(SysYFParser::INT, 0);
}


size_t SysYFParser::Const_defContext::getRuleIndex() const {
  return SysYFParser::RuleConst_def;
}


std::any SysYFParser::Const_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitConst_def(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Const_defContext* SysYFParser::const_def() {
  Const_defContext *_localctx = _tracker.createInstance<Const_defContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYFParser::RuleConst_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    ident();
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYFParser::LBRACKET) {
      setState(83);
      match(SysYFParser::LBRACKET);
      setState(85);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SysYFParser::INT) {
        setState(84);
        match(SysYFParser::INT);
      }
      setState(87);
      match(SysYFParser::RBRACKET);
    }
    setState(90);
    match(SysYFParser::T__3);
    setState(91);
    const_init_val();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Const_init_valContext ------------------------------------------------------------------

SysYFParser::Const_init_valContext::Const_init_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYFParser::ExpContext *> SysYFParser::Const_init_valContext::exp() {
  return getRuleContexts<SysYFParser::ExpContext>();
}

SysYFParser::ExpContext* SysYFParser::Const_init_valContext::exp(size_t i) {
  return getRuleContext<SysYFParser::ExpContext>(i);
}


size_t SysYFParser::Const_init_valContext::getRuleIndex() const {
  return SysYFParser::RuleConst_init_val;
}


std::any SysYFParser::Const_init_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitConst_init_val(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Const_init_valContext* SysYFParser::const_init_val() {
  Const_init_valContext *_localctx = _tracker.createInstance<Const_init_valContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYFParser::RuleConst_init_val);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(107);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(93);
      exp(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(94);
      match(SysYFParser::T__4);
      setState(95);
      match(SysYFParser::T__5);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(96);
      match(SysYFParser::T__4);
      setState(97);
      exp(0);
      setState(102);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYFParser::T__1) {
        setState(98);
        match(SysYFParser::T__1);
        setState(99);
        exp(0);
        setState(104);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(105);
      match(SysYFParser::T__5);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declContext ------------------------------------------------------------------

SysYFParser::Var_declContext::Var_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::BtypeContext* SysYFParser::Var_declContext::btype() {
  return getRuleContext<SysYFParser::BtypeContext>(0);
}

std::vector<SysYFParser::Var_defContext *> SysYFParser::Var_declContext::var_def() {
  return getRuleContexts<SysYFParser::Var_defContext>();
}

SysYFParser::Var_defContext* SysYFParser::Var_declContext::var_def(size_t i) {
  return getRuleContext<SysYFParser::Var_defContext>(i);
}


size_t SysYFParser::Var_declContext::getRuleIndex() const {
  return SysYFParser::RuleVar_decl;
}


std::any SysYFParser::Var_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitVar_decl(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Var_declContext* SysYFParser::var_decl() {
  Var_declContext *_localctx = _tracker.createInstance<Var_declContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYFParser::RuleVar_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    btype();
    setState(110);
    var_def();
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYFParser::T__1) {
      setState(111);
      match(SysYFParser::T__1);
      setState(112);
      var_def();
      setState(117);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(118);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_defContext ------------------------------------------------------------------

SysYFParser::Var_defContext::Var_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::IdentContext* SysYFParser::Var_defContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

tree::TerminalNode* SysYFParser::Var_defContext::LBRACKET() {
  return getToken(SysYFParser::LBRACKET, 0);
}

tree::TerminalNode* SysYFParser::Var_defContext::RBRACKET() {
  return getToken(SysYFParser::RBRACKET, 0);
}

SysYFParser::Init_valContext* SysYFParser::Var_defContext::init_val() {
  return getRuleContext<SysYFParser::Init_valContext>(0);
}

tree::TerminalNode* SysYFParser::Var_defContext::INT() {
  return getToken(SysYFParser::INT, 0);
}


size_t SysYFParser::Var_defContext::getRuleIndex() const {
  return SysYFParser::RuleVar_def;
}


std::any SysYFParser::Var_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitVar_def(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Var_defContext* SysYFParser::var_def() {
  Var_defContext *_localctx = _tracker.createInstance<Var_defContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYFParser::RuleVar_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    ident();
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYFParser::LBRACKET) {
      setState(121);
      match(SysYFParser::LBRACKET);
      setState(123);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SysYFParser::INT) {
        setState(122);
        match(SysYFParser::INT);
      }
      setState(125);
      match(SysYFParser::RBRACKET);
    }
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYFParser::T__3) {
      setState(128);
      match(SysYFParser::T__3);
      setState(129);
      init_val();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Init_valContext ------------------------------------------------------------------

SysYFParser::Init_valContext::Init_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYFParser::ExpContext *> SysYFParser::Init_valContext::exp() {
  return getRuleContexts<SysYFParser::ExpContext>();
}

SysYFParser::ExpContext* SysYFParser::Init_valContext::exp(size_t i) {
  return getRuleContext<SysYFParser::ExpContext>(i);
}


size_t SysYFParser::Init_valContext::getRuleIndex() const {
  return SysYFParser::RuleInit_val;
}


std::any SysYFParser::Init_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitInit_val(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Init_valContext* SysYFParser::init_val() {
  Init_valContext *_localctx = _tracker.createInstance<Init_valContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYFParser::RuleInit_val);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(132);
      exp(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(133);
      match(SysYFParser::T__4);
      setState(134);
      match(SysYFParser::T__5);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(135);
      match(SysYFParser::T__4);
      setState(136);
      exp(0);
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYFParser::T__1) {
        setState(137);
        match(SysYFParser::T__1);
        setState(138);
        exp(0);
        setState(143);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(144);
      match(SysYFParser::T__5);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_defContext ------------------------------------------------------------------

SysYFParser::Func_defContext::Func_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::BtypeContext* SysYFParser::Func_defContext::btype() {
  return getRuleContext<SysYFParser::BtypeContext>(0);
}

SysYFParser::IdentContext* SysYFParser::Func_defContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

SysYFParser::BlockContext* SysYFParser::Func_defContext::block() {
  return getRuleContext<SysYFParser::BlockContext>(0);
}

std::vector<SysYFParser::Func_fparamContext *> SysYFParser::Func_defContext::func_fparam() {
  return getRuleContexts<SysYFParser::Func_fparamContext>();
}

SysYFParser::Func_fparamContext* SysYFParser::Func_defContext::func_fparam(size_t i) {
  return getRuleContext<SysYFParser::Func_fparamContext>(i);
}

tree::TerminalNode* SysYFParser::Func_defContext::VOID_T() {
  return getToken(SysYFParser::VOID_T, 0);
}


size_t SysYFParser::Func_defContext::getRuleIndex() const {
  return SysYFParser::RuleFunc_def;
}


std::any SysYFParser::Func_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitFunc_def(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Func_defContext* SysYFParser::func_def() {
  Func_defContext *_localctx = _tracker.createInstance<Func_defContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYFParser::RuleFunc_def);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYFParser::INT_T:
      case SysYFParser::FLOAT_T: {
        enterOuterAlt(_localctx, 1);
        setState(148);
        btype();
        setState(149);
        ident();
        setState(150);
        match(SysYFParser::T__6);
        setState(159);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SysYFParser::INT_T

        || _la == SysYFParser::FLOAT_T) {
          setState(151);
          func_fparam();
          setState(156);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYFParser::T__1) {
            setState(152);
            match(SysYFParser::T__1);
            setState(153);
            func_fparam();
            setState(158);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(161);
        match(SysYFParser::T__7);
        setState(162);
        block();
        break;
      }

      case SysYFParser::VOID_T: {
        enterOuterAlt(_localctx, 2);
        setState(164);
        match(SysYFParser::VOID_T);
        setState(165);
        ident();
        setState(166);
        match(SysYFParser::T__6);
        setState(175);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SysYFParser::INT_T

        || _la == SysYFParser::FLOAT_T) {
          setState(167);
          func_fparam();
          setState(172);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYFParser::T__1) {
            setState(168);
            match(SysYFParser::T__1);
            setState(169);
            func_fparam();
            setState(174);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(177);
        match(SysYFParser::T__7);
        setState(178);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_fparamContext ------------------------------------------------------------------

SysYFParser::Func_fparamContext::Func_fparamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::BtypeContext* SysYFParser::Func_fparamContext::btype() {
  return getRuleContext<SysYFParser::BtypeContext>(0);
}

SysYFParser::IdentContext* SysYFParser::Func_fparamContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

tree::TerminalNode* SysYFParser::Func_fparamContext::LBRACKET() {
  return getToken(SysYFParser::LBRACKET, 0);
}

tree::TerminalNode* SysYFParser::Func_fparamContext::RBRACKET() {
  return getToken(SysYFParser::RBRACKET, 0);
}


size_t SysYFParser::Func_fparamContext::getRuleIndex() const {
  return SysYFParser::RuleFunc_fparam;
}


std::any SysYFParser::Func_fparamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitFunc_fparam(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Func_fparamContext* SysYFParser::func_fparam() {
  Func_fparamContext *_localctx = _tracker.createInstance<Func_fparamContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYFParser::RuleFunc_fparam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    btype();
    setState(183);
    ident();
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYFParser::LBRACKET) {
      setState(184);
      match(SysYFParser::LBRACKET);
      setState(185);
      match(SysYFParser::RBRACKET);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SysYFParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYFParser::Block_itemContext *> SysYFParser::BlockContext::block_item() {
  return getRuleContexts<SysYFParser::Block_itemContext>();
}

SysYFParser::Block_itemContext* SysYFParser::BlockContext::block_item(size_t i) {
  return getRuleContext<SysYFParser::Block_itemContext>(i);
}


size_t SysYFParser::BlockContext::getRuleIndex() const {
  return SysYFParser::RuleBlock;
}


std::any SysYFParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::BlockContext* SysYFParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 22, SysYFParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    match(SysYFParser::T__4);
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 122407582378) != 0)) {
      setState(189);
      block_item();
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(195);
    match(SysYFParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Block_itemContext ------------------------------------------------------------------

SysYFParser::Block_itemContext::Block_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::Const_declContext* SysYFParser::Block_itemContext::const_decl() {
  return getRuleContext<SysYFParser::Const_declContext>(0);
}

SysYFParser::Var_declContext* SysYFParser::Block_itemContext::var_decl() {
  return getRuleContext<SysYFParser::Var_declContext>(0);
}

SysYFParser::StmtContext* SysYFParser::Block_itemContext::stmt() {
  return getRuleContext<SysYFParser::StmtContext>(0);
}


size_t SysYFParser::Block_itemContext::getRuleIndex() const {
  return SysYFParser::RuleBlock_item;
}


std::any SysYFParser::Block_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitBlock_item(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Block_itemContext* SysYFParser::block_item() {
  Block_itemContext *_localctx = _tracker.createInstance<Block_itemContext>(_ctx, getState());
  enterRule(_localctx, 24, SysYFParser::RuleBlock_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(200);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYFParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(197);
        const_decl();
        break;
      }

      case SysYFParser::INT_T:
      case SysYFParser::FLOAT_T: {
        enterOuterAlt(_localctx, 2);
        setState(198);
        var_decl();
        break;
      }

      case SysYFParser::T__2:
      case SysYFParser::T__4:
      case SysYFParser::T__6:
      case SysYFParser::T__8:
      case SysYFParser::T__10:
      case SysYFParser::T__11:
      case SysYFParser::T__12:
      case SysYFParser::T__13:
      case SysYFParser::PLUS:
      case SysYFParser::MINUS:
      case SysYFParser::NOT:
      case SysYFParser::NAME:
      case SysYFParser::INT:
      case SysYFParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(199);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

SysYFParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::Assign_stmtContext* SysYFParser::StmtContext::assign_stmt() {
  return getRuleContext<SysYFParser::Assign_stmtContext>(0);
}

SysYFParser::Empty_stmtContext* SysYFParser::StmtContext::empty_stmt() {
  return getRuleContext<SysYFParser::Empty_stmtContext>(0);
}

SysYFParser::Exp_stmtContext* SysYFParser::StmtContext::exp_stmt() {
  return getRuleContext<SysYFParser::Exp_stmtContext>(0);
}

SysYFParser::BlockContext* SysYFParser::StmtContext::block() {
  return getRuleContext<SysYFParser::BlockContext>(0);
}

SysYFParser::If_stmtContext* SysYFParser::StmtContext::if_stmt() {
  return getRuleContext<SysYFParser::If_stmtContext>(0);
}

SysYFParser::While_stmtContext* SysYFParser::StmtContext::while_stmt() {
  return getRuleContext<SysYFParser::While_stmtContext>(0);
}

SysYFParser::Break_stmtContext* SysYFParser::StmtContext::break_stmt() {
  return getRuleContext<SysYFParser::Break_stmtContext>(0);
}

SysYFParser::Continue_stmtContext* SysYFParser::StmtContext::continue_stmt() {
  return getRuleContext<SysYFParser::Continue_stmtContext>(0);
}

SysYFParser::Return_stmtContext* SysYFParser::StmtContext::return_stmt() {
  return getRuleContext<SysYFParser::Return_stmtContext>(0);
}


size_t SysYFParser::StmtContext::getRuleIndex() const {
  return SysYFParser::RuleStmt;
}


std::any SysYFParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::StmtContext* SysYFParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 26, SysYFParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(211);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(202);
      assign_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(203);
      empty_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(204);
      exp_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(205);
      block();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(206);
      if_stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(207);
      while_stmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(208);
      break_stmt();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(209);
      continue_stmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(210);
      return_stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_stmtContext ------------------------------------------------------------------

SysYFParser::Assign_stmtContext::Assign_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::LvalContext* SysYFParser::Assign_stmtContext::lval() {
  return getRuleContext<SysYFParser::LvalContext>(0);
}

SysYFParser::ExpContext* SysYFParser::Assign_stmtContext::exp() {
  return getRuleContext<SysYFParser::ExpContext>(0);
}


size_t SysYFParser::Assign_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleAssign_stmt;
}


std::any SysYFParser::Assign_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitAssign_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Assign_stmtContext* SysYFParser::assign_stmt() {
  Assign_stmtContext *_localctx = _tracker.createInstance<Assign_stmtContext>(_ctx, getState());
  enterRule(_localctx, 28, SysYFParser::RuleAssign_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    lval();
    setState(214);
    match(SysYFParser::T__3);
    setState(215);
    exp(0);
    setState(216);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Empty_stmtContext ------------------------------------------------------------------

SysYFParser::Empty_stmtContext::Empty_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYFParser::Empty_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleEmpty_stmt;
}


std::any SysYFParser::Empty_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitEmpty_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Empty_stmtContext* SysYFParser::empty_stmt() {
  Empty_stmtContext *_localctx = _tracker.createInstance<Empty_stmtContext>(_ctx, getState());
  enterRule(_localctx, 30, SysYFParser::RuleEmpty_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Exp_stmtContext ------------------------------------------------------------------

SysYFParser::Exp_stmtContext::Exp_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::ExpContext* SysYFParser::Exp_stmtContext::exp() {
  return getRuleContext<SysYFParser::ExpContext>(0);
}


size_t SysYFParser::Exp_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleExp_stmt;
}


std::any SysYFParser::Exp_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitExp_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Exp_stmtContext* SysYFParser::exp_stmt() {
  Exp_stmtContext *_localctx = _tracker.createInstance<Exp_stmtContext>(_ctx, getState());
  enterRule(_localctx, 32, SysYFParser::RuleExp_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    exp(0);
    setState(221);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_stmtContext ------------------------------------------------------------------

SysYFParser::If_stmtContext::If_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::Cond_expContext* SysYFParser::If_stmtContext::cond_exp() {
  return getRuleContext<SysYFParser::Cond_expContext>(0);
}

std::vector<SysYFParser::StmtContext *> SysYFParser::If_stmtContext::stmt() {
  return getRuleContexts<SysYFParser::StmtContext>();
}

SysYFParser::StmtContext* SysYFParser::If_stmtContext::stmt(size_t i) {
  return getRuleContext<SysYFParser::StmtContext>(i);
}


size_t SysYFParser::If_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleIf_stmt;
}


std::any SysYFParser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::If_stmtContext* SysYFParser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 34, SysYFParser::RuleIf_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(SysYFParser::T__8);
    setState(224);
    match(SysYFParser::T__6);
    setState(225);
    cond_exp(0);
    setState(226);
    match(SysYFParser::T__7);
    setState(227);
    stmt();
    setState(230);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(228);
      match(SysYFParser::T__9);
      setState(229);
      stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_stmtContext ------------------------------------------------------------------

SysYFParser::While_stmtContext::While_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::Cond_expContext* SysYFParser::While_stmtContext::cond_exp() {
  return getRuleContext<SysYFParser::Cond_expContext>(0);
}

SysYFParser::StmtContext* SysYFParser::While_stmtContext::stmt() {
  return getRuleContext<SysYFParser::StmtContext>(0);
}


size_t SysYFParser::While_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleWhile_stmt;
}


std::any SysYFParser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::While_stmtContext* SysYFParser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 36, SysYFParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(SysYFParser::T__10);
    setState(233);
    match(SysYFParser::T__6);
    setState(234);
    cond_exp(0);
    setState(235);
    match(SysYFParser::T__7);
    setState(236);
    stmt();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Break_stmtContext ------------------------------------------------------------------

SysYFParser::Break_stmtContext::Break_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYFParser::Break_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleBreak_stmt;
}


std::any SysYFParser::Break_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitBreak_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Break_stmtContext* SysYFParser::break_stmt() {
  Break_stmtContext *_localctx = _tracker.createInstance<Break_stmtContext>(_ctx, getState());
  enterRule(_localctx, 38, SysYFParser::RuleBreak_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    match(SysYFParser::T__11);
    setState(239);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Continue_stmtContext ------------------------------------------------------------------

SysYFParser::Continue_stmtContext::Continue_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYFParser::Continue_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleContinue_stmt;
}


std::any SysYFParser::Continue_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitContinue_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Continue_stmtContext* SysYFParser::continue_stmt() {
  Continue_stmtContext *_localctx = _tracker.createInstance<Continue_stmtContext>(_ctx, getState());
  enterRule(_localctx, 40, SysYFParser::RuleContinue_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(SysYFParser::T__12);
    setState(242);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_stmtContext ------------------------------------------------------------------

SysYFParser::Return_stmtContext::Return_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::ExpContext* SysYFParser::Return_stmtContext::exp() {
  return getRuleContext<SysYFParser::ExpContext>(0);
}


size_t SysYFParser::Return_stmtContext::getRuleIndex() const {
  return SysYFParser::RuleReturn_stmt;
}


std::any SysYFParser::Return_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitReturn_stmt(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Return_stmtContext* SysYFParser::return_stmt() {
  Return_stmtContext *_localctx = _tracker.createInstance<Return_stmtContext>(_ctx, getState());
  enterRule(_localctx, 42, SysYFParser::RuleReturn_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(SysYFParser::T__13);
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 122407354496) != 0)) {
      setState(245);
      exp(0);
    }
    setState(248);
    match(SysYFParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cond_expContext ------------------------------------------------------------------

SysYFParser::Cond_expContext::Cond_expContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::ExpContext* SysYFParser::Cond_expContext::exp() {
  return getRuleContext<SysYFParser::ExpContext>(0);
}

std::vector<SysYFParser::Cond_expContext *> SysYFParser::Cond_expContext::cond_exp() {
  return getRuleContexts<SysYFParser::Cond_expContext>();
}

SysYFParser::Cond_expContext* SysYFParser::Cond_expContext::cond_exp(size_t i) {
  return getRuleContext<SysYFParser::Cond_expContext>(i);
}

tree::TerminalNode* SysYFParser::Cond_expContext::LT() {
  return getToken(SysYFParser::LT, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::GT() {
  return getToken(SysYFParser::GT, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::LTE() {
  return getToken(SysYFParser::LTE, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::GTE() {
  return getToken(SysYFParser::GTE, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::NEQ() {
  return getToken(SysYFParser::NEQ, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::EQ() {
  return getToken(SysYFParser::EQ, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::LAND() {
  return getToken(SysYFParser::LAND, 0);
}

tree::TerminalNode* SysYFParser::Cond_expContext::LOR() {
  return getToken(SysYFParser::LOR, 0);
}


size_t SysYFParser::Cond_expContext::getRuleIndex() const {
  return SysYFParser::RuleCond_exp;
}


std::any SysYFParser::Cond_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitCond_exp(this);
  else
    return visitor->visitChildren(this);
}


SysYFParser::Cond_expContext* SysYFParser::cond_exp() {
   return cond_exp(0);
}

SysYFParser::Cond_expContext* SysYFParser::cond_exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYFParser::Cond_expContext *_localctx = _tracker.createInstance<Cond_expContext>(_ctx, parentState);
  SysYFParser::Cond_expContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, SysYFParser::RuleCond_exp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(251);
    exp(0);
    _ctx->stop = _input->LT(-1);
    setState(267);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(265);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Cond_expContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond_exp);
          setState(253);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(254);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 2013265920) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(255);
          cond_exp(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Cond_expContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond_exp);
          setState(256);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(257);
          _la = _input->LA(1);
          if (!(_la == SysYFParser::EQ

          || _la == SysYFParser::NEQ)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(258);
          cond_exp(4);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<Cond_expContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond_exp);
          setState(259);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(260);
          match(SysYFParser::LAND);
          setState(261);
          cond_exp(3);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<Cond_expContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond_exp);
          setState(262);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(263);
          match(SysYFParser::LOR);
          setState(264);
          cond_exp(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(269);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

SysYFParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYFParser::ExpContext *> SysYFParser::ExpContext::exp() {
  return getRuleContexts<SysYFParser::ExpContext>();
}

SysYFParser::ExpContext* SysYFParser::ExpContext::exp(size_t i) {
  return getRuleContext<SysYFParser::ExpContext>(i);
}

tree::TerminalNode* SysYFParser::ExpContext::PLUS() {
  return getToken(SysYFParser::PLUS, 0);
}

tree::TerminalNode* SysYFParser::ExpContext::MINUS() {
  return getToken(SysYFParser::MINUS, 0);
}

tree::TerminalNode* SysYFParser::ExpContext::NOT() {
  return getToken(SysYFParser::NOT, 0);
}

SysYFParser::LvalContext* SysYFParser::ExpContext::lval() {
  return getRuleContext<SysYFParser::LvalContext>(0);
}

SysYFParser::NumberContext* SysYFParser::ExpContext::number() {
  return getRuleContext<SysYFParser::NumberContext>(0);
}

SysYFParser::Func_callContext* SysYFParser::ExpContext::func_call() {
  return getRuleContext<SysYFParser::Func_callContext>(0);
}

tree::TerminalNode* SysYFParser::ExpContext::MUL() {
  return getToken(SysYFParser::MUL, 0);
}

tree::TerminalNode* SysYFParser::ExpContext::DIV() {
  return getToken(SysYFParser::DIV, 0);
}

tree::TerminalNode* SysYFParser::ExpContext::MOD() {
  return getToken(SysYFParser::MOD, 0);
}


size_t SysYFParser::ExpContext::getRuleIndex() const {
  return SysYFParser::RuleExp;
}


std::any SysYFParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}


SysYFParser::ExpContext* SysYFParser::exp() {
   return exp(0);
}

SysYFParser::ExpContext* SysYFParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYFParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  SysYFParser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, SysYFParser::RuleExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(280);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(271);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2148270080) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(272);
      exp(7);
      break;
    }

    case 2: {
      setState(273);
      lval();
      break;
    }

    case 3: {
      setState(274);
      number();
      break;
    }

    case 4: {
      setState(275);
      func_call();
      break;
    }

    case 5: {
      setState(276);
      match(SysYFParser::T__6);
      setState(277);
      exp(0);
      setState(278);
      match(SysYFParser::T__7);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(290);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(288);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(282);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(283);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(284);
          exp(3);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExp);
          setState(285);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(286);
          _la = _input->LA(1);
          if (!(_la == SysYFParser::PLUS

          || _la == SysYFParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(287);
          exp(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(292);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Func_callContext ------------------------------------------------------------------

SysYFParser::Func_callContext::Func_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::IdentContext* SysYFParser::Func_callContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

std::vector<SysYFParser::ExpContext *> SysYFParser::Func_callContext::exp() {
  return getRuleContexts<SysYFParser::ExpContext>();
}

SysYFParser::ExpContext* SysYFParser::Func_callContext::exp(size_t i) {
  return getRuleContext<SysYFParser::ExpContext>(i);
}


size_t SysYFParser::Func_callContext::getRuleIndex() const {
  return SysYFParser::RuleFunc_call;
}


std::any SysYFParser::Func_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitFunc_call(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::Func_callContext* SysYFParser::func_call() {
  Func_callContext *_localctx = _tracker.createInstance<Func_callContext>(_ctx, getState());
  enterRule(_localctx, 48, SysYFParser::RuleFunc_call);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    ident();
    setState(294);
    match(SysYFParser::T__6);
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 122407354496) != 0)) {
      setState(295);
      exp(0);
      setState(300);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYFParser::T__1) {
        setState(296);
        match(SysYFParser::T__1);
        setState(297);
        exp(0);
        setState(302);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(305);
    match(SysYFParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LvalContext ------------------------------------------------------------------

SysYFParser::LvalContext::LvalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYFParser::IdentContext* SysYFParser::LvalContext::ident() {
  return getRuleContext<SysYFParser::IdentContext>(0);
}

tree::TerminalNode* SysYFParser::LvalContext::LBRACKET() {
  return getToken(SysYFParser::LBRACKET, 0);
}

SysYFParser::ExpContext* SysYFParser::LvalContext::exp() {
  return getRuleContext<SysYFParser::ExpContext>(0);
}

tree::TerminalNode* SysYFParser::LvalContext::RBRACKET() {
  return getToken(SysYFParser::RBRACKET, 0);
}


size_t SysYFParser::LvalContext::getRuleIndex() const {
  return SysYFParser::RuleLval;
}


std::any SysYFParser::LvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitLval(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::LvalContext* SysYFParser::lval() {
  LvalContext *_localctx = _tracker.createInstance<LvalContext>(_ctx, getState());
  enterRule(_localctx, 50, SysYFParser::RuleLval);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    ident();
    setState(312);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(308);
      match(SysYFParser::LBRACKET);
      setState(309);
      exp(0);
      setState(310);
      match(SysYFParser::RBRACKET);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentContext ------------------------------------------------------------------

SysYFParser::IdentContext::IdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYFParser::IdentContext::NAME() {
  return getToken(SysYFParser::NAME, 0);
}


size_t SysYFParser::IdentContext::getRuleIndex() const {
  return SysYFParser::RuleIdent;
}


std::any SysYFParser::IdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitIdent(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::IdentContext* SysYFParser::ident() {
  IdentContext *_localctx = _tracker.createInstance<IdentContext>(_ctx, getState());
  enterRule(_localctx, 52, SysYFParser::RuleIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    match(SysYFParser::NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

SysYFParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYFParser::NumberContext::INT() {
  return getToken(SysYFParser::INT, 0);
}

tree::TerminalNode* SysYFParser::NumberContext::FLOAT() {
  return getToken(SysYFParser::FLOAT, 0);
}


size_t SysYFParser::NumberContext::getRuleIndex() const {
  return SysYFParser::RuleNumber;
}


std::any SysYFParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYFVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

SysYFParser::NumberContext* SysYFParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 54, SysYFParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    _la = _input->LA(1);
    if (!(_la == SysYFParser::INT

    || _la == SysYFParser::FLOAT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SysYFParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 22: return cond_expSempred(antlrcpp::downCast<Cond_expContext *>(context), predicateIndex);
    case 23: return expSempred(antlrcpp::downCast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SysYFParser::cond_expSempred(Cond_expContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 2);
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYFParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void SysYFParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sysyfParserInitialize();
#else
  ::antlr4::internal::call_once(sysyfParserOnceFlag, sysyfParserInitialize);
#endif
}
