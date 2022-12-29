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


#include "passes/high_level/array_index_lowering.hpp"

array_index_lowering::array_index_lowering() : pass_base<hl_ast_node>("array index lowering"){

}

std::shared_ptr<hl_ast_node> array_index_lowering::process_leaf(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type==hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element);
        if(op->get_type()==var_type_array){
            std::vector<int> array_idx;
            for(auto&item:op->get_array_index()){
                auto idx_op = std::static_pointer_cast<hl_ast_operand>(item);
                array_idx.push_back(idx_op->get_int_value());
            }
            op->get_variable()->set_array_index(array_idx);
            op->set_array_index({});
        }
        return op;
    }
    return element;
}
