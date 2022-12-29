
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "asm_grammarParser.h"


namespace asm_parser {

/**
 * This interface defines an abstract listener for a parse tree produced by asm_grammarParser.
 */
class  asm_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(asm_grammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(asm_grammarParser::ProgramContext *ctx) = 0;

  virtual void enterCode(asm_grammarParser::CodeContext *ctx) = 0;
  virtual void exitCode(asm_grammarParser::CodeContext *ctx) = 0;

  virtual void enterDeclaration(asm_grammarParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(asm_grammarParser::DeclarationContext *ctx) = 0;

  virtual void enterInstruction(asm_grammarParser::InstructionContext *ctx) = 0;
  virtual void exitInstruction(asm_grammarParser::InstructionContext *ctx) = 0;

  virtual void enterReg_instr(asm_grammarParser::Reg_instrContext *ctx) = 0;
  virtual void exitReg_instr(asm_grammarParser::Reg_instrContext *ctx) = 0;

  virtual void enterImm_instr(asm_grammarParser::Imm_instrContext *ctx) = 0;
  virtual void exitImm_instr(asm_grammarParser::Imm_instrContext *ctx) = 0;

  virtual void enterLoad_instr(asm_grammarParser::Load_instrContext *ctx) = 0;
  virtual void exitLoad_instr(asm_grammarParser::Load_instrContext *ctx) = 0;

  virtual void enterBranch_instr(asm_grammarParser::Branch_instrContext *ctx) = 0;
  virtual void exitBranch_instr(asm_grammarParser::Branch_instrContext *ctx) = 0;

  virtual void enterConv_instr(asm_grammarParser::Conv_instrContext *ctx) = 0;
  virtual void exitConv_instr(asm_grammarParser::Conv_instrContext *ctx) = 0;

  virtual void enterIndep_instr(asm_grammarParser::Indep_instrContext *ctx) = 0;
  virtual void exitIndep_instr(asm_grammarParser::Indep_instrContext *ctx) = 0;

  virtual void enterPseudo_instr(asm_grammarParser::Pseudo_instrContext *ctx) = 0;
  virtual void exitPseudo_instr(asm_grammarParser::Pseudo_instrContext *ctx) = 0;

  virtual void enterOperand(asm_grammarParser::OperandContext *ctx) = 0;
  virtual void exitOperand(asm_grammarParser::OperandContext *ctx) = 0;

  virtual void enterDestination(asm_grammarParser::DestinationContext *ctx) = 0;
  virtual void exitDestination(asm_grammarParser::DestinationContext *ctx) = 0;

  virtual void enterImmediate(asm_grammarParser::ImmediateContext *ctx) = 0;
  virtual void exitImmediate(asm_grammarParser::ImmediateContext *ctx) = 0;

  virtual void enterFloat_const(asm_grammarParser::Float_constContext *ctx) = 0;
  virtual void exitFloat_const(asm_grammarParser::Float_constContext *ctx) = 0;

  virtual void enterInteger_const(asm_grammarParser::Integer_constContext *ctx) = 0;
  virtual void exitInteger_const(asm_grammarParser::Integer_constContext *ctx) = 0;

  virtual void enterReg_opcode(asm_grammarParser::Reg_opcodeContext *ctx) = 0;
  virtual void exitReg_opcode(asm_grammarParser::Reg_opcodeContext *ctx) = 0;

  virtual void enterConv_opcode(asm_grammarParser::Conv_opcodeContext *ctx) = 0;
  virtual void exitConv_opcode(asm_grammarParser::Conv_opcodeContext *ctx) = 0;

  virtual void enterImm_opcode(asm_grammarParser::Imm_opcodeContext *ctx) = 0;
  virtual void exitImm_opcode(asm_grammarParser::Imm_opcodeContext *ctx) = 0;

  virtual void enterBranch_opcode(asm_grammarParser::Branch_opcodeContext *ctx) = 0;
  virtual void exitBranch_opcode(asm_grammarParser::Branch_opcodeContext *ctx) = 0;

  virtual void enterPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext *ctx) = 0;
  virtual void exitPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext *ctx) = 0;

  virtual void enterFor_block(asm_grammarParser::For_blockContext *ctx) = 0;
  virtual void exitFor_block(asm_grammarParser::For_blockContext *ctx) = 0;

  virtual void enterFor_incr(asm_grammarParser::For_incrContext *ctx) = 0;
  virtual void exitFor_incr(asm_grammarParser::For_incrContext *ctx) = 0;

  virtual void enterFor_dec(asm_grammarParser::For_decContext *ctx) = 0;
  virtual void exitFor_dec(asm_grammarParser::For_decContext *ctx) = 0;

  virtual void enterFor_decl(asm_grammarParser::For_declContext *ctx) = 0;
  virtual void exitFor_decl(asm_grammarParser::For_declContext *ctx) = 0;

  virtual void enterFor_end(asm_grammarParser::For_endContext *ctx) = 0;
  virtual void exitFor_end(asm_grammarParser::For_endContext *ctx) = 0;

  virtual void enterFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext *ctx) = 0;
  virtual void exitFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext *ctx) = 0;

  virtual void enterPragma(asm_grammarParser::PragmaContext *ctx) = 0;
  virtual void exitPragma(asm_grammarParser::PragmaContext *ctx) = 0;

  virtual void enterVariable_decl(asm_grammarParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(asm_grammarParser::Variable_declContext *ctx) = 0;

  virtual void enterConstant_decl(asm_grammarParser::Constant_declContext *ctx) = 0;
  virtual void exitConstant_decl(asm_grammarParser::Constant_declContext *ctx) = 0;

  virtual void enterInput_decl(asm_grammarParser::Input_declContext *ctx) = 0;
  virtual void exitInput_decl(asm_grammarParser::Input_declContext *ctx) = 0;

  virtual void enterOutput_decl(asm_grammarParser::Output_declContext *ctx) = 0;
  virtual void exitOutput_decl(asm_grammarParser::Output_declContext *ctx) = 0;


};

}  // namespace asm_parser
