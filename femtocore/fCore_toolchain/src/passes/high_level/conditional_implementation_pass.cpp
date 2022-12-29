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

#include "passes/high_level/conditional_implementation_pass.h"

conditional_implementation_pass::conditional_implementation_pass() : pass_base<hl_ast_node>("Conditional Implementation pass"){

}

std::shared_ptr<hl_ast_node> conditional_implementation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::vector<std::shared_ptr<hl_ast_node>> body;

    for(const auto& item:element->get_content()){
        std::vector<std::shared_ptr<hl_ast_node>> selected_branch = process_block_by_type(item, element);
        body.insert(body.end(),selected_branch.begin(), selected_branch.end());
    }

    ret_val->set_content(body);
    return ret_val;
}


std::vector<std::shared_ptr<hl_ast_node>>
conditional_implementation_pass::process_block_by_type(const std::shared_ptr<hl_ast_node> &node,
                                                       const std::shared_ptr<hl_ast_node> &subtree) {

    if(node->node_type == hl_ast_node_type_loop){
        std::shared_ptr<hl_ast_loop_node> loop_node = std::static_pointer_cast<hl_ast_loop_node>(node);
        std::vector<std::shared_ptr<hl_ast_node>> loop_content =  process_loop(loop_node, subtree);
        loop_node->set_loop_content(loop_content);
        return{loop_node};
    } else if(node->node_type == hl_ast_node_type_conditional){
        return process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(node), subtree);
    } else {
        return {node};
    }
}

std::vector<std::shared_ptr<hl_ast_node>>
conditional_implementation_pass::process_loop(const std::shared_ptr<hl_ast_loop_node> &node,
                                              const std::shared_ptr<hl_ast_node> &subtree) {

    std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
    for(auto &loop_instr:node->get_loop_content()){
        if(loop_instr->node_type == hl_ast_node_type_conditional){
            std::shared_ptr<hl_ast_conditional_node> instr_node = std::static_pointer_cast<hl_ast_conditional_node>(loop_instr);
            std::vector<std::shared_ptr<hl_ast_node>> selected_branch = process_conditional(instr_node, subtree);
            new_block_content.insert(new_block_content.end(),selected_branch.begin(), selected_branch.end());
        } else{
            new_block_content.push_back(loop_instr);
        }
    }
    node->set_loop_content(new_block_content);

    return new_block_content;
}

std::vector<std::shared_ptr<hl_ast_node>>
conditional_implementation_pass::process_conditional(const std::shared_ptr<hl_ast_conditional_node>& node, const std::shared_ptr<hl_ast_node>& subtree) {
    std::vector<std::shared_ptr<hl_ast_node>> result_body;


    std::shared_ptr<hl_expression_node> condition = std::static_pointer_cast<hl_expression_node>(node->get_condition());
    std::shared_ptr<hl_ast_operand> lhs_op = get_operands(condition->get_lhs(), node, subtree->get_content());
    std::shared_ptr<hl_ast_operand> rhs_op = get_operands(condition->get_rhs(), node, subtree->get_content());

    std::shared_ptr<hl_expression_node> const_cond_expr = std::make_shared<hl_expression_node>(condition->get_type());
    const_cond_expr->set_lhs(lhs_op);
    const_cond_expr->set_rhs(rhs_op);

    std::shared_ptr<hl_ast_operand> result_op = expression_evaluator::evaluate_expression(const_cond_expr);
    bool result;
    if(result_op->get_type() == var_type_int_const) result = result_op->get_int_value();
    if(result_op->get_type() == var_type_float_const) result = result_op->get_float_val() == 1;

    if(result){
        std::vector<std::shared_ptr<hl_ast_node>> selected_block = node->get_if_block();
        result_body.insert(result_body.end(), selected_block.begin(), selected_block.end());
    } else if(node->has_else()){
        std::vector<std::shared_ptr<hl_ast_node>> selected_block = node->get_else_block();
        result_body.insert(result_body.end(), selected_block.begin(), selected_block.end());
    }
    return result_body;
}


std::shared_ptr<hl_ast_operand>
conditional_implementation_pass::find_variable_definition(const std::shared_ptr<hl_ast_node>& subexpr,
                                                          const std::shared_ptr<hl_ast_node>& item,
                                                          const std::vector<std::shared_ptr<hl_ast_node>>& prog_content) {
    std::shared_ptr<hl_ast_operand> retval;
    if(subexpr->node_type == hl_ast_node_type_expr){
        throw std::runtime_error("OH SNAP! Nested subexpression handling is not implemented yet");
    } else {
        std::shared_ptr<hl_ast_operand> variable = std::static_pointer_cast<hl_ast_operand>(subexpr);
        for(const auto& i: prog_content){
            if(i == item){
                throw std::runtime_error("The value of all variables in a conditional condition must be defined before the expression itself");
            } else if (i->node_type == hl_ast_node_type_definition){
                std::shared_ptr<hl_definition_node> def = std::static_pointer_cast<hl_definition_node>(i);
                if(def->get_name() == variable->get_name()){
                    if(def->is_initialized()){
                        if(def->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
                            return std::static_pointer_cast<hl_ast_operand>(def->get_scalar_initializer());
                        } else{
                            return find_variable_definition(def->get_scalar_initializer(), def, prog_content);
                        }
                    }
                }
            }
        }
    }

    return retval;
}


std::shared_ptr<hl_ast_operand>
conditional_implementation_pass::get_operands(const std::shared_ptr<hl_ast_node> &subexpr,
                                              const std::shared_ptr<hl_ast_node> &item,
                                              const std::vector<std::shared_ptr<hl_ast_node>> &prog_content) {
    std::shared_ptr<hl_ast_operand> retval;
    if(subexpr->node_type != hl_ast_node_type_operand){
        retval = find_variable_definition(subexpr, item, prog_content);
    } else{
        variable_type_t vt = std::static_pointer_cast<hl_ast_operand>(subexpr)->get_type();
        if(vt == var_type_scalar || vt == var_type_array){
            retval = find_variable_definition(subexpr, item, prog_content);
        } else {
            retval = std::static_pointer_cast<hl_ast_operand>(subexpr);
        }
    }
    return retval;
}
