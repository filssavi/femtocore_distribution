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

#include "passes/low_level/ll_pass_manager.hpp"

ll_pass_manager::ll_pass_manager(int dal) {
    dump_ast_level = dal;
}


std::vector<std::shared_ptr<ll_ast_node>>
ll_pass_manager::process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>> &pass) {
    std::shared_ptr<ll_ast_node> result;
    std::vector<std::shared_ptr<ll_ast_node>> content = subtree->get_content();
    std::vector<std::shared_ptr<ll_ast_node>> result_vector = content;
    for (int i = 0; i< content.size(); i++) {
        if(content[i]->is_terminal()) continue;
        std::vector<std::shared_ptr<ll_ast_node>> tmp_result;
        tmp_result = process_nodes(content[i], pass);
        result_vector.insert(result_vector.begin()+i, tmp_result.begin(), tmp_result.end());

        result_vector.erase(result_vector.begin()+i+tmp_result.size());
    }
    subtree->set_content(result_vector);
    return pass->process_node(subtree);
}

std::shared_ptr<ll_ast_node> ll_pass_manager::process_leaves(const std::shared_ptr<ll_ast_node> &subtree,
                                                             const std::shared_ptr<pass_base<ll_ast_node>> &pass) {

    std::shared_ptr<ll_ast_node> result;
    std::vector<std::shared_ptr<ll_ast_node>> content = subtree->get_content();
    std::vector<std::shared_ptr<ll_ast_node>> result_vector = content;
    for (auto & i : content) {
        if(i->is_terminal()) {
            i = pass->process_leaf(i);
        } else{
            process_leaves(i, pass);
        }

    }
    subtree->set_content(content);
    return subtree;
}

void ll_pass_manager::run_morphing_pass(std::shared_ptr<ll_ast_node> &subtree,
                                                       const std::shared_ptr<pass_base<ll_ast_node>> &pass) {
    switch (pass->get_pass_type()) {
        case NODE_PASS:{
            process_nodes(subtree, pass)[0];
            break;
        }
        case LEAF_PASS:{
            process_leaves(subtree, pass);
            break;
        }
        default:
            break;
    }
}


