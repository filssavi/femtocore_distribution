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
// limitations under the License.08/07/2021.
//

#ifndef FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H
#define FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

class operating_assignment_implementation_pass : public pass_base<hl_ast_node> {
public:
    operating_assignment_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
private:
    static std::shared_ptr<hl_expression_node> create_top_expression(assignment_type_t a);
};


#endif //FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H
