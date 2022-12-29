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

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"

variable_lifetime_mapping::variable_lifetime_mapping(std::shared_ptr<variable_map> &v) : stream_pass_base("Variable lifetime mapping") {
    vmap = v;
    instr_cntr = 0;
}

std::shared_ptr<ll_instruction_node>
variable_lifetime_mapping::apply_pass(std::shared_ptr<ll_instruction_node> element) {
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

    ++instr_cntr;
    return element;
}

void variable_lifetime_mapping::map_register_inst(const std::shared_ptr<ll_register_instr_node> &instr) {
    std::shared_ptr<variable> op_a = vmap->at(instr->get_operand_a()->get_linear_identifier());
    vmap->insert(op_a->get_linear_identifier(), update_variable_lifetime(op_a));

    std::shared_ptr<variable> op_b = vmap->at(instr->get_operand_b()->get_linear_identifier());
    vmap->insert(op_b->get_linear_identifier(), update_variable_lifetime(op_b));

    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->get_linear_identifier());
    vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));

}

void variable_lifetime_mapping::map_conv_instr(const std::shared_ptr<ll_conversion_instr_node> &instr) {
    std::shared_ptr<variable> src = vmap->at(instr->get_source()->get_linear_identifier());
    vmap->insert(src->get_linear_identifier(), update_variable_lifetime(src));

    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->get_linear_identifier());
    vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));

}

void variable_lifetime_mapping::map_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node> &instr) {
    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->get_linear_identifier());
    vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));
}

std::shared_ptr<variable> variable_lifetime_mapping::update_variable_lifetime(const std::shared_ptr<variable>& var) const {
   std::shared_ptr<variable> retval = var;
    if(!var->is_constant()){
        if(var->get_variable_class()==variable_input_type){
            retval->set_first_occurrence(0);
        } else{
            if(instr_cntr <= retval->get_first_occurrence())
                retval->set_first_occurrence(instr_cntr);
        }

        if(instr_cntr >= retval->get_last_occurrence())
            retval->set_last_occurrence(instr_cntr);
    }
    return retval;
}
