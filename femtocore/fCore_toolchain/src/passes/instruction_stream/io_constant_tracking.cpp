//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "passes/instruction_stream/io_constant_tracking.hpp"

#include <utility>

io_constant_tracking::io_constant_tracking(std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> lam) : stream_pass_base("io_constant_tracking"){
    index = 0;
    last_assignment_map = std::move(lam);
}

std::shared_ptr<ll_instruction_node> io_constant_tracking::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    if(element->get_type() == isa_register_instruction){
        auto dest = std::static_pointer_cast<ll_register_instr_node>(element)->get_destination();
        if(dest->get_variable_class() ==variable_output_type ||dest->get_variable_class() ==variable_input_type){
            add_assignment(dest->get_identifier());
        }
    } else if(element->get_type() == isa_conversion_instruction) {
        auto dest = std::static_pointer_cast<ll_conversion_instr_node>(element)->get_destination();
        if(dest->get_variable_class() ==variable_output_type ||dest->get_variable_class() ==variable_input_type){
            add_assignment(dest->get_identifier());
        }
    } else if(element->get_type() == isa_load_constant_instruction) {
        auto dest = std::static_pointer_cast<ll_load_constant_instr_node>(element)->get_destination();
        if(dest->get_variable_class() ==variable_output_type ||dest->get_variable_class() ==variable_input_type){
            add_assignment(dest->get_identifier());
        }
    }
    index++;
    return element;
}

void io_constant_tracking::add_assignment(const std::string& s) {
    if(last_assignment_map->contains(s)){
        last_assignment_map->at(s) = {last_assignment_map->at(s).first, index};
    } else {
        last_assignment_map->insert({s, {index, -1}});
    }
}