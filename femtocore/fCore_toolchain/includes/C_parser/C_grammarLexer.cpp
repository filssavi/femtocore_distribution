
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1


#include "C_grammarLexer.h"


using namespace antlr4;

using namespace C_parser;


using namespace antlr4;

namespace {

struct C_grammarLexerStaticData final {
  C_grammarLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  C_grammarLexerStaticData(const C_grammarLexerStaticData&) = delete;
  C_grammarLexerStaticData(C_grammarLexerStaticData&&) = delete;
  C_grammarLexerStaticData& operator=(const C_grammarLexerStaticData&) = delete;
  C_grammarLexerStaticData& operator=(C_grammarLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag c_grammarlexerLexerOnceFlag;
C_grammarLexerStaticData *c_grammarlexerLexerStaticData = nullptr;

void c_grammarlexerLexerInitialize() {
  assert(c_grammarlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<C_grammarLexerStaticData>(
    std::vector<std::string>{
      "Case", "Char", "Const", "Else", "Float", "For", "If", "Int", "Long", 
      "Return", "Short", "Signed", "Typedef", "Unsigned", "Void", "Volatile", 
      "While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", 
      "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", 
      "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", 
      "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
      "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
      "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", 
      "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IdentifierNondigit", 
      "Nondigit", "Digit", "UniversalCharacterName", "HexQuad", "IntegerConstant", 
      "BinaryConstant", "DecimalConstant", "OctalConstant", "HexadecimalConstant", 
      "HexadecimalPrefix", "NonzeroDigit", "OctalDigit", "HexadecimalDigit", 
      "IntegerSuffix", "UnsignedSuffix", "LongSuffix", "LongLongSuffix", 
      "FloatingConstant", "DecimalFloatingConstant", "HexadecimalFloatingConstant", 
      "FractionalConstant", "ExponentPart", "Sign", "DigitSequence", "HexadecimalFractionalConstant", 
      "BinaryExponentPart", "HexadecimalDigitSequence", "FloatingSuffix", 
      "CharacterConstant", "CCharSequence", "CChar", "EscapeSequence", "SimpleEscapeSequence", 
      "OctalEscapeSequence", "HexadecimalEscapeSequence", "StringLiteral", 
      "EncodingPrefix", "SCharSequence", "SChar", "ComplexDefine", "IncludeDirective", 
      "AsmBlock", "LineAfterPreprocessing", "LineDirective", "PragmaDirective", 
      "Whitespace", "Newline", "BlockComment", "LineComment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'case'", "'char'", "'const'", "'else'", "'float'", "'for'", "'if'", 
      "'int'", "'long'", "'return'", "'short'", "'signed'", "'typedef'", 
      "'unsigned'", "'void'", "'volatile'", "'while'", "'('", "')'", "'['", 
      "']'", "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", "'<<'", "'>>'", 
      "'+'", "'++'", "'-'", "'--'", "'*'", "'/'", "'%'", "'&'", "'|'", "'&&'", 
      "'||'", "'^'", "'!'", "'~'", "'\\u003F'", "':'", "';'", "','", "'='", 
      "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'&='", 
      "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
    },
    std::vector<std::string>{
      "", "Case", "Char", "Const", "Else", "Float", "For", "If", "Int", 
      "Long", "Return", "Short", "Signed", "Typedef", "Unsigned", "Void", 
      "Volatile", "While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", 
      "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", 
      "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", 
      "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
      "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
      "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", 
      "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "CharacterConstant", "StringLiteral", 
      "ComplexDefine", "IncludeDirective", "AsmBlock", "LineAfterPreprocessing", 
      "LineDirective", "PragmaDirective", "Whitespace", "Newline", "BlockComment", 
      "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,79,894,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,
  	7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,
  	7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,
  	7,84,2,85,7,85,2,86,7,86,2,87,7,87,2,88,7,88,2,89,7,89,2,90,7,90,2,91,
  	7,91,2,92,7,92,2,93,7,93,2,94,7,94,2,95,7,95,2,96,7,96,2,97,7,97,2,98,
  	7,98,2,99,7,99,2,100,7,100,2,101,7,101,2,102,7,102,2,103,7,103,2,104,
  	7,104,2,105,7,105,2,106,7,106,2,107,7,107,2,108,7,108,2,109,7,109,2,110,
  	7,110,2,111,7,111,2,112,7,112,2,113,7,113,1,0,1,0,1,0,1,0,1,0,1,1,1,1,
  	1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,
  	4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,
  	1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,
  	23,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,
  	28,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,32,1,32,1,32,1,33,1,33,1,34,1,
  	34,1,35,1,35,1,36,1,36,1,37,1,37,1,38,1,38,1,38,1,39,1,39,1,39,1,40,1,
  	40,1,41,1,41,1,42,1,42,1,43,1,43,1,44,1,44,1,45,1,45,1,46,1,46,1,47,1,
  	47,1,48,1,48,1,48,1,49,1,49,1,49,1,50,1,50,1,50,1,51,1,51,1,51,1,52,1,
  	52,1,52,1,53,1,53,1,53,1,53,1,54,1,54,1,54,1,54,1,55,1,55,1,55,1,56,1,
  	56,1,56,1,57,1,57,1,57,1,58,1,58,1,58,1,59,1,59,1,59,1,60,1,60,1,60,1,
  	61,1,61,1,62,1,62,1,62,1,62,1,63,1,63,1,63,5,63,450,8,63,10,63,12,63,
  	453,9,63,1,64,1,64,3,64,457,8,64,1,65,1,65,1,66,1,66,1,67,1,67,1,67,1,
  	67,1,67,1,67,1,67,1,67,1,67,1,67,3,67,473,8,67,1,68,1,68,1,68,1,68,1,
  	68,1,69,1,69,3,69,482,8,69,1,69,1,69,3,69,486,8,69,1,69,1,69,3,69,490,
  	8,69,1,69,3,69,493,8,69,1,70,1,70,1,70,4,70,498,8,70,11,70,12,70,499,
  	1,71,1,71,5,71,504,8,71,10,71,12,71,507,9,71,1,72,1,72,5,72,511,8,72,
  	10,72,12,72,514,9,72,1,73,1,73,4,73,518,8,73,11,73,12,73,519,1,74,1,74,
  	1,74,1,75,1,75,1,76,1,76,1,77,1,77,1,78,1,78,3,78,533,8,78,1,78,1,78,
  	1,78,1,78,1,78,3,78,540,8,78,1,78,1,78,3,78,544,8,78,3,78,546,8,78,1,
  	79,1,79,1,80,1,80,1,81,1,81,1,81,1,81,3,81,556,8,81,1,82,1,82,3,82,560,
  	8,82,1,83,1,83,3,83,564,8,83,1,83,3,83,567,8,83,1,83,1,83,1,83,3,83,572,
  	8,83,3,83,574,8,83,1,84,1,84,1,84,3,84,579,8,84,1,84,1,84,3,84,583,8,
  	84,1,85,3,85,586,8,85,1,85,1,85,1,85,1,85,1,85,3,85,593,8,85,1,86,1,86,
  	3,86,597,8,86,1,86,1,86,1,87,1,87,1,88,4,88,604,8,88,11,88,12,88,605,
  	1,89,3,89,609,8,89,1,89,1,89,1,89,1,89,1,89,3,89,616,8,89,1,90,1,90,3,
  	90,620,8,90,1,90,1,90,1,91,4,91,625,8,91,11,91,12,91,626,1,92,1,92,1,
  	93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,1,
  	93,1,93,1,93,1,93,1,93,1,93,1,93,1,93,3,93,653,8,93,1,94,4,94,656,8,94,
  	11,94,12,94,657,1,95,1,95,3,95,662,8,95,1,96,1,96,1,96,1,96,3,96,668,
  	8,96,1,97,1,97,1,97,1,98,1,98,1,98,3,98,676,8,98,1,98,3,98,679,8,98,1,
  	99,1,99,1,99,1,99,4,99,685,8,99,11,99,12,99,686,1,100,3,100,690,8,100,
  	1,100,1,100,3,100,694,8,100,1,100,1,100,1,101,1,101,1,101,3,101,701,8,
  	101,1,102,4,102,704,8,102,11,102,12,102,705,1,103,1,103,1,103,1,103,1,
  	103,1,103,1,103,3,103,715,8,103,1,104,1,104,3,104,719,8,104,1,104,1,104,
  	1,104,1,104,1,104,1,104,1,104,1,104,5,104,729,8,104,10,104,12,104,732,
  	9,104,1,104,1,104,1,105,1,105,3,105,738,8,105,1,105,1,105,1,105,1,105,
  	1,105,1,105,1,105,1,105,1,105,3,105,749,8,105,1,105,1,105,5,105,753,8,
  	105,10,105,12,105,756,9,105,1,105,1,105,1,105,5,105,761,8,105,10,105,
  	12,105,764,9,105,1,105,3,105,767,8,105,1,105,3,105,770,8,105,1,105,1,
  	105,1,105,1,105,1,106,1,106,1,106,1,106,1,106,5,106,781,8,106,10,106,
  	12,106,784,9,106,1,106,1,106,5,106,788,8,106,10,106,12,106,791,9,106,
  	1,106,1,106,1,106,1,106,1,107,1,107,1,107,1,107,1,107,1,107,1,107,5,107,
  	804,8,107,10,107,12,107,807,9,107,1,107,5,107,810,8,107,10,107,12,107,
  	813,9,107,1,107,1,107,1,108,1,108,3,108,819,8,108,1,108,1,108,3,108,823,
  	8,108,1,108,1,108,5,108,827,8,108,10,108,12,108,830,9,108,1,108,1,108,
  	1,109,1,109,3,109,836,8,109,1,109,1,109,1,109,1,109,1,109,1,109,1,109,
  	1,109,1,109,5,109,847,8,109,10,109,12,109,850,9,109,1,109,1,109,1,110,
  	4,110,855,8,110,11,110,12,110,856,1,110,1,110,1,111,1,111,3,111,863,8,
  	111,1,111,3,111,866,8,111,1,111,1,111,1,112,1,112,1,112,1,112,5,112,874,
  	8,112,10,112,12,112,877,9,112,1,112,1,112,1,112,1,112,1,112,1,113,1,113,
  	1,113,1,113,5,113,888,8,113,10,113,12,113,891,9,113,1,113,1,113,1,875,
  	0,114,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,
  	27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,
  	25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,
  	73,37,75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,
  	48,97,49,99,50,101,51,103,52,105,53,107,54,109,55,111,56,113,57,115,58,
  	117,59,119,60,121,61,123,62,125,63,127,64,129,0,131,0,133,0,135,0,137,
  	0,139,65,141,0,143,0,145,0,147,0,149,0,151,0,153,0,155,0,157,0,159,0,
  	161,0,163,0,165,66,167,0,169,0,171,0,173,0,175,0,177,67,179,0,181,0,183,
  	0,185,0,187,68,189,0,191,0,193,0,195,0,197,0,199,0,201,69,203,0,205,0,
  	207,0,209,70,211,71,213,72,215,73,217,74,219,75,221,76,223,77,225,78,
  	227,79,1,0,23,3,0,65,90,95,95,97,122,1,0,48,57,2,0,66,66,98,98,1,0,48,
  	49,2,0,88,88,120,120,1,0,49,57,1,0,48,55,3,0,48,57,65,70,97,102,2,0,85,
  	85,117,117,2,0,76,76,108,108,2,0,69,69,101,101,2,0,43,43,45,45,2,0,80,
  	80,112,112,4,0,70,70,76,76,102,102,108,108,4,0,10,10,13,13,39,39,92,92,
  	10,0,34,34,39,39,63,63,92,92,97,98,102,102,110,110,114,114,116,116,118,
  	118,3,0,76,76,85,85,117,117,4,0,10,10,13,13,34,34,92,92,3,0,10,10,13,
  	13,35,35,2,0,10,10,13,13,1,0,123,123,1,0,125,125,2,0,9,9,32,32,934,0,
  	1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
  	0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,
  	23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,
  	0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,
  	0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,
  	55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,
  	0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,
  	0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,
  	87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,
  	0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,0,0,105,1,0,0,0,0,107,1,
  	0,0,0,0,109,1,0,0,0,0,111,1,0,0,0,0,113,1,0,0,0,0,115,1,0,0,0,0,117,1,
  	0,0,0,0,119,1,0,0,0,0,121,1,0,0,0,0,123,1,0,0,0,0,125,1,0,0,0,0,127,1,
  	0,0,0,0,139,1,0,0,0,0,165,1,0,0,0,0,177,1,0,0,0,0,187,1,0,0,0,0,201,1,
  	0,0,0,0,209,1,0,0,0,0,211,1,0,0,0,0,213,1,0,0,0,0,215,1,0,0,0,0,217,1,
  	0,0,0,0,219,1,0,0,0,0,221,1,0,0,0,0,223,1,0,0,0,0,225,1,0,0,0,0,227,1,
  	0,0,0,1,229,1,0,0,0,3,234,1,0,0,0,5,239,1,0,0,0,7,245,1,0,0,0,9,250,1,
  	0,0,0,11,256,1,0,0,0,13,260,1,0,0,0,15,263,1,0,0,0,17,267,1,0,0,0,19,
  	272,1,0,0,0,21,279,1,0,0,0,23,285,1,0,0,0,25,292,1,0,0,0,27,300,1,0,0,
  	0,29,309,1,0,0,0,31,314,1,0,0,0,33,323,1,0,0,0,35,329,1,0,0,0,37,331,
  	1,0,0,0,39,333,1,0,0,0,41,335,1,0,0,0,43,337,1,0,0,0,45,339,1,0,0,0,47,
  	341,1,0,0,0,49,343,1,0,0,0,51,346,1,0,0,0,53,348,1,0,0,0,55,351,1,0,0,
  	0,57,354,1,0,0,0,59,357,1,0,0,0,61,359,1,0,0,0,63,362,1,0,0,0,65,364,
  	1,0,0,0,67,367,1,0,0,0,69,369,1,0,0,0,71,371,1,0,0,0,73,373,1,0,0,0,75,
  	375,1,0,0,0,77,377,1,0,0,0,79,380,1,0,0,0,81,383,1,0,0,0,83,385,1,0,0,
  	0,85,387,1,0,0,0,87,389,1,0,0,0,89,391,1,0,0,0,91,393,1,0,0,0,93,395,
  	1,0,0,0,95,397,1,0,0,0,97,399,1,0,0,0,99,402,1,0,0,0,101,405,1,0,0,0,
  	103,408,1,0,0,0,105,411,1,0,0,0,107,414,1,0,0,0,109,418,1,0,0,0,111,422,
  	1,0,0,0,113,425,1,0,0,0,115,428,1,0,0,0,117,431,1,0,0,0,119,434,1,0,0,
  	0,121,437,1,0,0,0,123,440,1,0,0,0,125,442,1,0,0,0,127,446,1,0,0,0,129,
  	456,1,0,0,0,131,458,1,0,0,0,133,460,1,0,0,0,135,472,1,0,0,0,137,474,1,
  	0,0,0,139,492,1,0,0,0,141,494,1,0,0,0,143,501,1,0,0,0,145,508,1,0,0,0,
  	147,515,1,0,0,0,149,521,1,0,0,0,151,524,1,0,0,0,153,526,1,0,0,0,155,528,
  	1,0,0,0,157,545,1,0,0,0,159,547,1,0,0,0,161,549,1,0,0,0,163,555,1,0,0,
  	0,165,559,1,0,0,0,167,573,1,0,0,0,169,575,1,0,0,0,171,592,1,0,0,0,173,
  	594,1,0,0,0,175,600,1,0,0,0,177,603,1,0,0,0,179,615,1,0,0,0,181,617,1,
  	0,0,0,183,624,1,0,0,0,185,628,1,0,0,0,187,652,1,0,0,0,189,655,1,0,0,0,
  	191,661,1,0,0,0,193,667,1,0,0,0,195,669,1,0,0,0,197,672,1,0,0,0,199,680,
  	1,0,0,0,201,689,1,0,0,0,203,700,1,0,0,0,205,703,1,0,0,0,207,714,1,0,0,
  	0,209,716,1,0,0,0,211,735,1,0,0,0,213,775,1,0,0,0,215,796,1,0,0,0,217,
  	816,1,0,0,0,219,833,1,0,0,0,221,854,1,0,0,0,223,865,1,0,0,0,225,869,1,
  	0,0,0,227,883,1,0,0,0,229,230,5,99,0,0,230,231,5,97,0,0,231,232,5,115,
  	0,0,232,233,5,101,0,0,233,2,1,0,0,0,234,235,5,99,0,0,235,236,5,104,0,
  	0,236,237,5,97,0,0,237,238,5,114,0,0,238,4,1,0,0,0,239,240,5,99,0,0,240,
  	241,5,111,0,0,241,242,5,110,0,0,242,243,5,115,0,0,243,244,5,116,0,0,244,
  	6,1,0,0,0,245,246,5,101,0,0,246,247,5,108,0,0,247,248,5,115,0,0,248,249,
  	5,101,0,0,249,8,1,0,0,0,250,251,5,102,0,0,251,252,5,108,0,0,252,253,5,
  	111,0,0,253,254,5,97,0,0,254,255,5,116,0,0,255,10,1,0,0,0,256,257,5,102,
  	0,0,257,258,5,111,0,0,258,259,5,114,0,0,259,12,1,0,0,0,260,261,5,105,
  	0,0,261,262,5,102,0,0,262,14,1,0,0,0,263,264,5,105,0,0,264,265,5,110,
  	0,0,265,266,5,116,0,0,266,16,1,0,0,0,267,268,5,108,0,0,268,269,5,111,
  	0,0,269,270,5,110,0,0,270,271,5,103,0,0,271,18,1,0,0,0,272,273,5,114,
  	0,0,273,274,5,101,0,0,274,275,5,116,0,0,275,276,5,117,0,0,276,277,5,114,
  	0,0,277,278,5,110,0,0,278,20,1,0,0,0,279,280,5,115,0,0,280,281,5,104,
  	0,0,281,282,5,111,0,0,282,283,5,114,0,0,283,284,5,116,0,0,284,22,1,0,
  	0,0,285,286,5,115,0,0,286,287,5,105,0,0,287,288,5,103,0,0,288,289,5,110,
  	0,0,289,290,5,101,0,0,290,291,5,100,0,0,291,24,1,0,0,0,292,293,5,116,
  	0,0,293,294,5,121,0,0,294,295,5,112,0,0,295,296,5,101,0,0,296,297,5,100,
  	0,0,297,298,5,101,0,0,298,299,5,102,0,0,299,26,1,0,0,0,300,301,5,117,
  	0,0,301,302,5,110,0,0,302,303,5,115,0,0,303,304,5,105,0,0,304,305,5,103,
  	0,0,305,306,5,110,0,0,306,307,5,101,0,0,307,308,5,100,0,0,308,28,1,0,
  	0,0,309,310,5,118,0,0,310,311,5,111,0,0,311,312,5,105,0,0,312,313,5,100,
  	0,0,313,30,1,0,0,0,314,315,5,118,0,0,315,316,5,111,0,0,316,317,5,108,
  	0,0,317,318,5,97,0,0,318,319,5,116,0,0,319,320,5,105,0,0,320,321,5,108,
  	0,0,321,322,5,101,0,0,322,32,1,0,0,0,323,324,5,119,0,0,324,325,5,104,
  	0,0,325,326,5,105,0,0,326,327,5,108,0,0,327,328,5,101,0,0,328,34,1,0,
  	0,0,329,330,5,40,0,0,330,36,1,0,0,0,331,332,5,41,0,0,332,38,1,0,0,0,333,
  	334,5,91,0,0,334,40,1,0,0,0,335,336,5,93,0,0,336,42,1,0,0,0,337,338,5,
  	123,0,0,338,44,1,0,0,0,339,340,5,125,0,0,340,46,1,0,0,0,341,342,5,60,
  	0,0,342,48,1,0,0,0,343,344,5,60,0,0,344,345,5,61,0,0,345,50,1,0,0,0,346,
  	347,5,62,0,0,347,52,1,0,0,0,348,349,5,62,0,0,349,350,5,61,0,0,350,54,
  	1,0,0,0,351,352,5,60,0,0,352,353,5,60,0,0,353,56,1,0,0,0,354,355,5,62,
  	0,0,355,356,5,62,0,0,356,58,1,0,0,0,357,358,5,43,0,0,358,60,1,0,0,0,359,
  	360,5,43,0,0,360,361,5,43,0,0,361,62,1,0,0,0,362,363,5,45,0,0,363,64,
  	1,0,0,0,364,365,5,45,0,0,365,366,5,45,0,0,366,66,1,0,0,0,367,368,5,42,
  	0,0,368,68,1,0,0,0,369,370,5,47,0,0,370,70,1,0,0,0,371,372,5,37,0,0,372,
  	72,1,0,0,0,373,374,5,38,0,0,374,74,1,0,0,0,375,376,5,124,0,0,376,76,1,
  	0,0,0,377,378,5,38,0,0,378,379,5,38,0,0,379,78,1,0,0,0,380,381,5,124,
  	0,0,381,382,5,124,0,0,382,80,1,0,0,0,383,384,5,94,0,0,384,82,1,0,0,0,
  	385,386,5,33,0,0,386,84,1,0,0,0,387,388,5,126,0,0,388,86,1,0,0,0,389,
  	390,5,63,0,0,390,88,1,0,0,0,391,392,5,58,0,0,392,90,1,0,0,0,393,394,5,
  	59,0,0,394,92,1,0,0,0,395,396,5,44,0,0,396,94,1,0,0,0,397,398,5,61,0,
  	0,398,96,1,0,0,0,399,400,5,42,0,0,400,401,5,61,0,0,401,98,1,0,0,0,402,
  	403,5,47,0,0,403,404,5,61,0,0,404,100,1,0,0,0,405,406,5,37,0,0,406,407,
  	5,61,0,0,407,102,1,0,0,0,408,409,5,43,0,0,409,410,5,61,0,0,410,104,1,
  	0,0,0,411,412,5,45,0,0,412,413,5,61,0,0,413,106,1,0,0,0,414,415,5,60,
  	0,0,415,416,5,60,0,0,416,417,5,61,0,0,417,108,1,0,0,0,418,419,5,62,0,
  	0,419,420,5,62,0,0,420,421,5,61,0,0,421,110,1,0,0,0,422,423,5,38,0,0,
  	423,424,5,61,0,0,424,112,1,0,0,0,425,426,5,94,0,0,426,427,5,61,0,0,427,
  	114,1,0,0,0,428,429,5,124,0,0,429,430,5,61,0,0,430,116,1,0,0,0,431,432,
  	5,61,0,0,432,433,5,61,0,0,433,118,1,0,0,0,434,435,5,33,0,0,435,436,5,
  	61,0,0,436,120,1,0,0,0,437,438,5,45,0,0,438,439,5,62,0,0,439,122,1,0,
  	0,0,440,441,5,46,0,0,441,124,1,0,0,0,442,443,5,46,0,0,443,444,5,46,0,
  	0,444,445,5,46,0,0,445,126,1,0,0,0,446,451,3,129,64,0,447,450,3,129,64,
  	0,448,450,3,133,66,0,449,447,1,0,0,0,449,448,1,0,0,0,450,453,1,0,0,0,
  	451,449,1,0,0,0,451,452,1,0,0,0,452,128,1,0,0,0,453,451,1,0,0,0,454,457,
  	3,131,65,0,455,457,3,135,67,0,456,454,1,0,0,0,456,455,1,0,0,0,457,130,
  	1,0,0,0,458,459,7,0,0,0,459,132,1,0,0,0,460,461,7,1,0,0,461,134,1,0,0,
  	0,462,463,5,92,0,0,463,464,5,117,0,0,464,465,1,0,0,0,465,473,3,137,68,
  	0,466,467,5,92,0,0,467,468,5,85,0,0,468,469,1,0,0,0,469,470,3,137,68,
  	0,470,471,3,137,68,0,471,473,1,0,0,0,472,462,1,0,0,0,472,466,1,0,0,0,
  	473,136,1,0,0,0,474,475,3,155,77,0,475,476,3,155,77,0,476,477,3,155,77,
  	0,477,478,3,155,77,0,478,138,1,0,0,0,479,481,3,143,71,0,480,482,3,157,
  	78,0,481,480,1,0,0,0,481,482,1,0,0,0,482,493,1,0,0,0,483,485,3,145,72,
  	0,484,486,3,157,78,0,485,484,1,0,0,0,485,486,1,0,0,0,486,493,1,0,0,0,
  	487,489,3,147,73,0,488,490,3,157,78,0,489,488,1,0,0,0,489,490,1,0,0,0,
  	490,493,1,0,0,0,491,493,3,141,70,0,492,479,1,0,0,0,492,483,1,0,0,0,492,
  	487,1,0,0,0,492,491,1,0,0,0,493,140,1,0,0,0,494,495,5,48,0,0,495,497,
  	7,2,0,0,496,498,7,3,0,0,497,496,1,0,0,0,498,499,1,0,0,0,499,497,1,0,0,
  	0,499,500,1,0,0,0,500,142,1,0,0,0,501,505,3,151,75,0,502,504,3,133,66,
  	0,503,502,1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,505,506,1,0,0,0,506,
  	144,1,0,0,0,507,505,1,0,0,0,508,512,5,48,0,0,509,511,3,153,76,0,510,509,
  	1,0,0,0,511,514,1,0,0,0,512,510,1,0,0,0,512,513,1,0,0,0,513,146,1,0,0,
  	0,514,512,1,0,0,0,515,517,3,149,74,0,516,518,3,155,77,0,517,516,1,0,0,
  	0,518,519,1,0,0,0,519,517,1,0,0,0,519,520,1,0,0,0,520,148,1,0,0,0,521,
  	522,5,48,0,0,522,523,7,4,0,0,523,150,1,0,0,0,524,525,7,5,0,0,525,152,
  	1,0,0,0,526,527,7,6,0,0,527,154,1,0,0,0,528,529,7,7,0,0,529,156,1,0,0,
  	0,530,532,3,159,79,0,531,533,3,161,80,0,532,531,1,0,0,0,532,533,1,0,0,
  	0,533,546,1,0,0,0,534,535,3,159,79,0,535,536,3,163,81,0,536,546,1,0,0,
  	0,537,539,3,161,80,0,538,540,3,159,79,0,539,538,1,0,0,0,539,540,1,0,0,
  	0,540,546,1,0,0,0,541,543,3,163,81,0,542,544,3,159,79,0,543,542,1,0,0,
  	0,543,544,1,0,0,0,544,546,1,0,0,0,545,530,1,0,0,0,545,534,1,0,0,0,545,
  	537,1,0,0,0,545,541,1,0,0,0,546,158,1,0,0,0,547,548,7,8,0,0,548,160,1,
  	0,0,0,549,550,7,9,0,0,550,162,1,0,0,0,551,552,5,108,0,0,552,556,5,108,
  	0,0,553,554,5,76,0,0,554,556,5,76,0,0,555,551,1,0,0,0,555,553,1,0,0,0,
  	556,164,1,0,0,0,557,560,3,167,83,0,558,560,3,169,84,0,559,557,1,0,0,0,
  	559,558,1,0,0,0,560,166,1,0,0,0,561,563,3,171,85,0,562,564,3,173,86,0,
  	563,562,1,0,0,0,563,564,1,0,0,0,564,566,1,0,0,0,565,567,3,185,92,0,566,
  	565,1,0,0,0,566,567,1,0,0,0,567,574,1,0,0,0,568,569,3,177,88,0,569,571,
  	3,173,86,0,570,572,3,185,92,0,571,570,1,0,0,0,571,572,1,0,0,0,572,574,
  	1,0,0,0,573,561,1,0,0,0,573,568,1,0,0,0,574,168,1,0,0,0,575,578,3,149,
  	74,0,576,579,3,179,89,0,577,579,3,183,91,0,578,576,1,0,0,0,578,577,1,
  	0,0,0,579,580,1,0,0,0,580,582,3,181,90,0,581,583,3,185,92,0,582,581,1,
  	0,0,0,582,583,1,0,0,0,583,170,1,0,0,0,584,586,3,177,88,0,585,584,1,0,
  	0,0,585,586,1,0,0,0,586,587,1,0,0,0,587,588,5,46,0,0,588,593,3,177,88,
  	0,589,590,3,177,88,0,590,591,5,46,0,0,591,593,1,0,0,0,592,585,1,0,0,0,
  	592,589,1,0,0,0,593,172,1,0,0,0,594,596,7,10,0,0,595,597,3,175,87,0,596,
  	595,1,0,0,0,596,597,1,0,0,0,597,598,1,0,0,0,598,599,3,177,88,0,599,174,
  	1,0,0,0,600,601,7,11,0,0,601,176,1,0,0,0,602,604,3,133,66,0,603,602,1,
  	0,0,0,604,605,1,0,0,0,605,603,1,0,0,0,605,606,1,0,0,0,606,178,1,0,0,0,
  	607,609,3,183,91,0,608,607,1,0,0,0,608,609,1,0,0,0,609,610,1,0,0,0,610,
  	611,5,46,0,0,611,616,3,183,91,0,612,613,3,183,91,0,613,614,5,46,0,0,614,
  	616,1,0,0,0,615,608,1,0,0,0,615,612,1,0,0,0,616,180,1,0,0,0,617,619,7,
  	12,0,0,618,620,3,175,87,0,619,618,1,0,0,0,619,620,1,0,0,0,620,621,1,0,
  	0,0,621,622,3,177,88,0,622,182,1,0,0,0,623,625,3,155,77,0,624,623,1,0,
  	0,0,625,626,1,0,0,0,626,624,1,0,0,0,626,627,1,0,0,0,627,184,1,0,0,0,628,
  	629,7,13,0,0,629,186,1,0,0,0,630,631,5,39,0,0,631,632,3,189,94,0,632,
  	633,5,39,0,0,633,653,1,0,0,0,634,635,5,76,0,0,635,636,5,39,0,0,636,637,
  	1,0,0,0,637,638,3,189,94,0,638,639,5,39,0,0,639,653,1,0,0,0,640,641,5,
  	117,0,0,641,642,5,39,0,0,642,643,1,0,0,0,643,644,3,189,94,0,644,645,5,
  	39,0,0,645,653,1,0,0,0,646,647,5,85,0,0,647,648,5,39,0,0,648,649,1,0,
  	0,0,649,650,3,189,94,0,650,651,5,39,0,0,651,653,1,0,0,0,652,630,1,0,0,
  	0,652,634,1,0,0,0,652,640,1,0,0,0,652,646,1,0,0,0,653,188,1,0,0,0,654,
  	656,3,191,95,0,655,654,1,0,0,0,656,657,1,0,0,0,657,655,1,0,0,0,657,658,
  	1,0,0,0,658,190,1,0,0,0,659,662,8,14,0,0,660,662,3,193,96,0,661,659,1,
  	0,0,0,661,660,1,0,0,0,662,192,1,0,0,0,663,668,3,195,97,0,664,668,3,197,
  	98,0,665,668,3,199,99,0,666,668,3,135,67,0,667,663,1,0,0,0,667,664,1,
  	0,0,0,667,665,1,0,0,0,667,666,1,0,0,0,668,194,1,0,0,0,669,670,5,92,0,
  	0,670,671,7,15,0,0,671,196,1,0,0,0,672,673,5,92,0,0,673,675,3,153,76,
  	0,674,676,3,153,76,0,675,674,1,0,0,0,675,676,1,0,0,0,676,678,1,0,0,0,
  	677,679,3,153,76,0,678,677,1,0,0,0,678,679,1,0,0,0,679,198,1,0,0,0,680,
  	681,5,92,0,0,681,682,5,120,0,0,682,684,1,0,0,0,683,685,3,155,77,0,684,
  	683,1,0,0,0,685,686,1,0,0,0,686,684,1,0,0,0,686,687,1,0,0,0,687,200,1,
  	0,0,0,688,690,3,203,101,0,689,688,1,0,0,0,689,690,1,0,0,0,690,691,1,0,
  	0,0,691,693,5,34,0,0,692,694,3,205,102,0,693,692,1,0,0,0,693,694,1,0,
  	0,0,694,695,1,0,0,0,695,696,5,34,0,0,696,202,1,0,0,0,697,698,5,117,0,
  	0,698,701,5,56,0,0,699,701,7,16,0,0,700,697,1,0,0,0,700,699,1,0,0,0,701,
  	204,1,0,0,0,702,704,3,207,103,0,703,702,1,0,0,0,704,705,1,0,0,0,705,703,
  	1,0,0,0,705,706,1,0,0,0,706,206,1,0,0,0,707,715,8,17,0,0,708,715,3,193,
  	96,0,709,710,5,92,0,0,710,715,5,10,0,0,711,712,5,92,0,0,712,713,5,13,
  	0,0,713,715,5,10,0,0,714,707,1,0,0,0,714,708,1,0,0,0,714,709,1,0,0,0,
  	714,711,1,0,0,0,715,208,1,0,0,0,716,718,5,35,0,0,717,719,3,221,110,0,
  	718,717,1,0,0,0,718,719,1,0,0,0,719,720,1,0,0,0,720,721,5,100,0,0,721,
  	722,5,101,0,0,722,723,5,102,0,0,723,724,5,105,0,0,724,725,5,110,0,0,725,
  	726,5,101,0,0,726,730,1,0,0,0,727,729,8,18,0,0,728,727,1,0,0,0,729,732,
  	1,0,0,0,730,728,1,0,0,0,730,731,1,0,0,0,731,733,1,0,0,0,732,730,1,0,0,
  	0,733,734,6,104,0,0,734,210,1,0,0,0,735,737,5,35,0,0,736,738,3,221,110,
  	0,737,736,1,0,0,0,737,738,1,0,0,0,738,739,1,0,0,0,739,740,5,105,0,0,740,
  	741,5,110,0,0,741,742,5,99,0,0,742,743,5,108,0,0,743,744,5,117,0,0,744,
  	745,5,100,0,0,745,746,5,101,0,0,746,748,1,0,0,0,747,749,3,221,110,0,748,
  	747,1,0,0,0,748,749,1,0,0,0,749,766,1,0,0,0,750,754,5,34,0,0,751,753,
  	8,19,0,0,752,751,1,0,0,0,753,756,1,0,0,0,754,752,1,0,0,0,754,755,1,0,
  	0,0,755,757,1,0,0,0,756,754,1,0,0,0,757,767,5,34,0,0,758,762,5,60,0,0,
  	759,761,8,19,0,0,760,759,1,0,0,0,761,764,1,0,0,0,762,760,1,0,0,0,762,
  	763,1,0,0,0,763,765,1,0,0,0,764,762,1,0,0,0,765,767,5,62,0,0,766,750,
  	1,0,0,0,766,758,1,0,0,0,767,769,1,0,0,0,768,770,3,221,110,0,769,768,1,
  	0,0,0,769,770,1,0,0,0,770,771,1,0,0,0,771,772,3,223,111,0,772,773,1,0,
  	0,0,773,774,6,105,0,0,774,212,1,0,0,0,775,776,5,97,0,0,776,777,5,115,
  	0,0,777,778,5,109,0,0,778,782,1,0,0,0,779,781,8,20,0,0,780,779,1,0,0,
  	0,781,784,1,0,0,0,782,780,1,0,0,0,782,783,1,0,0,0,783,785,1,0,0,0,784,
  	782,1,0,0,0,785,789,5,123,0,0,786,788,8,21,0,0,787,786,1,0,0,0,788,791,
  	1,0,0,0,789,787,1,0,0,0,789,790,1,0,0,0,790,792,1,0,0,0,791,789,1,0,0,
  	0,792,793,5,125,0,0,793,794,1,0,0,0,794,795,6,106,0,0,795,214,1,0,0,0,
  	796,797,5,35,0,0,797,798,5,108,0,0,798,799,5,105,0,0,799,800,5,110,0,
  	0,800,801,5,101,0,0,801,805,1,0,0,0,802,804,3,221,110,0,803,802,1,0,0,
  	0,804,807,1,0,0,0,805,803,1,0,0,0,805,806,1,0,0,0,806,811,1,0,0,0,807,
  	805,1,0,0,0,808,810,8,19,0,0,809,808,1,0,0,0,810,813,1,0,0,0,811,809,
  	1,0,0,0,811,812,1,0,0,0,812,814,1,0,0,0,813,811,1,0,0,0,814,815,6,107,
  	0,0,815,216,1,0,0,0,816,818,5,35,0,0,817,819,3,221,110,0,818,817,1,0,
  	0,0,818,819,1,0,0,0,819,820,1,0,0,0,820,822,3,143,71,0,821,823,3,221,
  	110,0,822,821,1,0,0,0,822,823,1,0,0,0,823,824,1,0,0,0,824,828,3,201,100,
  	0,825,827,8,19,0,0,826,825,1,0,0,0,827,830,1,0,0,0,828,826,1,0,0,0,828,
  	829,1,0,0,0,829,831,1,0,0,0,830,828,1,0,0,0,831,832,6,108,0,0,832,218,
  	1,0,0,0,833,835,5,35,0,0,834,836,3,221,110,0,835,834,1,0,0,0,835,836,
  	1,0,0,0,836,837,1,0,0,0,837,838,5,112,0,0,838,839,5,114,0,0,839,840,5,
  	97,0,0,840,841,5,103,0,0,841,842,5,109,0,0,842,843,5,97,0,0,843,844,1,
  	0,0,0,844,848,3,221,110,0,845,847,8,19,0,0,846,845,1,0,0,0,847,850,1,
  	0,0,0,848,846,1,0,0,0,848,849,1,0,0,0,849,851,1,0,0,0,850,848,1,0,0,0,
  	851,852,6,109,0,0,852,220,1,0,0,0,853,855,7,22,0,0,854,853,1,0,0,0,855,
  	856,1,0,0,0,856,854,1,0,0,0,856,857,1,0,0,0,857,858,1,0,0,0,858,859,6,
  	110,0,0,859,222,1,0,0,0,860,862,5,13,0,0,861,863,5,10,0,0,862,861,1,0,
  	0,0,862,863,1,0,0,0,863,866,1,0,0,0,864,866,5,10,0,0,865,860,1,0,0,0,
  	865,864,1,0,0,0,866,867,1,0,0,0,867,868,6,111,0,0,868,224,1,0,0,0,869,
  	870,5,47,0,0,870,871,5,42,0,0,871,875,1,0,0,0,872,874,9,0,0,0,873,872,
  	1,0,0,0,874,877,1,0,0,0,875,876,1,0,0,0,875,873,1,0,0,0,876,878,1,0,0,
  	0,877,875,1,0,0,0,878,879,5,42,0,0,879,880,5,47,0,0,880,881,1,0,0,0,881,
  	882,6,112,0,0,882,226,1,0,0,0,883,884,5,47,0,0,884,885,5,47,0,0,885,889,
  	1,0,0,0,886,888,8,19,0,0,887,886,1,0,0,0,888,891,1,0,0,0,889,887,1,0,
  	0,0,889,890,1,0,0,0,890,892,1,0,0,0,891,889,1,0,0,0,892,893,6,113,0,0,
  	893,228,1,0,0,0,67,0,449,451,456,472,481,485,489,492,499,505,512,519,
  	532,539,543,545,555,559,563,566,571,573,578,582,585,592,596,605,608,615,
  	619,626,652,657,661,667,675,678,686,689,693,700,705,714,718,730,737,748,
  	754,762,766,769,782,789,805,811,818,822,828,835,848,856,862,865,875,889,
  	1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  c_grammarlexerLexerStaticData = staticData.release();
}

}

C_grammarLexer::C_grammarLexer(CharStream *input) : Lexer(input) {
  C_grammarLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *c_grammarlexerLexerStaticData->atn, c_grammarlexerLexerStaticData->decisionToDFA, c_grammarlexerLexerStaticData->sharedContextCache);
}

C_grammarLexer::~C_grammarLexer() {
  delete _interpreter;
}

std::string C_grammarLexer::getGrammarFileName() const {
  return "C_grammar.g4";
}

const std::vector<std::string>& C_grammarLexer::getRuleNames() const {
  return c_grammarlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& C_grammarLexer::getChannelNames() const {
  return c_grammarlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& C_grammarLexer::getModeNames() const {
  return c_grammarlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& C_grammarLexer::getVocabulary() const {
  return c_grammarlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView C_grammarLexer::getSerializedATN() const {
  return c_grammarlexerLexerStaticData->serializedATN;
}

const atn::ATN& C_grammarLexer::getATN() const {
  return *c_grammarlexerLexerStaticData->atn;
}




void C_grammarLexer::initialize() {
  std::call_once(c_grammarlexerLexerOnceFlag, c_grammarlexerLexerInitialize);
}