// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP
#define FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP

#include "asm_parser/asm_grammarBaseListener.h"
#include "asm_parser/asm_grammarParser.h"
#include "fCore_isa.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "data_structures/common/variable.hpp"
#include "tools/variable_map.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>


typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class AsmTree_visitor : public  asm_parser::asm_grammarBaseListener{
public:
    explicit AsmTree_visitor(std::shared_ptr<variable_map> map);
    void exitReg_instr(asm_parser::asm_grammarParser::Reg_instrContext * ctx) override;
    void exitPseudo_instr(asm_parser::asm_grammarParser::Pseudo_instrContext *ctx) override;
    void exitIndep_instr(asm_parser::asm_grammarParser::Indep_instrContext * ctx) override;
    void exitBranch_instr(asm_parser::asm_grammarParser::Branch_instrContext * ctx) override;
    void exitConv_instr(asm_parser::asm_grammarParser::Conv_instrContext *ctx) override;
    void exitLoad_instr(asm_parser::asm_grammarParser::Load_instrContext *ctx) override;
    void enterFor_block(asm_parser::asm_grammarParser::For_blockContext * ctx) override;
    void exitFor_block(asm_parser::asm_grammarParser::For_blockContext * ctx) override;
    void exitProgram(asm_parser::asm_grammarParser::ProgramContext * ctx) override;
    void enterProgram(asm_parser::asm_grammarParser::ProgramContext *ctx) override;
    void exitPragma(asm_parser::asm_grammarParser::PragmaContext *ctx) override;
    void exitConstant_decl(asm_parser::asm_grammarParser::Constant_declContext *ctx) override;
    void exitVariable_decl(asm_parser::asm_grammarParser::Variable_declContext *ctx) override;
    void exitInput_decl(asm_parser::asm_grammarParser::Input_declContext *ctx) override;
    void exitOutput_decl(asm_parser::asm_grammarParser::Output_declContext *ctx) override;
    void exitImmediate(asm_parser::asm_grammarParser::ImmediateContext *ctx) override;
    void exitFloat_const(asm_parser::asm_grammarParser::Float_constContext *ctx) override;
    std::shared_ptr<ll_ast_node> get_program();

private:
    std::shared_ptr<ll_ast_node> program_head{};
    std::shared_ptr<ll_ast_node> current_element{};
    std::stack<std::shared_ptr<ll_ast_node>> parent_elements;
    std::shared_ptr<variable_map> varmap;
};

#endif //FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP
