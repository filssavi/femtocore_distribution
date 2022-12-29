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

#ifndef FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H
#define FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H

#include "passes/pass_base.hpp"
#include "tools/array_linearizer.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class array_initialization_substitution : public pass_base<hl_ast_node>{
public:
    array_initialization_substitution();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};

private:
    std::vector<std::shared_ptr<hl_ast_node>> process_node_by_type(const std::shared_ptr<hl_ast_node>& node);
    std::shared_ptr<hl_expression_node> build_initialization_expr(const std::shared_ptr<hl_definition_node>& var_name, int index);
};

#endif //FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H
