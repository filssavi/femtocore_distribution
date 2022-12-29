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

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP


#include "passes/pass_base.hpp"

#include "data_structures/low_level_ast/ll_instruction_node.hpp"

class instruction_counting_pass : public pass_base<ll_ast_node> {

public:
    instruction_counting_pass();
    void analyze_element(std::shared_ptr<ll_ast_node> element) override;
    int get_pass_type() override { return ANALYSIS_PASS;};
    std::vector<int> get_analysis_result() override;
    int instruction_count{0};
};


#endif //FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP
