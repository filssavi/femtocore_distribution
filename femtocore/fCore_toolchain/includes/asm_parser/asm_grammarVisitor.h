
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "asm_grammarParser.h"


namespace asm_parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by asm_grammarParser.
 */
class  asm_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by asm_grammarParser.
   */
    virtual std::any visitProgram(asm_grammarParser::ProgramContext *context) = 0;

    virtual std::any visitCode(asm_grammarParser::CodeContext *context) = 0;

    virtual std::any visitDeclaration(asm_grammarParser::DeclarationContext *context) = 0;

    virtual std::any visitInstruction(asm_grammarParser::InstructionContext *context) = 0;

    virtual std::any visitReg_instr(asm_grammarParser::Reg_instrContext *context) = 0;

    virtual std::any visitImm_instr(asm_grammarParser::Imm_instrContext *context) = 0;

    virtual std::any visitLoad_instr(asm_grammarParser::Load_instrContext *context) = 0;

    virtual std::any visitBranch_instr(asm_grammarParser::Branch_instrContext *context) = 0;

    virtual std::any visitConv_instr(asm_grammarParser::Conv_instrContext *context) = 0;

    virtual std::any visitIndep_instr(asm_grammarParser::Indep_instrContext *context) = 0;

    virtual std::any visitPseudo_instr(asm_grammarParser::Pseudo_instrContext *context) = 0;

    virtual std::any visitOperand(asm_grammarParser::OperandContext *context) = 0;

    virtual std::any visitDestination(asm_grammarParser::DestinationContext *context) = 0;

    virtual std::any visitImmediate(asm_grammarParser::ImmediateContext *context) = 0;

    virtual std::any visitFloat_const(asm_grammarParser::Float_constContext *context) = 0;

    virtual std::any visitInteger_const(asm_grammarParser::Integer_constContext *context) = 0;

    virtual std::any visitReg_opcode(asm_grammarParser::Reg_opcodeContext *context) = 0;

    virtual std::any visitConv_opcode(asm_grammarParser::Conv_opcodeContext *context) = 0;

    virtual std::any visitImm_opcode(asm_grammarParser::Imm_opcodeContext *context) = 0;

    virtual std::any visitBranch_opcode(asm_grammarParser::Branch_opcodeContext *context) = 0;

    virtual std::any visitPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext *context) = 0;

    virtual std::any visitFor_block(asm_grammarParser::For_blockContext *context) = 0;

    virtual std::any visitFor_incr(asm_grammarParser::For_incrContext *context) = 0;

    virtual std::any visitFor_dec(asm_grammarParser::For_decContext *context) = 0;

    virtual std::any visitFor_decl(asm_grammarParser::For_declContext *context) = 0;

    virtual std::any visitFor_end(asm_grammarParser::For_endContext *context) = 0;

    virtual std::any visitFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext *context) = 0;

    virtual std::any visitPragma(asm_grammarParser::PragmaContext *context) = 0;

    virtual std::any visitVariable_decl(asm_grammarParser::Variable_declContext *context) = 0;

    virtual std::any visitConstant_decl(asm_grammarParser::Constant_declContext *context) = 0;

    virtual std::any visitInput_decl(asm_grammarParser::Input_declContext *context) = 0;

    virtual std::any visitOutput_decl(asm_grammarParser::Output_declContext *context) = 0;


};

}  // namespace asm_parser
