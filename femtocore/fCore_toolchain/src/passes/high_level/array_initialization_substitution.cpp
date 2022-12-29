//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "passes/high_level/array_initialization_substitution.h"

array_initialization_substitution::array_initialization_substitution() : pass_base<hl_ast_node>("array_initialization_substitution"){

}

std::shared_ptr<hl_ast_node> array_initialization_substitution::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(auto &item:element->get_content()){
        std::vector<std::shared_ptr<hl_ast_node>> content = process_node_by_type(item);
        new_content.insert( new_content.end(), content.begin(), content.end());
    }

    element->set_content(new_content);
    return element;
}


std::vector<std::shared_ptr<hl_ast_node>>
array_initialization_substitution::process_node_by_type(const std::shared_ptr<hl_ast_node> &node) {
    if(node->node_type == hl_ast_node_type_definition){
        auto def = std::static_pointer_cast<hl_definition_node>(node);
        if(!def->is_scalar()){
            if(def->is_initialized()){
                std::vector<std::shared_ptr<hl_ast_node>> ret;
                for(int i = 0; i<def->get_array_initializer().size(); ++i){

                    auto init_expr = build_initialization_expr(def, i);

                    auto lhs = std::static_pointer_cast<hl_ast_operand>(init_expr->get_lhs());
                    lhs->get_variable()->set_array_shape(def->get_variable()->get_array_shape());
                    lhs->get_variable()->set_bound_reg_array(def->get_variable()->get_bound_reg_array());
                    lhs->get_variable()->set_variable_class(def->get_variable()->get_variable_class());
                    lhs->get_variable()->set_type(def->get_variable()->get_type());
                    ret.push_back(init_expr);
                }
                def->set_array_initializer({});
                ret.insert(ret.begin(), def);
                return ret;
            } else {
                return {node};
            }
        } else return {node};

    }
    else return {node};
}


std::shared_ptr<hl_expression_node> array_initialization_substitution::build_initialization_expr(const std::shared_ptr<hl_definition_node>& def, int index) {
    std::shared_ptr<hl_expression_node> init_expr = std::make_shared<hl_expression_node>(expr_assign);
    init_expr->set_rhs(def->get_array_initializer()[index]);
    std::shared_ptr<variable> var = std::make_shared<variable>(def->get_name());
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);


    auto array_shape = def->get_array_shape();
    std::vector<int> indices;
    if(array_shape.size()>1){
        indices = array_delinearize(def->get_array_shape(), index);
    } else{
        indices = {index};
    }

    std::vector<std::shared_ptr<hl_ast_node>> index_operands;
    for(auto &i:indices){
        var = std::make_shared<variable>("index", i);
        index_operands.push_back(std::make_shared<hl_ast_operand>(var));
    }

    op->set_array_index(index_operands);
    init_expr->set_lhs(op);
    return init_expr;
}
