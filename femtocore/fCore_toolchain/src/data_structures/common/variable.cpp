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

#include "data_structures/common/variable.hpp"


variable::variable() {

    name = "invalid-variable";
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(-1);
    contiguity = false;
}

variable::variable(std::string n, float value) {
    name = std::move(n);
    const_f = value;
    variable_type = var_type_float_const;

    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(-1);
    const_i = 0;
    contiguity = false;
}

variable::variable(std::string n, int value) {
    name = std::move(n);
    const_i = value;
    variable_type = var_type_int_const;
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(-1);
    const_f = 0;
    contiguity = false;
}


variable::variable(std::string n) {
    name = std::move(n);
    const_i = 0;
    variable_type = var_type_scalar;
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(-1);
    const_f = 0;
    contiguity = false;
}


void variable::set_used(bool status) {
    used[0] = status;
}

bool variable::is_used() const {
    return used[0];
}

uint32_t variable::get_value() const {

    std::regex re("r(\\d\\d?)");
    std::smatch m;

    if(std::regex_match(name, m, re)) {
        return std::stoi(m[1]);
    }

    if(is_constant()){
        return const_i;
    }
    throw std::runtime_error("Invalid operation: the compiler tried to get the numeric value of a variable");
}

bool operator==(const variable &lhs, const variable &rhs) {
    bool cond = lhs.variable_class == rhs.variable_class;
    cond &= lhs.first_occurrence == rhs.first_occurrence;
    cond &= lhs.last_occurrence == rhs.last_occurrence;
    cond &= lhs.name == rhs.name;
    cond &= lhs.bound_register == rhs.bound_register;
    cond &= lhs.used == rhs.used;
    cond &= lhs.variable_type == rhs.variable_type;
    cond &= lhs.const_i == rhs.const_i;
    cond &= lhs.const_f == rhs.const_f;
    cond &= lhs.contiguity == rhs.contiguity;
    cond &= lhs.array_index == rhs.array_index;
    cond &= lhs.array_shape == rhs.array_shape;
    return cond;
}

float variable::get_const_f() {
    if(variable_type == var_type_float_const){
        return const_f;
    } else {
        return (float) const_i;
    }
}

int variable::get_const_i() {
    if(variable_type == var_type_int_const){
        return const_i;
    } else {
        return (int)const_f;
    }
}

std::string variable::to_str() {
    switch (variable_type) {
        case var_type_int_const:
            return std::to_string(const_i);
        case var_type_float_const:
            return std::to_string(const_f);
        case var_type_scalar:
        case var_type_array:
            return name;
    }
    return "";
}

void variable::set_const_f(float f) {
    if(variable_type == var_type_float_const){
        const_f = f;
    } else {
        throw std::runtime_error("Setting the floating point value of a non floating point variable is not allowed");
    }
}

void variable::set_const_i(int i) {
    if(variable_type == var_type_int_const){
        const_i = i;
    } else {
        throw std::runtime_error("Setting the integer  value of a non integer point variable is not allowed");
    }
}

std::shared_ptr<variable> variable::deep_copy(const std::shared_ptr <variable>& original) {
    std::shared_ptr<variable> copied_var = std::make_shared<variable>();

    copied_var->name = original->name;
    copied_var->variable_type = original->variable_type;
    copied_var->variable_class = original->variable_class;
    copied_var->first_occurrence = original->first_occurrence;
    copied_var->last_occurrence = original->last_occurrence;
    copied_var->bound_register = original->bound_register;
    copied_var->used = original->used;
    copied_var->const_i = original->const_i;
    copied_var->const_f = original->const_f;
    copied_var->contiguity = original->contiguity;
    copied_var->array_shape = original->array_shape;
    copied_var->array_index = original->array_index;
    return copied_var;
}

nlohmann::json variable::dump() {
    nlohmann::json ret_val;

    ret_val["name"] = name;
    ret_val["type"] = variable_type;
    ret_val["class"] = variable_class;
    ret_val["first_occurrence"] = first_occurrence;
    ret_val["last_occurrence"] = last_occurrence;
    ret_val["bound_register"] = bound_register;
    ret_val["contiguity"] = contiguity;
    ret_val["used"] = used;
    ret_val["const_i"] = const_i;
    ret_val["const_f"] = const_f;
    ret_val["array_shape"] = array_shape;
    ret_val["array_index"] = array_index;
    return ret_val;
}

std::string variable::get_identifier() {
    return get_identifier(array_index);
}

std::string variable::get_identifier(const std::vector<int>& idx) {
    std::string ret = name;
    for(auto &elem:idx){
        ret += "_" + std::to_string(elem);
    }
    return ret;
}

std::string variable::get_linear_identifier() {
    if(array_shape.empty()){
        return name;
    }
    std::string ret = name + "_" + std::to_string(get_linear_index());
    return ret;
}

std::string variable::get_linear_identifier(const std::vector<int> &idx) {
    if(array_shape.empty()){
        return name;
    }
    std::string ret = name + "_" + std::to_string(get_linear_index(idx));
    return ret;
}

std::string variable::get_linear_identifier(const int &idx) {
    if(array_shape.empty()){
        return name;
    }
    std::string ret = name + "_" + std::to_string(idx);
    return ret;
}




int variable::get_linear_index() {
    return get_linear_index(array_index);
}

int variable::get_linear_index(const std::vector<int> &idx) {
    if(variable_type == var_type_scalar || variable_type == var_type_float_const || variable_type == var_type_int_const){
        return -1;
    }
    return linearize_array(array_shape, idx);
}

int variable::get_bound_reg() {
    if(!array_index.empty() && bound_register.size()!=1){
        return bound_register[get_linear_index()];
    }
    return bound_register[0];
}

unsigned int variable::get_size() {

    unsigned int shape = 1;
    for(auto &dim:array_shape){
        shape *= dim;
    }
    return shape;
}

