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

#ifndef FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
#define FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP

#include <map>
#include <string>

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

class intrinsics_implementation_pass : public  pass_base<hl_ast_node> {
public:
    intrinsics_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> process_node_by_type(const std::shared_ptr<hl_ast_node>& element);
    std::shared_ptr<hl_ast_node> process_function_call(const std::shared_ptr<hl_function_call_node>& element);
    int get_pass_type() override { return LEAF_PASS;};
private:
    std::map<std::string, expression_type_t> substitutions;
    std::map<std::string, int> n_arguments;
};


#endif //FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
