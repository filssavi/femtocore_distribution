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
//

#include "passes/high_level/division_implementation_pass.hpp"


division_implementation_pass::division_implementation_pass() : pass_base<hl_ast_node>("division implementation pass"){

}

std::shared_ptr<hl_ast_node> division_implementation_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_expr){
        ret_val = process_expression(std::static_pointer_cast<hl_expression_node>(element));
    } else if(element->node_type == hl_ast_node_type_function_call){
        ret_val = process_f_call(std::static_pointer_cast<hl_function_call_node>(element));
    }
    return ret_val;
}

std::shared_ptr<hl_ast_node> division_implementation_pass::process_expression(std::shared_ptr<hl_expression_node> exp) {
    if(exp->get_type() == expr_div){
        std::shared_ptr<hl_ast_node> lhs = exp->get_lhs();
        std::shared_ptr<hl_expression_node> modulo_expr = std::make_shared<hl_expression_node>(expr_reciprocal);
        modulo_expr->set_rhs(exp->get_rhs());
        std::shared_ptr<hl_expression_node> mult_expr = std::make_shared<hl_expression_node>(expr_mult);
        mult_expr->set_lhs(exp->get_lhs());
        mult_expr->set_rhs(modulo_expr);
        return mult_expr;
    } else {
        return exp;
    }
}

std::shared_ptr<hl_ast_node> division_implementation_pass::process_f_call(std::shared_ptr<hl_function_call_node> f_call) {
    auto args = f_call->get_arguments();
    for(auto &i: args) {
        if(i->node_type == hl_ast_node_type_expr){
            i = process_expression(std::static_pointer_cast<hl_expression_node>(i));
        }
    }
    f_call->set_arguments(args);
    return f_call;
}

