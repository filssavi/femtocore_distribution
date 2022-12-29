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

#include "passes/low_level/instruction_counting_pass.hpp"

instruction_counting_pass::instruction_counting_pass() : pass_base<ll_ast_node>("instruction counting pass"){

}

void instruction_counting_pass::analyze_element(std::shared_ptr<ll_ast_node> element) {
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        int count = node->instruction_count();
        if(count>=0)
            instruction_count += count;
        else
            throw std::runtime_error("Instruction counting in brancing code is not supported");
    }

}

std::vector<int> instruction_counting_pass::get_analysis_result() {
    std::vector<int> result_count = {instruction_count};
    return result_count;
}

