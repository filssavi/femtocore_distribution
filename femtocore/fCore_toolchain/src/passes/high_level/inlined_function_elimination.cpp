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

#include "passes/high_level/inlined_function_elimination.hpp"


inlined_function_elimination::inlined_function_elimination(std::string entry_point_name) : pass_base("inlined function elimination pass") {
    entry_point = std::move(entry_point_name);
}

std::shared_ptr<hl_ast_node> inlined_function_elimination::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> new_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_content;


    for(auto &item:element->get_content()){
        if(item->node_type == hl_ast_node_type_function_def){
            std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(item);
            if(node->get_name() == entry_point){
                std::vector<std::shared_ptr<hl_ast_node>> main_body = node->get_body();
                new_content.insert(new_content.end(), main_body.begin(), main_body.end());
            }
        } else{
            new_content.push_back(item);
        }
    }
    new_root->set_content(new_content);
    return new_root;
}


