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

#ifndef FCORE_TOOLCHAIN_ZERO_ASSIGNMENT_REMOVAL_PASS_HPP
#define FCORE_TOOLCHAIN_ZERO_ASSIGNMENT_REMOVAL_PASS_HPP

#include "passes/instruction_stream/stream_pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class zero_assignment_removal_pass : public stream_pass_base{
public:
    zero_assignment_removal_pass();
    std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) override;
private:
    bool delete_intercalated_const;
};


#endif //FCORE_TOOLCHAIN_ZERO_ASSIGNMENT_REMOVAL_PASS_HPP
