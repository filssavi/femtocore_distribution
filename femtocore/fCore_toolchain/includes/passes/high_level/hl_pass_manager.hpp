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

#ifndef FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP

#include <gtest/gtest_prod.h>

#include "data_structures/high_level_ast/high_level_ast.hpp"

#include "passes/pass_manager_base.hpp"
#include "passes/pass_base.hpp"


class hl_pass_manager : public pass_manager_base<hl_ast_node> {
public:
    explicit hl_pass_manager( int dump_ast_level);
    void run_morphing_pass( std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass) override;
    std::vector<nlohmann::json> run_morphing_pass_group(std::shared_ptr<hl_ast_node> &subtree, const std::vector<std::shared_ptr<pass_base<hl_ast_node>>>& group, int dal) override;

    std::shared_ptr<hl_ast_node> run_global_pass(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

    std::shared_ptr<hl_ast_node> process_leaves(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::vector<std::shared_ptr<hl_ast_node>> process_nodes(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

private:
    FRIEND_TEST(HlPassesTest, functionMapping);
    std::shared_ptr<hl_ast_node> process_terminal_by_type(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_ast_node> process_expression(const std::shared_ptr<hl_expression_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    static std::shared_ptr<hl_ast_operand> process_operand(const std::shared_ptr<hl_ast_operand> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_ast_node> process_function_call(const std::shared_ptr<hl_function_call_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_definition_node> process_definition(const std::shared_ptr<hl_definition_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_ast_loop_node> process_loop(const std::shared_ptr<hl_ast_loop_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_ast_conditional_node> process_conditional(const std::shared_ptr<hl_ast_conditional_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
};


#endif //FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
