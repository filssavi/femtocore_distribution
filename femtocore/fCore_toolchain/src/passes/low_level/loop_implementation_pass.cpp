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

#include "passes/low_level/loop_implementation_pass.hpp"


loop_implementation_pass::loop_implementation_pass() : pass_base<ll_ast_node>("loop implementation pass"){

}

std::vector<std::shared_ptr<ll_ast_node>> loop_implementation_pass::process_node(std::shared_ptr<ll_ast_node> element) {
    bool unroll_mode = false;
    std::vector<std::shared_ptr<ll_ast_node>> loop_content;
    std::vector<std::shared_ptr<ll_ast_node>> new_loop_content;
    if(element->type == ll_type_for_block){
        std::shared_ptr<ll_loop_node> loop = std::static_pointer_cast<ll_loop_node>(element);
        for(auto & item:loop->get_content()){
            if(item->type == ll_type_pragma) {
                std::shared_ptr<ll_ast_pragma> pragma_item = std::static_pointer_cast<ll_ast_pragma>(item);
                unroll_mode =  pragma_item->get_directive() == "unroll";
            } else{
                loop_content.push_back(item);
            }
        }
        if(unroll_mode){
            int loop_idx = 0;

            loop_end_t end_obj = loop->get_loop_end();
            int loop_end_val = end_obj.end_count;
            loop_advance_t advance = loop->get_advance();
            if(end_obj.condition == "<=" | end_obj.condition == ">=")
                loop_end_val--;

            if(advance.direction){

                for(loop_idx=loop->get_loop_start().starting_value; loop_idx<loop_end_val; loop_idx++){
                    for(auto&item:loop_content){
                        new_loop_content.push_back(item);
                    }
                }

            } else{
                for(loop_idx=loop->get_loop_start().starting_value; loop_idx>loop_end_val; loop_idx--){
                    for(auto&item:loop_content){
                        new_loop_content.push_back(item);
                    }
                }
            }
        } else{
            throw std::runtime_error("Standard loop are not supported yet");
        }

    } else{
        new_loop_content.push_back(element);
    }

    return new_loop_content;
}

