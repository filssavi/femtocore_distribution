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
// limitations under the License.01/07/2021.
//

#include "data_structures/high_level_ast/hl_ast_operand.hpp"

#include <utility>

hl_ast_operand::hl_ast_operand(std::shared_ptr<variable> iv) : hl_ast_node(hl_ast_node_type_operand) {
inner_variable = std::move(iv);
}

void hl_ast_operand::set_name(const std::string &n) {
    inner_variable->set_name(n);
}

void hl_ast_operand::set_immediate(const int &v) {
    inner_variable->set_const_i(v);
}

void hl_ast_operand::set_immediate(const float &v) {
    inner_variable->set_const_f(v);
}

int hl_ast_operand::get_int_value() const {
    return inner_variable->get_const_i();
}

float hl_ast_operand::get_float_val() const {
    return inner_variable->get_const_f();
}

void hl_ast_operand::set_type(variable_type_t type) {
    inner_variable->set_type(type);
}

variable_type_t hl_ast_operand::get_type() {
    return inner_variable->get_type();
}

bool operator==(const hl_ast_operand &lhs, const hl_ast_operand &rhs) {
    bool ret_val = true;
    ret_val &= lhs.node_type == rhs.node_type;

    if(lhs.inner_variable == nullptr && rhs.inner_variable == nullptr) ret_val &= true;
    else if (lhs.inner_variable == nullptr || rhs.inner_variable == nullptr) ret_val &= false;
    else ret_val &= *lhs.inner_variable == *rhs.inner_variable;

    ret_val &= hl_ast_node::compare_vectors(lhs.array_index, rhs.array_index);

    return ret_val;
}

hl_ast_operand::operator std::string() {
    return pretty_print();
}

std::string hl_ast_operand::pretty_print() {
    std::string ret_val;
    switch (inner_variable->get_type()) {
        case var_type_int_const:
            ret_val = std::to_string(inner_variable->get_const_i());
            break;
        case var_type_float_const:
            ret_val = std::to_string(inner_variable->get_const_f());
            break;
        case var_type_scalar:
            ret_val = inner_variable->get_name();
            break;
        case var_type_array:{
            ret_val = inner_variable->get_name();
            for(auto &item:array_index){
                ret_val += '[' + item->pretty_print() + ']';
            }
        }

    }
    return ret_val;
}

std::vector<std::shared_ptr<hl_ast_node>> hl_ast_operand::get_array_index() {
    return array_index;
}

void hl_ast_operand::set_array_index(std::vector<std::shared_ptr<hl_ast_node>> idx) {
    array_index = std::move(idx);
}

void hl_ast_operand::set_variable(std::shared_ptr<variable> v) {
    inner_variable = std::move(v);
}

std::shared_ptr<variable> hl_ast_operand::get_variable() {
    return inner_variable;
}

nlohmann::json hl_ast_operand::dump() {
    nlohmann::json retval = hl_ast_node::dump();
    retval["inner_variable"] = inner_variable->dump();
    std::vector<nlohmann::json> array_index_dump;
    retval["array_index"] = hl_ast_node::dump_array(array_index);
    return retval;
}
