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

#include "passes/instruction_stream/zero_assignment_removal_pass.hpp"

zero_assignment_removal_pass::zero_assignment_removal_pass() : stream_pass_base("Zero assignment removal"){
    delete_intercalated_const = false;
}

std::shared_ptr<ll_instruction_node>
zero_assignment_removal_pass::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    if(element->get_type() == isa_load_constant_instruction){
        std::shared_ptr<ll_load_constant_instr_node> node = std::static_pointer_cast<ll_load_constant_instr_node>(element);
        if(node->get_destination()->get_name() == "r0"){
            delete_intercalated_const = true;
            return nullptr;
        } else {
            return element;
        }
    } else if(element->get_type() == isa_intercalated_constant){
        if(delete_intercalated_const){
            delete_intercalated_const = false;
            return nullptr;
        } else {
            return element;
        }
    } else{
        return element;
    }
}
