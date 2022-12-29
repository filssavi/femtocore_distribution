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

#include "tools/high_level_ast_lowering.hpp"

high_level_ast_lowering::high_level_ast_lowering() {
    output_ast = std::make_shared<ll_ast_node>(ll_type_program_head);
    expr_instruction_mapping = {
            {expr_add, "add"},
            {expr_sub, "sub"},
            {expr_mult, "mul"},
            {expr_incr_pre, "add"},
            {expr_incr_post, "add"},
            {expr_decr_pre, "sub"},
            {expr_decr_post, "sub"},
            {expr_and_b, "and"},
            {expr_or_b, "or"},
            {expr_not_b, "not"},
            {expr_xor_b, "xor"},
            {expr_eq, "beq"},
            {expr_neq, "bne"},
            {expr_neg, "neg"},
            {expr_lt, "bgt"},
            {expr_gt, "bgt"},
            {expr_lte, "ble"},
            {expr_gte, "ble"},
            {expr_reciprocal, "rec"},
            {expr_itf, "itf"},
            {expr_fti, "fti"},
            {expr_satp, "satp"},
            {expr_satn, "satn"},
            {expr_popcnt, "popcnt"},
            {expr_abs, "abs"},
            {expr_efi, "efi"},
            {expr_bsel, "bsel"},
            {expr_bset, "bset"},
            {expr_nop, "nop"},
            {expr_xor_b, "xor"}
    };
}



void high_level_ast_lowering::translate() {
    for(const auto &i:input_ast->get_content()){
        std::shared_ptr<ll_ast_node> lowered_instr = translate_node(i);
        if(lowered_instr != nullptr){
            output_ast->add_content(lowered_instr);
        }
    }

}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(const std::shared_ptr<hl_ast_node>& input) {
    switch (input->node_type) {
        case hl_ast_node_type_definition:{
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(input);
            std::shared_ptr<variable> dest = node->get_variable();
            return translate_node(node, dest);
        }
        case hl_ast_node_type_operand:
            throw std::runtime_error("standalone operands nodes should not reach the ast lowering stage");
        case hl_ast_node_type_expr:{
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(input);
            if(node->get_type() == expr_assign){
                if(node->get_lhs()->node_type != hl_ast_node_type_operand){
                    throw std::runtime_error("Invalid assignment expression detected  the lowering stage as the LHS is an expression and not a variable");
                }
                if(node->get_rhs()->node_type == hl_ast_node_type_expr){
                    std::shared_ptr<variable> dest = std::static_pointer_cast<hl_ast_operand>(node->get_lhs())->get_variable();
                    return translate_node(std::static_pointer_cast<hl_expression_node>(node->get_rhs()), dest);
                } else if(node->get_rhs()->node_type == hl_ast_node_type_operand){
                    std::shared_ptr<variable> dest = std::static_pointer_cast<hl_ast_operand>(node->get_lhs())->get_variable();
                    return translate_node(std::static_pointer_cast<hl_ast_operand>(node->get_rhs()), dest);
                } else{
                    throw std::runtime_error("Invalid assignment expression detected at the lowering stage as the RHS is neither an expression nor an operand");
                }
            } else if(node->is_immediate()){
                return translate_node(node, nullptr);
            } else{
                throw std::runtime_error("Invalid expression detected at the lowering stage");
            }
        }
        case hl_ast_node_type_program_root:
            throw std::runtime_error("program_root nodes should not reach the ast lowering stage");
        case hl_ast_node_type_loop:
            throw std::runtime_error("loop nodes should not reach the ast lowering stage");
        case hl_ast_node_type_conditional:
            throw std::runtime_error("conditional nodes should not reach the ast lowering stage");
        case hl_ast_node_type_function_call:
            throw std::runtime_error("function call nodes should not reach the ast lowering stage");
        case hl_ast_node_type_function_def:
            throw std::runtime_error("function definition nodes should not reach the ast lowering stage");
        default:
            throw std::runtime_error("unknown type nodes should not reach the ast lowering stage");
    }

}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(const std::shared_ptr<hl_expression_node>& input, const std::shared_ptr<variable>& dest) {
    if(input->is_immediate()){
        return process_immediate_expression(input);
    }else if(input->is_unary()){
        return process_unary_expression(input,dest);
    } else{
        return process_regular_expression(input,dest);
    }
}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(const std::shared_ptr<hl_definition_node>& input, const std::shared_ptr<variable>& dest) {
    if(input->is_initialized()){
        if(input->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
            return translate_node(std::static_pointer_cast<hl_expression_node>(input->get_scalar_initializer()), dest);
        } else if(input->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
            return translate_node(std::static_pointer_cast<hl_ast_operand>(input->get_scalar_initializer()), dest);
        } else{
            throw std::runtime_error("unexpected high level ast node encountered during the lowering phase");
        }
    } else {
        return nullptr;
    }
}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_unary_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest) {

    std::shared_ptr<ll_ast_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]){
        throw std::runtime_error("The required operation is not implementable on the fCore hardware");
    }

    std::shared_ptr<variable> op_b = std::static_pointer_cast<hl_ast_operand>(input->get_rhs())->get_variable();
    std::vector<std::shared_ptr<variable>> args = {op_b, dest};
    retval = create_ast_node(fcore_op_types[opcode], args, opcode);
    return retval;
}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_regular_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest) {

    std::shared_ptr<ll_ast_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]) {
        throw std::runtime_error("The required operation is not implementable on the fCore hardware");
    }

    std::shared_ptr<variable> op_a = std::static_pointer_cast<hl_ast_operand>(input->get_lhs())->get_variable();
    std::shared_ptr<variable> op_b = std::static_pointer_cast<hl_ast_operand>(input->get_rhs())->get_variable();
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
    retval = create_ast_node(fcore_op_types[opcode], args, opcode);
    return retval;

}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::translate_node(const std::shared_ptr<hl_ast_operand>& input, std::shared_ptr<variable> dest) {


    std::shared_ptr<ll_ast_node> retval;
    std::shared_ptr<variable> var;
    if(input->get_type() == var_type_int_const){
        var = std::make_shared<variable>("constant", input->get_int_value());
    } else if (input->get_type() == var_type_float_const){
        var= std::make_shared<variable>("constant",input->get_float_val());
    } else{
        var = input->get_variable();
        std::shared_ptr<variable> op_b = std::make_shared<variable>("r0");
        std::vector<std::shared_ptr<variable>> args = {var, op_b, dest};
        retval = create_ast_node(isa_register_instruction, args, "add");
        return retval;
    }
    std::vector<std::shared_ptr<variable>> args = {std::move(dest), var};
    if(args[0]->get_variable_class()== variable_regular_type){
        if(args[1]->get_const_f() == 0 && args[1]->get_const_i() == 0 && args[1]->is_constant() && !args[0]->is_contiguous()){
            args[0]->set_bound_reg(0);
        }
    }
    retval = create_ast_node(isa_load_constant_instruction, args, "ldc");
    return retval;

}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::create_ast_node(isa_instruction_type t, std::vector<std::shared_ptr<variable>> args, const std::string& op) {
    std::shared_ptr<ll_ast_node> retval;

    switch (t) {
        case isa_register_instruction:
            retval = std::make_shared<ll_register_instr_node>(op, args[0], args[1], args[2]);
            break;
        case isa_conversion_instruction:
            retval = std::make_shared<ll_conversion_instr_node>(op, args[0], args[1]);
            break;
        case isa_load_constant_instruction:
            retval = std::make_shared<ll_load_constant_instr_node>(op, args[0], args[1]);
            break;
        case isa_independent_instruction:
            retval = std::make_shared<ll_independent_inst_node>(op);
            break;
        case isa_pseudo_instruction:
            retval = std::make_shared<ll_pseudo_instr_node>(op, args);
            break;
    }
    return retval;
}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_immediate_expression(std::shared_ptr<hl_expression_node> input) {

    std::shared_ptr<ll_ast_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]){
        throw std::runtime_error("The required operation is not implementable on the fCore hardware");
    }

    retval = create_ast_node(fcore_op_types[opcode], {}, opcode);
    return retval;
}
