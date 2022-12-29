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
// limitations under the License.29/06/2021.
//

#include "tools/expression_evaluator.hpp"


bool expression_evaluator::is_constant_expression(const std::shared_ptr<hl_expression_node>& expression) {
    bool retval = true;
    if(expression->is_immediate()) return false;
    if(expression->get_type() == expr_efi) return false;
    retval &= is_constant_subexpr(expression->get_rhs());
    if(!expression->is_unary()) retval &= is_constant_subexpr(expression->get_lhs());
    return retval;
}

bool expression_evaluator::is_constant_subexpr(const std::shared_ptr<hl_ast_node>& subex) {
    if(subex->node_type == hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> node = std::static_pointer_cast<hl_ast_operand>(subex);
        if(node->get_type() == var_type_scalar ||  node->get_type() == var_type_array){
            return false;
        } else{
            return true;
        }
    } else{
        return is_constant_expression(std::static_pointer_cast<hl_expression_node>(subex));
    }
}

std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_expression(std::shared_ptr<hl_expression_node> expression) {
    if(expression->is_unary()){
        return evaluate_unary_expression(expression);
    } else {
        return evaluate_regular_expression(expression);
    }
}



std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_unary_expression(std::shared_ptr<hl_expression_node> expression) {
    std::shared_ptr<hl_ast_operand> retval;

    std::shared_ptr<hl_ast_operand> rhs;
    if(expression->get_rhs()->node_type ==hl_ast_node_type_expr){
        rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));
    } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
        rhs = std::static_pointer_cast<hl_ast_operand>(expression->get_rhs());
    } else {
        throw std::runtime_error("node type not expected during expression evaluation");
    }

    c_types_t expr_type = c_type_int;
    //In order for the result type to be flating point either the operand is a float or the expression is reciprocal, which
    //always results in a float
    if(rhs->get_type() == var_type_float_const || expression->get_type() == expr_reciprocal){
        expr_type = c_type_float;
    }

    if(expression->get_type() != expr_fti || expression->get_type() != expr_itf  ){
        if(expr_type == c_type_float){
            float operand = rhs->get_float_val();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

            retval->set_immediate(evaluate_unary_expr_f(operand, expression->get_type()));
        } else {
            int operand = rhs->get_int_value();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

            retval->set_immediate(evaluate_unary_expr_i(operand, expression->get_type()));
        }
    }

    return retval;
}

std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_regular_expression(std::shared_ptr<hl_expression_node> expression) {

    std::shared_ptr<hl_ast_operand> retval;

    std::shared_ptr<hl_ast_operand> lhs;
    if(expression->get_lhs()->node_type ==hl_ast_node_type_expr){
        lhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_lhs()));
    } else if(expression->get_lhs()->node_type ==hl_ast_node_type_operand) {
        lhs = std::static_pointer_cast<hl_ast_operand>(expression->get_lhs());
    } else {
        throw std::runtime_error("node type not expected during expression evaluation");
    }

    std::shared_ptr<hl_ast_operand> rhs;
    if(expression->get_rhs()->node_type ==hl_ast_node_type_expr){
        rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));
    } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
        rhs = std::static_pointer_cast<hl_ast_operand>(expression->get_rhs());
    } else {
        throw std::runtime_error("node type not expected during expression evaluation");
    }

    c_types_t expr_type = c_type_int;

    if(rhs->get_type() == var_type_float_const || lhs->get_type() == var_type_float_const){
        expr_type = c_type_float;
    }


    if(expr_type == c_type_int) {
        int op_a = lhs->get_int_value();
        int op_b = rhs->get_int_value();


        int operand = evaluate_regular_expr_i(op_a, op_b, expression->get_type());

        std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
        retval = std::make_shared<hl_ast_operand>(var);

    } else {
        float op_a = lhs->get_float_val();
        float op_b = rhs->get_float_val();

        float operand = evaluate_regular_expr_f(op_a, op_b, expression->get_type());

        std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
        retval = std::make_shared<hl_ast_operand>(var);

    }

    return retval;
}



std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_expression_side(const std::shared_ptr<hl_ast_node> &side) {
    std::shared_ptr<hl_ast_operand> retval;

    if(side->node_type == hl_ast_node_type_operand){
        retval = std::static_pointer_cast<hl_ast_operand>(side);
    } else{
        retval = evaluate_expression(std::static_pointer_cast<hl_expression_node>(side));
    }
    return retval;
}


float expression_evaluator::evaluate_unary_expr_f(float operand, expression_type_t operation) {
    switch (operation) {
        case expr_reciprocal:
            return 1/operand;
        case expr_not_b:
            return (float)~(unsigned int)operand;
        case expr_neg:
            return -operand;
        case expr_incr_pre:
        case expr_incr_post:
            return operand+1;
        case expr_decr_post:
        case expr_decr_pre:
            return operand-1;
        default:
            throw std::runtime_error("Internal this condition should not have been possible");

    }
}

int expression_evaluator::evaluate_unary_expr_i(int operand, expression_type_t operation) {
    switch (operation) {
        case expr_reciprocal:
            return 1/operand;
        case expr_not_b:
            return ~operand;
        case expr_neg:
            return -operand;
        case expr_incr_pre:
        case expr_incr_post:
            return operand+1;
        case expr_decr_post:
        case expr_decr_pre:
            return operand-1;
        default:
            throw std::runtime_error("Internal this condition should not have been possible");

    }
}


float expression_evaluator::evaluate_regular_expr_f(float operand_a, float operand_b, expression_type_t operation) {
    switch (operation) {
        case expr_add:
            return operand_a+operand_b;
        case expr_sub:
            return operand_a-operand_b;
        case expr_mult:
            return operand_a*operand_b;
        case expr_div:
            return operand_a/operand_b;
        case expr_eq:
            return operand_a==operand_b?1:0;
        case expr_neq:
            return operand_a!=operand_b?1:0;
        case expr_lt:
            return operand_a<operand_b?1:0;
        case expr_gt:
            return operand_a>operand_b?1:0;
        case expr_lte:
            return operand_a<=operand_b?1:0;
        case expr_gte:
            return operand_a>=operand_b?1:0;
        case expr_satp:
            return operand_a>operand_b?operand_b:operand_a;
        case expr_satn:
            return operand_a<operand_b?operand_b:operand_a;
        default:
            throw std::runtime_error("Internal Unexpected constant expression");
    }
}

int expression_evaluator::evaluate_regular_expr_i(int operand_a, int operand_b, expression_type_t operation) {
    switch (operation) {
        case expr_add:
            return operand_a+operand_b;
        case expr_sub:
            return operand_a-operand_b;
        case expr_mult:
            return operand_a*operand_b;
        case expr_div:
            return operand_a/operand_b;
        case expr_modulo:
            return operand_a%operand_b;
        case expr_and_l:
            return operand_a&&operand_b;
        case expr_and_b:
            return operand_a&operand_b;
        case expr_or_l:
            return operand_a||operand_b;
        case expr_or_b:
            return operand_a|operand_b;
        case expr_xor_b:
            return operand_a^operand_b;
        case expr_lsh:
            return operand_a<<operand_b;
        case expr_rsh:
            return operand_a>>operand_b;
        case expr_eq:
            return operand_a==operand_b?1:0;
        case expr_neq:
            return operand_a!=operand_b?1:0;
        case expr_lt:
            return operand_a<operand_b?1:0;
        case expr_gt:
            return operand_a>operand_b?1:0;
        case expr_lte:
            return operand_a<=operand_b?1:0;
        case expr_gte:
            return operand_a>=operand_b?1:0;
        case expr_satp:
            return operand_a>operand_b?operand_b:operand_a;
        case expr_satn:
            return operand_a<operand_b?operand_b:operand_a;
        default:
            throw std::runtime_error("Internal Unexpected constant expression");
    }
}