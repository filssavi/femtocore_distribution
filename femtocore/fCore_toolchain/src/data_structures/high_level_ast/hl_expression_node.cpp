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

#include "data_structures/high_level_ast/hl_expression_node.hpp"

hl_expression_node::hl_expression_node(expression_type_t et) : hl_ast_node(hl_ast_node_type_expr) {
    expr_type = et;
    assignment_type = regular_assignment;
    type_print = {
            {expr_add, "+"},
            {expr_sub, "-"},
            {expr_mult, "*"},
            {expr_div, "/"},
            {expr_incr_pre, "++(pre)"},
            {expr_incr_post, "(post)++"},
            {expr_decr_pre, "--(pre)"},
            {expr_decr_post, "(post)--"},
            {expr_modulo, "%"},
            {expr_and_l, "&&"},
            {expr_and_b, "&"},
            {expr_or_l, "||"},
            {expr_or_b, "|"},
            {expr_not_l, "!"},
            {expr_not_b, "~"},
            {expr_xor_b, "^"},
            {expr_lsh, "<<"},
            {expr_rsh, ">>"},
            {expr_eq, "=="},
            {expr_neq, "!="},
            {expr_neg, "-"},
            {expr_lt, "<"},
            {expr_gt, ">"},
            {expr_lte, "<="},
            {expr_gte, ">="},
            {expr_assign, "="},
            {expr_reciprocal, "1/"}
    };

    assign_prefix_print = {
            {regular_assignment, ""},
            {addition_assignment, "+"},
            {subtraction_assignment, "-"},
            {multiplication_assignment, "*"},
            {division_assignment, "/"},
            {modulo_assignment, "%"},
            {and_assignment, "&"},
            {or_assignment,"|"},
            {xor_assignment,"^"},
            {lsh_assignment,"<<"},
            {rsh_assignment,">>"},
    };
}

void hl_expression_node::set_lhs(const std::shared_ptr<hl_ast_node> &node) {
    lhs = node;
}

void hl_expression_node::set_rhs(const std::shared_ptr<hl_ast_node> &node) {
    rhs = node;
}

std::shared_ptr<hl_ast_node> hl_expression_node::get_lhs() {
    return lhs;
}

std::shared_ptr<hl_ast_node> hl_expression_node::get_rhs() {
    return rhs;
}

bool operator==(const hl_expression_node &lhs, const hl_expression_node &rhs) {
    bool ret_val = true;

    if(lhs.lhs != nullptr && rhs.lhs != nullptr){
        if(lhs.lhs->node_type == hl_ast_node_type_expr && rhs.lhs->node_type ==  hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(lhs.lhs);
            std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(rhs.lhs);
            ret_val &= *ex_1 == *ex_2;
        }else if(lhs.lhs->node_type == hl_ast_node_type_operand && rhs.lhs->node_type ==  hl_ast_node_type_operand){
            std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(lhs.lhs);
            std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(rhs.lhs);
            ret_val &= *ex_1 == *ex_2;
        } else {
            return false;
        }
    } else if(lhs.lhs == nullptr && rhs.lhs == nullptr);
    else return false;

    if(lhs.rhs != nullptr && rhs.rhs != nullptr){
        if((lhs.rhs->node_type == hl_ast_node_type_expr) && (rhs.rhs->node_type ==  hl_ast_node_type_expr)){
            std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(lhs.rhs);
            std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(rhs.rhs);
            ret_val &= *ex_1 == *ex_2;
        }else if((lhs.rhs->node_type == hl_ast_node_type_operand) && (rhs.rhs->node_type ==  hl_ast_node_type_operand)){
            std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(lhs.rhs);
            std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(rhs.rhs);
            ret_val &= *ex_1 == *ex_2;
        }else if((lhs.rhs->node_type == hl_ast_node_type_function_call) && (rhs.rhs->node_type ==  hl_ast_node_type_function_call)){
            std::shared_ptr<hl_function_call_node> ex_1 = std::static_pointer_cast<hl_function_call_node>(lhs.rhs);
            std::shared_ptr<hl_function_call_node> ex_2 = std::static_pointer_cast<hl_function_call_node>(rhs.rhs);
            ret_val &= *ex_1 == *ex_2;
        } else {
            return false;
        }
    } else if(lhs.rhs == nullptr && rhs.rhs == nullptr);
    else return false;

    ret_val &= lhs.expr_type == rhs.expr_type;
    ret_val &= lhs.assignment_type == rhs.assignment_type;

    return ret_val;
}

std::string hl_expression_node::pretty_print() {
    std::ostringstream ss;
    if (lhs != nullptr) {
        if (lhs->node_type == hl_ast_node_type_operand) {
            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(lhs);
            std::string tmp_lhs = *op;
            ss << tmp_lhs;
        } else {
            ss << std::static_pointer_cast<hl_expression_node>(lhs)->pretty_print();
        }

    }

    ss << assign_prefix_print[assignment_type] << type_print[expr_type];

    if (rhs->node_type == hl_ast_node_type_operand) {

        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(rhs);
        std::string tmp_rhs = *op;
        ss << tmp_rhs;
    } else if(rhs->node_type == hl_ast_node_type_function_call){
        ss << std::static_pointer_cast<hl_function_call_node>(rhs)->pretty_print();
    }else{
        ss << std::static_pointer_cast<hl_expression_node>(rhs)->pretty_print();
    }
    std::string ret = ss.str();
    return ret;
}

expression_type_t hl_expression_node::get_type() {
    return expr_type;
}

bool hl_expression_node::is_unary() {
    bool res  = false;
    res |= expr_type == expr_reciprocal;
    res |= expr_type == expr_not_b;
    res |= expr_type == expr_not_l;
    res |= expr_type == expr_neg;
    res |= expr_type == expr_incr_pre;
    res |= expr_type == expr_incr_post;
    res |= expr_type == expr_decr_post;
    res |= expr_type == expr_decr_pre;
    res |= expr_type == expr_call;
    res |= expr_type == expr_itf;
    res |= expr_type == expr_fti;
    res |= expr_type == expr_abs;
    res |= expr_type == expr_popcnt;
    return res;
}

bool hl_expression_node::is_hardware_compatible(expression_type_t et) {
    return false;
}

nlohmann::json hl_expression_node::dump() {
    nlohmann::json retval = hl_ast_node::dump();

    if(!is_unary()){
        retval["lhs"] = hl_ast_node::dump_by_type(lhs);
    }
    retval["rhs"] = hl_ast_node::dump_by_type(rhs);
    retval["expr_type"] = expression_type_to_string(expr_type);
    retval["assignment_type"] = assignment_type_to_string(assignment_type);

    return retval;
}

bool hl_expression_node::is_immediate() {
    bool res  = false;
    res |= expr_type == expr_nop;
    return res;
}
