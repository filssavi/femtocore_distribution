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
// limitations under the License.01/07/2021.
//

#include "data_structures/high_level_ast/hl_function_call_node.hpp"





hl_function_call_node::hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a) : hl_ast_node(hl_ast_node_type_function_call){
    name = std::move(n);
    arguments = std::move(a);
}

std::string hl_function_call_node::pretty_print() {
    std::ostringstream ss;
    ss << name<<"( ";
    if(!arguments.empty()){
        for(const auto& item:arguments){
            if(item->node_type == hl_ast_node_type_expr){
                ss << std::static_pointer_cast<hl_expression_node>(item)->pretty_print();
            } else if(item->node_type == hl_ast_node_type_operand){
                hl_ast_operand op = *std::static_pointer_cast<hl_ast_operand>(item);
                std::string op_s = op;
                ss <<  op_s;
            }
            ss<<", ";
        }
    }
    std::string ret = ss.str();

    ret.pop_back();
    ret.pop_back();
    ret += " )";
    return ret;
}

bool operator==(const hl_function_call_node &lhs, const hl_function_call_node &rhs) {
    bool ret_val = true;

    ret_val &= lhs.name == rhs.name;

    ret_val &= hl_ast_node::compare_vectors(lhs.arguments, rhs.arguments);

    return ret_val;
}

nlohmann::json hl_function_call_node::dump() {
    nlohmann::json retval = hl_ast_node::dump();

    retval["name"] = name;
    retval["arguments"] = hl_ast_node::dump_array(arguments);

    return retval;
}
