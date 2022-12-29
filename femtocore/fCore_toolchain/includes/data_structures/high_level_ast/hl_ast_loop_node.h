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
// limitations under the License.30/06/2021.
//

#ifndef FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H
#define FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H

#include <utility>

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"

class hl_ast_loop_node : public hl_ast_node {
public:
    hl_ast_loop_node();
    void set_loop_content(std::vector<std::shared_ptr<hl_ast_node>> content) {loop_content = std::move(content);};
    std::vector<std::shared_ptr<hl_ast_node>> get_loop_content() {return loop_content;};
    std::shared_ptr<hl_expression_node> get_condition() {return condition;};
    void set_condition(std::shared_ptr<hl_expression_node> c) {condition = std::move(c);};
    std::shared_ptr<hl_definition_node> get_init_statement() { return  init_statement;};
    void set_init_statement(std::shared_ptr<hl_definition_node> init_s) {init_statement = std::move(init_s);}
    std::shared_ptr<hl_expression_node> get_iteration_expr() {return iteration_expr;};
    void set_iteration_expr(std::shared_ptr<hl_expression_node> i) {iteration_expr = std::move(i);};
    std::string pretty_print() override;
    nlohmann::json dump() override;
    friend bool operator==(const hl_ast_loop_node& lhs, const hl_ast_loop_node& rhs);
private:
    std::vector<std::shared_ptr<hl_ast_node>> loop_content;
    std::shared_ptr<hl_expression_node> condition;
    std::shared_ptr<hl_expression_node> iteration_expr;
    std::shared_ptr<hl_definition_node> init_statement;
};


#endif //FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H
