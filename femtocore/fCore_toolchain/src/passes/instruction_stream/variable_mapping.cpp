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

#include "passes/instruction_stream/variable_mapping.hpp"

variable_mapping::variable_mapping(std::shared_ptr<variable_map> &v) : stream_pass_base("Variable mapping"){
    vmap = v;
}

std::shared_ptr<ll_instruction_node> variable_mapping::apply_pass(std::shared_ptr<ll_instruction_node> element) {

    switch (element->get_type()) {
        case isa_register_instruction:
            map_register_inst(std::static_pointer_cast<ll_register_instr_node>(element));
            break;
        case isa_conversion_instruction:
            map_conv_instr(std::static_pointer_cast<ll_conversion_instr_node>(element));
            break;
        case isa_independent_instruction:
        case isa_intercalated_constant:
            // INDEPENDENT INSTRUCTIONS AND INTERCALATED CONSTANTS DO NOT USE VARIABLES
            break;
        case isa_load_constant_instruction:
            map_load_const_instr(std::static_pointer_cast<ll_load_constant_instr_node>(element));
            break;
        default:
            throw std::runtime_error("Invalid instruction type reached variable mapping stage");
    }


    return element;
}

void variable_mapping::map_register_inst(const std::shared_ptr<ll_register_instr_node>& instr) {
    std::string op_a = instr->get_operand_a()->get_linear_identifier();
    std::string op_b = instr->get_operand_b()->get_linear_identifier();
    std::string dst = instr->get_destination()->get_linear_identifier();

    vmap->insert(op_a, instr->get_operand_a());
    vmap->insert(op_b, instr->get_operand_b());
    vmap->insert(dst, instr->get_destination());
}

void variable_mapping::map_conv_instr(const std::shared_ptr<ll_conversion_instr_node>& instr) {
    std::string src = instr->get_source()->get_linear_identifier();
    std::string dst = instr->get_destination()->get_linear_identifier();

    vmap->insert(src, instr->get_source());
    vmap->insert(dst, instr->get_destination());
}


void variable_mapping::map_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node>& instr) {
    std::string dst = instr->get_destination()->get_linear_identifier();
    vmap->insert(dst, instr->get_destination());

}