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

#ifndef FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/common/variable.hpp"

#include <utility>
#include <string>

class hl_definition_node : public hl_ast_node{
public:
    hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v);
    void set_name(std::string name);
    std::string get_name(){ return name;};
    c_types_t get_type(){ return type;};

    bool is_initialized();
    bool is_scalar();
    void set_constant(bool c);
    bool is_constant();

    std::vector<std::shared_ptr<hl_ast_node>> get_array_index() {return array_index;};
    void set_array_index(std::vector<std::shared_ptr<hl_ast_node>> i) {array_index = std::move(i);};

    std::shared_ptr<hl_ast_node> get_scalar_initializer();
    void set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init);
    void set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init, int idx);

    std::vector<std::shared_ptr<hl_ast_node>> get_array_initializer() {return initializer;};
    void set_array_initializer(const std::vector<std::shared_ptr<hl_ast_node>> &init) {initializer = init;};

    std::shared_ptr<variable> get_variable() {return inner_variable;};
    void set_variable(std::shared_ptr<variable> var) {inner_variable = std::move(var);};

    void set_array_shape(std::vector<int> &shape){inner_variable->set_array_shape(shape);};
    std::vector<int> get_array_shape(){return inner_variable->get_array_shape();};

    nlohmann::json dump() override;

    std::string pretty_print() override;
    bool is_terminal() override {
        return true;
    }

    friend bool operator==(const hl_definition_node& lhs, const hl_definition_node& rhs);

protected:
    bool constant;
    std::string name;
    c_types_t type;
    std::vector<std::shared_ptr<hl_ast_node>> initializer;
    std::vector<std::shared_ptr<hl_ast_node>> array_index;
    std::shared_ptr<variable> inner_variable;

};


#endif //FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
