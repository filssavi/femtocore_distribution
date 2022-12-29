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

#ifndef FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
#define FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP


#include <utility>
#include <stdexcept>

#include "tools/variable_map.hpp"
#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"

class high_level_ast_lowering {
public:
    explicit high_level_ast_lowering();
    void set_input_ast(std::shared_ptr<hl_ast_node> i) {input_ast = std::move(i);};
    void translate();
    std::shared_ptr<ll_ast_node> get_output_ast() {return output_ast;};
private:
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_ast_node>& input);
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_expression_node>& input, const std::shared_ptr<variable>& dest);
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_ast_operand>& input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_definition_node>& input, const std::shared_ptr<variable>& dest);
    std::shared_ptr<ll_ast_node> process_unary_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> process_immediate_expression(std::shared_ptr<hl_expression_node> input);
    std::shared_ptr<ll_ast_node> process_regular_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<hl_ast_node> input_ast;
    std::shared_ptr<ll_ast_node> output_ast;

    std::shared_ptr<ll_ast_node> create_ast_node(isa_instruction_type t, std::vector<std::shared_ptr<variable>> args, const std::string& op);
    std::map<expression_type_t, std::string> expr_instruction_mapping;

};


#endif //FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
