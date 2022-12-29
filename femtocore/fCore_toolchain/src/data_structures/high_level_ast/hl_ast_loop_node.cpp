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
// limitations under the License.30/06/2021.
//

#include "data_structures/high_level_ast/hl_ast_loop_node.h"

hl_ast_loop_node::hl_ast_loop_node() : hl_ast_node(hl_ast_node_type_loop){

}

std::string hl_ast_loop_node::pretty_print() {

    std::ostringstream ss;

    ss << "for (" << init_statement->pretty_print()<< "; ";
    ss << condition->pretty_print() << "; ";
    ss << iteration_expr->pretty_print() << ") {"<< std::endl;

    if(!loop_content.empty()){
        for(const auto& item:loop_content){
            ss << item->pretty_print() << ";" << std::endl;
        }
    }
    ss<< "}";
    return ss.str();
}

bool operator==(const hl_ast_loop_node &lhs, const hl_ast_loop_node &rhs) {
    bool ret_val = true;

    ret_val &= hl_ast_node::compare_content_by_type( lhs.init_statement, rhs.init_statement);
    ret_val &= hl_ast_node::compare_content_by_type( lhs.condition, rhs.condition);
    ret_val &= hl_ast_node::compare_content_by_type( lhs.iteration_expr, rhs.iteration_expr);

    ret_val &= hl_ast_node::compare_vectors(lhs.loop_content, rhs.loop_content);

    return ret_val;
}

nlohmann::json hl_ast_loop_node::dump() {
    nlohmann::json retval = hl_ast_node::dump();
    retval["loop_content"] = hl_ast_node::dump_array(loop_content);
    retval["iteration_expr"] = iteration_expr->dump();
    retval["condition"] = condition->dump();
    retval["init_statement"] = init_statement->dump();

    return retval;
}
