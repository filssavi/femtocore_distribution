
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "asm_grammarVisitor.h"


namespace asm_parser {

/**
 * This class provides an empty implementation of asm_grammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  asm_grammarBaseVisitor : public asm_grammarVisitor {
public:

  virtual std::any visitProgram(asm_grammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCode(asm_grammarParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(asm_grammarParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstruction(asm_grammarParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReg_instr(asm_grammarParser::Reg_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImm_instr(asm_grammarParser::Imm_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoad_instr(asm_grammarParser::Load_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBranch_instr(asm_grammarParser::Branch_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConv_instr(asm_grammarParser::Conv_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndep_instr(asm_grammarParser::Indep_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudo_instr(asm_grammarParser::Pseudo_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperand(asm_grammarParser::OperandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDestination(asm_grammarParser::DestinationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImmediate(asm_grammarParser::ImmediateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloat_const(asm_grammarParser::Float_constContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteger_const(asm_grammarParser::Integer_constContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReg_opcode(asm_grammarParser::Reg_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConv_opcode(asm_grammarParser::Conv_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImm_opcode(asm_grammarParser::Imm_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBranch_opcode(asm_grammarParser::Branch_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_block(asm_grammarParser::For_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_incr(asm_grammarParser::For_incrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_dec(asm_grammarParser::For_decContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_decl(asm_grammarParser::For_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_end(asm_grammarParser::For_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPragma(asm_grammarParser::PragmaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_decl(asm_grammarParser::Variable_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstant_decl(asm_grammarParser::Constant_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_decl(asm_grammarParser::Input_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOutput_decl(asm_grammarParser::Output_declContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace asm_parser
