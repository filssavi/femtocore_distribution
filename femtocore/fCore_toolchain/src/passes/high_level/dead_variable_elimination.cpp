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


#include "passes/high_level/dead_variable_elimination.hpp"

dead_variable_elimination::dead_variable_elimination() : pass_base<hl_ast_node>("dead variable elimination"){

}

std::shared_ptr<hl_ast_node> dead_variable_elimination::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval =  std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_body;

    std::map<std::string, bool> defined_variables;
    for(const auto& item:element->get_content()){

        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node =std::static_pointer_cast<hl_definition_node>(item);
            if(node->is_initialized())
                defined_variables.insert(std::make_pair(node->get_name(), true));
        } else if(item->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node =std::static_pointer_cast<hl_expression_node>(item);
            if(node->get_type() == expr_assign){
                std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
                defined_variables.insert(std::make_pair(lhs->get_name(), true));
            }
        }
    }

    for(const auto& item:element->get_content()){

        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node =std::static_pointer_cast<hl_definition_node>(item);
            if(defined_variables.count(node->get_name())>0){
                new_body.push_back(hl_ast_node::deep_copy(item));
            }
        } else {
            new_body.push_back(hl_ast_node::deep_copy(item));
        }
    }

    retval->set_content(new_body);
    return retval;
}
