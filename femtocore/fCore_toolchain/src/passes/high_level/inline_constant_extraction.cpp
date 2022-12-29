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


#include "passes/high_level/inline_constant_extraction.hpp"

inline_constant_extraction::inline_constant_extraction() : pass_base<hl_ast_node>("inline constant extraction pass"){
    n_var = 0;
}

std::shared_ptr<hl_ast_node>
inline_constant_extraction::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(const auto& item:element->get_content()){
        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(item);
            auto res = process_node(node);
            new_content.insert(new_content.end(), res.begin(), res.end());
        } else if(item->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(item);
            auto res = process_node(node);
            new_content.insert(new_content.end(), res.begin(), res.end());
        } else{
            new_content.push_back(item);
        }
    }
    retval->set_content(new_content);
    return retval;
}



std::vector<std::shared_ptr<hl_ast_node>> inline_constant_extraction::process_node(const std::shared_ptr<hl_expression_node> &element) {
    std::vector<std::shared_ptr<hl_ast_node>> ret_val;
    if(!element->is_immediate() && element->get_type()!=expr_assign){
        throw std::runtime_error("Non assignment top level expressions should not reach inline constant extraction pass");
    }

    if(element->get_type()==expr_assign){
        if(element->get_rhs()->node_type != hl_ast_node_type_operand){
            std::vector<std::shared_ptr<hl_ast_node>> res = process_expression(std::static_pointer_cast<hl_expression_node>(element->get_rhs()));
            if(res.size()>1){
                element->set_rhs(res[0]);
                ret_val.push_back(res[1]);
            }
        }
    }

    ret_val.push_back(element);
    return ret_val;
}

std::vector<std::shared_ptr<hl_ast_node>>
inline_constant_extraction::process_node(const std::shared_ptr<hl_definition_node> &element) {

    std::vector<std::shared_ptr<hl_ast_node>> ret_val;
    if(element->is_initialized()){
        if(element->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> expr = std::static_pointer_cast<hl_expression_node>(
                    element->get_scalar_initializer());
            std::vector<std::shared_ptr<hl_ast_node>> res = process_expression(expr);
            element->set_scalar_initializer(res[0]);
            if(res.size()>1)
                ret_val.insert(ret_val.end(), res.begin()+1, res.end());

        }
    }
    ret_val.push_back(element);
    return ret_val;
}


std::vector<std::shared_ptr<hl_ast_node>>
inline_constant_extraction::process_expression(const std::shared_ptr<hl_expression_node> &element) {
std::vector<std::shared_ptr<hl_ast_node>> retval;

    std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);

    if(node->get_type()==expr_efi){
        retval.push_back(element);
    } else {
        std::vector<std::shared_ptr<hl_ast_node>> rhs_result = process_operand(std::static_pointer_cast<hl_ast_operand>(node->get_rhs()));
        node->set_rhs(rhs_result[0]);
        if(rhs_result.size()==2){
            retval.push_back(rhs_result[1]);
        }

        if(!node->is_unary()){
            std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
            std::vector<std::shared_ptr<hl_ast_node>> lhs_result = process_operand(lhs);
            node->set_lhs(lhs_result[0]);
            if(lhs_result.size()==2)
                retval.push_back(lhs_result[1]);
        }
        retval.insert(retval.begin(), node);
    }

    return retval;
}


std::vector<std::shared_ptr<hl_ast_node>>
inline_constant_extraction::process_operand(const std::shared_ptr<hl_ast_operand>& element) {

    std::vector<std::shared_ptr<hl_ast_node>> retval;

    if(element->get_type() != var_type_float_const && element->get_type() != var_type_int_const ){
        retval.push_back(element);
        return retval;
    }

    c_types_t selected_type = element->get_type() == var_type_float_const ?  c_type_float: c_type_int;

    std::string var_name = "inlined_variable_"+std::to_string(n_var);
    std::shared_ptr<variable> var = std::make_shared<variable>( var_name);
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>(var_name, selected_type, var);
    def->set_scalar_initializer(element);
    std::shared_ptr<hl_ast_operand> var_op = std::make_shared<hl_ast_operand>(std::make_shared<variable>(var_name));

    auto bound_reg = element->get_variable()->get_bound_reg();
    if(bound_reg != -1){
        def->get_variable()->set_bound_reg(bound_reg);
        var_op->get_variable()->set_bound_reg(bound_reg);
    }
    var_op->get_variable()->set_variable_class(element->get_variable()->get_variable_class());
    def->get_variable()->set_variable_class(element->get_variable()->get_variable_class());


    retval.insert(retval.end(), {var_op, def});
    n_var++;
    return retval;
}



