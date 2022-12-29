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


#include "data_structures/low_level_ast/ll_instruction_node.hpp"

#include "data_structures/low_level_ast/ll_register_instr_node.hpp"
#include "data_structures/low_level_ast/ll_conversion_instr_node.hpp"
#include "data_structures/low_level_ast/ll_independent_instr_node.hpp"
#include "data_structures/low_level_ast/ll_load_constant_instr_node.hpp"
#include "data_structures/low_level_ast/ll_pseudo_instr_node.hpp"
#include "data_structures/low_level_ast/ll_intercalated_const_instr_node.hpp"

ll_instruction_node::ll_instruction_node(isa_instruction_type t) : ll_ast_node(ll_type_instr) {
    instruction_type = t;
}

ll_instruction_node::ll_instruction_node(const ll_instruction_node &old_obj) {

    instruction_type = old_obj.instruction_type;
    opcode = old_obj.opcode;
}

isa_instruction_type ll_instruction_node::get_type() {
    return instruction_type;
}

bool ll_instruction_node::is_terminal() {
    return true;
}

bool operator==(const ll_instruction_node &lhs, const ll_instruction_node &rhs) {
    bool retval = true;

    retval &= lhs.opcode == rhs.opcode;
    return retval;
}


bool
ll_instruction_node::compare_content_by_type(const std::shared_ptr<ll_instruction_node> &lhs, const std::shared_ptr<ll_instruction_node> &rhs) {
    if(lhs->get_type() != rhs->get_type()) return false;

    switch (lhs->instruction_type) {
        case isa_register_instruction:
            return *std::static_pointer_cast<ll_register_instr_node>(lhs) == *std::static_pointer_cast<ll_register_instr_node>(rhs);
        case isa_independent_instruction:
            return *std::static_pointer_cast<ll_independent_inst_node>(lhs) == *std::static_pointer_cast<ll_independent_inst_node>(rhs);
        case isa_pseudo_instruction:
            return *std::static_pointer_cast<ll_pseudo_instr_node>(lhs) == *std::static_pointer_cast<ll_pseudo_instr_node>(rhs);
        case isa_conversion_instruction:
            return *std::static_pointer_cast<ll_conversion_instr_node>(lhs) == *std::static_pointer_cast<ll_conversion_instr_node>(rhs);
        case isa_load_constant_instruction:
            return *std::static_pointer_cast<ll_load_constant_instr_node>(lhs) == *std::static_pointer_cast<ll_load_constant_instr_node>(rhs);
        case isa_intercalated_constant:
            return *std::static_pointer_cast<ll_intercalated_const_instr_node>(lhs) == *std::static_pointer_cast<ll_intercalated_const_instr_node>(rhs);
    }
    return false;
}

nlohmann::json ll_instruction_node::dump() {
    nlohmann::json retval = ll_ast_node::dump();
    retval["opcode"] = opcode;
    retval["instruction_type"] = isa_instr_type_to_string(instruction_type);
    return retval;
}

nlohmann::json ll_instruction_node::dump_instruction_by_type(const std::shared_ptr<ll_instruction_node> &node) {
    switch (node->get_type()) {
        case isa_independent_instruction: return std::static_pointer_cast<ll_independent_inst_node>(node)->dump();
        case isa_register_instruction: return std::static_pointer_cast<ll_register_instr_node>(node)->dump();
        case isa_pseudo_instruction: return std::static_pointer_cast<ll_pseudo_instr_node>(node)->dump();
        case isa_conversion_instruction: return std::static_pointer_cast<ll_conversion_instr_node>(node)->dump();
        case isa_load_constant_instruction: return std::static_pointer_cast<ll_load_constant_instr_node>(node)->dump();
        case isa_intercalated_constant: return std::static_pointer_cast<ll_intercalated_const_instr_node>(node)->dump();
        default:
            throw std::runtime_error("Unknown instruction node type has been dumped");
    }
}

bool ll_instruction_node::is_stop() {
    return opcode == "stop";
}

