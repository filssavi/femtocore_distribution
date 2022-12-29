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

#ifndef FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

#include <utility>

class function_inlining_pass :public pass_base<hl_ast_node>{
public:
    function_inlining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;

    std::vector<std::shared_ptr<hl_ast_node>> process_element(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_loop_node> process_loop(std::shared_ptr<hl_ast_loop_node> element);
    std::shared_ptr<hl_ast_conditional_node> process_conditional(std::shared_ptr<hl_ast_conditional_node> element);
    std::vector<std::shared_ptr<hl_ast_node>> process_expression(std::shared_ptr<hl_expression_node> element);
    std::vector<std::shared_ptr<hl_ast_node>> process_definition(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_function_def_node> process_function_def(std::shared_ptr<hl_function_def_node> element);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> element);
    std::vector<std::shared_ptr<hl_ast_node>> process_function_call(std::shared_ptr<hl_function_call_node> element);


    std::shared_ptr<hl_ast_node> substitute_arguments(const std::shared_ptr<hl_ast_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_loop_arguments(const std::shared_ptr<hl_ast_loop_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_conditional_arguments(const std::shared_ptr<hl_ast_conditional_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_expression_arguments(const std::shared_ptr<hl_expression_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_definition_arguments(const std::shared_ptr<hl_definition_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_operand_arguments(const std::shared_ptr<hl_ast_operand> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_code_block(const std::shared_ptr<hl_ast_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>> functions_map;
};


#endif //FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
