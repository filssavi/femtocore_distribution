
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.10.1


#include "asm_grammarListener.h"
#include "asm_grammarVisitor.h"

#include "asm_grammarParser.h"


using namespace antlrcpp;
using namespace asm_parser;

using namespace antlr4;

namespace {

struct Asm_grammarParserStaticData final {
  Asm_grammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Asm_grammarParserStaticData(const Asm_grammarParserStaticData&) = delete;
  Asm_grammarParserStaticData(Asm_grammarParserStaticData&&) = delete;
  Asm_grammarParserStaticData& operator=(const Asm_grammarParserStaticData&) = delete;
  Asm_grammarParserStaticData& operator=(Asm_grammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag asm_grammarParserOnceFlag;
Asm_grammarParserStaticData *asm_grammarParserStaticData = nullptr;

void asm_grammarParserInitialize() {
  assert(asm_grammarParserStaticData == nullptr);
  auto staticData = std::make_unique<Asm_grammarParserStaticData>(
    std::vector<std::string>{
      "program", "code", "declaration", "instruction", "reg_instr", "imm_instr", 
      "load_instr", "branch_instr", "conv_instr", "indep_instr", "pseudo_instr", 
      "operand", "destination", "immediate", "float_const", "integer_const", 
      "reg_opcode", "conv_opcode", "imm_opcode", "branch_opcode", "pseudo_opcode", 
      "for_block", "for_incr", "for_dec", "for_decl", "for_end", "for_end_comp_type", 
      "pragma", "variable_decl", "constant_decl", "input_decl", "output_decl"
    },
    std::vector<std::string>{
      "", "','", "'ldc'", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", 
      "'and'", "'or'", "'satp'", "'satn'", "'efi'", "'bset'", "'bsel'", 
      "'xor'", "'itf'", "'fti'", "'not'", "'rec'", "'abs'", "'popcnt'", 
      "'ldr'", "'ble'", "'bgt'", "'beq'", "'bne'", "'mov'", "'for('", "';'", 
      "')'", "'{'", "'}'", "'++'", "'--'", "'='", "'<'", "'>'", "'<='", 
      "'>='", "'#pragma '", "'let'", "'const'", "'input'", "'output'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "Register", "Identifier", 
      "Hexnum", "Integer", "Octalnum", "FloatingPointLiteral", "String", 
      "Label", "WS", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,55,199,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,1,0,1,1,1,1,1,1,1,1,4,1,71,8,1,11,
  	1,12,1,72,1,2,1,2,1,2,1,2,3,2,79,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,
  	88,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,
  	6,1,6,3,6,107,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,
  	1,9,1,10,1,10,1,10,1,10,1,10,1,10,5,10,129,8,10,10,10,12,10,132,9,10,
  	1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,
  	1,18,1,18,1,19,1,19,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,
  	161,8,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,23,1,24,
  	1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,26,1,26,1,27,1,27,1,27,1,28,1,28,
  	1,28,1,29,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,1,31,0,0,32,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,0,8,1,0,3,4,1,0,45,46,1,0,46,49,1,0,47,49,1,0,5,15,1,0,16,
  	21,1,0,23,26,1,0,36,39,182,0,64,1,0,0,0,2,70,1,0,0,0,4,78,1,0,0,0,6,87,
  	1,0,0,0,8,89,1,0,0,0,10,96,1,0,0,0,12,101,1,0,0,0,14,108,1,0,0,0,16,115,
  	1,0,0,0,18,120,1,0,0,0,20,122,1,0,0,0,22,133,1,0,0,0,24,135,1,0,0,0,26,
  	137,1,0,0,0,28,139,1,0,0,0,30,141,1,0,0,0,32,143,1,0,0,0,34,145,1,0,0,
  	0,36,147,1,0,0,0,38,149,1,0,0,0,40,151,1,0,0,0,42,153,1,0,0,0,44,167,
  	1,0,0,0,46,170,1,0,0,0,48,173,1,0,0,0,50,177,1,0,0,0,52,181,1,0,0,0,54,
  	183,1,0,0,0,56,186,1,0,0,0,58,189,1,0,0,0,60,192,1,0,0,0,62,195,1,0,0,
  	0,64,65,3,2,1,0,65,1,1,0,0,0,66,71,3,6,3,0,67,71,3,42,21,0,68,71,3,54,
  	27,0,69,71,3,4,2,0,70,66,1,0,0,0,70,67,1,0,0,0,70,68,1,0,0,0,70,69,1,
  	0,0,0,71,72,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,3,1,0,0,0,74,79,3,
  	60,30,0,75,79,3,56,28,0,76,79,3,58,29,0,77,79,3,62,31,0,78,74,1,0,0,0,
  	78,75,1,0,0,0,78,76,1,0,0,0,78,77,1,0,0,0,79,5,1,0,0,0,80,88,3,8,4,0,
  	81,88,3,10,5,0,82,88,3,18,9,0,83,88,3,20,10,0,84,88,3,14,7,0,85,88,3,
  	16,8,0,86,88,3,12,6,0,87,80,1,0,0,0,87,81,1,0,0,0,87,82,1,0,0,0,87,83,
  	1,0,0,0,87,84,1,0,0,0,87,85,1,0,0,0,87,86,1,0,0,0,88,7,1,0,0,0,89,90,
  	3,32,16,0,90,91,3,22,11,0,91,92,5,1,0,0,92,93,3,22,11,0,93,94,5,1,0,0,
  	94,95,3,24,12,0,95,9,1,0,0,0,96,97,3,36,18,0,97,98,3,24,12,0,98,99,5,
  	1,0,0,99,100,3,26,13,0,100,11,1,0,0,0,101,102,5,2,0,0,102,103,3,24,12,
  	0,103,106,5,1,0,0,104,107,5,50,0,0,105,107,3,30,15,0,106,104,1,0,0,0,
  	106,105,1,0,0,0,107,13,1,0,0,0,108,109,3,38,19,0,109,110,3,22,11,0,110,
  	111,5,1,0,0,111,112,3,22,11,0,112,113,5,1,0,0,113,114,3,22,11,0,114,15,
  	1,0,0,0,115,116,3,34,17,0,116,117,3,22,11,0,117,118,5,1,0,0,118,119,3,
  	22,11,0,119,17,1,0,0,0,120,121,7,0,0,0,121,19,1,0,0,0,122,123,3,40,20,
  	0,123,124,3,22,11,0,124,125,5,1,0,0,125,130,3,22,11,0,126,127,5,1,0,0,
  	127,129,3,22,11,0,128,126,1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,130,
  	131,1,0,0,0,131,21,1,0,0,0,132,130,1,0,0,0,133,134,7,1,0,0,134,23,1,0,
  	0,0,135,136,7,1,0,0,136,25,1,0,0,0,137,138,7,2,0,0,138,27,1,0,0,0,139,
  	140,5,50,0,0,140,29,1,0,0,0,141,142,7,3,0,0,142,31,1,0,0,0,143,144,7,
  	4,0,0,144,33,1,0,0,0,145,146,7,5,0,0,146,35,1,0,0,0,147,148,5,22,0,0,
  	148,37,1,0,0,0,149,150,7,6,0,0,150,39,1,0,0,0,151,152,5,27,0,0,152,41,
  	1,0,0,0,153,154,5,28,0,0,154,155,3,48,24,0,155,156,5,29,0,0,156,157,3,
  	50,25,0,157,160,5,29,0,0,158,161,3,44,22,0,159,161,3,46,23,0,160,158,
  	1,0,0,0,160,159,1,0,0,0,161,162,1,0,0,0,162,163,5,30,0,0,163,164,5,31,
  	0,0,164,165,3,2,1,0,165,166,5,32,0,0,166,43,1,0,0,0,167,168,5,46,0,0,
  	168,169,5,33,0,0,169,45,1,0,0,0,170,171,5,46,0,0,171,172,5,34,0,0,172,
  	47,1,0,0,0,173,174,5,46,0,0,174,175,5,35,0,0,175,176,5,48,0,0,176,49,
  	1,0,0,0,177,178,5,46,0,0,178,179,3,52,26,0,179,180,5,48,0,0,180,51,1,
  	0,0,0,181,182,7,7,0,0,182,53,1,0,0,0,183,184,5,40,0,0,184,185,5,46,0,
  	0,185,55,1,0,0,0,186,187,5,41,0,0,187,188,7,1,0,0,188,57,1,0,0,0,189,
  	190,5,42,0,0,190,191,7,1,0,0,191,59,1,0,0,0,192,193,5,43,0,0,193,194,
  	7,1,0,0,194,61,1,0,0,0,195,196,5,44,0,0,196,197,7,1,0,0,197,63,1,0,0,
  	0,7,70,72,78,87,106,130,160
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asm_grammarParserStaticData = staticData.release();
}

}

asm_grammarParser::asm_grammarParser(TokenStream *input) : asm_grammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

asm_grammarParser::asm_grammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  asm_grammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *asm_grammarParserStaticData->atn, asm_grammarParserStaticData->decisionToDFA, asm_grammarParserStaticData->sharedContextCache, options);
}

asm_grammarParser::~asm_grammarParser() {
  delete _interpreter;
}

const atn::ATN& asm_grammarParser::getATN() const {
  return *asm_grammarParserStaticData->atn;
}

std::string asm_grammarParser::getGrammarFileName() const {
  return "asm_grammar.g4";
}

const std::vector<std::string>& asm_grammarParser::getRuleNames() const {
  return asm_grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& asm_grammarParser::getVocabulary() const {
  return asm_grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView asm_grammarParser::getSerializedATN() const {
  return asm_grammarParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

asm_grammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::CodeContext* asm_grammarParser::ProgramContext::code() {
  return getRuleContext<asm_grammarParser::CodeContext>(0);
}


size_t asm_grammarParser::ProgramContext::getRuleIndex() const {
  return asm_grammarParser::RuleProgram;
}

void asm_grammarParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void asm_grammarParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any asm_grammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::ProgramContext* asm_grammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, asm_grammarParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    code();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeContext ------------------------------------------------------------------

asm_grammarParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<asm_grammarParser::InstructionContext *> asm_grammarParser::CodeContext::instruction() {
  return getRuleContexts<asm_grammarParser::InstructionContext>();
}

asm_grammarParser::InstructionContext* asm_grammarParser::CodeContext::instruction(size_t i) {
  return getRuleContext<asm_grammarParser::InstructionContext>(i);
}

std::vector<asm_grammarParser::For_blockContext *> asm_grammarParser::CodeContext::for_block() {
  return getRuleContexts<asm_grammarParser::For_blockContext>();
}

asm_grammarParser::For_blockContext* asm_grammarParser::CodeContext::for_block(size_t i) {
  return getRuleContext<asm_grammarParser::For_blockContext>(i);
}

std::vector<asm_grammarParser::PragmaContext *> asm_grammarParser::CodeContext::pragma() {
  return getRuleContexts<asm_grammarParser::PragmaContext>();
}

asm_grammarParser::PragmaContext* asm_grammarParser::CodeContext::pragma(size_t i) {
  return getRuleContext<asm_grammarParser::PragmaContext>(i);
}

std::vector<asm_grammarParser::DeclarationContext *> asm_grammarParser::CodeContext::declaration() {
  return getRuleContexts<asm_grammarParser::DeclarationContext>();
}

asm_grammarParser::DeclarationContext* asm_grammarParser::CodeContext::declaration(size_t i) {
  return getRuleContext<asm_grammarParser::DeclarationContext>(i);
}


size_t asm_grammarParser::CodeContext::getRuleIndex() const {
  return asm_grammarParser::RuleCode;
}

void asm_grammarParser::CodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode(this);
}

void asm_grammarParser::CodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode(this);
}


std::any asm_grammarParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::CodeContext* asm_grammarParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 2, asm_grammarParser::RuleCode);
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
    setState(70); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(70);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case asm_grammarParser::T__1:
        case asm_grammarParser::T__2:
        case asm_grammarParser::T__3:
        case asm_grammarParser::T__4:
        case asm_grammarParser::T__5:
        case asm_grammarParser::T__6:
        case asm_grammarParser::T__7:
        case asm_grammarParser::T__8:
        case asm_grammarParser::T__9:
        case asm_grammarParser::T__10:
        case asm_grammarParser::T__11:
        case asm_grammarParser::T__12:
        case asm_grammarParser::T__13:
        case asm_grammarParser::T__14:
        case asm_grammarParser::T__15:
        case asm_grammarParser::T__16:
        case asm_grammarParser::T__17:
        case asm_grammarParser::T__18:
        case asm_grammarParser::T__19:
        case asm_grammarParser::T__20:
        case asm_grammarParser::T__21:
        case asm_grammarParser::T__22:
        case asm_grammarParser::T__23:
        case asm_grammarParser::T__24:
        case asm_grammarParser::T__25:
        case asm_grammarParser::T__26: {
          setState(66);
          instruction();
          break;
        }

        case asm_grammarParser::T__27: {
          setState(67);
          for_block();
          break;
        }

        case asm_grammarParser::T__39: {
          setState(68);
          pragma();
          break;
        }

        case asm_grammarParser::T__40:
        case asm_grammarParser::T__41:
        case asm_grammarParser::T__42:
        case asm_grammarParser::T__43: {
          setState(69);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(72); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::T__1)
      | (1ULL << asm_grammarParser::T__2)
      | (1ULL << asm_grammarParser::T__3)
      | (1ULL << asm_grammarParser::T__4)
      | (1ULL << asm_grammarParser::T__5)
      | (1ULL << asm_grammarParser::T__6)
      | (1ULL << asm_grammarParser::T__7)
      | (1ULL << asm_grammarParser::T__8)
      | (1ULL << asm_grammarParser::T__9)
      | (1ULL << asm_grammarParser::T__10)
      | (1ULL << asm_grammarParser::T__11)
      | (1ULL << asm_grammarParser::T__12)
      | (1ULL << asm_grammarParser::T__13)
      | (1ULL << asm_grammarParser::T__14)
      | (1ULL << asm_grammarParser::T__15)
      | (1ULL << asm_grammarParser::T__16)
      | (1ULL << asm_grammarParser::T__17)
      | (1ULL << asm_grammarParser::T__18)
      | (1ULL << asm_grammarParser::T__19)
      | (1ULL << asm_grammarParser::T__20)
      | (1ULL << asm_grammarParser::T__21)
      | (1ULL << asm_grammarParser::T__22)
      | (1ULL << asm_grammarParser::T__23)
      | (1ULL << asm_grammarParser::T__24)
      | (1ULL << asm_grammarParser::T__25)
      | (1ULL << asm_grammarParser::T__26)
      | (1ULL << asm_grammarParser::T__27)
      | (1ULL << asm_grammarParser::T__39)
      | (1ULL << asm_grammarParser::T__40)
      | (1ULL << asm_grammarParser::T__41)
      | (1ULL << asm_grammarParser::T__42)
      | (1ULL << asm_grammarParser::T__43))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

asm_grammarParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Input_declContext* asm_grammarParser::DeclarationContext::input_decl() {
  return getRuleContext<asm_grammarParser::Input_declContext>(0);
}

asm_grammarParser::Variable_declContext* asm_grammarParser::DeclarationContext::variable_decl() {
  return getRuleContext<asm_grammarParser::Variable_declContext>(0);
}

asm_grammarParser::Constant_declContext* asm_grammarParser::DeclarationContext::constant_decl() {
  return getRuleContext<asm_grammarParser::Constant_declContext>(0);
}

asm_grammarParser::Output_declContext* asm_grammarParser::DeclarationContext::output_decl() {
  return getRuleContext<asm_grammarParser::Output_declContext>(0);
}


size_t asm_grammarParser::DeclarationContext::getRuleIndex() const {
  return asm_grammarParser::RuleDeclaration;
}

void asm_grammarParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void asm_grammarParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any asm_grammarParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::DeclarationContext* asm_grammarParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, asm_grammarParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm_grammarParser::T__42: {
        setState(74);
        input_decl();
        break;
      }

      case asm_grammarParser::T__40: {
        setState(75);
        variable_decl();
        break;
      }

      case asm_grammarParser::T__41: {
        setState(76);
        constant_decl();
        break;
      }

      case asm_grammarParser::T__43: {
        setState(77);
        output_decl();
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

//----------------- InstructionContext ------------------------------------------------------------------

asm_grammarParser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Reg_instrContext* asm_grammarParser::InstructionContext::reg_instr() {
  return getRuleContext<asm_grammarParser::Reg_instrContext>(0);
}

asm_grammarParser::Imm_instrContext* asm_grammarParser::InstructionContext::imm_instr() {
  return getRuleContext<asm_grammarParser::Imm_instrContext>(0);
}

asm_grammarParser::Indep_instrContext* asm_grammarParser::InstructionContext::indep_instr() {
  return getRuleContext<asm_grammarParser::Indep_instrContext>(0);
}

asm_grammarParser::Pseudo_instrContext* asm_grammarParser::InstructionContext::pseudo_instr() {
  return getRuleContext<asm_grammarParser::Pseudo_instrContext>(0);
}

asm_grammarParser::Branch_instrContext* asm_grammarParser::InstructionContext::branch_instr() {
  return getRuleContext<asm_grammarParser::Branch_instrContext>(0);
}

asm_grammarParser::Conv_instrContext* asm_grammarParser::InstructionContext::conv_instr() {
  return getRuleContext<asm_grammarParser::Conv_instrContext>(0);
}

asm_grammarParser::Load_instrContext* asm_grammarParser::InstructionContext::load_instr() {
  return getRuleContext<asm_grammarParser::Load_instrContext>(0);
}


size_t asm_grammarParser::InstructionContext::getRuleIndex() const {
  return asm_grammarParser::RuleInstruction;
}

void asm_grammarParser::InstructionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstruction(this);
}

void asm_grammarParser::InstructionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstruction(this);
}


std::any asm_grammarParser::InstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitInstruction(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::InstructionContext* asm_grammarParser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 6, asm_grammarParser::RuleInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(87);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm_grammarParser::T__4:
      case asm_grammarParser::T__5:
      case asm_grammarParser::T__6:
      case asm_grammarParser::T__7:
      case asm_grammarParser::T__8:
      case asm_grammarParser::T__9:
      case asm_grammarParser::T__10:
      case asm_grammarParser::T__11:
      case asm_grammarParser::T__12:
      case asm_grammarParser::T__13:
      case asm_grammarParser::T__14: {
        enterOuterAlt(_localctx, 1);
        setState(80);
        reg_instr();
        break;
      }

      case asm_grammarParser::T__21: {
        enterOuterAlt(_localctx, 2);
        setState(81);
        imm_instr();
        break;
      }

      case asm_grammarParser::T__2:
      case asm_grammarParser::T__3: {
        enterOuterAlt(_localctx, 3);
        setState(82);
        indep_instr();
        break;
      }

      case asm_grammarParser::T__26: {
        enterOuterAlt(_localctx, 4);
        setState(83);
        pseudo_instr();
        break;
      }

      case asm_grammarParser::T__22:
      case asm_grammarParser::T__23:
      case asm_grammarParser::T__24:
      case asm_grammarParser::T__25: {
        enterOuterAlt(_localctx, 5);
        setState(84);
        branch_instr();
        break;
      }

      case asm_grammarParser::T__15:
      case asm_grammarParser::T__16:
      case asm_grammarParser::T__17:
      case asm_grammarParser::T__18:
      case asm_grammarParser::T__19:
      case asm_grammarParser::T__20: {
        enterOuterAlt(_localctx, 6);
        setState(85);
        conv_instr();
        break;
      }

      case asm_grammarParser::T__1: {
        enterOuterAlt(_localctx, 7);
        setState(86);
        load_instr();
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

//----------------- Reg_instrContext ------------------------------------------------------------------

asm_grammarParser::Reg_instrContext::Reg_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Reg_opcodeContext* asm_grammarParser::Reg_instrContext::reg_opcode() {
  return getRuleContext<asm_grammarParser::Reg_opcodeContext>(0);
}

std::vector<asm_grammarParser::OperandContext *> asm_grammarParser::Reg_instrContext::operand() {
  return getRuleContexts<asm_grammarParser::OperandContext>();
}

asm_grammarParser::OperandContext* asm_grammarParser::Reg_instrContext::operand(size_t i) {
  return getRuleContext<asm_grammarParser::OperandContext>(i);
}

asm_grammarParser::DestinationContext* asm_grammarParser::Reg_instrContext::destination() {
  return getRuleContext<asm_grammarParser::DestinationContext>(0);
}


size_t asm_grammarParser::Reg_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleReg_instr;
}

void asm_grammarParser::Reg_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReg_instr(this);
}

void asm_grammarParser::Reg_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReg_instr(this);
}


std::any asm_grammarParser::Reg_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitReg_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Reg_instrContext* asm_grammarParser::reg_instr() {
  Reg_instrContext *_localctx = _tracker.createInstance<Reg_instrContext>(_ctx, getState());
  enterRule(_localctx, 8, asm_grammarParser::RuleReg_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    reg_opcode();
    setState(90);
    operand();
    setState(91);
    match(asm_grammarParser::T__0);
    setState(92);
    operand();
    setState(93);
    match(asm_grammarParser::T__0);
    setState(94);
    destination();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imm_instrContext ------------------------------------------------------------------

asm_grammarParser::Imm_instrContext::Imm_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Imm_opcodeContext* asm_grammarParser::Imm_instrContext::imm_opcode() {
  return getRuleContext<asm_grammarParser::Imm_opcodeContext>(0);
}

asm_grammarParser::DestinationContext* asm_grammarParser::Imm_instrContext::destination() {
  return getRuleContext<asm_grammarParser::DestinationContext>(0);
}

asm_grammarParser::ImmediateContext* asm_grammarParser::Imm_instrContext::immediate() {
  return getRuleContext<asm_grammarParser::ImmediateContext>(0);
}


size_t asm_grammarParser::Imm_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleImm_instr;
}

void asm_grammarParser::Imm_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_instr(this);
}

void asm_grammarParser::Imm_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_instr(this);
}


std::any asm_grammarParser::Imm_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Imm_instrContext* asm_grammarParser::imm_instr() {
  Imm_instrContext *_localctx = _tracker.createInstance<Imm_instrContext>(_ctx, getState());
  enterRule(_localctx, 10, asm_grammarParser::RuleImm_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    imm_opcode();
    setState(97);
    destination();
    setState(98);
    match(asm_grammarParser::T__0);
    setState(99);
    immediate();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Load_instrContext ------------------------------------------------------------------

asm_grammarParser::Load_instrContext::Load_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::DestinationContext* asm_grammarParser::Load_instrContext::destination() {
  return getRuleContext<asm_grammarParser::DestinationContext>(0);
}

tree::TerminalNode* asm_grammarParser::Load_instrContext::FloatingPointLiteral() {
  return getToken(asm_grammarParser::FloatingPointLiteral, 0);
}

asm_grammarParser::Integer_constContext* asm_grammarParser::Load_instrContext::integer_const() {
  return getRuleContext<asm_grammarParser::Integer_constContext>(0);
}


size_t asm_grammarParser::Load_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleLoad_instr;
}

void asm_grammarParser::Load_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoad_instr(this);
}

void asm_grammarParser::Load_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoad_instr(this);
}


std::any asm_grammarParser::Load_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitLoad_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Load_instrContext* asm_grammarParser::load_instr() {
  Load_instrContext *_localctx = _tracker.createInstance<Load_instrContext>(_ctx, getState());
  enterRule(_localctx, 12, asm_grammarParser::RuleLoad_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    match(asm_grammarParser::T__1);
    setState(102);
    destination();
    setState(103);
    match(asm_grammarParser::T__0);
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case asm_grammarParser::FloatingPointLiteral: {
        setState(104);
        match(asm_grammarParser::FloatingPointLiteral);
        break;
      }

      case asm_grammarParser::Hexnum:
      case asm_grammarParser::Integer:
      case asm_grammarParser::Octalnum: {
        setState(105);
        integer_const();
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

//----------------- Branch_instrContext ------------------------------------------------------------------

asm_grammarParser::Branch_instrContext::Branch_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Branch_opcodeContext* asm_grammarParser::Branch_instrContext::branch_opcode() {
  return getRuleContext<asm_grammarParser::Branch_opcodeContext>(0);
}

std::vector<asm_grammarParser::OperandContext *> asm_grammarParser::Branch_instrContext::operand() {
  return getRuleContexts<asm_grammarParser::OperandContext>();
}

asm_grammarParser::OperandContext* asm_grammarParser::Branch_instrContext::operand(size_t i) {
  return getRuleContext<asm_grammarParser::OperandContext>(i);
}


size_t asm_grammarParser::Branch_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleBranch_instr;
}

void asm_grammarParser::Branch_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBranch_instr(this);
}

void asm_grammarParser::Branch_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBranch_instr(this);
}


std::any asm_grammarParser::Branch_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitBranch_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Branch_instrContext* asm_grammarParser::branch_instr() {
  Branch_instrContext *_localctx = _tracker.createInstance<Branch_instrContext>(_ctx, getState());
  enterRule(_localctx, 14, asm_grammarParser::RuleBranch_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    branch_opcode();
    setState(109);
    operand();
    setState(110);
    match(asm_grammarParser::T__0);
    setState(111);
    operand();
    setState(112);
    match(asm_grammarParser::T__0);
    setState(113);
    operand();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Conv_instrContext ------------------------------------------------------------------

asm_grammarParser::Conv_instrContext::Conv_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Conv_opcodeContext* asm_grammarParser::Conv_instrContext::conv_opcode() {
  return getRuleContext<asm_grammarParser::Conv_opcodeContext>(0);
}

std::vector<asm_grammarParser::OperandContext *> asm_grammarParser::Conv_instrContext::operand() {
  return getRuleContexts<asm_grammarParser::OperandContext>();
}

asm_grammarParser::OperandContext* asm_grammarParser::Conv_instrContext::operand(size_t i) {
  return getRuleContext<asm_grammarParser::OperandContext>(i);
}


size_t asm_grammarParser::Conv_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleConv_instr;
}

void asm_grammarParser::Conv_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConv_instr(this);
}

void asm_grammarParser::Conv_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConv_instr(this);
}


std::any asm_grammarParser::Conv_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitConv_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Conv_instrContext* asm_grammarParser::conv_instr() {
  Conv_instrContext *_localctx = _tracker.createInstance<Conv_instrContext>(_ctx, getState());
  enterRule(_localctx, 16, asm_grammarParser::RuleConv_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    conv_opcode();
    setState(116);
    operand();
    setState(117);
    match(asm_grammarParser::T__0);
    setState(118);
    operand();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Indep_instrContext ------------------------------------------------------------------

asm_grammarParser::Indep_instrContext::Indep_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Indep_instrContext::getRuleIndex() const {
  return asm_grammarParser::RuleIndep_instr;
}

void asm_grammarParser::Indep_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndep_instr(this);
}

void asm_grammarParser::Indep_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndep_instr(this);
}


std::any asm_grammarParser::Indep_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitIndep_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Indep_instrContext* asm_grammarParser::indep_instr() {
  Indep_instrContext *_localctx = _tracker.createInstance<Indep_instrContext>(_ctx, getState());
  enterRule(_localctx, 18, asm_grammarParser::RuleIndep_instr);
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
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::T__2

    || _la == asm_grammarParser::T__3)) {
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

//----------------- Pseudo_instrContext ------------------------------------------------------------------

asm_grammarParser::Pseudo_instrContext::Pseudo_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::Pseudo_opcodeContext* asm_grammarParser::Pseudo_instrContext::pseudo_opcode() {
  return getRuleContext<asm_grammarParser::Pseudo_opcodeContext>(0);
}

std::vector<asm_grammarParser::OperandContext *> asm_grammarParser::Pseudo_instrContext::operand() {
  return getRuleContexts<asm_grammarParser::OperandContext>();
}

asm_grammarParser::OperandContext* asm_grammarParser::Pseudo_instrContext::operand(size_t i) {
  return getRuleContext<asm_grammarParser::OperandContext>(i);
}


size_t asm_grammarParser::Pseudo_instrContext::getRuleIndex() const {
  return asm_grammarParser::RulePseudo_instr;
}

void asm_grammarParser::Pseudo_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudo_instr(this);
}

void asm_grammarParser::Pseudo_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudo_instr(this);
}


std::any asm_grammarParser::Pseudo_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitPseudo_instr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Pseudo_instrContext* asm_grammarParser::pseudo_instr() {
  Pseudo_instrContext *_localctx = _tracker.createInstance<Pseudo_instrContext>(_ctx, getState());
  enterRule(_localctx, 20, asm_grammarParser::RulePseudo_instr);
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
    setState(122);
    pseudo_opcode();
    setState(123);
    operand();
    setState(124);
    match(asm_grammarParser::T__0);
    setState(125);
    operand();
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == asm_grammarParser::T__0) {
      setState(126);
      match(asm_grammarParser::T__0);
      setState(127);
      operand();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandContext ------------------------------------------------------------------

asm_grammarParser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::OperandContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::OperandContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::OperandContext::getRuleIndex() const {
  return asm_grammarParser::RuleOperand;
}

void asm_grammarParser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void asm_grammarParser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}


std::any asm_grammarParser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::OperandContext* asm_grammarParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 22, asm_grammarParser::RuleOperand);
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
    setState(133);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

//----------------- DestinationContext ------------------------------------------------------------------

asm_grammarParser::DestinationContext::DestinationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::DestinationContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::DestinationContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::DestinationContext::getRuleIndex() const {
  return asm_grammarParser::RuleDestination;
}

void asm_grammarParser::DestinationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDestination(this);
}

void asm_grammarParser::DestinationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDestination(this);
}


std::any asm_grammarParser::DestinationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitDestination(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::DestinationContext* asm_grammarParser::destination() {
  DestinationContext *_localctx = _tracker.createInstance<DestinationContext>(_ctx, getState());
  enterRule(_localctx, 24, asm_grammarParser::RuleDestination);
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
    setState(135);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

//----------------- ImmediateContext ------------------------------------------------------------------

asm_grammarParser::ImmediateContext::ImmediateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::ImmediateContext::Integer() {
  return getToken(asm_grammarParser::Integer, 0);
}

tree::TerminalNode* asm_grammarParser::ImmediateContext::Hexnum() {
  return getToken(asm_grammarParser::Hexnum, 0);
}

tree::TerminalNode* asm_grammarParser::ImmediateContext::Octalnum() {
  return getToken(asm_grammarParser::Octalnum, 0);
}

tree::TerminalNode* asm_grammarParser::ImmediateContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::ImmediateContext::getRuleIndex() const {
  return asm_grammarParser::RuleImmediate;
}

void asm_grammarParser::ImmediateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImmediate(this);
}

void asm_grammarParser::ImmediateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImmediate(this);
}


std::any asm_grammarParser::ImmediateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitImmediate(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::ImmediateContext* asm_grammarParser::immediate() {
  ImmediateContext *_localctx = _tracker.createInstance<ImmediateContext>(_ctx, getState());
  enterRule(_localctx, 26, asm_grammarParser::RuleImmediate);
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
    setState(137);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::Identifier)
      | (1ULL << asm_grammarParser::Hexnum)
      | (1ULL << asm_grammarParser::Integer)
      | (1ULL << asm_grammarParser::Octalnum))) != 0))) {
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

//----------------- Float_constContext ------------------------------------------------------------------

asm_grammarParser::Float_constContext::Float_constContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Float_constContext::FloatingPointLiteral() {
  return getToken(asm_grammarParser::FloatingPointLiteral, 0);
}


size_t asm_grammarParser::Float_constContext::getRuleIndex() const {
  return asm_grammarParser::RuleFloat_const;
}

void asm_grammarParser::Float_constContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat_const(this);
}

void asm_grammarParser::Float_constContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat_const(this);
}


std::any asm_grammarParser::Float_constContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFloat_const(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Float_constContext* asm_grammarParser::float_const() {
  Float_constContext *_localctx = _tracker.createInstance<Float_constContext>(_ctx, getState());
  enterRule(_localctx, 28, asm_grammarParser::RuleFloat_const);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(asm_grammarParser::FloatingPointLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Integer_constContext ------------------------------------------------------------------

asm_grammarParser::Integer_constContext::Integer_constContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Integer_constContext::Integer() {
  return getToken(asm_grammarParser::Integer, 0);
}

tree::TerminalNode* asm_grammarParser::Integer_constContext::Hexnum() {
  return getToken(asm_grammarParser::Hexnum, 0);
}

tree::TerminalNode* asm_grammarParser::Integer_constContext::Octalnum() {
  return getToken(asm_grammarParser::Octalnum, 0);
}


size_t asm_grammarParser::Integer_constContext::getRuleIndex() const {
  return asm_grammarParser::RuleInteger_const;
}

void asm_grammarParser::Integer_constContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInteger_const(this);
}

void asm_grammarParser::Integer_constContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInteger_const(this);
}


std::any asm_grammarParser::Integer_constContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitInteger_const(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Integer_constContext* asm_grammarParser::integer_const() {
  Integer_constContext *_localctx = _tracker.createInstance<Integer_constContext>(_ctx, getState());
  enterRule(_localctx, 30, asm_grammarParser::RuleInteger_const);
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
    setState(141);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::Hexnum)
      | (1ULL << asm_grammarParser::Integer)
      | (1ULL << asm_grammarParser::Octalnum))) != 0))) {
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

//----------------- Reg_opcodeContext ------------------------------------------------------------------

asm_grammarParser::Reg_opcodeContext::Reg_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Reg_opcodeContext::getRuleIndex() const {
  return asm_grammarParser::RuleReg_opcode;
}

void asm_grammarParser::Reg_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReg_opcode(this);
}

void asm_grammarParser::Reg_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReg_opcode(this);
}


std::any asm_grammarParser::Reg_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitReg_opcode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Reg_opcodeContext* asm_grammarParser::reg_opcode() {
  Reg_opcodeContext *_localctx = _tracker.createInstance<Reg_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 32, asm_grammarParser::RuleReg_opcode);
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
    setState(143);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::T__4)
      | (1ULL << asm_grammarParser::T__5)
      | (1ULL << asm_grammarParser::T__6)
      | (1ULL << asm_grammarParser::T__7)
      | (1ULL << asm_grammarParser::T__8)
      | (1ULL << asm_grammarParser::T__9)
      | (1ULL << asm_grammarParser::T__10)
      | (1ULL << asm_grammarParser::T__11)
      | (1ULL << asm_grammarParser::T__12)
      | (1ULL << asm_grammarParser::T__13)
      | (1ULL << asm_grammarParser::T__14))) != 0))) {
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

//----------------- Conv_opcodeContext ------------------------------------------------------------------

asm_grammarParser::Conv_opcodeContext::Conv_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Conv_opcodeContext::getRuleIndex() const {
  return asm_grammarParser::RuleConv_opcode;
}

void asm_grammarParser::Conv_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConv_opcode(this);
}

void asm_grammarParser::Conv_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConv_opcode(this);
}


std::any asm_grammarParser::Conv_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitConv_opcode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Conv_opcodeContext* asm_grammarParser::conv_opcode() {
  Conv_opcodeContext *_localctx = _tracker.createInstance<Conv_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 34, asm_grammarParser::RuleConv_opcode);
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
    setState(145);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::T__15)
      | (1ULL << asm_grammarParser::T__16)
      | (1ULL << asm_grammarParser::T__17)
      | (1ULL << asm_grammarParser::T__18)
      | (1ULL << asm_grammarParser::T__19)
      | (1ULL << asm_grammarParser::T__20))) != 0))) {
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

//----------------- Imm_opcodeContext ------------------------------------------------------------------

asm_grammarParser::Imm_opcodeContext::Imm_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Imm_opcodeContext::getRuleIndex() const {
  return asm_grammarParser::RuleImm_opcode;
}

void asm_grammarParser::Imm_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_opcode(this);
}

void asm_grammarParser::Imm_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_opcode(this);
}


std::any asm_grammarParser::Imm_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_opcode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Imm_opcodeContext* asm_grammarParser::imm_opcode() {
  Imm_opcodeContext *_localctx = _tracker.createInstance<Imm_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 36, asm_grammarParser::RuleImm_opcode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(asm_grammarParser::T__21);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Branch_opcodeContext ------------------------------------------------------------------

asm_grammarParser::Branch_opcodeContext::Branch_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Branch_opcodeContext::getRuleIndex() const {
  return asm_grammarParser::RuleBranch_opcode;
}

void asm_grammarParser::Branch_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBranch_opcode(this);
}

void asm_grammarParser::Branch_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBranch_opcode(this);
}


std::any asm_grammarParser::Branch_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitBranch_opcode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Branch_opcodeContext* asm_grammarParser::branch_opcode() {
  Branch_opcodeContext *_localctx = _tracker.createInstance<Branch_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 38, asm_grammarParser::RuleBranch_opcode);
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
    setState(149);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::T__22)
      | (1ULL << asm_grammarParser::T__23)
      | (1ULL << asm_grammarParser::T__24)
      | (1ULL << asm_grammarParser::T__25))) != 0))) {
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

//----------------- Pseudo_opcodeContext ------------------------------------------------------------------

asm_grammarParser::Pseudo_opcodeContext::Pseudo_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::Pseudo_opcodeContext::getRuleIndex() const {
  return asm_grammarParser::RulePseudo_opcode;
}

void asm_grammarParser::Pseudo_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudo_opcode(this);
}

void asm_grammarParser::Pseudo_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudo_opcode(this);
}


std::any asm_grammarParser::Pseudo_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitPseudo_opcode(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Pseudo_opcodeContext* asm_grammarParser::pseudo_opcode() {
  Pseudo_opcodeContext *_localctx = _tracker.createInstance<Pseudo_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 40, asm_grammarParser::RulePseudo_opcode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(asm_grammarParser::T__26);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_blockContext ------------------------------------------------------------------

asm_grammarParser::For_blockContext::For_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

asm_grammarParser::For_declContext* asm_grammarParser::For_blockContext::for_decl() {
  return getRuleContext<asm_grammarParser::For_declContext>(0);
}

asm_grammarParser::For_endContext* asm_grammarParser::For_blockContext::for_end() {
  return getRuleContext<asm_grammarParser::For_endContext>(0);
}

asm_grammarParser::CodeContext* asm_grammarParser::For_blockContext::code() {
  return getRuleContext<asm_grammarParser::CodeContext>(0);
}

asm_grammarParser::For_incrContext* asm_grammarParser::For_blockContext::for_incr() {
  return getRuleContext<asm_grammarParser::For_incrContext>(0);
}

asm_grammarParser::For_decContext* asm_grammarParser::For_blockContext::for_dec() {
  return getRuleContext<asm_grammarParser::For_decContext>(0);
}


size_t asm_grammarParser::For_blockContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_block;
}

void asm_grammarParser::For_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_block(this);
}

void asm_grammarParser::For_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_block(this);
}


std::any asm_grammarParser::For_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_block(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_blockContext* asm_grammarParser::for_block() {
  For_blockContext *_localctx = _tracker.createInstance<For_blockContext>(_ctx, getState());
  enterRule(_localctx, 42, asm_grammarParser::RuleFor_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    match(asm_grammarParser::T__27);
    setState(154);
    for_decl();
    setState(155);
    match(asm_grammarParser::T__28);
    setState(156);
    for_end();
    setState(157);
    match(asm_grammarParser::T__28);
    setState(160);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(158);
      for_incr();
      break;
    }

    case 2: {
      setState(159);
      for_dec();
      break;
    }

    default:
      break;
    }
    setState(162);
    match(asm_grammarParser::T__29);
    setState(163);
    match(asm_grammarParser::T__30);
    setState(164);
    code();
    setState(165);
    match(asm_grammarParser::T__31);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_incrContext ------------------------------------------------------------------

asm_grammarParser::For_incrContext::For_incrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::For_incrContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::For_incrContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_incr;
}

void asm_grammarParser::For_incrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_incr(this);
}

void asm_grammarParser::For_incrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_incr(this);
}


std::any asm_grammarParser::For_incrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_incr(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_incrContext* asm_grammarParser::for_incr() {
  For_incrContext *_localctx = _tracker.createInstance<For_incrContext>(_ctx, getState());
  enterRule(_localctx, 44, asm_grammarParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    match(asm_grammarParser::Identifier);

    setState(168);
    match(asm_grammarParser::T__32);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_decContext ------------------------------------------------------------------

asm_grammarParser::For_decContext::For_decContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::For_decContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::For_decContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_dec;
}

void asm_grammarParser::For_decContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_dec(this);
}

void asm_grammarParser::For_decContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_dec(this);
}


std::any asm_grammarParser::For_decContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_dec(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_decContext* asm_grammarParser::for_dec() {
  For_decContext *_localctx = _tracker.createInstance<For_decContext>(_ctx, getState());
  enterRule(_localctx, 46, asm_grammarParser::RuleFor_dec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(asm_grammarParser::Identifier);

    setState(171);
    match(asm_grammarParser::T__33);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_declContext ------------------------------------------------------------------

asm_grammarParser::For_declContext::For_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::For_declContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}

tree::TerminalNode* asm_grammarParser::For_declContext::Integer() {
  return getToken(asm_grammarParser::Integer, 0);
}


size_t asm_grammarParser::For_declContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_decl;
}

void asm_grammarParser::For_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_decl(this);
}

void asm_grammarParser::For_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_decl(this);
}


std::any asm_grammarParser::For_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_decl(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_declContext* asm_grammarParser::for_decl() {
  For_declContext *_localctx = _tracker.createInstance<For_declContext>(_ctx, getState());
  enterRule(_localctx, 48, asm_grammarParser::RuleFor_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(asm_grammarParser::Identifier);
    setState(174);
    match(asm_grammarParser::T__34);
    setState(175);
    match(asm_grammarParser::Integer);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_endContext ------------------------------------------------------------------

asm_grammarParser::For_endContext::For_endContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::For_endContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}

asm_grammarParser::For_end_comp_typeContext* asm_grammarParser::For_endContext::for_end_comp_type() {
  return getRuleContext<asm_grammarParser::For_end_comp_typeContext>(0);
}

tree::TerminalNode* asm_grammarParser::For_endContext::Integer() {
  return getToken(asm_grammarParser::Integer, 0);
}


size_t asm_grammarParser::For_endContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_end;
}

void asm_grammarParser::For_endContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_end(this);
}

void asm_grammarParser::For_endContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_end(this);
}


std::any asm_grammarParser::For_endContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_end(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_endContext* asm_grammarParser::for_end() {
  For_endContext *_localctx = _tracker.createInstance<For_endContext>(_ctx, getState());
  enterRule(_localctx, 50, asm_grammarParser::RuleFor_end);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(asm_grammarParser::Identifier);
    setState(178);
    for_end_comp_type();
    setState(179);
    match(asm_grammarParser::Integer);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_end_comp_typeContext ------------------------------------------------------------------

asm_grammarParser::For_end_comp_typeContext::For_end_comp_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t asm_grammarParser::For_end_comp_typeContext::getRuleIndex() const {
  return asm_grammarParser::RuleFor_end_comp_type;
}

void asm_grammarParser::For_end_comp_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_end_comp_type(this);
}

void asm_grammarParser::For_end_comp_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_end_comp_type(this);
}


std::any asm_grammarParser::For_end_comp_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_end_comp_type(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::For_end_comp_typeContext* asm_grammarParser::for_end_comp_type() {
  For_end_comp_typeContext *_localctx = _tracker.createInstance<For_end_comp_typeContext>(_ctx, getState());
  enterRule(_localctx, 52, asm_grammarParser::RuleFor_end_comp_type);
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
    setState(181);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << asm_grammarParser::T__35)
      | (1ULL << asm_grammarParser::T__36)
      | (1ULL << asm_grammarParser::T__37)
      | (1ULL << asm_grammarParser::T__38))) != 0))) {
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

//----------------- PragmaContext ------------------------------------------------------------------

asm_grammarParser::PragmaContext::PragmaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::PragmaContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::PragmaContext::getRuleIndex() const {
  return asm_grammarParser::RulePragma;
}

void asm_grammarParser::PragmaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPragma(this);
}

void asm_grammarParser::PragmaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPragma(this);
}


std::any asm_grammarParser::PragmaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitPragma(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::PragmaContext* asm_grammarParser::pragma() {
  PragmaContext *_localctx = _tracker.createInstance<PragmaContext>(_ctx, getState());
  enterRule(_localctx, 54, asm_grammarParser::RulePragma);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(asm_grammarParser::T__39);
    setState(184);
    match(asm_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

asm_grammarParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Variable_declContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::Variable_declContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::Variable_declContext::getRuleIndex() const {
  return asm_grammarParser::RuleVariable_decl;
}

void asm_grammarParser::Variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_decl(this);
}

void asm_grammarParser::Variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_decl(this);
}


std::any asm_grammarParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Variable_declContext* asm_grammarParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 56, asm_grammarParser::RuleVariable_decl);
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
    setState(186);
    match(asm_grammarParser::T__40);
    setState(187);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

//----------------- Constant_declContext ------------------------------------------------------------------

asm_grammarParser::Constant_declContext::Constant_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Constant_declContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::Constant_declContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::Constant_declContext::getRuleIndex() const {
  return asm_grammarParser::RuleConstant_decl;
}

void asm_grammarParser::Constant_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant_decl(this);
}

void asm_grammarParser::Constant_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant_decl(this);
}


std::any asm_grammarParser::Constant_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitConstant_decl(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Constant_declContext* asm_grammarParser::constant_decl() {
  Constant_declContext *_localctx = _tracker.createInstance<Constant_declContext>(_ctx, getState());
  enterRule(_localctx, 58, asm_grammarParser::RuleConstant_decl);
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
    setState(189);
    match(asm_grammarParser::T__41);
    setState(190);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

//----------------- Input_declContext ------------------------------------------------------------------

asm_grammarParser::Input_declContext::Input_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Input_declContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::Input_declContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::Input_declContext::getRuleIndex() const {
  return asm_grammarParser::RuleInput_decl;
}

void asm_grammarParser::Input_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInput_decl(this);
}

void asm_grammarParser::Input_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInput_decl(this);
}


std::any asm_grammarParser::Input_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitInput_decl(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Input_declContext* asm_grammarParser::input_decl() {
  Input_declContext *_localctx = _tracker.createInstance<Input_declContext>(_ctx, getState());
  enterRule(_localctx, 60, asm_grammarParser::RuleInput_decl);
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
    setState(192);
    match(asm_grammarParser::T__42);
    setState(193);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

//----------------- Output_declContext ------------------------------------------------------------------

asm_grammarParser::Output_declContext::Output_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* asm_grammarParser::Output_declContext::Register() {
  return getToken(asm_grammarParser::Register, 0);
}

tree::TerminalNode* asm_grammarParser::Output_declContext::Identifier() {
  return getToken(asm_grammarParser::Identifier, 0);
}


size_t asm_grammarParser::Output_declContext::getRuleIndex() const {
  return asm_grammarParser::RuleOutput_decl;
}

void asm_grammarParser::Output_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOutput_decl(this);
}

void asm_grammarParser::Output_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<asm_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOutput_decl(this);
}


std::any asm_grammarParser::Output_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<asm_grammarVisitor*>(visitor))
    return parserVisitor->visitOutput_decl(this);
  else
    return visitor->visitChildren(this);
}

asm_grammarParser::Output_declContext* asm_grammarParser::output_decl() {
  Output_declContext *_localctx = _tracker.createInstance<Output_declContext>(_ctx, getState());
  enterRule(_localctx, 62, asm_grammarParser::RuleOutput_decl);
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
    setState(195);
    match(asm_grammarParser::T__43);
    setState(196);
    _la = _input->LA(1);
    if (!(_la == asm_grammarParser::Register

    || _la == asm_grammarParser::Identifier)) {
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

void asm_grammarParser::initialize() {
  std::call_once(asm_grammarParserOnceFlag, asm_grammarParserInitialize);
}
