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
// limitations under the License.02/07/2021.
//

#include "passes/instruction_stream/bound_register_mapping.hpp"

bound_register_mapping_pass::bound_register_mapping_pass() : stream_pass_base("Bound register mapping"){

}

std::shared_ptr<ll_instruction_node>
bound_register_mapping_pass::apply_pass(std::shared_ptr<ll_instruction_node> element) {

    switch (element->get_type()) {
        case isa_intercalated_constant:
        case isa_independent_instruction:
        case isa_pseudo_instruction:
            return element;
        case isa_register_instruction:
            return process_reg_instr(element);
        case isa_conversion_instruction:
            return process_conv_instr(element);
        case isa_load_constant_instruction:
            return process_load_instr(element);
    }

    return element;
}

std::shared_ptr<ll_instruction_node>
bound_register_mapping_pass::process_reg_instr(std::shared_ptr<ll_instruction_node> node) {
    auto instr = std::static_pointer_cast<ll_register_instr_node>(node);

    std::string raw_dest = instr->get_destination()->get_name();
    int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
    instr->get_destination()->set_bound_reg(dest);

    std::string raw_op_a = instr->get_operand_a()->get_name();
    int op_a = std::stoi(raw_op_a.substr(1, raw_op_a.size()-1));
    instr->get_operand_a()->set_bound_reg(op_a);

    std::string raw_op_b = instr->get_operand_b()->get_name();
    int op_b = std::stoi(raw_op_b.substr(1, raw_op_b.size()-1));
    instr->get_operand_b()->set_bound_reg(op_b);


    return node;
}

std::shared_ptr<ll_instruction_node>
bound_register_mapping_pass::process_conv_instr(std::shared_ptr<ll_instruction_node> node) {
    auto instr = std::static_pointer_cast<ll_conversion_instr_node>(node);
    std::string raw_dest = instr->get_destination()->get_name();
    int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
    instr->get_destination()->set_bound_reg(dest);

    std::string raw_src = instr->get_source()->get_name();
    int src = std::stoi(raw_src.substr(1, raw_src.size()-1));
    instr->get_source()->set_bound_reg(src);

    return node;
}

std::shared_ptr<ll_instruction_node>
bound_register_mapping_pass::process_load_instr(std::shared_ptr<ll_instruction_node> node) {
    auto instr = std::static_pointer_cast<ll_load_constant_instr_node>(node);

    std::string raw_dest = instr->get_destination()->get_name();
    int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
    instr->get_destination()->set_bound_reg(dest);

    return node;
}
