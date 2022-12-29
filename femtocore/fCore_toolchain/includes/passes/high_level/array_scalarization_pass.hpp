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
//

#ifndef FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP
#define FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP

#include "passes/pass_base.hpp"
#include "tools/array_linearizer.hpp"
#include "tools/expression_evaluator.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class array_scalarization_pass : public pass_base<hl_ast_node> {
public:
    array_scalarization_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:

    std::shared_ptr<hl_ast_node> process_element(const std::shared_ptr<hl_ast_node>& node);
    std::shared_ptr<hl_expression_node> process_expression(std::shared_ptr<hl_expression_node> node);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> node);
    std::shared_ptr<hl_definition_node> process_definition(std::shared_ptr<hl_definition_node> node);
    std::shared_ptr<hl_function_call_node> process_function_call(std::shared_ptr<hl_function_call_node> node);
    std::shared_ptr<hl_function_def_node> process_function_def(std::shared_ptr<hl_function_def_node> node);
    std::shared_ptr<hl_ast_conditional_node> process_conditional(std::shared_ptr<hl_ast_conditional_node> node);

    int evaluate_index_definition(std::shared_ptr<hl_definition_node> node);

    std::string mangle_name(std::vector<std::shared_ptr<hl_ast_node>> old_array_idx, std::string var_name, int array_size);
    std::unordered_map<std::string, std::shared_ptr<hl_definition_node>> def_map_vect;
    std::unordered_map<std::string, std::shared_ptr<hl_definition_node>> def_map_s;
};


#endif //FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP
