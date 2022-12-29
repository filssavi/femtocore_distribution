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

#include "passes/low_level/load_intercalation_pass.hpp"

load_intercalation_pass::load_intercalation_pass() : pass_base<ll_ast_node>("load intercalation pass") {

}


std::shared_ptr<ll_ast_node> load_intercalation_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> container = std::make_shared<ll_ast_node>(ll_type_code_block);

    bool float_present = false;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);

        if(node->get_opcode() == "ldc"){
            std::shared_ptr<ll_load_constant_instr_node> load_instr = std::static_pointer_cast<ll_load_constant_instr_node>(node);
            std::shared_ptr<ll_intercalated_const_instr_node> constant;
            std::vector<std::shared_ptr<ll_ast_node>> block_content;
            if(load_instr->is_float()){
                float desired_constant = load_instr->get_constant_f();
                constant = std::make_shared<ll_intercalated_const_instr_node>(desired_constant);
            } else {
                uint32_t desired_constant = load_instr->get_constant_i();
                constant = std::make_shared<ll_intercalated_const_instr_node>(desired_constant);
            }


            block_content.push_back(node);
            block_content.push_back(constant);
            container->set_content(block_content);

            return container;
        }

    }
    return element;

}

