
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "asm_grammarListener.h"


namespace asm_parser {

/**
 * This class provides an empty implementation of asm_grammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  asm_grammarBaseListener : public asm_grammarListener {
public:

  virtual void enterProgram(asm_grammarParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(asm_grammarParser::ProgramContext * /*ctx*/) override { }

  virtual void enterCode(asm_grammarParser::CodeContext * /*ctx*/) override { }
  virtual void exitCode(asm_grammarParser::CodeContext * /*ctx*/) override { }

  virtual void enterDeclaration(asm_grammarParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(asm_grammarParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterInstruction(asm_grammarParser::InstructionContext * /*ctx*/) override { }
  virtual void exitInstruction(asm_grammarParser::InstructionContext * /*ctx*/) override { }

  virtual void enterReg_instr(asm_grammarParser::Reg_instrContext * /*ctx*/) override { }
  virtual void exitReg_instr(asm_grammarParser::Reg_instrContext * /*ctx*/) override { }

  virtual void enterImm_instr(asm_grammarParser::Imm_instrContext * /*ctx*/) override { }
  virtual void exitImm_instr(asm_grammarParser::Imm_instrContext * /*ctx*/) override { }

  virtual void enterLoad_instr(asm_grammarParser::Load_instrContext * /*ctx*/) override { }
  virtual void exitLoad_instr(asm_grammarParser::Load_instrContext * /*ctx*/) override { }

  virtual void enterBranch_instr(asm_grammarParser::Branch_instrContext * /*ctx*/) override { }
  virtual void exitBranch_instr(asm_grammarParser::Branch_instrContext * /*ctx*/) override { }

  virtual void enterConv_instr(asm_grammarParser::Conv_instrContext * /*ctx*/) override { }
  virtual void exitConv_instr(asm_grammarParser::Conv_instrContext * /*ctx*/) override { }

  virtual void enterIndep_instr(asm_grammarParser::Indep_instrContext * /*ctx*/) override { }
  virtual void exitIndep_instr(asm_grammarParser::Indep_instrContext * /*ctx*/) override { }

  virtual void enterPseudo_instr(asm_grammarParser::Pseudo_instrContext * /*ctx*/) override { }
  virtual void exitPseudo_instr(asm_grammarParser::Pseudo_instrContext * /*ctx*/) override { }

  virtual void enterOperand(asm_grammarParser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(asm_grammarParser::OperandContext * /*ctx*/) override { }

  virtual void enterDestination(asm_grammarParser::DestinationContext * /*ctx*/) override { }
  virtual void exitDestination(asm_grammarParser::DestinationContext * /*ctx*/) override { }

  virtual void enterImmediate(asm_grammarParser::ImmediateContext * /*ctx*/) override { }
  virtual void exitImmediate(asm_grammarParser::ImmediateContext * /*ctx*/) override { }

  virtual void enterFloat_const(asm_grammarParser::Float_constContext * /*ctx*/) override { }
  virtual void exitFloat_const(asm_grammarParser::Float_constContext * /*ctx*/) override { }

  virtual void enterInteger_const(asm_grammarParser::Integer_constContext * /*ctx*/) override { }
  virtual void exitInteger_const(asm_grammarParser::Integer_constContext * /*ctx*/) override { }

  virtual void enterReg_opcode(asm_grammarParser::Reg_opcodeContext * /*ctx*/) override { }
  virtual void exitReg_opcode(asm_grammarParser::Reg_opcodeContext * /*ctx*/) override { }

  virtual void enterConv_opcode(asm_grammarParser::Conv_opcodeContext * /*ctx*/) override { }
  virtual void exitConv_opcode(asm_grammarParser::Conv_opcodeContext * /*ctx*/) override { }

  virtual void enterImm_opcode(asm_grammarParser::Imm_opcodeContext * /*ctx*/) override { }
  virtual void exitImm_opcode(asm_grammarParser::Imm_opcodeContext * /*ctx*/) override { }

  virtual void enterBranch_opcode(asm_grammarParser::Branch_opcodeContext * /*ctx*/) override { }
  virtual void exitBranch_opcode(asm_grammarParser::Branch_opcodeContext * /*ctx*/) override { }

  virtual void enterPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext * /*ctx*/) override { }
  virtual void exitPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext * /*ctx*/) override { }

  virtual void enterFor_block(asm_grammarParser::For_blockContext * /*ctx*/) override { }
  virtual void exitFor_block(asm_grammarParser::For_blockContext * /*ctx*/) override { }

  virtual void enterFor_incr(asm_grammarParser::For_incrContext * /*ctx*/) override { }
  virtual void exitFor_incr(asm_grammarParser::For_incrContext * /*ctx*/) override { }

  virtual void enterFor_dec(asm_grammarParser::For_decContext * /*ctx*/) override { }
  virtual void exitFor_dec(asm_grammarParser::For_decContext * /*ctx*/) override { }

  virtual void enterFor_decl(asm_grammarParser::For_declContext * /*ctx*/) override { }
  virtual void exitFor_decl(asm_grammarParser::For_declContext * /*ctx*/) override { }

  virtual void enterFor_end(asm_grammarParser::For_endContext * /*ctx*/) override { }
  virtual void exitFor_end(asm_grammarParser::For_endContext * /*ctx*/) override { }

  virtual void enterFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext * /*ctx*/) override { }
  virtual void exitFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext * /*ctx*/) override { }

  virtual void enterPragma(asm_grammarParser::PragmaContext * /*ctx*/) override { }
  virtual void exitPragma(asm_grammarParser::PragmaContext * /*ctx*/) override { }

  virtual void enterVariable_decl(asm_grammarParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(asm_grammarParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterConstant_decl(asm_grammarParser::Constant_declContext * /*ctx*/) override { }
  virtual void exitConstant_decl(asm_grammarParser::Constant_declContext * /*ctx*/) override { }

  virtual void enterInput_decl(asm_grammarParser::Input_declContext * /*ctx*/) override { }
  virtual void exitInput_decl(asm_grammarParser::Input_declContext * /*ctx*/) override { }

  virtual void enterOutput_decl(asm_grammarParser::Output_declContext * /*ctx*/) override { }
  virtual void exitOutput_decl(asm_grammarParser::Output_declContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace asm_parser
