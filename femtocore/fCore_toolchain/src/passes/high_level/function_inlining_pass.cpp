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

#include "passes/high_level/function_inlining_pass.hpp"


function_inlining_pass::function_inlining_pass() : pass_base<hl_ast_node>("function inlining pass"){

}

std::shared_ptr<hl_ast_node> function_inlining_pass::process_global(std::shared_ptr<hl_ast_node> element) {

    for(auto &item:element->get_content()){
        if(item->node_type == hl_ast_node_type_function_def){
            std::shared_ptr<hl_function_def_node> function_def = std::static_pointer_cast<hl_function_def_node>(item);
            functions_map[function_def->get_name()] = function_def;
        }
    }

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_content()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        new_content.insert(new_content.end(), processed_elements.begin(), processed_elements.end());
    }
    element->set_content(new_content);
    return element;
}

std::vector<std::shared_ptr<hl_ast_node>> function_inlining_pass::process_element(std::shared_ptr<hl_ast_node> element) {
    switch (element->node_type) {
        case hl_ast_node_type_expr:
            return {process_expression(std::static_pointer_cast<hl_expression_node>(element))};
        case hl_ast_node_type_definition:
            return {process_definition(std::static_pointer_cast<hl_definition_node>(element))};
        case hl_ast_node_type_conditional:
            return {process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(element))};
        case hl_ast_node_type_loop:
            return {process_loop(std::static_pointer_cast<hl_ast_loop_node>(element))};
        case hl_ast_node_type_function_def:
            return {process_function_def(std::static_pointer_cast<hl_function_def_node>(element))};
        case hl_ast_node_type_operand:
            return {process_operand(std::static_pointer_cast<hl_ast_operand>(element))};
        case hl_ast_node_type_function_call:
            return process_function_call(std::static_pointer_cast<hl_function_call_node>(element));
        default:
            return {element};
    }
}

std::shared_ptr<hl_ast_loop_node> function_inlining_pass::process_loop(std::shared_ptr<hl_ast_loop_node> element) {

    std::vector<std::shared_ptr<hl_ast_node>> processed_condition = process_expression(element->get_condition());
    if(processed_condition.size()>1){
        throw std::runtime_error("internal error #5923");
    }
    element->set_condition(std::static_pointer_cast<hl_expression_node>(processed_condition[0]));

    std::vector<std::shared_ptr<hl_ast_node>> processed_init = process_definition(element->get_init_statement());
    if(processed_init.size()>1){
        throw std::runtime_error("internal error #5924");
    }
    element->set_init_statement(std::static_pointer_cast<hl_definition_node>(processed_init[0]));

    std::vector<std::shared_ptr<hl_ast_node>> processed_iter_expr = process_expression(element->get_iteration_expr());
    if(processed_iter_expr.size()>1){
        throw std::runtime_error("internal error #5925");
    }
    element->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(processed_iter_expr[0]));

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_loop_content()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        new_content.insert(new_content.end(), processed_elements.begin(), processed_elements.end());
    }
    element->set_loop_content(new_content);

    return element;
}

std::shared_ptr<hl_ast_conditional_node>
function_inlining_pass::process_conditional(std::shared_ptr<hl_ast_conditional_node> element) {
    element->set_condition(process_element(element->get_condition())[0]);

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_if_block()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        new_content.insert(new_content.end(), processed_elements.begin(), processed_elements.end());
    }
    element->set_if_block(new_content);

    new_content.clear();
    for(auto &item:element->get_else_block()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        new_content.insert(new_content.end(), processed_elements.begin(), processed_elements.end());
    }
    element->set_else_block(new_content);

    return element;
}

std::vector<std::shared_ptr<hl_ast_node>>
function_inlining_pass::process_expression(std::shared_ptr<hl_expression_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> ret_val;
   if(!element->is_immediate()){
       if(!element->is_unary()){
           std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(element->get_lhs());
           if(processed_elements.size() == 1)
               element->set_lhs(processed_elements[0]);
           else{
               element->set_lhs(processed_elements[1]);
               ret_val.push_back(processed_elements[0]);
           }
       }

       std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(element->get_rhs());
       if(processed_elements.size() == 1)
           element->set_rhs(processed_elements[0]);
       else{
           element->set_rhs(processed_elements[1]);
           ret_val.push_back(processed_elements[0]);
       }
   }

    ret_val.push_back(element);
    return ret_val;
}

std::vector<std::shared_ptr<hl_ast_node>>
function_inlining_pass::process_definition(std::shared_ptr<hl_definition_node> element) {

    std::vector<std::shared_ptr<hl_ast_node>> ret_val;

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_array_index()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        if(processed_elements.size() == 1)
            new_content.push_back(processed_elements[0]);
        else{
            new_content.push_back(processed_elements[1]);
            ret_val.push_back(processed_elements[0]);
        }
    }
    element->set_array_index(new_content);


    if(element->is_initialized()){
        new_content.clear();
        for(auto &item:element->get_array_initializer()){
            std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
            if(processed_elements.size() == 1)
                new_content.push_back(processed_elements[0]);
            else{
                new_content.push_back(processed_elements[1]);
                ret_val.push_back(processed_elements[0]);
            }
        }
        element->set_array_initializer(new_content);
    }

    ret_val.push_back(element);
    return ret_val;
}

std::shared_ptr<hl_function_def_node>
function_inlining_pass::process_function_def(std::shared_ptr<hl_function_def_node> element) {


    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_body()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_elements = process_element(item);
        new_content.insert(new_content.end(), processed_elements.begin(), processed_elements.end());
    }

    if(element->get_return() != nullptr){
        std::vector<std::shared_ptr<hl_ast_node>> processed_return = process_element(element->get_return());
        if(processed_return.size() == 1)
            element->set_return(processed_return[0]);
        else{
            element->set_return(processed_return[1]);
            new_content.push_back(processed_return[0]);
        }
    }
    element->set_body(new_content);
    return element;
}

std::shared_ptr<hl_ast_operand> function_inlining_pass::process_operand(std::shared_ptr<hl_ast_operand> element) {
    return element;
}


std::vector<std::shared_ptr<hl_ast_node>>
function_inlining_pass::process_function_call(std::shared_ptr<hl_function_call_node> f_call) {
    std::shared_ptr<hl_ast_node> ret_val;


    if(functions_map.count(f_call->get_name())==0){
        throw std::runtime_error("Function " + f_call->get_name() + " is not defined");
    }

    std::shared_ptr<hl_function_def_node> f_def = functions_map[f_call->get_name()];

    // MAP ARGUMENTS OF  THE CALL WITH its name
    int idx = 0;
    std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> arguments_map;
    for(const auto& arg: f_call->get_arguments()){
        std::string arg_name = f_def->get_parameters_list()[idx]->get_name();
        arguments_map[arg_name] = hl_ast_node::deep_copy(arg);
        ++idx;

    }

    std::shared_ptr<hl_ast_node> inlined_code = std::make_shared<hl_ast_node>(hl_ast_node_type_code_block);

    // SUBSTITUTE THE ARGUMENTS OF THE CALL WITHIN THE FUNCTION BODY
    std::vector<std::shared_ptr<hl_ast_node>> body;


    for(auto &i: f_def->get_body()){
        std::shared_ptr<hl_ast_node> copied_node = hl_ast_node::deep_copy(i);
        body.push_back(substitute_arguments(copied_node,arguments_map));
    }
    inlined_code->set_content(body);

    std::shared_ptr<hl_ast_node> inlined_return = nullptr;

    if(f_def->get_return() != nullptr){
        inlined_return = substitute_arguments(hl_ast_node::deep_copy(f_def->get_return()), arguments_map);
        return {inlined_code, inlined_return};
    }

    return {inlined_code};
    }

 std::shared_ptr<hl_ast_node> function_inlining_pass::substitute_arguments(const std::shared_ptr<hl_ast_node> &statement,
                                                                           std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {
    std::shared_ptr<hl_ast_node> retval = statement;
    if (statement->node_type == hl_ast_node_type_expr){
        return substitute_expression_arguments(std::static_pointer_cast<hl_expression_node>(statement), parameters);
    } else if (statement->node_type == hl_ast_node_type_definition){
        return substitute_definition_arguments(std::static_pointer_cast<hl_definition_node>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_operand){
        return substitute_operand_arguments(std::static_pointer_cast<hl_ast_operand>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_conditional){
        return substitute_conditional_arguments(std::static_pointer_cast<hl_ast_conditional_node>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_loop){
        return substitute_loop_arguments(std::static_pointer_cast<hl_ast_loop_node>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_code_block){
        return substitute_code_block(statement, parameters);
    }
     return retval;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_loop_arguments(const std::shared_ptr<hl_ast_loop_node> &statement,
                                                  std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_loop_content()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_loop_content(tmp_vect);

    auto new_init = substitute_arguments(statement->get_init_statement(), parameters);
    statement->set_init_statement(std::static_pointer_cast<hl_definition_node>(new_init));

    auto new_cond = substitute_arguments(statement->get_condition(), parameters);
    statement->set_condition(std::static_pointer_cast<hl_expression_node>(new_cond));

    auto new_iter = substitute_arguments(statement->get_iteration_expr(), parameters);
    statement->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(new_iter));

    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_conditional_arguments(const std::shared_ptr<hl_ast_conditional_node> &statement,
                                                         std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_if_block()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_if_block(tmp_vect);

    tmp_vect.clear();
    for(auto &item: statement->get_else_block()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_else_block(tmp_vect);

    statement->set_condition(substitute_arguments(statement->get_condition(), parameters));
    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_expression_arguments(const std::shared_ptr<hl_expression_node> &statement,
                                                        std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {
    if(statement->is_immediate()){
        return statement;
    }

    if(!statement->is_unary()){
        std::shared_ptr<hl_ast_node> tmp_lhs = substitute_arguments(statement->get_lhs(), parameters);
        statement->set_lhs(tmp_lhs);
    }
    std::shared_ptr<hl_ast_node> tmp_rhs = substitute_arguments(statement->get_rhs(), parameters);
    statement->set_rhs(tmp_rhs);
    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_definition_arguments(const std::shared_ptr<hl_definition_node> &statement,
                                                        std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {
    if(statement->is_initialized()){
        std::shared_ptr<hl_ast_node> tmp = statement->get_scalar_initializer();
        std::shared_ptr<hl_ast_node> substituted_node = substitute_arguments(tmp, parameters);
        if(substituted_node->node_type == hl_ast_node_type_expr || substituted_node->node_type == hl_ast_node_type_operand){
            statement->set_scalar_initializer(substituted_node);
        } else {
            throw std::runtime_error("unexpected node type detected");
        }
    }

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_array_index()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_array_index(tmp_vect);

    tmp_vect.clear();
    for(auto &item: statement->get_array_initializer()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_array_initializer(tmp_vect);



    return statement;
}
std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_code_block(const std::shared_ptr<hl_ast_node> &statement,
                                              std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {

    std::shared_ptr<hl_ast_node> ret_code_block = std::make_shared<hl_ast_node>(hl_ast_node_type_code_block);

    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(auto &item:statement->get_content()){
        new_content.push_back(substitute_arguments(item, parameters));
    }

    ret_code_block->set_content(new_content);
    return ret_code_block;

}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_operand_arguments(const std::shared_ptr<hl_ast_operand> &old_operand,
                                                     std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters) {


    std::string old_operand_name = old_operand->get_name();
    std::shared_ptr<hl_ast_node> ret_val;
    std::shared_ptr<hl_ast_operand> new_operand;
    auto op_node = parameters[old_operand->get_name()];
    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    if(op_node != nullptr){
        if(op_node->node_type == hl_ast_node_type_operand){
            std::shared_ptr<hl_ast_operand> p = std::static_pointer_cast<hl_ast_operand>(op_node);
            if(p->get_variable()->get_type() != var_type_array){

                new_operand = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(p));

                for(auto &item: old_operand->get_array_index()){
                    tmp_vect.push_back(substitute_arguments(item, parameters));
                }
                if(!tmp_vect.empty()){
                    new_operand->set_type(var_type_array);
                }
                new_operand->set_array_index(tmp_vect);
            } else{
                new_operand = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(p));

                for(auto &item: p->get_array_index()){
                    tmp_vect.push_back(substitute_arguments(item, parameters));
                }
                std::vector<std::shared_ptr<hl_ast_node>> old_idx = old_operand->get_array_index();

                if(!old_idx.empty()) {
                    tmp_vect.insert(tmp_vect.end(), old_idx.begin(), old_idx.end());
                }

                if(!tmp_vect.empty()){
                    new_operand->set_type(var_type_array);
                }

                new_operand->set_array_index(tmp_vect);
            }
            ret_val = new_operand;
        } else if(op_node->node_type == hl_ast_node_type_expr){
            ret_val = hl_ast_node::deep_copy(op_node);
        }

    } else {
        ret_val = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(old_operand));
    }

    return ret_val;
}