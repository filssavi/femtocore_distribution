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

#include "passes/low_level/pseudo_instructions_pass.hpp"


pseudo_instructions_pass::pseudo_instructions_pass() : pass_base<ll_ast_node>("pseudo instruction implementation pass"){

}

std::shared_ptr<ll_ast_node> pseudo_instructions_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> ret_val = element;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        if (node->is_pseudo()){
            std::shared_ptr<ll_pseudo_instr_node> pseudo_instr = std::static_pointer_cast<ll_pseudo_instr_node>(node);
            std::string opcode = node->get_opcode();
            auto arguments = pseudo_instr->get_arguments();
            if(opcode ==  "mov"){
                arguments.push_back(arguments[1]);
                variable zero("r0");
                arguments[1] = std::make_shared<variable>(zero);
            } else if(opcode == "neg"){
                variable zero("r0");
                arguments.insert(arguments.begin(), std::make_shared<variable>(zero));
                arguments.push_back(arguments[1]);

            }

            std::string new_opcode = fcore_pseudo_op[node->get_opcode()];
            switch (fcore_op_types[new_opcode]) {
                case isa_register_instruction:
                    ret_val = std::make_shared<ll_register_instr_node>(new_opcode, arguments[0], arguments[1], arguments[2]);
                    break;
                case isa_independent_instruction:
                    ret_val = std::make_shared<ll_independent_inst_node>(new_opcode);
                    break;
                case isa_conversion_instruction:
                    ret_val = std::make_shared<ll_conversion_instr_node>(new_opcode, arguments[0], arguments[1]);
                    break;
                case isa_load_constant_instruction:
                    ret_val = std::make_shared<ll_load_constant_instr_node>(new_opcode, arguments[0], arguments[1]);
                    break;
            }
        }
    }

    return ret_val;
}
