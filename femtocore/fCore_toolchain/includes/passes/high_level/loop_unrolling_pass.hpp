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


#ifndef FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H
#define FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H


#include <utility>

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/expression_evaluator.hpp"
#include "data_structures/common/variable.hpp"

class loop_unrolling_pass : public pass_base<hl_ast_node> {
public:
    loop_unrolling_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:

    std::shared_ptr<hl_ast_node> process_function_def(const std::shared_ptr<hl_function_def_node> &node);

    std::vector<std::shared_ptr<hl_ast_node>> process_loop(const std::shared_ptr<hl_ast_loop_node>& element);
    unsigned int process_loop_initializer(const std::shared_ptr<hl_ast_node>& raw_initializer);
    bool evaluate_loop(const std::shared_ptr<hl_expression_node>& condition, const std::shared_ptr<hl_expression_node>& iteration_exp, std::shared_ptr<hl_ast_operand> &loop_var);
    std::shared_ptr<hl_expression_node> update_loop_condition(std::shared_ptr<hl_expression_node> expression, std::shared_ptr<hl_ast_operand> loop_var);
    void update_expression(std::shared_ptr<hl_expression_node> expression, std::shared_ptr<hl_ast_operand> loop_var);

    std::shared_ptr<hl_ast_node> substitute_index(std::shared_ptr<hl_ast_node> element, std::string idx_name, int value);
    std::shared_ptr<hl_expression_node> substitute_index_in_expression(const std::shared_ptr<hl_expression_node>& node, const std::string& idx_name, int value);
    std::shared_ptr<hl_definition_node> substitute_index_in_definition(const std::shared_ptr<hl_definition_node>& node, const std::string& idx_name, int value);
    std::shared_ptr<hl_ast_operand> substitute_index_in_operand(const std::shared_ptr<hl_ast_operand>& node, const std::string& idx_name, int value);
    std::shared_ptr<hl_ast_conditional_node> substitute_index_in_conditional(const std::shared_ptr<hl_ast_conditional_node> &node, const std::string &idx_name, int value);
    std::shared_ptr<hl_function_call_node> substitute_index_in_function_call(const std::shared_ptr<hl_function_call_node> &node, const std::string &idx_name, int value);

    std::vector<std::shared_ptr<hl_ast_node>> proces_array_of_indices(const std::vector<std::shared_ptr<hl_ast_node>>& old_idx_array, const std::string& idx_name, int value);
    const unsigned int max_loop_iterations = 32767;
    unsigned int current_loop_iteration;

};


#endif //FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H
