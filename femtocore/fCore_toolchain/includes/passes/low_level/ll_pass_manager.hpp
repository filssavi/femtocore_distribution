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
// limitations under the License.06/07/2021.
//

#ifndef FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "passes/pass_manager_base.hpp"
#include "passes/pass_base.hpp"

class ll_pass_manager : public pass_manager_base<ll_ast_node> {
public:
    explicit ll_pass_manager(int dal);
    void run_morphing_pass( std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass) override;
    std::vector<std::shared_ptr<ll_ast_node>> process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);
    std::shared_ptr<ll_ast_node> process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);

};


#endif //FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP
