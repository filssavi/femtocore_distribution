
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1


#include "C_grammarListener.h"
#include "C_grammarVisitor.h"

#include "C_grammarParser.h"


using namespace antlrcpp;
using namespace C_parser;

using namespace antlr4;

namespace {

struct C_grammarParserStaticData final {
  C_grammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  C_grammarParserStaticData(const C_grammarParserStaticData&) = delete;
  C_grammarParserStaticData(C_grammarParserStaticData&&) = delete;
  C_grammarParserStaticData& operator=(const C_grammarParserStaticData&) = delete;
  C_grammarParserStaticData& operator=(C_grammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag c_grammarParserOnceFlag;
C_grammarParserStaticData *c_grammarParserStaticData = nullptr;

void c_grammarParserInitialize() {
  assert(c_grammarParserStaticData == nullptr);
  auto staticData = std::make_unique<C_grammarParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "primaryExpression", "unaryExpression", "arrayAccessExpression", 
      "unaryOperator", "multiplicativeOperator", "multiplicativeExpression", 
      "additiveOperator", "additiveExpression", "shiftOperator", "shiftExpression", 
      "relationalOperator", "relationalExpression", "equalityOperator", 
      "equalityExpression", "andExpression", "exclusiveOrExpression", "inclusiveOrExpression", 
      "logicalAndExpression", "logicalOrExpression", "conditionalExpression", 
      "assignmentExpression", "assignmentOperator", "expression", "constantExpression", 
      "declaration", "initDeclaratorList", "initDeclarator", "typeSpecifier", 
      "specifierQualifierList", "declarator", "directDeclarator", "arrayDeclarator", 
      "nestedParenthesesBlock", "parameterTypeList", "parameterList", "parameterDeclaration", 
      "identifierList", "typeName", "typedefName", "initializer", "functionCallExpression", 
      "argumentExpressionList", "argumentExpression", "initializerList", 
      "designation", "designatorList", "designator", "statement", "compoundStatement", 
      "blockItem", "expressionStatement", "ifContent", "elseContent", "conditionalBlockItem", 
      "conditionContent", "selectionStatement", "iterationStatement", "forContent", 
      "forBlockItem", "forExitCondition", "forDeclaration", "forIterationExpression", 
      "returnStatement", "translationUnit", "externalDeclaration", "functionDefinition", 
      "declarationList", "constant"
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
  	4,1,79,662,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,1,0,3,0,140,8,0,
  	1,0,1,0,1,1,1,1,1,1,4,1,147,8,1,11,1,12,1,148,1,1,1,1,1,1,1,1,3,1,155,
  	8,1,1,2,5,2,158,8,2,10,2,12,2,161,9,2,1,2,1,2,1,2,1,2,1,2,3,2,168,8,2,
  	1,2,3,2,171,8,2,1,3,1,3,1,3,1,3,1,3,4,3,178,8,3,11,3,12,3,179,1,4,1,4,
  	1,5,1,5,1,6,1,6,1,6,1,6,5,6,190,8,6,10,6,12,6,193,9,6,1,7,1,7,1,8,1,8,
  	1,8,1,8,5,8,201,8,8,10,8,12,8,204,9,8,1,9,1,9,1,10,1,10,1,10,1,10,5,10,
  	212,8,10,10,10,12,10,215,9,10,1,11,1,11,1,12,1,12,1,12,1,12,5,12,223,
  	8,12,10,12,12,12,226,9,12,1,13,1,13,1,14,1,14,1,14,1,14,5,14,234,8,14,
  	10,14,12,14,237,9,14,1,15,1,15,1,15,5,15,242,8,15,10,15,12,15,245,9,15,
  	1,16,1,16,1,16,5,16,250,8,16,10,16,12,16,253,9,16,1,17,1,17,1,17,5,17,
  	258,8,17,10,17,12,17,261,9,17,1,18,1,18,1,18,5,18,266,8,18,10,18,12,18,
  	269,9,18,1,19,1,19,1,19,5,19,274,8,19,10,19,12,19,277,9,19,1,20,1,20,
  	1,20,1,20,1,20,1,20,3,20,285,8,20,1,21,1,21,1,21,1,21,1,21,1,21,3,21,
  	293,8,21,1,22,1,22,1,23,1,23,1,23,5,23,300,8,23,10,23,12,23,303,9,23,
  	1,24,1,24,1,25,3,25,308,8,25,1,25,1,25,3,25,312,8,25,1,26,1,26,1,26,5,
  	26,317,8,26,10,26,12,26,320,9,26,1,27,1,27,1,27,3,27,325,8,27,1,28,1,
  	28,3,28,329,8,28,1,29,1,29,3,29,333,8,29,1,29,3,29,336,8,29,1,30,1,30,
  	1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,3,31,349,8,31,1,31,1,31,
  	4,31,353,8,31,11,31,12,31,354,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	3,31,365,8,31,1,31,5,31,368,8,31,10,31,12,31,371,9,31,1,32,1,32,3,32,
  	375,8,32,1,32,3,32,378,8,32,1,32,1,32,1,33,1,33,1,33,1,33,1,33,5,33,387,
  	8,33,10,33,12,33,390,9,33,1,34,1,34,1,34,3,34,395,8,34,1,35,1,35,1,35,
  	5,35,400,8,35,10,35,12,35,403,9,35,1,36,3,36,406,8,36,1,36,1,36,1,36,
  	1,37,1,37,1,37,5,37,414,8,37,10,37,12,37,417,9,37,1,38,3,38,420,8,38,
  	1,39,1,39,1,40,1,40,1,40,1,40,3,40,428,8,40,1,40,1,40,3,40,432,8,40,1,
  	41,1,41,1,41,3,41,437,8,41,1,41,1,41,1,42,1,42,1,42,5,42,444,8,42,10,
  	42,12,42,447,9,42,1,43,1,43,1,44,3,44,452,8,44,1,44,1,44,1,44,3,44,457,
  	8,44,1,44,5,44,460,8,44,10,44,12,44,463,9,44,1,45,1,45,1,45,1,46,4,46,
  	469,8,46,11,46,12,46,470,1,47,1,47,1,47,1,47,1,47,1,47,3,47,479,8,47,
  	1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,5,48,491,8,48,10,48,
  	12,48,494,9,48,3,48,496,8,48,1,48,1,48,1,48,1,48,5,48,502,8,48,10,48,
  	12,48,505,9,48,3,48,507,8,48,5,48,509,8,48,10,48,12,48,512,9,48,1,48,
  	1,48,3,48,516,8,48,1,49,1,49,5,49,520,8,49,10,49,12,49,523,9,49,1,49,
  	1,49,1,50,1,50,1,50,1,50,3,50,531,8,50,1,51,3,51,534,8,51,1,52,1,52,5,
  	52,538,8,52,10,52,12,52,541,9,52,1,52,1,52,3,52,545,8,52,1,53,1,53,5,
  	53,549,8,53,10,53,12,53,552,9,53,1,53,1,53,3,53,556,8,53,1,54,1,54,1,
  	54,1,54,3,54,562,8,54,1,55,1,55,1,56,1,56,1,56,1,56,1,56,1,56,1,56,3,
  	56,573,8,56,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,58,1,
  	58,5,58,587,8,58,10,58,12,58,590,9,58,1,58,1,58,3,58,594,8,58,1,59,1,
  	59,1,59,1,59,3,59,600,8,59,1,60,1,60,1,61,1,61,1,62,1,62,1,62,5,62,609,
  	8,62,10,62,12,62,612,9,62,1,63,1,63,3,63,616,8,63,1,63,1,63,1,64,4,64,
  	621,8,64,11,64,12,64,622,1,65,1,65,1,65,1,65,1,65,3,65,630,8,65,1,66,
  	3,66,633,8,66,1,66,3,66,636,8,66,1,66,1,66,3,66,640,8,66,1,66,1,66,1,
  	67,1,67,1,67,4,67,647,8,67,11,67,12,67,648,1,68,3,68,652,8,68,1,68,1,
  	68,3,68,656,8,68,1,68,1,68,3,68,660,8,68,1,68,0,1,62,69,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
  	58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,
  	104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,0,
  	10,2,0,31,31,33,33,2,0,32,32,42,43,1,0,34,36,2,0,30,30,32,32,1,0,28,29,
  	1,0,24,27,1,0,59,60,1,0,48,58,5,0,2,2,5,5,8,9,11,12,14,15,1,0,18,19,682,
  	0,139,1,0,0,0,2,154,1,0,0,0,4,170,1,0,0,0,6,172,1,0,0,0,8,181,1,0,0,0,
  	10,183,1,0,0,0,12,185,1,0,0,0,14,194,1,0,0,0,16,196,1,0,0,0,18,205,1,
  	0,0,0,20,207,1,0,0,0,22,216,1,0,0,0,24,218,1,0,0,0,26,227,1,0,0,0,28,
  	229,1,0,0,0,30,238,1,0,0,0,32,246,1,0,0,0,34,254,1,0,0,0,36,262,1,0,0,
  	0,38,270,1,0,0,0,40,278,1,0,0,0,42,292,1,0,0,0,44,294,1,0,0,0,46,296,
  	1,0,0,0,48,304,1,0,0,0,50,307,1,0,0,0,52,313,1,0,0,0,54,321,1,0,0,0,56,
  	328,1,0,0,0,58,332,1,0,0,0,60,337,1,0,0,0,62,348,1,0,0,0,64,372,1,0,0,
  	0,66,388,1,0,0,0,68,391,1,0,0,0,70,396,1,0,0,0,72,405,1,0,0,0,74,410,
  	1,0,0,0,76,419,1,0,0,0,78,421,1,0,0,0,80,431,1,0,0,0,82,433,1,0,0,0,84,
  	440,1,0,0,0,86,448,1,0,0,0,88,451,1,0,0,0,90,464,1,0,0,0,92,468,1,0,0,
  	0,94,478,1,0,0,0,96,515,1,0,0,0,98,517,1,0,0,0,100,530,1,0,0,0,102,533,
  	1,0,0,0,104,544,1,0,0,0,106,555,1,0,0,0,108,561,1,0,0,0,110,563,1,0,0,
  	0,112,565,1,0,0,0,114,574,1,0,0,0,116,593,1,0,0,0,118,599,1,0,0,0,120,
  	601,1,0,0,0,122,603,1,0,0,0,124,605,1,0,0,0,126,613,1,0,0,0,128,620,1,
  	0,0,0,130,629,1,0,0,0,132,635,1,0,0,0,134,646,1,0,0,0,136,659,1,0,0,0,
  	138,140,3,128,64,0,139,138,1,0,0,0,139,140,1,0,0,0,140,141,1,0,0,0,141,
  	142,5,0,0,1,142,1,1,0,0,0,143,155,5,64,0,0,144,155,3,136,68,0,145,147,
  	5,69,0,0,146,145,1,0,0,0,147,148,1,0,0,0,148,146,1,0,0,0,148,149,1,0,
  	0,0,149,155,1,0,0,0,150,151,5,18,0,0,151,152,3,46,23,0,152,153,5,19,0,
  	0,153,155,1,0,0,0,154,143,1,0,0,0,154,144,1,0,0,0,154,146,1,0,0,0,154,
  	150,1,0,0,0,155,3,1,0,0,0,156,158,7,0,0,0,157,156,1,0,0,0,158,161,1,0,
  	0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,167,1,0,0,0,161,159,1,0,0,0,162,
  	168,3,2,1,0,163,164,3,8,4,0,164,165,3,4,2,0,165,168,1,0,0,0,166,168,3,
  	82,41,0,167,162,1,0,0,0,167,163,1,0,0,0,167,166,1,0,0,0,168,171,1,0,0,
  	0,169,171,3,6,3,0,170,159,1,0,0,0,170,169,1,0,0,0,171,5,1,0,0,0,172,177,
  	3,2,1,0,173,174,5,20,0,0,174,175,3,2,1,0,175,176,5,21,0,0,176,178,1,0,
  	0,0,177,173,1,0,0,0,178,179,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,0,180,
  	7,1,0,0,0,181,182,7,1,0,0,182,9,1,0,0,0,183,184,7,2,0,0,184,11,1,0,0,
  	0,185,191,3,4,2,0,186,187,3,10,5,0,187,188,3,4,2,0,188,190,1,0,0,0,189,
  	186,1,0,0,0,190,193,1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,192,13,1,
  	0,0,0,193,191,1,0,0,0,194,195,7,3,0,0,195,15,1,0,0,0,196,202,3,12,6,0,
  	197,198,3,14,7,0,198,199,3,12,6,0,199,201,1,0,0,0,200,197,1,0,0,0,201,
  	204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,0,0,203,17,1,0,0,0,204,202,1,
  	0,0,0,205,206,7,4,0,0,206,19,1,0,0,0,207,213,3,16,8,0,208,209,3,18,9,
  	0,209,210,3,16,8,0,210,212,1,0,0,0,211,208,1,0,0,0,212,215,1,0,0,0,213,
  	211,1,0,0,0,213,214,1,0,0,0,214,21,1,0,0,0,215,213,1,0,0,0,216,217,7,
  	5,0,0,217,23,1,0,0,0,218,224,3,20,10,0,219,220,3,22,11,0,220,221,3,20,
  	10,0,221,223,1,0,0,0,222,219,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,
  	224,225,1,0,0,0,225,25,1,0,0,0,226,224,1,0,0,0,227,228,7,6,0,0,228,27,
  	1,0,0,0,229,235,3,24,12,0,230,231,3,26,13,0,231,232,3,24,12,0,232,234,
  	1,0,0,0,233,230,1,0,0,0,234,237,1,0,0,0,235,233,1,0,0,0,235,236,1,0,0,
  	0,236,29,1,0,0,0,237,235,1,0,0,0,238,243,3,28,14,0,239,240,5,37,0,0,240,
  	242,3,28,14,0,241,239,1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,244,
  	1,0,0,0,244,31,1,0,0,0,245,243,1,0,0,0,246,251,3,30,15,0,247,248,5,41,
  	0,0,248,250,3,30,15,0,249,247,1,0,0,0,250,253,1,0,0,0,251,249,1,0,0,0,
  	251,252,1,0,0,0,252,33,1,0,0,0,253,251,1,0,0,0,254,259,3,32,16,0,255,
  	256,5,38,0,0,256,258,3,32,16,0,257,255,1,0,0,0,258,261,1,0,0,0,259,257,
  	1,0,0,0,259,260,1,0,0,0,260,35,1,0,0,0,261,259,1,0,0,0,262,267,3,34,17,
  	0,263,264,5,39,0,0,264,266,3,34,17,0,265,263,1,0,0,0,266,269,1,0,0,0,
  	267,265,1,0,0,0,267,268,1,0,0,0,268,37,1,0,0,0,269,267,1,0,0,0,270,275,
  	3,36,18,0,271,272,5,40,0,0,272,274,3,36,18,0,273,271,1,0,0,0,274,277,
  	1,0,0,0,275,273,1,0,0,0,275,276,1,0,0,0,276,39,1,0,0,0,277,275,1,0,0,
  	0,278,284,3,38,19,0,279,280,5,44,0,0,280,281,3,46,23,0,281,282,5,45,0,
  	0,282,283,3,40,20,0,283,285,1,0,0,0,284,279,1,0,0,0,284,285,1,0,0,0,285,
  	41,1,0,0,0,286,293,3,40,20,0,287,288,3,4,2,0,288,289,3,44,22,0,289,290,
  	3,42,21,0,290,293,1,0,0,0,291,293,5,67,0,0,292,286,1,0,0,0,292,287,1,
  	0,0,0,292,291,1,0,0,0,293,43,1,0,0,0,294,295,7,7,0,0,295,45,1,0,0,0,296,
  	301,3,42,21,0,297,298,5,47,0,0,298,300,3,42,21,0,299,297,1,0,0,0,300,
  	303,1,0,0,0,301,299,1,0,0,0,301,302,1,0,0,0,302,47,1,0,0,0,303,301,1,
  	0,0,0,304,305,3,40,20,0,305,49,1,0,0,0,306,308,5,3,0,0,307,306,1,0,0,
  	0,307,308,1,0,0,0,308,309,1,0,0,0,309,311,3,56,28,0,310,312,3,52,26,0,
  	311,310,1,0,0,0,311,312,1,0,0,0,312,51,1,0,0,0,313,318,3,54,27,0,314,
  	315,5,47,0,0,315,317,3,54,27,0,316,314,1,0,0,0,317,320,1,0,0,0,318,316,
  	1,0,0,0,318,319,1,0,0,0,319,53,1,0,0,0,320,318,1,0,0,0,321,324,3,60,30,
  	0,322,323,5,48,0,0,323,325,3,80,40,0,324,322,1,0,0,0,324,325,1,0,0,0,
  	325,55,1,0,0,0,326,329,7,8,0,0,327,329,3,78,39,0,328,326,1,0,0,0,328,
  	327,1,0,0,0,329,57,1,0,0,0,330,333,3,56,28,0,331,333,5,3,0,0,332,330,
  	1,0,0,0,332,331,1,0,0,0,333,335,1,0,0,0,334,336,3,58,29,0,335,334,1,0,
  	0,0,335,336,1,0,0,0,336,59,1,0,0,0,337,338,3,62,31,0,338,61,1,0,0,0,339,
  	340,6,31,-1,0,340,349,5,64,0,0,341,342,5,18,0,0,342,343,3,60,30,0,343,
  	344,5,19,0,0,344,349,1,0,0,0,345,346,5,64,0,0,346,347,5,45,0,0,347,349,
  	5,67,0,0,348,339,1,0,0,0,348,341,1,0,0,0,348,345,1,0,0,0,349,369,1,0,
  	0,0,350,352,10,4,0,0,351,353,3,64,32,0,352,351,1,0,0,0,353,354,1,0,0,
  	0,354,352,1,0,0,0,354,355,1,0,0,0,355,368,1,0,0,0,356,357,10,3,0,0,357,
  	358,5,18,0,0,358,359,3,68,34,0,359,360,5,19,0,0,360,368,1,0,0,0,361,362,
  	10,2,0,0,362,364,5,18,0,0,363,365,3,74,37,0,364,363,1,0,0,0,364,365,1,
  	0,0,0,365,366,1,0,0,0,366,368,5,19,0,0,367,350,1,0,0,0,367,356,1,0,0,
  	0,367,361,1,0,0,0,368,371,1,0,0,0,369,367,1,0,0,0,369,370,1,0,0,0,370,
  	63,1,0,0,0,371,369,1,0,0,0,372,374,5,20,0,0,373,375,5,3,0,0,374,373,1,
  	0,0,0,374,375,1,0,0,0,375,377,1,0,0,0,376,378,3,42,21,0,377,376,1,0,0,
  	0,377,378,1,0,0,0,378,379,1,0,0,0,379,380,5,21,0,0,380,65,1,0,0,0,381,
  	387,8,9,0,0,382,383,5,18,0,0,383,384,3,66,33,0,384,385,5,19,0,0,385,387,
  	1,0,0,0,386,381,1,0,0,0,386,382,1,0,0,0,387,390,1,0,0,0,388,386,1,0,0,
  	0,388,389,1,0,0,0,389,67,1,0,0,0,390,388,1,0,0,0,391,394,3,70,35,0,392,
  	393,5,47,0,0,393,395,5,63,0,0,394,392,1,0,0,0,394,395,1,0,0,0,395,69,
  	1,0,0,0,396,401,3,72,36,0,397,398,5,47,0,0,398,400,3,72,36,0,399,397,
  	1,0,0,0,400,403,1,0,0,0,401,399,1,0,0,0,401,402,1,0,0,0,402,71,1,0,0,
  	0,403,401,1,0,0,0,404,406,5,3,0,0,405,404,1,0,0,0,405,406,1,0,0,0,406,
  	407,1,0,0,0,407,408,3,56,28,0,408,409,3,60,30,0,409,73,1,0,0,0,410,415,
  	5,64,0,0,411,412,5,47,0,0,412,414,5,64,0,0,413,411,1,0,0,0,414,417,1,
  	0,0,0,415,413,1,0,0,0,415,416,1,0,0,0,416,75,1,0,0,0,417,415,1,0,0,0,
  	418,420,3,58,29,0,419,418,1,0,0,0,419,420,1,0,0,0,420,77,1,0,0,0,421,
  	422,5,64,0,0,422,79,1,0,0,0,423,432,3,42,21,0,424,425,5,22,0,0,425,427,
  	3,88,44,0,426,428,5,47,0,0,427,426,1,0,0,0,427,428,1,0,0,0,428,429,1,
  	0,0,0,429,430,5,23,0,0,430,432,1,0,0,0,431,423,1,0,0,0,431,424,1,0,0,
  	0,432,81,1,0,0,0,433,434,3,78,39,0,434,436,5,18,0,0,435,437,3,84,42,0,
  	436,435,1,0,0,0,436,437,1,0,0,0,437,438,1,0,0,0,438,439,5,19,0,0,439,
  	83,1,0,0,0,440,445,3,86,43,0,441,442,5,47,0,0,442,444,3,86,43,0,443,441,
  	1,0,0,0,444,447,1,0,0,0,445,443,1,0,0,0,445,446,1,0,0,0,446,85,1,0,0,
  	0,447,445,1,0,0,0,448,449,3,42,21,0,449,87,1,0,0,0,450,452,3,90,45,0,
  	451,450,1,0,0,0,451,452,1,0,0,0,452,453,1,0,0,0,453,461,3,80,40,0,454,
  	456,5,47,0,0,455,457,3,90,45,0,456,455,1,0,0,0,456,457,1,0,0,0,457,458,
  	1,0,0,0,458,460,3,80,40,0,459,454,1,0,0,0,460,463,1,0,0,0,461,459,1,0,
  	0,0,461,462,1,0,0,0,462,89,1,0,0,0,463,461,1,0,0,0,464,465,3,92,46,0,
  	465,466,5,48,0,0,466,91,1,0,0,0,467,469,3,94,47,0,468,467,1,0,0,0,469,
  	470,1,0,0,0,470,468,1,0,0,0,470,471,1,0,0,0,471,93,1,0,0,0,472,473,5,
  	20,0,0,473,474,3,48,24,0,474,475,5,21,0,0,475,479,1,0,0,0,476,477,5,62,
  	0,0,477,479,5,64,0,0,478,472,1,0,0,0,478,476,1,0,0,0,479,95,1,0,0,0,480,
  	481,3,102,51,0,481,482,5,46,0,0,482,516,1,0,0,0,483,516,3,112,56,0,484,
  	516,3,114,57,0,485,516,3,126,63,0,486,495,5,18,0,0,487,492,3,38,19,0,
  	488,489,5,47,0,0,489,491,3,38,19,0,490,488,1,0,0,0,491,494,1,0,0,0,492,
  	490,1,0,0,0,492,493,1,0,0,0,493,496,1,0,0,0,494,492,1,0,0,0,495,487,1,
  	0,0,0,495,496,1,0,0,0,496,510,1,0,0,0,497,506,5,45,0,0,498,503,3,38,19,
  	0,499,500,5,47,0,0,500,502,3,38,19,0,501,499,1,0,0,0,502,505,1,0,0,0,
  	503,501,1,0,0,0,503,504,1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,506,498,
  	1,0,0,0,506,507,1,0,0,0,507,509,1,0,0,0,508,497,1,0,0,0,509,512,1,0,0,
  	0,510,508,1,0,0,0,510,511,1,0,0,0,511,513,1,0,0,0,512,510,1,0,0,0,513,
  	514,5,19,0,0,514,516,5,46,0,0,515,480,1,0,0,0,515,483,1,0,0,0,515,484,
  	1,0,0,0,515,485,1,0,0,0,515,486,1,0,0,0,516,97,1,0,0,0,517,521,5,22,0,
  	0,518,520,3,100,50,0,519,518,1,0,0,0,520,523,1,0,0,0,521,519,1,0,0,0,
  	521,522,1,0,0,0,522,524,1,0,0,0,523,521,1,0,0,0,524,525,5,23,0,0,525,
  	99,1,0,0,0,526,531,3,96,48,0,527,528,3,50,25,0,528,529,5,46,0,0,529,531,
  	1,0,0,0,530,526,1,0,0,0,530,527,1,0,0,0,531,101,1,0,0,0,532,534,3,46,
  	23,0,533,532,1,0,0,0,533,534,1,0,0,0,534,103,1,0,0,0,535,539,5,22,0,0,
  	536,538,3,108,54,0,537,536,1,0,0,0,538,541,1,0,0,0,539,537,1,0,0,0,539,
  	540,1,0,0,0,540,542,1,0,0,0,541,539,1,0,0,0,542,545,5,23,0,0,543,545,
  	3,108,54,0,544,535,1,0,0,0,544,543,1,0,0,0,545,105,1,0,0,0,546,550,5,
  	22,0,0,547,549,3,108,54,0,548,547,1,0,0,0,549,552,1,0,0,0,550,548,1,0,
  	0,0,550,551,1,0,0,0,551,553,1,0,0,0,552,550,1,0,0,0,553,556,5,23,0,0,
  	554,556,3,108,54,0,555,546,1,0,0,0,555,554,1,0,0,0,556,107,1,0,0,0,557,
  	562,3,96,48,0,558,559,3,50,25,0,559,560,5,46,0,0,560,562,1,0,0,0,561,
  	557,1,0,0,0,561,558,1,0,0,0,562,109,1,0,0,0,563,564,3,46,23,0,564,111,
  	1,0,0,0,565,566,5,7,0,0,566,567,5,18,0,0,567,568,3,110,55,0,568,569,5,
  	19,0,0,569,572,3,104,52,0,570,571,5,4,0,0,571,573,3,106,53,0,572,570,
  	1,0,0,0,572,573,1,0,0,0,573,113,1,0,0,0,574,575,5,6,0,0,575,576,5,18,
  	0,0,576,577,3,122,61,0,577,578,5,46,0,0,578,579,3,120,60,0,579,580,5,
  	46,0,0,580,581,3,124,62,0,581,582,5,19,0,0,582,583,3,116,58,0,583,115,
  	1,0,0,0,584,588,5,22,0,0,585,587,3,118,59,0,586,585,1,0,0,0,587,590,1,
  	0,0,0,588,586,1,0,0,0,588,589,1,0,0,0,589,591,1,0,0,0,590,588,1,0,0,0,
  	591,594,5,23,0,0,592,594,3,118,59,0,593,584,1,0,0,0,593,592,1,0,0,0,594,
  	117,1,0,0,0,595,600,3,96,48,0,596,597,3,50,25,0,597,598,5,46,0,0,598,
  	600,1,0,0,0,599,595,1,0,0,0,599,596,1,0,0,0,600,119,1,0,0,0,601,602,3,
  	42,21,0,602,121,1,0,0,0,603,604,3,50,25,0,604,123,1,0,0,0,605,610,3,42,
  	21,0,606,607,5,47,0,0,607,609,3,42,21,0,608,606,1,0,0,0,609,612,1,0,0,
  	0,610,608,1,0,0,0,610,611,1,0,0,0,611,125,1,0,0,0,612,610,1,0,0,0,613,
  	615,5,10,0,0,614,616,3,46,23,0,615,614,1,0,0,0,615,616,1,0,0,0,616,617,
  	1,0,0,0,617,618,5,46,0,0,618,127,1,0,0,0,619,621,3,130,65,0,620,619,1,
  	0,0,0,621,622,1,0,0,0,622,620,1,0,0,0,622,623,1,0,0,0,623,129,1,0,0,0,
  	624,630,3,132,66,0,625,626,3,50,25,0,626,627,5,46,0,0,627,630,1,0,0,0,
  	628,630,5,46,0,0,629,624,1,0,0,0,629,625,1,0,0,0,629,628,1,0,0,0,630,
  	131,1,0,0,0,631,633,5,3,0,0,632,631,1,0,0,0,632,633,1,0,0,0,633,634,1,
  	0,0,0,634,636,3,56,28,0,635,632,1,0,0,0,635,636,1,0,0,0,636,637,1,0,0,
  	0,637,639,3,60,30,0,638,640,3,134,67,0,639,638,1,0,0,0,639,640,1,0,0,
  	0,640,641,1,0,0,0,641,642,3,98,49,0,642,133,1,0,0,0,643,644,3,50,25,0,
  	644,645,5,46,0,0,645,647,1,0,0,0,646,643,1,0,0,0,647,648,1,0,0,0,648,
  	646,1,0,0,0,648,649,1,0,0,0,649,135,1,0,0,0,650,652,5,32,0,0,651,650,
  	1,0,0,0,651,652,1,0,0,0,652,653,1,0,0,0,653,660,5,65,0,0,654,656,5,32,
  	0,0,655,654,1,0,0,0,655,656,1,0,0,0,656,657,1,0,0,0,657,660,5,66,0,0,
  	658,660,5,68,0,0,659,651,1,0,0,0,659,655,1,0,0,0,659,658,1,0,0,0,660,
  	137,1,0,0,0,79,139,148,154,159,167,170,179,191,202,213,224,235,243,251,
  	259,267,275,284,292,301,307,311,318,324,328,332,335,348,354,364,367,369,
  	374,377,386,388,394,401,405,415,419,427,431,436,445,451,456,461,470,478,
  	492,495,503,506,510,515,521,530,533,539,544,550,555,561,572,588,593,599,
  	610,615,622,629,632,635,639,648,651,655,659
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  c_grammarParserStaticData = staticData.release();
}

}

C_grammarParser::C_grammarParser(TokenStream *input) : C_grammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

C_grammarParser::C_grammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  C_grammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *c_grammarParserStaticData->atn, c_grammarParserStaticData->decisionToDFA, c_grammarParserStaticData->sharedContextCache, options);
}

C_grammarParser::~C_grammarParser() {
  delete _interpreter;
}

const atn::ATN& C_grammarParser::getATN() const {
  return *c_grammarParserStaticData->atn;
}

std::string C_grammarParser::getGrammarFileName() const {
  return "C_grammar.g4";
}

const std::vector<std::string>& C_grammarParser::getRuleNames() const {
  return c_grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& C_grammarParser::getVocabulary() const {
  return c_grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView C_grammarParser::getSerializedATN() const {
  return c_grammarParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

C_grammarParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompilationUnitContext::EOF() {
  return getToken(C_grammarParser::EOF, 0);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::CompilationUnitContext::translationUnit() {
  return getRuleContext<C_grammarParser::TranslationUnitContext>(0);
}


size_t C_grammarParser::CompilationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleCompilationUnit;
}

void C_grammarParser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void C_grammarParser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}


std::any C_grammarParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompilationUnitContext* C_grammarParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, C_grammarParser::RuleCompilationUnit);
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
    setState(139);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::LeftParen - 2))
      | (1ULL << (C_grammarParser::Semi - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(138);
      translationUnit();
    }
    setState(141);
    match(C_grammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

C_grammarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

C_grammarParser::ConstantContext* C_grammarParser::PrimaryExpressionContext::constant() {
  return getRuleContext<C_grammarParser::ConstantContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PrimaryExpressionContext::StringLiteral() {
  return getTokens(C_grammarParser::StringLiteral);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::StringLiteral(size_t i) {
  return getToken(C_grammarParser::StringLiteral, i);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::PrimaryExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::PrimaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RulePrimaryExpression;
}

void C_grammarParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void C_grammarParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any C_grammarParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, C_grammarParser::RulePrimaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(143);
        match(C_grammarParser::Identifier);
        break;
      }

      case C_grammarParser::Minus:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(144);
        constant();
        break;
      }

      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(146); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(145);
          match(C_grammarParser::StringLiteral);
          setState(148); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == C_grammarParser::StringLiteral);
        break;
      }

      case C_grammarParser::LeftParen: {
        enterOuterAlt(_localctx, 4);
        setState(150);
        match(C_grammarParser::LeftParen);
        setState(151);
        expression();
        setState(152);
        match(C_grammarParser::RightParen);
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

//----------------- UnaryExpressionContext ------------------------------------------------------------------

C_grammarParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(0);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<C_grammarParser::UnaryOperatorContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::UnaryExpressionContext::functionCallExpression() {
  return getRuleContext<C_grammarParser::FunctionCallExpressionContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::PlusPlus() {
  return getTokens(C_grammarParser::PlusPlus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::PlusPlus(size_t i) {
  return getToken(C_grammarParser::PlusPlus, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::MinusMinus() {
  return getTokens(C_grammarParser::MinusMinus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::MinusMinus(size_t i) {
  return getToken(C_grammarParser::MinusMinus, i);
}

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::UnaryExpressionContext::arrayAccessExpression() {
  return getRuleContext<C_grammarParser::ArrayAccessExpressionContext>(0);
}


size_t C_grammarParser::UnaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryExpression;
}

void C_grammarParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void C_grammarParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


std::any C_grammarParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, C_grammarParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(170);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::PlusPlus

      || _la == C_grammarParser::MinusMinus) {
        setState(156);
        _la = _input->LA(1);
        if (!(_la == C_grammarParser::PlusPlus

        || _la == C_grammarParser::MinusMinus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(161);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(167);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(162);
        primaryExpression();
        break;
      }

      case 2: {
        setState(163);
        unaryOperator();
        setState(164);
        unaryExpression();
        break;
      }

      case 3: {
        setState(166);
        functionCallExpression();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(169);
      arrayAccessExpression();
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

//----------------- ArrayAccessExpressionContext ------------------------------------------------------------------

C_grammarParser::ArrayAccessExpressionContext::ArrayAccessExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::PrimaryExpressionContext *> C_grammarParser::ArrayAccessExpressionContext::primaryExpression() {
  return getRuleContexts<C_grammarParser::PrimaryExpressionContext>();
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::ArrayAccessExpressionContext::primaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::LeftBracket() {
  return getTokens(C_grammarParser::LeftBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::LeftBracket(size_t i) {
  return getToken(C_grammarParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::RightBracket() {
  return getTokens(C_grammarParser::RightBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::RightBracket(size_t i) {
  return getToken(C_grammarParser::RightBracket, i);
}


size_t C_grammarParser::ArrayAccessExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayAccessExpression;
}

void C_grammarParser::ArrayAccessExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccessExpression(this);
}

void C_grammarParser::ArrayAccessExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccessExpression(this);
}


std::any C_grammarParser::ArrayAccessExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayAccessExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::arrayAccessExpression() {
  ArrayAccessExpressionContext *_localctx = _tracker.createInstance<ArrayAccessExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, C_grammarParser::RuleArrayAccessExpression);
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
    setState(172);
    primaryExpression();
    setState(177); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(173);
      match(C_grammarParser::LeftBracket);
      setState(174);
      primaryExpression();
      setState(175);
      match(C_grammarParser::RightBracket);
      setState(179); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

C_grammarParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Tilde() {
  return getToken(C_grammarParser::Tilde, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Not() {
  return getToken(C_grammarParser::Not, 0);
}


size_t C_grammarParser::UnaryOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryOperator;
}

void C_grammarParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void C_grammarParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}


std::any C_grammarParser::UnaryOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 8, C_grammarParser::RuleUnaryOperator);
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
      ((1ULL << _la) & ((1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde))) != 0))) {
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

//----------------- MultiplicativeOperatorContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeOperatorContext::MultiplicativeOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Div() {
  return getToken(C_grammarParser::Div, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Mod() {
  return getToken(C_grammarParser::Mod, 0);
}


size_t C_grammarParser::MultiplicativeOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeOperator;
}

void C_grammarParser::MultiplicativeOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeOperator(this);
}

void C_grammarParser::MultiplicativeOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeOperator(this);
}


std::any C_grammarParser::MultiplicativeOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::multiplicativeOperator() {
  MultiplicativeOperatorContext *_localctx = _tracker.createInstance<MultiplicativeOperatorContext>(_ctx, getState());
  enterRule(_localctx, 10, C_grammarParser::RuleMultiplicativeOperator);
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
    setState(183);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod))) != 0))) {
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

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::UnaryExpressionContext *> C_grammarParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<C_grammarParser::UnaryExpressionContext>();
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(i);
}

std::vector<C_grammarParser::MultiplicativeOperatorContext *> C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator() {
  return getRuleContexts<C_grammarParser::MultiplicativeOperatorContext>();
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeOperatorContext>(i);
}


size_t C_grammarParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeExpression;
}

void C_grammarParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void C_grammarParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


std::any C_grammarParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 12, C_grammarParser::RuleMultiplicativeExpression);
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
    setState(185);
    unaryExpression();
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod))) != 0)) {
      setState(186);
      multiplicativeOperator();
      setState(187);
      unaryExpression();
      setState(193);
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

//----------------- AdditiveOperatorContext ------------------------------------------------------------------

C_grammarParser::AdditiveOperatorContext::AdditiveOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Plus() {
  return getToken(C_grammarParser::Plus, 0);
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}


size_t C_grammarParser::AdditiveOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveOperator;
}

void C_grammarParser::AdditiveOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveOperator(this);
}

void C_grammarParser::AdditiveOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveOperator(this);
}


std::any C_grammarParser::AdditiveOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::additiveOperator() {
  AdditiveOperatorContext *_localctx = _tracker.createInstance<AdditiveOperatorContext>(_ctx, getState());
  enterRule(_localctx, 14, C_grammarParser::RuleAdditiveOperator);
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
    setState(194);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus)) {
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

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

C_grammarParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::MultiplicativeExpressionContext *> C_grammarParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<C_grammarParser::MultiplicativeExpressionContext>();
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeExpressionContext>(i);
}

std::vector<C_grammarParser::AdditiveOperatorContext *> C_grammarParser::AdditiveExpressionContext::additiveOperator() {
  return getRuleContexts<C_grammarParser::AdditiveOperatorContext>();
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::AdditiveExpressionContext::additiveOperator(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveOperatorContext>(i);
}


size_t C_grammarParser::AdditiveExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveExpression;
}

void C_grammarParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void C_grammarParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


std::any C_grammarParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, C_grammarParser::RuleAdditiveExpression);
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
    setState(196);
    multiplicativeExpression();
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus) {
      setState(197);
      additiveOperator();
      setState(198);
      multiplicativeExpression();
      setState(204);
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

//----------------- ShiftOperatorContext ------------------------------------------------------------------

C_grammarParser::ShiftOperatorContext::ShiftOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::LeftShift() {
  return getToken(C_grammarParser::LeftShift, 0);
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::RightShift() {
  return getToken(C_grammarParser::RightShift, 0);
}


size_t C_grammarParser::ShiftOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftOperator;
}

void C_grammarParser::ShiftOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftOperator(this);
}

void C_grammarParser::ShiftOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftOperator(this);
}


std::any C_grammarParser::ShiftOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::shiftOperator() {
  ShiftOperatorContext *_localctx = _tracker.createInstance<ShiftOperatorContext>(_ctx, getState());
  enterRule(_localctx, 18, C_grammarParser::RuleShiftOperator);
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
    setState(205);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift)) {
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

//----------------- ShiftExpressionContext ------------------------------------------------------------------

C_grammarParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AdditiveExpressionContext *> C_grammarParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<C_grammarParser::AdditiveExpressionContext>();
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveExpressionContext>(i);
}

std::vector<C_grammarParser::ShiftOperatorContext *> C_grammarParser::ShiftExpressionContext::shiftOperator() {
  return getRuleContexts<C_grammarParser::ShiftOperatorContext>();
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::ShiftExpressionContext::shiftOperator(size_t i) {
  return getRuleContext<C_grammarParser::ShiftOperatorContext>(i);
}


size_t C_grammarParser::ShiftExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftExpression;
}

void C_grammarParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void C_grammarParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}


std::any C_grammarParser::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, C_grammarParser::RuleShiftExpression);
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
    setState(207);
    additiveExpression();
    setState(213);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift) {
      setState(208);
      shiftOperator();
      setState(209);
      additiveExpression();
      setState(215);
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

//----------------- RelationalOperatorContext ------------------------------------------------------------------

C_grammarParser::RelationalOperatorContext::RelationalOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Less() {
  return getToken(C_grammarParser::Less, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Greater() {
  return getToken(C_grammarParser::Greater, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::LessEqual() {
  return getToken(C_grammarParser::LessEqual, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::GreaterEqual() {
  return getToken(C_grammarParser::GreaterEqual, 0);
}


size_t C_grammarParser::RelationalOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalOperator;
}

void C_grammarParser::RelationalOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalOperator(this);
}

void C_grammarParser::RelationalOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalOperator(this);
}


std::any C_grammarParser::RelationalOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::relationalOperator() {
  RelationalOperatorContext *_localctx = _tracker.createInstance<RelationalOperatorContext>(_ctx, getState());
  enterRule(_localctx, 22, C_grammarParser::RuleRelationalOperator);
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
    setState(216);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual))) != 0))) {
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

//----------------- RelationalExpressionContext ------------------------------------------------------------------

C_grammarParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ShiftExpressionContext *> C_grammarParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<C_grammarParser::ShiftExpressionContext>();
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<C_grammarParser::ShiftExpressionContext>(i);
}

std::vector<C_grammarParser::RelationalOperatorContext *> C_grammarParser::RelationalExpressionContext::relationalOperator() {
  return getRuleContexts<C_grammarParser::RelationalOperatorContext>();
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::RelationalExpressionContext::relationalOperator(size_t i) {
  return getRuleContext<C_grammarParser::RelationalOperatorContext>(i);
}


size_t C_grammarParser::RelationalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalExpression;
}

void C_grammarParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void C_grammarParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


std::any C_grammarParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, C_grammarParser::RuleRelationalExpression);
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
    setState(218);
    shiftExpression();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual))) != 0)) {
      setState(219);
      relationalOperator();
      setState(220);
      shiftExpression();
      setState(226);
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

//----------------- EqualityOperatorContext ------------------------------------------------------------------

C_grammarParser::EqualityOperatorContext::EqualityOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::Equal() {
  return getToken(C_grammarParser::Equal, 0);
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::NotEqual() {
  return getToken(C_grammarParser::NotEqual, 0);
}


size_t C_grammarParser::EqualityOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityOperator;
}

void C_grammarParser::EqualityOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityOperator(this);
}

void C_grammarParser::EqualityOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityOperator(this);
}


std::any C_grammarParser::EqualityOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::equalityOperator() {
  EqualityOperatorContext *_localctx = _tracker.createInstance<EqualityOperatorContext>(_ctx, getState());
  enterRule(_localctx, 26, C_grammarParser::RuleEqualityOperator);
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
    setState(227);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual)) {
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

//----------------- EqualityExpressionContext ------------------------------------------------------------------

C_grammarParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::RelationalExpressionContext *> C_grammarParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<C_grammarParser::RelationalExpressionContext>();
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<C_grammarParser::RelationalExpressionContext>(i);
}

std::vector<C_grammarParser::EqualityOperatorContext *> C_grammarParser::EqualityExpressionContext::equalityOperator() {
  return getRuleContexts<C_grammarParser::EqualityOperatorContext>();
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::EqualityExpressionContext::equalityOperator(size_t i) {
  return getRuleContext<C_grammarParser::EqualityOperatorContext>(i);
}


size_t C_grammarParser::EqualityExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityExpression;
}

void C_grammarParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void C_grammarParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


std::any C_grammarParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 28, C_grammarParser::RuleEqualityExpression);
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
    setState(229);
    relationalExpression();
    setState(235);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual) {
      setState(230);
      equalityOperator();
      setState(231);
      relationalExpression();
      setState(237);
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

//----------------- AndExpressionContext ------------------------------------------------------------------

C_grammarParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::EqualityExpressionContext *> C_grammarParser::AndExpressionContext::equalityExpression() {
  return getRuleContexts<C_grammarParser::EqualityExpressionContext>();
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::AndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<C_grammarParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::AndExpressionContext::And() {
  return getTokens(C_grammarParser::And);
}

tree::TerminalNode* C_grammarParser::AndExpressionContext::And(size_t i) {
  return getToken(C_grammarParser::And, i);
}


size_t C_grammarParser::AndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAndExpression;
}

void C_grammarParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void C_grammarParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


std::any C_grammarParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AndExpressionContext* C_grammarParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, C_grammarParser::RuleAndExpression);
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
    setState(238);
    equalityExpression();
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::And) {
      setState(239);
      match(C_grammarParser::And);
      setState(240);
      equalityExpression();
      setState(245);
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

//----------------- ExclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::ExclusiveOrExpressionContext::ExclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AndExpressionContext *> C_grammarParser::ExclusiveOrExpressionContext::andExpression() {
  return getRuleContexts<C_grammarParser::AndExpressionContext>();
}

C_grammarParser::AndExpressionContext* C_grammarParser::ExclusiveOrExpressionContext::andExpression(size_t i) {
  return getRuleContext<C_grammarParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExclusiveOrExpressionContext::Caret() {
  return getTokens(C_grammarParser::Caret);
}

tree::TerminalNode* C_grammarParser::ExclusiveOrExpressionContext::Caret(size_t i) {
  return getToken(C_grammarParser::Caret, i);
}


size_t C_grammarParser::ExclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExclusiveOrExpression;
}

void C_grammarParser::ExclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExclusiveOrExpression(this);
}

void C_grammarParser::ExclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExclusiveOrExpression(this);
}


std::any C_grammarParser::ExclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::exclusiveOrExpression() {
  ExclusiveOrExpressionContext *_localctx = _tracker.createInstance<ExclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, C_grammarParser::RuleExclusiveOrExpression);
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
    setState(246);
    andExpression();
    setState(251);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Caret) {
      setState(247);
      match(C_grammarParser::Caret);
      setState(248);
      andExpression();
      setState(253);
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

//----------------- InclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::InclusiveOrExpressionContext::InclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExclusiveOrExpressionContext *> C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::ExclusiveOrExpressionContext>();
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::ExclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InclusiveOrExpressionContext::Or() {
  return getTokens(C_grammarParser::Or);
}

tree::TerminalNode* C_grammarParser::InclusiveOrExpressionContext::Or(size_t i) {
  return getToken(C_grammarParser::Or, i);
}


size_t C_grammarParser::InclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleInclusiveOrExpression;
}

void C_grammarParser::InclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInclusiveOrExpression(this);
}

void C_grammarParser::InclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInclusiveOrExpression(this);
}


std::any C_grammarParser::InclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::inclusiveOrExpression() {
  InclusiveOrExpressionContext *_localctx = _tracker.createInstance<InclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, C_grammarParser::RuleInclusiveOrExpression);
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
    setState(254);
    exclusiveOrExpression();
    setState(259);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Or) {
      setState(255);
      match(C_grammarParser::Or);
      setState(256);
      exclusiveOrExpression();
      setState(261);
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

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InclusiveOrExpressionContext *> C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::InclusiveOrExpressionContext>();
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::InclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalAndExpressionContext::AndAnd() {
  return getTokens(C_grammarParser::AndAnd);
}

tree::TerminalNode* C_grammarParser::LogicalAndExpressionContext::AndAnd(size_t i) {
  return getToken(C_grammarParser::AndAnd, i);
}


size_t C_grammarParser::LogicalAndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalAndExpression;
}

void C_grammarParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void C_grammarParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


std::any C_grammarParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, C_grammarParser::RuleLogicalAndExpression);
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
    setState(262);
    inclusiveOrExpression();
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::AndAnd) {
      setState(263);
      match(C_grammarParser::AndAnd);
      setState(264);
      inclusiveOrExpression();
      setState(269);
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

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::LogicalAndExpressionContext *> C_grammarParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<C_grammarParser::LogicalAndExpressionContext>();
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalOrExpressionContext::OrOr() {
  return getTokens(C_grammarParser::OrOr);
}

tree::TerminalNode* C_grammarParser::LogicalOrExpressionContext::OrOr(size_t i) {
  return getToken(C_grammarParser::OrOr, i);
}


size_t C_grammarParser::LogicalOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalOrExpression;
}

void C_grammarParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void C_grammarParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


std::any C_grammarParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, C_grammarParser::RuleLogicalOrExpression);
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
    setState(270);
    logicalAndExpression();
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::OrOr) {
      setState(271);
      match(C_grammarParser::OrOr);
      setState(272);
      logicalAndExpression();
      setState(277);
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

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

C_grammarParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::ConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Question() {
  return getToken(C_grammarParser::Question, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionalExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConditionalExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConditionalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalExpression;
}

void C_grammarParser::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void C_grammarParser::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}


std::any C_grammarParser::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, C_grammarParser::RuleConditionalExpression);
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
    setState(278);
    logicalOrExpression();
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Question) {
      setState(279);
      match(C_grammarParser::Question);
      setState(280);
      expression();
      setState(281);
      match(C_grammarParser::Colon);
      setState(282);
      conditionalExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

C_grammarParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::AssignmentExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::AssignmentExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::AssignmentExpressionContext::assignmentOperator() {
  return getRuleContext<C_grammarParser::AssignmentOperatorContext>(0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::AssignmentExpressionContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}


size_t C_grammarParser::AssignmentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentExpression;
}

void C_grammarParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void C_grammarParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}


std::any C_grammarParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, C_grammarParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(292);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(286);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(287);
      unaryExpression();
      setState(288);
      assignmentOperator();
      setState(289);
      assignmentExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(291);
      match(C_grammarParser::DigitSequence);
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

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

C_grammarParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::StarAssign() {
  return getToken(C_grammarParser::StarAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::DivAssign() {
  return getToken(C_grammarParser::DivAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::ModAssign() {
  return getToken(C_grammarParser::ModAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::PlusAssign() {
  return getToken(C_grammarParser::PlusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::MinusAssign() {
  return getToken(C_grammarParser::MinusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::LeftShiftAssign() {
  return getToken(C_grammarParser::LeftShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::RightShiftAssign() {
  return getToken(C_grammarParser::RightShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::AndAssign() {
  return getToken(C_grammarParser::AndAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::XorAssign() {
  return getToken(C_grammarParser::XorAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::OrAssign() {
  return getToken(C_grammarParser::OrAssign, 0);
}


size_t C_grammarParser::AssignmentOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentOperator;
}

void C_grammarParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void C_grammarParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}


std::any C_grammarParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 44, C_grammarParser::RuleAssignmentOperator);
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
    setState(294);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Assign)
      | (1ULL << C_grammarParser::StarAssign)
      | (1ULL << C_grammarParser::DivAssign)
      | (1ULL << C_grammarParser::ModAssign)
      | (1ULL << C_grammarParser::PlusAssign)
      | (1ULL << C_grammarParser::MinusAssign)
      | (1ULL << C_grammarParser::LeftShiftAssign)
      | (1ULL << C_grammarParser::RightShiftAssign)
      | (1ULL << C_grammarParser::AndAssign)
      | (1ULL << C_grammarParser::XorAssign)
      | (1ULL << C_grammarParser::OrAssign))) != 0))) {
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

//----------------- ExpressionContext ------------------------------------------------------------------

C_grammarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExpression;
}

void C_grammarParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void C_grammarParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any C_grammarParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionContext* C_grammarParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, C_grammarParser::RuleExpression);
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
    setState(296);
    assignmentExpression();
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(297);
      match(C_grammarParser::Comma);
      setState(298);
      assignmentExpression();
      setState(303);
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

//----------------- ConstantExpressionContext ------------------------------------------------------------------

C_grammarParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConstantExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConstantExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConstantExpression;
}

void C_grammarParser::ConstantExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstantExpression(this);
}

void C_grammarParser::ConstantExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstantExpression(this);
}


std::any C_grammarParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, C_grammarParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

C_grammarParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::DeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::DeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::DeclarationContext::initDeclaratorList() {
  return getRuleContext<C_grammarParser::InitDeclaratorListContext>(0);
}


size_t C_grammarParser::DeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclaration;
}

void C_grammarParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void C_grammarParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any C_grammarParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationContext* C_grammarParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 50, C_grammarParser::RuleDeclaration);
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
    setState(307);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(306);
      match(C_grammarParser::Const);
    }
    setState(309);
    typeSpecifier();
    setState(311);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen

    || _la == C_grammarParser::Identifier) {
      setState(310);
      initDeclaratorList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorListContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorListContext::InitDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitDeclaratorContext *> C_grammarParser::InitDeclaratorListContext::initDeclarator() {
  return getRuleContexts<C_grammarParser::InitDeclaratorContext>();
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::InitDeclaratorListContext::initDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::InitDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitDeclaratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitDeclaratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclaratorList;
}

void C_grammarParser::InitDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclaratorList(this);
}

void C_grammarParser::InitDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclaratorList(this);
}


std::any C_grammarParser::InitDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::initDeclaratorList() {
  InitDeclaratorListContext *_localctx = _tracker.createInstance<InitDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 52, C_grammarParser::RuleInitDeclaratorList);
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
    setState(313);
    initDeclarator();
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(314);
      match(C_grammarParser::Comma);
      setState(315);
      initDeclarator();
      setState(320);
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

//----------------- InitDeclaratorContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::InitDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

C_grammarParser::InitializerContext* C_grammarParser::InitDeclaratorContext::initializer() {
  return getRuleContext<C_grammarParser::InitializerContext>(0);
}


size_t C_grammarParser::InitDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclarator;
}

void C_grammarParser::InitDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclarator(this);
}

void C_grammarParser::InitDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclarator(this);
}


std::any C_grammarParser::InitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 54, C_grammarParser::RuleInitDeclarator);
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
    setState(321);
    declarator();
    setState(324);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(322);
      match(C_grammarParser::Assign);
      setState(323);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

C_grammarParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Void() {
  return getToken(C_grammarParser::Void, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Char() {
  return getToken(C_grammarParser::Char, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Short() {
  return getToken(C_grammarParser::Short, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Int() {
  return getToken(C_grammarParser::Int, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Long() {
  return getToken(C_grammarParser::Long, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Float() {
  return getToken(C_grammarParser::Float, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Signed() {
  return getToken(C_grammarParser::Signed, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Unsigned() {
  return getToken(C_grammarParser::Unsigned, 0);
}

C_grammarParser::TypedefNameContext* C_grammarParser::TypeSpecifierContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}


size_t C_grammarParser::TypeSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeSpecifier;
}

void C_grammarParser::TypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpecifier(this);
}

void C_grammarParser::TypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpecifier(this);
}


std::any C_grammarParser::TypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 56, C_grammarParser::RuleTypeSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(328);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(326);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(327);
        typedefName();
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

//----------------- SpecifierQualifierListContext ------------------------------------------------------------------

C_grammarParser::SpecifierQualifierListContext::SpecifierQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::SpecifierQualifierListContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::SpecifierQualifierListContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::SpecifierQualifierListContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::SpecifierQualifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleSpecifierQualifierList;
}

void C_grammarParser::SpecifierQualifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecifierQualifierList(this);
}

void C_grammarParser::SpecifierQualifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecifierQualifierList(this);
}


std::any C_grammarParser::SpecifierQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSpecifierQualifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::specifierQualifierList() {
  SpecifierQualifierListContext *_localctx = _tracker.createInstance<SpecifierQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 58, C_grammarParser::RuleSpecifierQualifierList);
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
    setState(332);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Identifier: {
        setState(330);
        typeSpecifier();
        break;
      }

      case C_grammarParser::Const: {
        setState(331);
        match(C_grammarParser::Const);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(334);
      specifierQualifierList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclaratorContext ------------------------------------------------------------------

C_grammarParser::DeclaratorContext::DeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}


size_t C_grammarParser::DeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarator;
}

void C_grammarParser::DeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarator(this);
}

void C_grammarParser::DeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarator(this);
}


std::any C_grammarParser::DeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclaratorContext* C_grammarParser::declarator() {
  DeclaratorContext *_localctx = _tracker.createInstance<DeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 60, C_grammarParser::RuleDeclarator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    directDeclarator(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectDeclaratorContext ------------------------------------------------------------------

C_grammarParser::DirectDeclaratorContext::DirectDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::DirectDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DirectDeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}

std::vector<C_grammarParser::ArrayDeclaratorContext *> C_grammarParser::DirectDeclaratorContext::arrayDeclarator() {
  return getRuleContexts<C_grammarParser::ArrayDeclaratorContext>();
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::DirectDeclaratorContext::arrayDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::ArrayDeclaratorContext>(i);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::DirectDeclaratorContext::parameterTypeList() {
  return getRuleContext<C_grammarParser::ParameterTypeListContext>(0);
}

C_grammarParser::IdentifierListContext* C_grammarParser::DirectDeclaratorContext::identifierList() {
  return getRuleContext<C_grammarParser::IdentifierListContext>(0);
}


size_t C_grammarParser::DirectDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDirectDeclarator;
}

void C_grammarParser::DirectDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectDeclarator(this);
}

void C_grammarParser::DirectDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectDeclarator(this);
}


std::any C_grammarParser::DirectDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDirectDeclarator(this);
  else
    return visitor->visitChildren(this);
}


C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator() {
   return directDeclarator(0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C_grammarParser::DirectDeclaratorContext *_localctx = _tracker.createInstance<DirectDeclaratorContext>(_ctx, parentState);
  C_grammarParser::DirectDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, C_grammarParser::RuleDirectDeclarator, precedence);

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
    setState(348);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(340);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(341);
      match(C_grammarParser::LeftParen);
      setState(342);
      declarator();
      setState(343);
      match(C_grammarParser::RightParen);
      break;
    }

    case 3: {
      setState(345);
      match(C_grammarParser::Identifier);
      setState(346);
      match(C_grammarParser::Colon);
      setState(347);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(369);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(367);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(350);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(352); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(351);
                    arrayDeclarator();
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(354); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(356);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(357);
          match(C_grammarParser::LeftParen);
          setState(358);
          parameterTypeList();
          setState(359);
          match(C_grammarParser::RightParen);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(361);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(362);
          match(C_grammarParser::LeftParen);
          setState(364);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == C_grammarParser::Identifier) {
            setState(363);
            identifierList();
          }
          setState(366);
          match(C_grammarParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(371);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArrayDeclaratorContext ------------------------------------------------------------------

C_grammarParser::ArrayDeclaratorContext::ArrayDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArrayDeclaratorContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArrayDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayDeclarator;
}

void C_grammarParser::ArrayDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDeclarator(this);
}

void C_grammarParser::ArrayDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDeclarator(this);
}


std::any C_grammarParser::ArrayDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::arrayDeclarator() {
  ArrayDeclaratorContext *_localctx = _tracker.createInstance<ArrayDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 64, C_grammarParser::RuleArrayDeclarator);
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
    setState(372);
    match(C_grammarParser::LeftBracket);
    setState(374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(373);
      match(C_grammarParser::Const);
    }
    setState(377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(376);
      assignmentExpression();
    }
    setState(379);
    match(C_grammarParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NestedParenthesesBlockContext ------------------------------------------------------------------

C_grammarParser::NestedParenthesesBlockContext::NestedParenthesesBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

std::vector<C_grammarParser::NestedParenthesesBlockContext *> C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock() {
  return getRuleContexts<C_grammarParser::NestedParenthesesBlockContext>();
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock(size_t i) {
  return getRuleContext<C_grammarParser::NestedParenthesesBlockContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}


size_t C_grammarParser::NestedParenthesesBlockContext::getRuleIndex() const {
  return C_grammarParser::RuleNestedParenthesesBlock;
}

void C_grammarParser::NestedParenthesesBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNestedParenthesesBlock(this);
}

void C_grammarParser::NestedParenthesesBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNestedParenthesesBlock(this);
}


std::any C_grammarParser::NestedParenthesesBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitNestedParenthesesBlock(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::nestedParenthesesBlock() {
  NestedParenthesesBlockContext *_localctx = _tracker.createInstance<NestedParenthesesBlockContext>(_ctx, getState());
  enterRule(_localctx, 66, C_grammarParser::RuleNestedParenthesesBlock);
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
    setState(388);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Else)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBracket)
      | (1ULL << C_grammarParser::RightBracket)
      | (1ULL << C_grammarParser::LeftBrace)
      | (1ULL << C_grammarParser::RightBrace)
      | (1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual)
      | (1ULL << C_grammarParser::LeftShift)
      | (1ULL << C_grammarParser::RightShift)
      | (1ULL << C_grammarParser::Plus)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod)
      | (1ULL << C_grammarParser::And)
      | (1ULL << C_grammarParser::Or)
      | (1ULL << C_grammarParser::AndAnd)
      | (1ULL << C_grammarParser::OrOr)
      | (1ULL << C_grammarParser::Caret)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Question)
      | (1ULL << C_grammarParser::Colon)
      | (1ULL << C_grammarParser::Semi)
      | (1ULL << C_grammarParser::Comma)
      | (1ULL << C_grammarParser::Assign)
      | (1ULL << C_grammarParser::StarAssign)
      | (1ULL << C_grammarParser::DivAssign)
      | (1ULL << C_grammarParser::ModAssign)
      | (1ULL << C_grammarParser::PlusAssign)
      | (1ULL << C_grammarParser::MinusAssign)
      | (1ULL << C_grammarParser::LeftShiftAssign)
      | (1ULL << C_grammarParser::RightShiftAssign)
      | (1ULL << C_grammarParser::AndAssign)
      | (1ULL << C_grammarParser::XorAssign)
      | (1ULL << C_grammarParser::OrAssign)
      | (1ULL << C_grammarParser::Equal)
      | (1ULL << C_grammarParser::NotEqual)
      | (1ULL << C_grammarParser::Arrow)
      | (1ULL << C_grammarParser::Dot)
      | (1ULL << C_grammarParser::Ellipsis))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::IntegerConstant - 64))
      | (1ULL << (C_grammarParser::FloatingConstant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
      | (1ULL << (C_grammarParser::CharacterConstant - 64))
      | (1ULL << (C_grammarParser::StringLiteral - 64))
      | (1ULL << (C_grammarParser::ComplexDefine - 64))
      | (1ULL << (C_grammarParser::IncludeDirective - 64))
      | (1ULL << (C_grammarParser::AsmBlock - 64))
      | (1ULL << (C_grammarParser::LineAfterPreprocessing - 64))
      | (1ULL << (C_grammarParser::LineDirective - 64))
      | (1ULL << (C_grammarParser::PragmaDirective - 64))
      | (1ULL << (C_grammarParser::Whitespace - 64))
      | (1ULL << (C_grammarParser::Newline - 64))
      | (1ULL << (C_grammarParser::BlockComment - 64))
      | (1ULL << (C_grammarParser::LineComment - 64)))) != 0)) {
      setState(386);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C_grammarParser::Case:
        case C_grammarParser::Char:
        case C_grammarParser::Const:
        case C_grammarParser::Else:
        case C_grammarParser::Float:
        case C_grammarParser::For:
        case C_grammarParser::If:
        case C_grammarParser::Int:
        case C_grammarParser::Long:
        case C_grammarParser::Return:
        case C_grammarParser::Short:
        case C_grammarParser::Signed:
        case C_grammarParser::Typedef:
        case C_grammarParser::Unsigned:
        case C_grammarParser::Void:
        case C_grammarParser::Volatile:
        case C_grammarParser::While:
        case C_grammarParser::LeftBracket:
        case C_grammarParser::RightBracket:
        case C_grammarParser::LeftBrace:
        case C_grammarParser::RightBrace:
        case C_grammarParser::Less:
        case C_grammarParser::LessEqual:
        case C_grammarParser::Greater:
        case C_grammarParser::GreaterEqual:
        case C_grammarParser::LeftShift:
        case C_grammarParser::RightShift:
        case C_grammarParser::Plus:
        case C_grammarParser::PlusPlus:
        case C_grammarParser::Minus:
        case C_grammarParser::MinusMinus:
        case C_grammarParser::Star:
        case C_grammarParser::Div:
        case C_grammarParser::Mod:
        case C_grammarParser::And:
        case C_grammarParser::Or:
        case C_grammarParser::AndAnd:
        case C_grammarParser::OrOr:
        case C_grammarParser::Caret:
        case C_grammarParser::Not:
        case C_grammarParser::Tilde:
        case C_grammarParser::Question:
        case C_grammarParser::Colon:
        case C_grammarParser::Semi:
        case C_grammarParser::Comma:
        case C_grammarParser::Assign:
        case C_grammarParser::StarAssign:
        case C_grammarParser::DivAssign:
        case C_grammarParser::ModAssign:
        case C_grammarParser::PlusAssign:
        case C_grammarParser::MinusAssign:
        case C_grammarParser::LeftShiftAssign:
        case C_grammarParser::RightShiftAssign:
        case C_grammarParser::AndAssign:
        case C_grammarParser::XorAssign:
        case C_grammarParser::OrAssign:
        case C_grammarParser::Equal:
        case C_grammarParser::NotEqual:
        case C_grammarParser::Arrow:
        case C_grammarParser::Dot:
        case C_grammarParser::Ellipsis:
        case C_grammarParser::Identifier:
        case C_grammarParser::IntegerConstant:
        case C_grammarParser::FloatingConstant:
        case C_grammarParser::DigitSequence:
        case C_grammarParser::CharacterConstant:
        case C_grammarParser::StringLiteral:
        case C_grammarParser::ComplexDefine:
        case C_grammarParser::IncludeDirective:
        case C_grammarParser::AsmBlock:
        case C_grammarParser::LineAfterPreprocessing:
        case C_grammarParser::LineDirective:
        case C_grammarParser::PragmaDirective:
        case C_grammarParser::Whitespace:
        case C_grammarParser::Newline:
        case C_grammarParser::BlockComment:
        case C_grammarParser::LineComment: {
          setState(381);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == C_grammarParser::LeftParen

          || _la == C_grammarParser::RightParen)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case C_grammarParser::LeftParen: {
          setState(382);
          match(C_grammarParser::LeftParen);
          setState(383);
          nestedParenthesesBlock();
          setState(384);
          match(C_grammarParser::RightParen);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(390);
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

//----------------- ParameterTypeListContext ------------------------------------------------------------------

C_grammarParser::ParameterTypeListContext::ParameterTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ParameterListContext* C_grammarParser::ParameterTypeListContext::parameterList() {
  return getRuleContext<C_grammarParser::ParameterListContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Ellipsis() {
  return getToken(C_grammarParser::Ellipsis, 0);
}


size_t C_grammarParser::ParameterTypeListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterTypeList;
}

void C_grammarParser::ParameterTypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterTypeList(this);
}

void C_grammarParser::ParameterTypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterTypeList(this);
}


std::any C_grammarParser::ParameterTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterTypeList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::parameterTypeList() {
  ParameterTypeListContext *_localctx = _tracker.createInstance<ParameterTypeListContext>(_ctx, getState());
  enterRule(_localctx, 68, C_grammarParser::RuleParameterTypeList);
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
    setState(391);
    parameterList();
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Comma) {
      setState(392);
      match(C_grammarParser::Comma);
      setState(393);
      match(C_grammarParser::Ellipsis);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

C_grammarParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ParameterDeclarationContext *> C_grammarParser::ParameterListContext::parameterDeclaration() {
  return getRuleContexts<C_grammarParser::ParameterDeclarationContext>();
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::ParameterListContext::parameterDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ParameterDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ParameterListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ParameterListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ParameterListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterList;
}

void C_grammarParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void C_grammarParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any C_grammarParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterListContext* C_grammarParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 70, C_grammarParser::RuleParameterList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(396);
    parameterDeclaration();
    setState(401);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(397);
        match(C_grammarParser::Comma);
        setState(398);
        parameterDeclaration(); 
      }
      setState(403);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclarationContext ------------------------------------------------------------------

C_grammarParser::ParameterDeclarationContext::ParameterDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::ParameterDeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::ParameterDeclarationContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterDeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}


size_t C_grammarParser::ParameterDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterDeclaration;
}

void C_grammarParser::ParameterDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterDeclaration(this);
}

void C_grammarParser::ParameterDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterDeclaration(this);
}


std::any C_grammarParser::ParameterDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::parameterDeclaration() {
  ParameterDeclarationContext *_localctx = _tracker.createInstance<ParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 72, C_grammarParser::RuleParameterDeclaration);
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
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(404);
      match(C_grammarParser::Const);
    }
    setState(407);
    typeSpecifier();
    setState(408);
    declarator();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

C_grammarParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Identifier() {
  return getTokens(C_grammarParser::Identifier);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Identifier(size_t i) {
  return getToken(C_grammarParser::Identifier, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::IdentifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleIdentifierList;
}

void C_grammarParser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void C_grammarParser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


std::any C_grammarParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IdentifierListContext* C_grammarParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 74, C_grammarParser::RuleIdentifierList);
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
    setState(410);
    match(C_grammarParser::Identifier);
    setState(415);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(411);
      match(C_grammarParser::Comma);
      setState(412);
      match(C_grammarParser::Identifier);
      setState(417);
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

//----------------- TypeNameContext ------------------------------------------------------------------

C_grammarParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::TypeNameContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::TypeNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeName;
}

void C_grammarParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void C_grammarParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


std::any C_grammarParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeNameContext* C_grammarParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 76, C_grammarParser::RuleTypeName);
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
    setState(419);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(418);
      specifierQualifierList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypedefNameContext ------------------------------------------------------------------

C_grammarParser::TypedefNameContext::TypedefNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypedefNameContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::TypedefNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypedefName;
}

void C_grammarParser::TypedefNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypedefName(this);
}

void C_grammarParser::TypedefNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypedefName(this);
}


std::any C_grammarParser::TypedefNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypedefName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypedefNameContext* C_grammarParser::typedefName() {
  TypedefNameContext *_localctx = _tracker.createInstance<TypedefNameContext>(_ctx, getState());
  enterRule(_localctx, 78, C_grammarParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    match(C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

C_grammarParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::InitializerContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::InitializerListContext* C_grammarParser::InitializerContext::initializerList() {
  return getRuleContext<C_grammarParser::InitializerListContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}


size_t C_grammarParser::InitializerContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializer;
}

void C_grammarParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void C_grammarParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}


std::any C_grammarParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerContext* C_grammarParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 80, C_grammarParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(431);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(423);
        assignmentExpression();
        break;
      }

      case C_grammarParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(424);
        match(C_grammarParser::LeftBrace);
        setState(425);
        initializerList();
        setState(427);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::Comma) {
          setState(426);
          match(C_grammarParser::Comma);
        }
        setState(429);
        match(C_grammarParser::RightBrace);
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

//----------------- FunctionCallExpressionContext ------------------------------------------------------------------

C_grammarParser::FunctionCallExpressionContext::FunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypedefNameContext* C_grammarParser::FunctionCallExpressionContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::FunctionCallExpressionContext::argumentExpressionList() {
  return getRuleContext<C_grammarParser::ArgumentExpressionListContext>(0);
}


size_t C_grammarParser::FunctionCallExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionCallExpression;
}

void C_grammarParser::FunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpression(this);
}

void C_grammarParser::FunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpression(this);
}


std::any C_grammarParser::FunctionCallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionCallExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::functionCallExpression() {
  FunctionCallExpressionContext *_localctx = _tracker.createInstance<FunctionCallExpressionContext>(_ctx, getState());
  enterRule(_localctx, 82, C_grammarParser::RuleFunctionCallExpression);
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
    setState(433);
    typedefName();
    setState(434);
    match(C_grammarParser::LeftParen);
    setState(436);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(435);
      argumentExpressionList();
    }
    setState(438);
    match(C_grammarParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ArgumentExpressionContext *> C_grammarParser::ArgumentExpressionListContext::argumentExpression() {
  return getRuleContexts<C_grammarParser::ArgumentExpressionContext>();
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::ArgumentExpressionListContext::argumentExpression(size_t i) {
  return getRuleContext<C_grammarParser::ArgumentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArgumentExpressionListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ArgumentExpressionListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ArgumentExpressionListContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpressionList;
}

void C_grammarParser::ArgumentExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpressionList(this);
}

void C_grammarParser::ArgumentExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpressionList(this);
}


std::any C_grammarParser::ArgumentExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpressionList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::argumentExpressionList() {
  ArgumentExpressionListContext *_localctx = _tracker.createInstance<ArgumentExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 84, C_grammarParser::RuleArgumentExpressionList);
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
    setState(440);
    argumentExpression();
    setState(445);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(441);
      match(C_grammarParser::Comma);
      setState(442);
      argumentExpression();
      setState(447);
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

//----------------- ArgumentExpressionContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionContext::ArgumentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArgumentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArgumentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpression;
}

void C_grammarParser::ArgumentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpression(this);
}

void C_grammarParser::ArgumentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpression(this);
}


std::any C_grammarParser::ArgumentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::argumentExpression() {
  ArgumentExpressionContext *_localctx = _tracker.createInstance<ArgumentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 86, C_grammarParser::RuleArgumentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(448);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerListContext ------------------------------------------------------------------

C_grammarParser::InitializerListContext::InitializerListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitializerContext *> C_grammarParser::InitializerListContext::initializer() {
  return getRuleContexts<C_grammarParser::InitializerContext>();
}

C_grammarParser::InitializerContext* C_grammarParser::InitializerListContext::initializer(size_t i) {
  return getRuleContext<C_grammarParser::InitializerContext>(i);
}

std::vector<C_grammarParser::DesignationContext *> C_grammarParser::InitializerListContext::designation() {
  return getRuleContexts<C_grammarParser::DesignationContext>();
}

C_grammarParser::DesignationContext* C_grammarParser::InitializerListContext::designation(size_t i) {
  return getRuleContext<C_grammarParser::DesignationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitializerListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitializerListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitializerListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializerList;
}

void C_grammarParser::InitializerListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializerList(this);
}

void C_grammarParser::InitializerListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializerList(this);
}


std::any C_grammarParser::InitializerListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializerList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerListContext* C_grammarParser::initializerList() {
  InitializerListContext *_localctx = _tracker.createInstance<InitializerListContext>(_ctx, getState());
  enterRule(_localctx, 88, C_grammarParser::RuleInitializerList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot) {
      setState(450);
      designation();
    }
    setState(453);
    initializer();
    setState(461);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(454);
        match(C_grammarParser::Comma);
        setState(456);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::LeftBracket

        || _la == C_grammarParser::Dot) {
          setState(455);
          designation();
        }
        setState(458);
        initializer(); 
      }
      setState(463);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignationContext ------------------------------------------------------------------

C_grammarParser::DesignationContext::DesignationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DesignatorListContext* C_grammarParser::DesignationContext::designatorList() {
  return getRuleContext<C_grammarParser::DesignatorListContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignationContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}


size_t C_grammarParser::DesignationContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignation;
}

void C_grammarParser::DesignationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignation(this);
}

void C_grammarParser::DesignationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignation(this);
}


std::any C_grammarParser::DesignationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignation(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignationContext* C_grammarParser::designation() {
  DesignationContext *_localctx = _tracker.createInstance<DesignationContext>(_ctx, getState());
  enterRule(_localctx, 90, C_grammarParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(464);
    designatorList();
    setState(465);
    match(C_grammarParser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorListContext ------------------------------------------------------------------

C_grammarParser::DesignatorListContext::DesignatorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DesignatorContext *> C_grammarParser::DesignatorListContext::designator() {
  return getRuleContexts<C_grammarParser::DesignatorContext>();
}

C_grammarParser::DesignatorContext* C_grammarParser::DesignatorListContext::designator(size_t i) {
  return getRuleContext<C_grammarParser::DesignatorContext>(i);
}


size_t C_grammarParser::DesignatorListContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignatorList;
}

void C_grammarParser::DesignatorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignatorList(this);
}

void C_grammarParser::DesignatorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignatorList(this);
}


std::any C_grammarParser::DesignatorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignatorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorListContext* C_grammarParser::designatorList() {
  DesignatorListContext *_localctx = _tracker.createInstance<DesignatorListContext>(_ctx, getState());
  enterRule(_localctx, 92, C_grammarParser::RuleDesignatorList);
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
    setState(468); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(467);
      designator();
      setState(470); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorContext ------------------------------------------------------------------

C_grammarParser::DesignatorContext::DesignatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DesignatorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::DesignatorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Dot() {
  return getToken(C_grammarParser::Dot, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::DesignatorContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignator;
}

void C_grammarParser::DesignatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignator(this);
}

void C_grammarParser::DesignatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignator(this);
}


std::any C_grammarParser::DesignatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorContext* C_grammarParser::designator() {
  DesignatorContext *_localctx = _tracker.createInstance<DesignatorContext>(_ctx, getState());
  enterRule(_localctx, 94, C_grammarParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(478);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(472);
        match(C_grammarParser::LeftBracket);
        setState(473);
        constantExpression();
        setState(474);
        match(C_grammarParser::RightBracket);
        break;
      }

      case C_grammarParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(476);
        match(C_grammarParser::Dot);
        setState(477);
        match(C_grammarParser::Identifier);
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

//----------------- StatementContext ------------------------------------------------------------------

C_grammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::StatementContext::expressionStatement() {
  return getRuleContext<C_grammarParser::ExpressionStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::StatementContext::selectionStatement() {
  return getRuleContext<C_grammarParser::SelectionStatementContext>(0);
}

C_grammarParser::IterationStatementContext* C_grammarParser::StatementContext::iterationStatement() {
  return getRuleContext<C_grammarParser::IterationStatementContext>(0);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::StatementContext::returnStatement() {
  return getRuleContext<C_grammarParser::ReturnStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::StatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

std::vector<C_grammarParser::LogicalOrExpressionContext *> C_grammarParser::StatementContext::logicalOrExpression() {
  return getRuleContexts<C_grammarParser::LogicalOrExpressionContext>();
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::StatementContext::logicalOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Colon() {
  return getTokens(C_grammarParser::Colon);
}

tree::TerminalNode* C_grammarParser::StatementContext::Colon(size_t i) {
  return getToken(C_grammarParser::Colon, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::StatementContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::StatementContext::getRuleIndex() const {
  return C_grammarParser::RuleStatement;
}

void C_grammarParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void C_grammarParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any C_grammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StatementContext* C_grammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 96, C_grammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(515);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(480);
      expressionStatement();
      setState(481);
      match(C_grammarParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(483);
      selectionStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(484);
      iterationStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(485);
      returnStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(486);
      match(C_grammarParser::LeftParen);
      setState(495);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 18) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
        | (1ULL << (C_grammarParser::PlusPlus - 18))
        | (1ULL << (C_grammarParser::Minus - 18))
        | (1ULL << (C_grammarParser::MinusMinus - 18))
        | (1ULL << (C_grammarParser::Not - 18))
        | (1ULL << (C_grammarParser::Tilde - 18))
        | (1ULL << (C_grammarParser::Identifier - 18))
        | (1ULL << (C_grammarParser::IntegerConstant - 18))
        | (1ULL << (C_grammarParser::FloatingConstant - 18))
        | (1ULL << (C_grammarParser::CharacterConstant - 18))
        | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
        setState(487);
        logicalOrExpression();
        setState(492);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C_grammarParser::Comma) {
          setState(488);
          match(C_grammarParser::Comma);
          setState(489);
          logicalOrExpression();
          setState(494);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(510);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::Colon) {
        setState(497);
        match(C_grammarParser::Colon);
        setState(506);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 18) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
          | (1ULL << (C_grammarParser::PlusPlus - 18))
          | (1ULL << (C_grammarParser::Minus - 18))
          | (1ULL << (C_grammarParser::MinusMinus - 18))
          | (1ULL << (C_grammarParser::Not - 18))
          | (1ULL << (C_grammarParser::Tilde - 18))
          | (1ULL << (C_grammarParser::Identifier - 18))
          | (1ULL << (C_grammarParser::IntegerConstant - 18))
          | (1ULL << (C_grammarParser::FloatingConstant - 18))
          | (1ULL << (C_grammarParser::CharacterConstant - 18))
          | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
          setState(498);
          logicalOrExpression();
          setState(503);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == C_grammarParser::Comma) {
            setState(499);
            match(C_grammarParser::Comma);
            setState(500);
            logicalOrExpression();
            setState(505);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(512);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(513);
      match(C_grammarParser::RightParen);
      setState(514);
      match(C_grammarParser::Semi);
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

//----------------- CompoundStatementContext ------------------------------------------------------------------

C_grammarParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::BlockItemContext *> C_grammarParser::CompoundStatementContext::blockItem() {
  return getRuleContexts<C_grammarParser::BlockItemContext>();
}

C_grammarParser::BlockItemContext* C_grammarParser::CompoundStatementContext::blockItem(size_t i) {
  return getRuleContext<C_grammarParser::BlockItemContext>(i);
}


size_t C_grammarParser::CompoundStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleCompoundStatement;
}

void C_grammarParser::CompoundStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompoundStatement(this);
}

void C_grammarParser::CompoundStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompoundStatement(this);
}


std::any C_grammarParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, C_grammarParser::RuleCompoundStatement);
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
    setState(517);
    match(C_grammarParser::LeftBrace);
    setState(521);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::IntegerConstant - 64))
      | (1ULL << (C_grammarParser::FloatingConstant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
      | (1ULL << (C_grammarParser::CharacterConstant - 64))
      | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
      setState(518);
      blockItem();
      setState(523);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(524);
    match(C_grammarParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

C_grammarParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::BlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::BlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::BlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::BlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleBlockItem;
}

void C_grammarParser::BlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItem(this);
}

void C_grammarParser::BlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItem(this);
}


std::any C_grammarParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::BlockItemContext* C_grammarParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 100, C_grammarParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(530);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(526);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(527);
      declaration();
      setState(528);
      match(C_grammarParser::Semi);
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

//----------------- ExpressionStatementContext ------------------------------------------------------------------

C_grammarParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionContext* C_grammarParser::ExpressionStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ExpressionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleExpressionStatement;
}

void C_grammarParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void C_grammarParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


std::any C_grammarParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 102, C_grammarParser::RuleExpressionStatement);
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
    setState(533);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(532);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfContentContext ------------------------------------------------------------------

C_grammarParser::IfContentContext::IfContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IfContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::IfContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::IfContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::IfContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::IfContentContext::getRuleIndex() const {
  return C_grammarParser::RuleIfContent;
}

void C_grammarParser::IfContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfContent(this);
}

void C_grammarParser::IfContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfContent(this);
}


std::any C_grammarParser::IfContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIfContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IfContentContext* C_grammarParser::ifContent() {
  IfContentContext *_localctx = _tracker.createInstance<IfContentContext>(_ctx, getState());
  enterRule(_localctx, 104, C_grammarParser::RuleIfContent);
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
    setState(544);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(535);
        match(C_grammarParser::LeftBrace);
        setState(539);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(536);
          conditionalBlockItem();
          setState(541);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(542);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(543);
        conditionalBlockItem();
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

//----------------- ElseContentContext ------------------------------------------------------------------

C_grammarParser::ElseContentContext::ElseContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ElseContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ElseContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::ElseContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::ElseContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::ElseContentContext::getRuleIndex() const {
  return C_grammarParser::RuleElseContent;
}

void C_grammarParser::ElseContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseContent(this);
}

void C_grammarParser::ElseContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseContent(this);
}


std::any C_grammarParser::ElseContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitElseContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ElseContentContext* C_grammarParser::elseContent() {
  ElseContentContext *_localctx = _tracker.createInstance<ElseContentContext>(_ctx, getState());
  enterRule(_localctx, 106, C_grammarParser::RuleElseContent);
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
    setState(555);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(546);
        match(C_grammarParser::LeftBrace);
        setState(550);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(547);
          conditionalBlockItem();
          setState(552);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(553);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(554);
        conditionalBlockItem();
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

//----------------- ConditionalBlockItemContext ------------------------------------------------------------------

C_grammarParser::ConditionalBlockItemContext::ConditionalBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ConditionalBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ConditionalBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ConditionalBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalBlockItem;
}

void C_grammarParser::ConditionalBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalBlockItem(this);
}

void C_grammarParser::ConditionalBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalBlockItem(this);
}


std::any C_grammarParser::ConditionalBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::conditionalBlockItem() {
  ConditionalBlockItemContext *_localctx = _tracker.createInstance<ConditionalBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 108, C_grammarParser::RuleConditionalBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(561);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(557);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(558);
      declaration();
      setState(559);
      match(C_grammarParser::Semi);
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

//----------------- ConditionContentContext ------------------------------------------------------------------

C_grammarParser::ConditionContentContext::ConditionContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionContentContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ConditionContentContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionContent;
}

void C_grammarParser::ConditionContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionContent(this);
}

void C_grammarParser::ConditionContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionContent(this);
}


std::any C_grammarParser::ConditionContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionContentContext* C_grammarParser::conditionContent() {
  ConditionContentContext *_localctx = _tracker.createInstance<ConditionContentContext>(_ctx, getState());
  enterRule(_localctx, 110, C_grammarParser::RuleConditionContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(563);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

C_grammarParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::If() {
  return getToken(C_grammarParser::If, 0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ConditionContentContext* C_grammarParser::SelectionStatementContext::conditionContent() {
  return getRuleContext<C_grammarParser::ConditionContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::IfContentContext* C_grammarParser::SelectionStatementContext::ifContent() {
  return getRuleContext<C_grammarParser::IfContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::Else() {
  return getToken(C_grammarParser::Else, 0);
}

C_grammarParser::ElseContentContext* C_grammarParser::SelectionStatementContext::elseContent() {
  return getRuleContext<C_grammarParser::ElseContentContext>(0);
}


size_t C_grammarParser::SelectionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleSelectionStatement;
}

void C_grammarParser::SelectionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectionStatement(this);
}

void C_grammarParser::SelectionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectionStatement(this);
}


std::any C_grammarParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 112, C_grammarParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(565);
    match(C_grammarParser::If);
    setState(566);
    match(C_grammarParser::LeftParen);
    setState(567);
    conditionContent();
    setState(568);
    match(C_grammarParser::RightParen);
    setState(569);
    ifContent();
    setState(572);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      setState(570);
      match(C_grammarParser::Else);
      setState(571);
      elseContent();
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

//----------------- IterationStatementContext ------------------------------------------------------------------

C_grammarParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::For() {
  return getToken(C_grammarParser::For, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::IterationStatementContext::forDeclaration() {
  return getRuleContext<C_grammarParser::ForDeclarationContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::IterationStatementContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::IterationStatementContext::forExitCondition() {
  return getRuleContext<C_grammarParser::ForExitConditionContext>(0);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::IterationStatementContext::forIterationExpression() {
  return getRuleContext<C_grammarParser::ForIterationExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ForContentContext* C_grammarParser::IterationStatementContext::forContent() {
  return getRuleContext<C_grammarParser::ForContentContext>(0);
}


size_t C_grammarParser::IterationStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleIterationStatement;
}

void C_grammarParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void C_grammarParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}


std::any C_grammarParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IterationStatementContext* C_grammarParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 114, C_grammarParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(C_grammarParser::For);
    setState(575);
    match(C_grammarParser::LeftParen);
    setState(576);
    forDeclaration();
    setState(577);
    match(C_grammarParser::Semi);
    setState(578);
    forExitCondition();
    setState(579);
    match(C_grammarParser::Semi);
    setState(580);
    forIterationExpression();
    setState(581);
    match(C_grammarParser::RightParen);
    setState(582);
    forContent();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForContentContext ------------------------------------------------------------------

C_grammarParser::ForContentContext::ForContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ForContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ForContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ForBlockItemContext *> C_grammarParser::ForContentContext::forBlockItem() {
  return getRuleContexts<C_grammarParser::ForBlockItemContext>();
}

C_grammarParser::ForBlockItemContext* C_grammarParser::ForContentContext::forBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ForBlockItemContext>(i);
}


size_t C_grammarParser::ForContentContext::getRuleIndex() const {
  return C_grammarParser::RuleForContent;
}

void C_grammarParser::ForContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForContent(this);
}

void C_grammarParser::ForContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForContent(this);
}


std::any C_grammarParser::ForContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForContentContext* C_grammarParser::forContent() {
  ForContentContext *_localctx = _tracker.createInstance<ForContentContext>(_ctx, getState());
  enterRule(_localctx, 116, C_grammarParser::RuleForContent);
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
    setState(593);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(584);
        match(C_grammarParser::LeftBrace);
        setState(588);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(585);
          forBlockItem();
          setState(590);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(591);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(592);
        forBlockItem();
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

//----------------- ForBlockItemContext ------------------------------------------------------------------

C_grammarParser::ForBlockItemContext::ForBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ForBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ForBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ForBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ForBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleForBlockItem;
}

void C_grammarParser::ForBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForBlockItem(this);
}

void C_grammarParser::ForBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForBlockItem(this);
}


std::any C_grammarParser::ForBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForBlockItemContext* C_grammarParser::forBlockItem() {
  ForBlockItemContext *_localctx = _tracker.createInstance<ForBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 118, C_grammarParser::RuleForBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(599);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(595);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(596);
      declaration();
      setState(597);
      match(C_grammarParser::Semi);
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

//----------------- ForExitConditionContext ------------------------------------------------------------------

C_grammarParser::ForExitConditionContext::ForExitConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForExitConditionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ForExitConditionContext::getRuleIndex() const {
  return C_grammarParser::RuleForExitCondition;
}

void C_grammarParser::ForExitConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForExitCondition(this);
}

void C_grammarParser::ForExitConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForExitCondition(this);
}


std::any C_grammarParser::ForExitConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForExitCondition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::forExitCondition() {
  ForExitConditionContext *_localctx = _tracker.createInstance<ForExitConditionContext>(_ctx, getState());
  enterRule(_localctx, 120, C_grammarParser::RuleForExitCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForDeclarationContext ------------------------------------------------------------------

C_grammarParser::ForDeclarationContext::ForDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclarationContext* C_grammarParser::ForDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}


size_t C_grammarParser::ForDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleForDeclaration;
}

void C_grammarParser::ForDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForDeclaration(this);
}

void C_grammarParser::ForDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForDeclaration(this);
}


std::any C_grammarParser::ForDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::forDeclaration() {
  ForDeclarationContext *_localctx = _tracker.createInstance<ForDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 122, C_grammarParser::RuleForDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(603);
    declaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForIterationExpressionContext ------------------------------------------------------------------

C_grammarParser::ForIterationExpressionContext::ForIterationExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ForIterationExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForIterationExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ForIterationExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ForIterationExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ForIterationExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleForIterationExpression;
}

void C_grammarParser::ForIterationExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForIterationExpression(this);
}

void C_grammarParser::ForIterationExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForIterationExpression(this);
}


std::any C_grammarParser::ForIterationExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForIterationExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::forIterationExpression() {
  ForIterationExpressionContext *_localctx = _tracker.createInstance<ForIterationExpressionContext>(_ctx, getState());
  enterRule(_localctx, 124, C_grammarParser::RuleForIterationExpression);
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
    setState(605);
    assignmentExpression();
    setState(610);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(606);
      match(C_grammarParser::Comma);
      setState(607);
      assignmentExpression();
      setState(612);
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

//----------------- ReturnStatementContext ------------------------------------------------------------------

C_grammarParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Return() {
  return getToken(C_grammarParser::Return, 0);
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ReturnStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ReturnStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleReturnStatement;
}

void C_grammarParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void C_grammarParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any C_grammarParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 126, C_grammarParser::RuleReturnStatement);
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
    setState(613);
    match(C_grammarParser::Return);
    setState(615);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(614);
      expression();
    }
    setState(617);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TranslationUnitContext ------------------------------------------------------------------

C_grammarParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExternalDeclarationContext *> C_grammarParser::TranslationUnitContext::externalDeclaration() {
  return getRuleContexts<C_grammarParser::ExternalDeclarationContext>();
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::TranslationUnitContext::externalDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ExternalDeclarationContext>(i);
}


size_t C_grammarParser::TranslationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleTranslationUnit;
}

void C_grammarParser::TranslationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTranslationUnit(this);
}

void C_grammarParser::TranslationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTranslationUnit(this);
}


std::any C_grammarParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 128, C_grammarParser::RuleTranslationUnit);
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
    setState(620); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(619);
      externalDeclaration();
      setState(622); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::LeftParen - 2))
      | (1ULL << (C_grammarParser::Semi - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalDeclarationContext ------------------------------------------------------------------

C_grammarParser::ExternalDeclarationContext::ExternalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::ExternalDeclarationContext::functionDefinition() {
  return getRuleContext<C_grammarParser::FunctionDefinitionContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ExternalDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ExternalDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ExternalDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleExternalDeclaration;
}

void C_grammarParser::ExternalDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternalDeclaration(this);
}

void C_grammarParser::ExternalDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternalDeclaration(this);
}


std::any C_grammarParser::ExternalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExternalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::externalDeclaration() {
  ExternalDeclarationContext *_localctx = _tracker.createInstance<ExternalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 130, C_grammarParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(629);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(624);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(625);
      declaration();
      setState(626);
      match(C_grammarParser::Semi);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(628);
      match(C_grammarParser::Semi);
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

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

C_grammarParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::FunctionDefinitionContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<C_grammarParser::CompoundStatementContext>(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::FunctionDefinitionContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclarationListContext* C_grammarParser::FunctionDefinitionContext::declarationList() {
  return getRuleContext<C_grammarParser::DeclarationListContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionDefinitionContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}


size_t C_grammarParser::FunctionDefinitionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionDefinition;
}

void C_grammarParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void C_grammarParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


std::any C_grammarParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 132, C_grammarParser::RuleFunctionDefinition);
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
    setState(635);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      setState(632);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Const) {
        setState(631);
        match(C_grammarParser::Const);
      }
      setState(634);
      typeSpecifier();
      break;
    }

    default:
      break;
    }
    setState(637);
    declarator();
    setState(639);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(638);
      declarationList();
    }
    setState(641);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

C_grammarParser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DeclarationContext *> C_grammarParser::DeclarationListContext::declaration() {
  return getRuleContexts<C_grammarParser::DeclarationContext>();
}

C_grammarParser::DeclarationContext* C_grammarParser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<C_grammarParser::DeclarationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::DeclarationListContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::DeclarationListContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}


size_t C_grammarParser::DeclarationListContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationList;
}

void C_grammarParser::DeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationList(this);
}

void C_grammarParser::DeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationList(this);
}


std::any C_grammarParser::DeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationListContext* C_grammarParser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 134, C_grammarParser::RuleDeclarationList);
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
    setState(646); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(643);
      declaration();
      setState(644);
      match(C_grammarParser::Semi);
      setState(648); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

C_grammarParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ConstantContext::IntegerConstant() {
  return getToken(C_grammarParser::IntegerConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::FloatingConstant() {
  return getToken(C_grammarParser::FloatingConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::CharacterConstant() {
  return getToken(C_grammarParser::CharacterConstant, 0);
}


size_t C_grammarParser::ConstantContext::getRuleIndex() const {
  return C_grammarParser::RuleConstant;
}

void C_grammarParser::ConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant(this);
}

void C_grammarParser::ConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant(this);
}


std::any C_grammarParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantContext* C_grammarParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 136, C_grammarParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(659);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(651);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(650);
        match(C_grammarParser::Minus);
      }
      setState(653);
      match(C_grammarParser::IntegerConstant);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(655);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(654);
        match(C_grammarParser::Minus);
      }
      setState(657);
      match(C_grammarParser::FloatingConstant);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(658);
      match(C_grammarParser::CharacterConstant);
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

bool C_grammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 31: return directDeclaratorSempred(antlrcpp::downCast<DirectDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void C_grammarParser::initialize() {
  std::call_once(c_grammarParserOnceFlag, c_grammarParserInitialize);
}
