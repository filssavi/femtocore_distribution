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

#ifndef FCORE_TOOLCHAIN_HL_AST_NODE_HPP
#define FCORE_TOOLCHAIN_HL_AST_NODE_HPP

#include <map>
#include <string>
#include <stdexcept>

#include "data_structures/ast_node_base.hpp"
#include <nlohmann/json.hpp>


typedef enum {
    hl_ast_node_type_expr = 1,
    hl_ast_node_type_definition = 2,
    hl_ast_node_type_conditional = 3,
    hl_ast_node_type_loop = 4,
    hl_ast_node_type_function_def = 5,
    hl_ast_node_type_operand = 6,
    hl_ast_node_type_function_call = 7,
    hl_ast_node_type_program_root = 8,
    hl_ast_node_type_code_block = 9
} hl_ast_node_type_t;

constexpr std::string_view hl_ast_node_to_string(hl_ast_node_type_t i){
    switch (i) {
        case hl_ast_node_type_expr:return "hl_ast_node_type_expr";
        case hl_ast_node_type_definition: return "hl_ast_node_type_definition";
        case hl_ast_node_type_conditional: return "hl_ast_node_type_conditional";
        case hl_ast_node_type_loop: return "hl_ast_node_type_loop";
        case hl_ast_node_type_function_def: return "hl_ast_node_type_function_def";
        case hl_ast_node_type_operand: return "hl_ast_node_type_operand";
        case hl_ast_node_type_function_call: return "hl_ast_node_type_function_call";
        case hl_ast_node_type_program_root: return "hl_ast_node_type_program_root";
        case hl_ast_node_type_code_block: return "hl_ast_node_type_code_block";
        default: return "unknown hl ast type";
    }
}

typedef enum {
    c_type_void = 1,
    c_type_char = 2,
    c_type_short = 3,
    c_type_int = 4,
    c_type_long = 5,
    c_type_float = 6
} c_types_t;

constexpr std::string_view c_types_to_string(c_types_t i){
    switch (i) {
        case c_type_void:return "c_type_void";
        case c_type_char: return "c_type_char";
        case c_type_short: return "c_type_short";
        case c_type_int: return "c_type_int";
        case c_type_long: return "c_type_long";
        case c_type_float: return "c_type_float";
        default: return "unknown c type";
    }
}

class hl_ast_node : public ast_node_base<hl_ast_node>{

public:
    explicit hl_ast_node(hl_ast_node_type_t t);
    static c_types_t string_to_type(const std::string& t);
    static std::string  type_to_string(const c_types_t &t);

    virtual bool is_terminal();

    virtual std::string pretty_print();

    friend bool operator==(const hl_ast_node& lhs, const hl_ast_node& rhs);

    static  bool compare_content_by_type(const std::shared_ptr<hl_ast_node>& lhs, const std::shared_ptr<hl_ast_node>& rhs);

    virtual nlohmann::json dump();
    static nlohmann::json dump_by_type(const std::shared_ptr<hl_ast_node>& node);
    static std::vector<nlohmann::json> dump_array(const std::vector<std::shared_ptr<hl_ast_node>>& vect);
    static std::shared_ptr<hl_ast_node> deep_copy(const std::shared_ptr<hl_ast_node> &node);
    hl_ast_node_type_t node_type;
    static bool compare_vectors(const std::vector<std::shared_ptr<hl_ast_node>>& lhs, const std::vector<std::shared_ptr<hl_ast_node>>& rhs);

private:
    static std::shared_ptr<hl_ast_node> deep_copy_expr(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_conditional(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_loop(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_operands(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_call(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_program_root(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_code_block(const std::shared_ptr<hl_ast_node> &node);
};


#endif //FCORE_TOOLCHAIN_HL_AST_NODE_HPP
