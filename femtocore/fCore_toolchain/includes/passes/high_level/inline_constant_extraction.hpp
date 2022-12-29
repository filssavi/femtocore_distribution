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
#ifndef FCORE_TOOLCHAIN_INLINE_CONSTANT_EXTRACTION_H
#define FCORE_TOOLCHAIN_INLINE_CONSTANT_EXTRACTION_H

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class inline_constant_extraction : public pass_base<hl_ast_node> {
public:
    inline_constant_extraction();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::vector<std::shared_ptr<hl_ast_node>> process_node(const std::shared_ptr<hl_expression_node> &element);
    std::vector<std::shared_ptr<hl_ast_node>> process_node(const std::shared_ptr<hl_definition_node> &element);

    std::vector<std::shared_ptr<hl_ast_node>> process_expression(const std::shared_ptr<hl_expression_node>& element);
    std::vector<std::shared_ptr<hl_ast_node>> process_operand(const std::shared_ptr<hl_ast_operand>& element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    int n_var;
};


#endif //FCORE_TOOLCHAIN_INLINE_CONSTANT_EXTRACTION_H
