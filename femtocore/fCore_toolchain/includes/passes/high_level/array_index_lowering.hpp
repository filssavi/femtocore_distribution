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


#ifndef FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP
#define FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class array_index_lowering : public  pass_base<hl_ast_node> {
public:
    array_index_lowering();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
};

#endif //FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP
