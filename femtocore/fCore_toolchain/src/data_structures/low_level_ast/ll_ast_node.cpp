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

#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "data_structures/low_level_ast/ll_loop_node.hpp"
#include "data_structures/low_level_ast/ll_ast_pragma.hpp"
#include "data_structures/low_level_ast/ll_instruction_node.hpp"

ll_ast_node::ll_ast_node() {

}

ll_ast_node::ll_ast_node(ll_ast_node_type_t block_type) {
    type = block_type;
}



bool ll_ast_node::is_terminal() {

    return false;
}

std::shared_ptr<ll_ast_node> ll_ast_node::deep_copy_element(const std::shared_ptr<ll_ast_node> &element) {
    std::shared_ptr<ll_ast_node> result;

    if(element->type == ll_type_for_block) {
        std::shared_ptr<ll_loop_node> loop_elem = std::static_pointer_cast<ll_loop_node>(element);
        std::shared_ptr<ll_loop_node> loop_res = std::make_shared<ll_loop_node>();

        loop_res->set_loop_start(loop_elem->get_loop_start());
        loop_res->set_advance(loop_elem->get_advance());
        loop_res->set_loop_end(loop_elem->get_loop_end());
        result = std::static_pointer_cast<ll_ast_node>(loop_res);
    } else if(element->type == ll_type_pragma){
        std::shared_ptr<ll_ast_pragma> pragma_elem = std::static_pointer_cast<ll_ast_pragma>(element);
        std::shared_ptr<ll_ast_pragma> pragma_res = std::make_shared<ll_ast_pragma>(pragma_elem->get_directive());
        result = std::static_pointer_cast<ll_ast_node>(pragma_res);
    } else if(element->type == ll_type_instr ){
        std::shared_ptr<ll_instruction_node> instr_elem = std::static_pointer_cast<ll_instruction_node>(element);
        std::shared_ptr<ll_instruction_node> instr_res = std::make_shared<ll_instruction_node>(*instr_elem);

        result = std::static_pointer_cast<ll_ast_node>(instr_res);
    } else {
        ll_ast_node copied_elem;
        result = std::make_shared<ll_ast_node>(copied_elem);
    }

    if(element->has_content()){
        std::vector<std::shared_ptr<ll_ast_node>> children;
        for(auto &item:element->get_content()){
            std::shared_ptr<ll_ast_node> child = deep_copy_element(item);
            children.push_back(child);
        }
        result->set_content(children);
    }
    result->type = element->type;

    return result;
}






bool operator==(const ll_ast_node &lhs, const ll_ast_node &rhs) {
    if(lhs.type != rhs.type) return false;

        bool retval = true;
        if(lhs.content.empty() && rhs.content.empty()){
            retval &= true;
        } else if(lhs.content.empty() || rhs.content.empty()){
            retval = false;
        } else {
            bool args_equal = true;
            if(lhs.content.size() != rhs.content.size()) return false;
            for (int i = 0; i < lhs.content.size(); i++) {
                args_equal &= *lhs.content[i] == *rhs.content[i];
            }
            retval &= args_equal;
        }
        return retval;

}


bool
ll_ast_node::compare_content_by_type(const std::shared_ptr<ll_ast_node> &lhs, const std::shared_ptr<ll_ast_node> &rhs) {
    if(lhs->type != rhs->type) return false;

    switch (lhs->type) {
        case ll_type_program_head:
        case ll_type_code_block:
            return *lhs == *rhs;
        case ll_type_pragma:
            return *std::static_pointer_cast<ll_ast_pragma>(lhs) == *std::static_pointer_cast<ll_ast_pragma>(rhs);
        case ll_type_for_block:
            return *std::static_pointer_cast<ll_loop_node>(lhs) == *std::static_pointer_cast<ll_loop_node>(rhs);
        case ll_type_instr:
            return *std::static_pointer_cast<ll_instruction_node>(lhs) == *std::static_pointer_cast<ll_instruction_node>(rhs);
        default:
            return false;
    }
    return false;
}

nlohmann::json ll_ast_node::dump() {
    nlohmann::json ret_val;
    ret_val["type"] = ll_ast_node_to_string(type);
    ret_val["content"] = dump_array(content);
    return ret_val;
}

std::vector<nlohmann::json> ll_ast_node::dump_array(const std::vector<std::shared_ptr<ll_ast_node>>& vect) {
    std::vector<nlohmann::json> ret_val;
    for(auto &i: vect){
        ret_val.push_back(ll_ast_node::dump_by_type(i));
    }
    return ret_val;
}

nlohmann::json ll_ast_node::dump_by_type(const std::shared_ptr<ll_ast_node>& node) {
    switch (node->type) {
        case ll_type_for_block: return std::static_pointer_cast<ll_loop_node>(node)->dump();
        case ll_type_instr: return ll_instruction_node::dump_instruction_by_type(std::static_pointer_cast<ll_instruction_node>(node));
        case ll_type_program_head: return node->dump();
        case ll_type_pragma: return std::static_pointer_cast<ll_ast_pragma>(node)->dump();
        case ll_type_code_block: return node->dump();
        default:
            throw std::runtime_error("Unknown node type has been dumped");
    }
}