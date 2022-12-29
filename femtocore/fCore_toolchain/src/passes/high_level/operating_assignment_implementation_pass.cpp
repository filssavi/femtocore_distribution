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

#include "passes/high_level/operating_assignment_implementation_pass.hpp"


operating_assignment_implementation_pass::operating_assignment_implementation_pass() : pass_base<hl_ast_node>("operating assignments implementation pass"){

}

std::shared_ptr<hl_ast_node>
operating_assignment_implementation_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {

    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_assign && node->get_assignment_type() != regular_assignment ){
            std::shared_ptr<hl_expression_node> outer_exp = std::make_shared<hl_expression_node>(expr_assign);
            outer_exp->set_lhs(node->get_lhs());
            std::shared_ptr<hl_expression_node> inner_exp = create_top_expression(node->get_assignment_type());
            inner_exp->set_lhs(node->get_lhs());
            inner_exp->set_rhs(node->get_rhs());
            outer_exp->set_rhs(inner_exp);
            ret_val = outer_exp;
        }
    }
    return ret_val;

}

std::shared_ptr<hl_expression_node>
operating_assignment_implementation_pass::create_top_expression(assignment_type_t a) {
    std::shared_ptr<hl_expression_node> retval;
    switch (a) {
        case addition_assignment:
            retval = std::make_shared<hl_expression_node>(expr_add);
            break;
        case subtraction_assignment:
            retval = std::make_shared<hl_expression_node>(expr_sub);
            break;
        case multiplication_assignment:
            retval = std::make_shared<hl_expression_node>(expr_mult);
            break;
        case division_assignment:
            retval = std::make_shared<hl_expression_node>(expr_div);
            break;
        case modulo_assignment:
            retval = std::make_shared<hl_expression_node>(expr_modulo);
            break;
        case and_assignment:
            retval = std::make_shared<hl_expression_node>(expr_and_b);
            break;
        case or_assignment:
            retval = std::make_shared<hl_expression_node>(expr_or_b);
            break;
        case xor_assignment:
            retval = std::make_shared<hl_expression_node>(expr_xor_b);
            break;
        case lsh_assignment:
            retval = std::make_shared<hl_expression_node>(expr_lsh);
            break;
        case rsh_assignment:
            retval = std::make_shared<hl_expression_node>(expr_rsh);
            break;
    }
    return retval;
}


