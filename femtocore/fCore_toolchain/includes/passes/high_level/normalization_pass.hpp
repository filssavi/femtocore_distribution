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

#ifndef FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
#define FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"


typedef enum {
    expr_normalized = 0,
    expr_normalize_lhs = 1,
    expr_normalize_rhs = 2,
} side_to_normalize;

typedef std::pair<std::shared_ptr<hl_ast_node>, std::vector<std::shared_ptr<hl_ast_node>>> norm_pair_t;

class normalization_pass : public pass_base<hl_ast_node> {
public:
    normalization_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    bool is_normal(const std::shared_ptr<hl_ast_node>& element);

    norm_pair_t process_node_by_type(std::shared_ptr<hl_ast_node> n);
    norm_pair_t process_node_def(const std::shared_ptr<hl_definition_node>& n);
    norm_pair_t process_node_exp(const std::shared_ptr<hl_expression_node>& n);

    c_types_t get_expression_type(std::shared_ptr<hl_expression_node> expr);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    int intermediate_ordinal = 0;
};


#endif //FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
