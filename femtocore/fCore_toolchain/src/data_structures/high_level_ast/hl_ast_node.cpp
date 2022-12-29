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

#include "data_structures/high_level_ast/hl_ast_node.hpp"

#include "data_structures/high_level_ast/hl_ast_operand.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_function_call_node.hpp"
#include "data_structures/high_level_ast/hl_function_def_node.hpp"
#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"
#include "data_structures/high_level_ast/hl_ast_loop_node.h"

bool hl_ast_node::is_terminal() {
    return false;
}

hl_ast_node::hl_ast_node(hl_ast_node_type_t t) {
    node_type = t;
}

c_types_t hl_ast_node::string_to_type(const std::string &t) {
    std::map <std::string, c_types_t>  translator {
            {"void", c_type_void},
            {"char", c_type_char},
            {"short", c_type_short},
            {"int", c_type_int},
            {"long", c_type_long},
            {"float", c_type_float}
    };


    return translator[t];
}



bool operator==(const hl_ast_node &lhs, const hl_ast_node &rhs) {
    bool ret_val = true;
    ret_val &= lhs.node_type == rhs.node_type;

    if(lhs.content.empty() && rhs.content.empty()){
        ret_val &= true;
    } else if(lhs.content.empty() || rhs.content.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        if(lhs.content.size() != rhs.content.size()) return false;

        for(int i = 0; i<lhs.content.size(); i++){
            body_equal &=  hl_ast_node::compare_content_by_type(lhs.content[i], rhs.content[i]);
        }
        ret_val &= body_equal;
    }

    return ret_val;
}

bool
hl_ast_node::compare_content_by_type(const std::shared_ptr<hl_ast_node> &lhs, const std::shared_ptr<hl_ast_node> &rhs) {
    if(lhs->node_type != rhs->node_type) return false;

    switch (lhs->node_type) {
        case hl_ast_node_type_program_root:
        case hl_ast_node_type_code_block:
            return *lhs == *rhs;
        case hl_ast_node_type_loop:
            return *std::static_pointer_cast<hl_ast_loop_node>(lhs) == *std::static_pointer_cast<hl_ast_loop_node>(rhs);
        case hl_ast_node_type_conditional:
            return *std::static_pointer_cast<hl_ast_conditional_node>(lhs) == *std::static_pointer_cast<hl_ast_conditional_node>(rhs);
        case hl_ast_node_type_operand:
            return *std::static_pointer_cast<hl_ast_operand>(lhs) == *std::static_pointer_cast<hl_ast_operand>(rhs);
        case hl_ast_node_type_expr:
            return *std::static_pointer_cast<hl_expression_node>(lhs) == *std::static_pointer_cast<hl_expression_node>(rhs);
        case hl_ast_node_type_definition:
            return *std::static_pointer_cast<hl_definition_node>(lhs) == *std::static_pointer_cast<hl_definition_node>(rhs);
        case hl_ast_node_type_function_def:
            return *std::static_pointer_cast<hl_function_def_node>(lhs) == *std::static_pointer_cast<hl_function_def_node>(rhs);
        case hl_ast_node_type_function_call:
            return *std::static_pointer_cast<hl_function_call_node>(lhs) == *std::static_pointer_cast<hl_function_call_node>(rhs);
        default:
            return false;
    }
    return false;
}

std::string hl_ast_node::type_to_string(const c_types_t &t) {
    std::map <c_types_t,std::string>  translator {
            {c_type_void, "void"},
            {c_type_char, "char"},
            {c_type_short, "short"},
            {c_type_int, "int"},
            {c_type_long, "long"},
            {c_type_float, "float"}
    };

    return translator[t];
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy(const std::shared_ptr<hl_ast_node> &node) {
    if(node == nullptr){
        return nullptr;
    } else if(node->node_type == hl_ast_node_type_expr){
        return deep_copy_expr(node);
    } else if(node->node_type == hl_ast_node_type_definition){
        return deep_copy_def(node);
    } else if(node->node_type == hl_ast_node_type_conditional){
        return deep_copy_conditional(node);
    } else if(node->node_type == hl_ast_node_type_loop){
        return deep_copy_loop(node);
    } else if(node->node_type == hl_ast_node_type_function_def){
        return deep_copy_function_def(node);
    } else if(node->node_type == hl_ast_node_type_operand){
        return deep_copy_operands(node);
    } else if(node->node_type == hl_ast_node_type_function_call){
        return deep_copy_function_call(node);
    } else if(node->node_type == hl_ast_node_type_program_root) {
        return deep_copy_program_root(node);
    } else if(node->node_type == hl_ast_node_type_code_block){
        return deep_copy_code_block(node);
    } else {
        throw std::runtime_error("HL ast node with unknown type");
    }

}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_expr(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_expression_node> orig = std::static_pointer_cast<hl_expression_node>(node);
    std::shared_ptr<hl_expression_node> copied_obj = std::make_shared<hl_expression_node>(orig->get_type());

    std::shared_ptr<hl_ast_node> lhs = deep_copy(orig->get_lhs());
    std::shared_ptr<hl_ast_node> rhs = deep_copy(orig->get_rhs());

    copied_obj->set_lhs(lhs);
    copied_obj->set_rhs(rhs);

    copied_obj->set_assignment_type(orig->get_assignment_type());

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_def(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_definition_node> orig = std::static_pointer_cast<hl_definition_node>(node);
    std::shared_ptr<variable> new_var = variable::deep_copy(orig->get_variable());
    std::shared_ptr<hl_definition_node> copied_obj = std::make_shared<hl_definition_node>(orig->get_name(), orig->get_type(), new_var);
    copied_obj->set_constant(orig->is_constant());
    if(orig->is_initialized()){
        std::vector<std::shared_ptr<hl_ast_node>> old_initializer = orig->get_array_initializer();
        std::vector<std::shared_ptr<hl_ast_node>> new_initializer;
        for(auto &item:old_initializer){
            new_initializer.push_back(deep_copy(item));
        }
        copied_obj->set_array_initializer(new_initializer);
    }


    std::vector<std::shared_ptr<hl_ast_node>> index;
    for(const auto& i:orig->get_array_index()){
        index.push_back(deep_copy(i));
    }
    copied_obj->set_array_index(index);

    std::vector<int> shape = orig->get_array_shape();
    copied_obj->set_array_shape(shape);

    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_conditional(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_conditional_node> orig = std::static_pointer_cast<hl_ast_conditional_node>(node);
    std::shared_ptr<hl_ast_conditional_node> copied_obj = std::make_shared<hl_ast_conditional_node>();


    std::shared_ptr<hl_ast_node> cond = deep_copy(orig->get_condition());
    copied_obj->set_condition(cond);


    std::vector<std::shared_ptr<hl_ast_node>> block;
    for(const auto& i:orig->get_if_block()){
        block.push_back(deep_copy(i));
    }
    copied_obj->set_if_block(block);

    block.clear();
    for(const auto& i:orig->get_else_block()){
        block.push_back(deep_copy(i));
    }
    copied_obj->set_else_block(block);

    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_loop(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_loop_node> orig = std::static_pointer_cast<hl_ast_loop_node>(node);
    std::shared_ptr<hl_ast_loop_node> copied_obj = std::make_shared<hl_ast_loop_node>();

    copied_obj->set_condition(std::static_pointer_cast<hl_expression_node>(deep_copy(orig->get_condition())));
    copied_obj->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(deep_copy(orig->get_iteration_expr())));
    copied_obj->set_init_statement(std::static_pointer_cast<hl_definition_node>(deep_copy(orig->get_init_statement())));

    std::vector<std::shared_ptr<hl_ast_node>> block;
    for(const auto& i:orig->get_loop_content()){
        block.push_back(deep_copy(i));
    }
    copied_obj->set_loop_content(block);

    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_function_def(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_function_def_node> orig = std::static_pointer_cast<hl_function_def_node>(node);
    std::shared_ptr<hl_function_def_node> copied_obj = std::make_shared<hl_function_def_node>();

    copied_obj->set_return_type(orig->get_return_type());
    copied_obj->set_name(orig->get_name());
    std::shared_ptr<hl_ast_node> ret_expr = deep_copy(orig->get_return());
    copied_obj->set_return(ret_expr);

    std::vector<std::shared_ptr<hl_definition_node>> params;
    for(const auto& i:orig->get_parameters_list()){
        params.push_back(std::static_pointer_cast<hl_definition_node>(deep_copy_def(i)));
    }
    copied_obj->set_parameters_list(params);

    std::vector<std::shared_ptr<hl_ast_node>> body;
    for(const auto& i:orig->get_body()){
        body.push_back(deep_copy(i));
    }
    copied_obj->set_body(body);

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_operands(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_operand> orig = std::static_pointer_cast<hl_ast_operand>(node);

    std::shared_ptr<variable> new_var = variable::deep_copy(orig->get_variable());
    std::shared_ptr<hl_ast_operand> copied_obj = std::make_shared<hl_ast_operand>(new_var);
    
    std::vector<std::shared_ptr<hl_ast_node>> new_array_idx;
    for(auto &item:orig->get_array_index()){
        new_array_idx.push_back(deep_copy(item));
    }
    copied_obj->set_array_index(new_array_idx);

    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_function_call(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_function_call_node> orig = std::static_pointer_cast<hl_function_call_node>(node);
    std::vector<std::shared_ptr<hl_ast_node>> args;
    for(const auto &i :orig->get_arguments()){
        args.push_back(deep_copy(i));
    }

    std::shared_ptr<hl_function_call_node> copied_obj = std::make_shared<hl_function_call_node>(orig->get_name(), args);
    copied_obj->set_content(orig->get_content());
    return copied_obj;
}


std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_program_root(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_node> copied_obj = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::vector<std::shared_ptr<hl_ast_node>> args;
    for(const auto &i :node->get_content()){
        args.push_back(deep_copy(i));
    }

    copied_obj->set_content(args);
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_code_block(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_node> copied_obj = std::make_shared<hl_ast_node>(hl_ast_node_type_code_block);

    std::vector<std::shared_ptr<hl_ast_node>> args;
    for(const auto &i :node->get_content()){
        args.push_back(deep_copy(i));
    }

    copied_obj->set_content(args);
    return copied_obj;
}



bool hl_ast_node::compare_vectors(const std::vector<std::shared_ptr<hl_ast_node>> &lhs,
                                  const std::vector<std::shared_ptr<hl_ast_node>> &rhs) {
    bool ret_val = true;
    if(lhs.empty() && rhs.empty()){
        ret_val &= true;
    } else if(lhs.empty() || rhs.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        if(lhs.size() != rhs.size()) return false;

        for(int i = 0; i<lhs.size(); i++){
            body_equal &= hl_ast_node::compare_content_by_type( lhs[i], rhs[i]);
        }
        ret_val &= body_equal;
    }
    return ret_val;
}

std::string hl_ast_node::pretty_print() {
    std::ostringstream ss;

    for(auto &item:content){
        ss << item->pretty_print()<<std::endl;
    }
    return ss.str();
}

nlohmann::json hl_ast_node::dump() {
    nlohmann::json retval;
    if(node_type==hl_ast_node_type_program_root)
        retval["type"] = hl_ast_node_to_string(node_type);
    else
        retval["node_type"] = hl_ast_node_to_string(node_type);
    retval["content"] = dump_array(content);
    return retval;
}

std::vector<nlohmann::json> hl_ast_node::dump_array(const std::vector<std::shared_ptr<hl_ast_node>>& vect) {
    std::vector<nlohmann::json> ret_val;
    for(auto &i: vect){
        ret_val.push_back(hl_ast_node::dump_by_type(i));
    }
    return ret_val;
}

nlohmann::json hl_ast_node::dump_by_type(const std::shared_ptr<hl_ast_node>& node) {
    switch (node->node_type) {
        case hl_ast_node_type_operand: return std::static_pointer_cast<hl_ast_operand>(node)->dump();
        case hl_ast_node_type_expr: return std::static_pointer_cast<hl_expression_node>(node)->dump();
        case hl_ast_node_type_definition: return std::static_pointer_cast<hl_definition_node>(node)->dump();
        case hl_ast_node_type_conditional: return std::static_pointer_cast<hl_ast_conditional_node>(node)->dump();
        case hl_ast_node_type_loop: return std::static_pointer_cast<hl_ast_loop_node>(node)->dump();
        case hl_ast_node_type_function_def: return std::static_pointer_cast<hl_function_def_node>(node)->dump();
        case hl_ast_node_type_function_call: return std::static_pointer_cast<hl_function_call_node>(node)->dump();
        case hl_ast_node_type_program_root:
        case hl_ast_node_type_code_block:
            return node->dump();
        default:
            throw std::runtime_error("Unknown node type has been dumped");
    }
}
