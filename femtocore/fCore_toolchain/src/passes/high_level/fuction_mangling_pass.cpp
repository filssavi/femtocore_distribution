// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#include "passes/high_level/fuction_mangling_pass.hpp"

#include <utility>

fuction_mangling_pass::fuction_mangling_pass() : pass_base<hl_ast_node>("Function Mangling pass") {

}

std::shared_ptr<hl_ast_node> fuction_mangling_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::vector<std::shared_ptr<hl_ast_node>> body;

    for(const auto& item:element->get_content()){
        if(item->node_type !=hl_ast_node_type_function_def){
            body.insert(body.end(), item);
            continue;
        }

        std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(item);
        if(node->get_name() == "main"){
            body.insert(body.end(), item);
            continue;
        }

        std::shared_ptr<hl_function_def_node> mangled_node = std::make_shared<hl_function_def_node>();
        mangled_node->set_return_type(node->get_return_type());
        mangled_node->set_name(node->get_name());

        std::vector<std::shared_ptr<hl_ast_node>> new_func_body;

        for(auto &b: node->get_body()){
            new_func_body.push_back(mangle_node(hl_ast_node::deep_copy(b), node->get_name()));
        }
        mangled_node->set_body(new_func_body);
        if(node->get_return() != nullptr)
            mangled_node->set_return(mangle_node(hl_ast_node::deep_copy(node->get_return()), node->get_name()));
        std::vector<std::shared_ptr<hl_definition_node>> new_params;

        for(auto &p: node->get_parameters_list()){
            auto n_def = mangle_node(hl_ast_node::deep_copy(p), node->get_name());
            new_params.push_back(std::static_pointer_cast<hl_definition_node>(n_def));
        }
        mangled_node->set_parameters_list(new_params);
        body.insert(body.end(),mangled_node);
    }

    ret_val->set_content(body);
    return ret_val;
}

std::shared_ptr<hl_ast_node> fuction_mangling_pass::mangle_node(const std::shared_ptr<hl_ast_node>& node, const std::string &function) {
    switch (node->node_type) {
        case hl_ast_node_type_expr:
            return mangle_node(std::static_pointer_cast<hl_expression_node>(node), function);
        case hl_ast_node_type_definition:
            return mangle_node(std::static_pointer_cast<hl_definition_node>(node), function);
        case hl_ast_node_type_conditional:
            return mangle_node(std::static_pointer_cast<hl_ast_conditional_node>(node), function);
        case hl_ast_node_type_loop:
            return mangle_node(std::static_pointer_cast<hl_ast_loop_node>(node), function);
        case hl_ast_node_type_function_def:
            throw std::runtime_error("Nested function definitions are not supported");
        case hl_ast_node_type_operand:
            return mangle_node(std::static_pointer_cast<hl_ast_operand>(node), function);
        case hl_ast_node_type_function_call:
            return mangle_node(std::static_pointer_cast<hl_function_call_node>(node), function);
        default:
            throw std::runtime_error("Encountered unexpected node type in function call mangling");
    }
}

std::shared_ptr<hl_ast_conditional_node>
fuction_mangling_pass::mangle_node(std::shared_ptr<hl_ast_conditional_node> node, const std::string& function) {
    node->set_condition(mangle_node(node->get_condition(), function));
    node->set_if_block(mangle_vector(node->get_if_block(), function));
    node->set_else_block(mangle_vector(node->get_else_block(), function));
    return node;
}

std::shared_ptr<hl_ast_loop_node>
fuction_mangling_pass::mangle_node(std::shared_ptr<hl_ast_loop_node> node, const std::string& function) {
    node->set_condition(mangle_node(node->get_condition(), function));
    node->set_init_statement(mangle_node(node->get_init_statement(), function));
    node->set_iteration_expr(mangle_node(node->get_iteration_expr(), function));
    node->set_loop_content(mangle_vector(node->get_loop_content(), function));
    return node;
}

std::shared_ptr<hl_expression_node>
fuction_mangling_pass::mangle_node(std::shared_ptr<hl_expression_node> node, const std::string& function) {
    if(node->is_immediate())
        return node;
    if(!node->is_unary()){
        node->set_lhs(mangle_node(node->get_lhs(), function));
    }
    node->set_rhs(mangle_node(node->get_rhs(),function));
    return node;
}

std::shared_ptr<hl_definition_node>
fuction_mangling_pass::mangle_node(const std::shared_ptr<hl_definition_node>& node, const std::string& function) {
    node->set_array_index(mangle_vector(node->get_array_index(),function));
    node->set_array_initializer(mangle_vector(node->get_array_initializer(), function));
    node->set_name(mangle_string(node->get_name(),function));
    node->set_variable(mangle_variable(node->get_variable(), function));
    return node;
}

std::shared_ptr<hl_function_call_node>
fuction_mangling_pass::mangle_node(const std::shared_ptr<hl_function_call_node>& node, const std::string& function) {
    node->set_arguments(mangle_vector(node->get_arguments(), function));
    return node;
}

std::shared_ptr<hl_ast_operand>
fuction_mangling_pass::mangle_node(const std::shared_ptr<hl_ast_operand>& node, const std::string& function) {
    node->set_variable(mangle_variable(node->get_variable(), function));
    node->set_array_index(mangle_vector(node->get_array_index(),function));
    return node;
}

std::vector<std::shared_ptr<hl_ast_node>>
fuction_mangling_pass::mangle_vector(const std::vector<std::shared_ptr<hl_ast_node>> &v, const std::string& function) {
    for(auto &item:v){
        mangle_node(item, function);
    }
    return v;
}

std::string fuction_mangling_pass::mangle_string(const std::string& s, const std::string& function) {
    return "_fcmglr_function_"+  function + "_" + s;
}

std::shared_ptr<variable> fuction_mangling_pass::mangle_variable(const std::shared_ptr<variable> &v, const std::string &function) {
    v->set_name(mangle_string(v->get_name(), function));
    v->set_variable_class(variable_regular_type);
    v->set_bound_reg(-1);
    return v;
}
