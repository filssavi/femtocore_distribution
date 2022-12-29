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

#ifndef FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP
#define FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "AsmTree_visitor.hpp"
#include "AsmErrorHandling.hpp"

#include "antlr4-runtime.h"
#include "asm_parser/asm_grammarLexer.h"
#include "asm_parser/asm_grammarParser.h"

class asm_language_parser{
    public:
    explicit asm_language_parser(std::istream &stream);
    asm_language_parser(std::istream &stream, std::shared_ptr<variable_map> new_varmap);
    void construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};

    std::shared_ptr<ll_ast_node> AST;
    varmap_t var_map;

    std::string error;


    private:

    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
};


#endif //FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP
