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

#ifndef FCORE_TOOLCHAIN_LL_AST_NODE_HPP
#define FCORE_TOOLCHAIN_LL_AST_NODE_HPP

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>
#include <utility>

#include "data_structures/common/variable.hpp"
#include "data_structures/ast_node_base.hpp"


typedef enum {
    ll_type_instr = 1,
    ll_type_for_block = 4,
    ll_type_program_head = 5,
    ll_type_pragma = 6,
    ll_type_code_block = 7,
} ll_ast_node_type_t;

constexpr std::string_view ll_ast_node_to_string(ll_ast_node_type_t i){
    switch (i) {
        case ll_type_instr:return "ll_type_instr";
        case ll_type_for_block: return "ll_type_for_block";
        case ll_type_program_head: return "ll_type_program_head";
        case ll_type_pragma: return "ll_type_pragma";
        case ll_type_code_block: return "ll_type_code_block";
    }
    return "";
}

class ll_ast_node : public ast_node_base<ll_ast_node> {

public:
    ll_ast_node();
    explicit ll_ast_node(ll_ast_node_type_t block_type);

    virtual bool is_terminal();
    static std::shared_ptr<ll_ast_node> deep_copy_element(const std::shared_ptr<ll_ast_node>& element);
    bool compare_content_by_type(const std::shared_ptr<ll_ast_node> &lhs, const std::shared_ptr<ll_ast_node> &rhs);
    ll_ast_node_type_t type;

    virtual nlohmann::json dump();
    static std::vector<nlohmann::json> dump_array(const std::vector<std::shared_ptr<ll_ast_node>>& vect);
    static nlohmann::json dump_by_type(const std::shared_ptr<ll_ast_node>& node);

    friend bool operator==(const ll_ast_node& lhs, const ll_ast_node& rhs);


};





#endif //FCORE_TOOLCHAIN_LL_AST_NODE_HPP
