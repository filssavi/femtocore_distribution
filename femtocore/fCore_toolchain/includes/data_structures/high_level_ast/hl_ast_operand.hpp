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

#ifndef FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP
#define FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP

#include "hl_ast_node.hpp"
#include "data_structures/common/variable.hpp"
#include <nlohmann/json.hpp>

#include <string>


class hl_ast_operand : public hl_ast_node{
public:
    explicit hl_ast_operand(std::shared_ptr<variable> iv);
    // VARIABLE NAME
    void set_name(const std::string &name);
    std::string get_name() { return inner_variable->get_name();};
    std::string get_identifier() { return inner_variable->get_identifier();};
    // INTEGER IMMEDIATE VALUE
    void set_immediate(const int &v);
    [[nodiscard]] int get_int_value() const;
    // FLOAT IMMEDIATE VALUE
    void set_immediate(const float &v);
    [[nodiscard]] float get_float_val() const;
    // TYPE
    variable_type_t get_type();
    void set_type(variable_type_t type);
    // ARRAY INDEX
    std::vector<std::shared_ptr<hl_ast_node>> get_array_index();
    void set_array_index(std::vector<std::shared_ptr<hl_ast_node>> idx);

    // ARRAY CONTIGUITY
        void set_contiguity(bool c){ inner_variable->set_contiguity(c);}
        bool get_contiguity() {return inner_variable->is_contiguous();};

    //INNER VARIABLE
    void set_variable(std::shared_ptr<variable> v);
    std::shared_ptr<variable> get_variable();

    nlohmann::json dump() override;

    bool is_terminal() override {return true;}
    bool is_scalar() {return  inner_variable->get_type()!=var_type_array;};
    std::string pretty_print() override;
    operator std::string();
    friend bool operator==(const hl_ast_operand& lhs, const hl_ast_operand& rhs);
private:

    std::vector<std::shared_ptr<hl_ast_node>> array_index;
    std::shared_ptr<variable> inner_variable;
};

#endif //FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP
