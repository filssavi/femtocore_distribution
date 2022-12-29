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

#ifndef FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP


#include "hl_ast_operand.hpp"
#include "hl_ast_node.hpp"
#include "hl_function_call_node.hpp"

#include <iostream>
#include <sstream>

typedef enum {
    expr_add = 0,
    expr_sub = 1,
    expr_mult = 2,
    expr_div = 3,
    expr_incr_pre= 4,
    expr_incr_post= 5,
    expr_decr_pre= 6,
    expr_decr_post= 7,
    expr_modulo =8,
    expr_and_l = 9,
    expr_and_b = 10,
    expr_or_l = 11,
    expr_or_b = 12,
    expr_not_l = 13,
    expr_not_b = 14,
    expr_xor_b = 15,
    expr_lsh = 16,
    expr_rsh = 17,
    expr_eq = 18,
    expr_neq = 19,
    expr_neg = 20,
    expr_lt = 21,
    expr_gt = 22,
    expr_lte = 23,
    expr_gte = 24,
    expr_assign = 25,
    expr_call = 26,
    expr_reciprocal = 27,
    expr_itf = 28,
    expr_fti = 29,
    expr_satp = 30,
    expr_satn = 31,
    expr_abs = 32,
    expr_popcnt = 33,
    expr_efi = 34,
    expr_bset = 35,
    expr_bsel = 37,
    expr_nop = 38
} expression_type_t;

constexpr std::string_view expression_type_to_string(expression_type_t in){
    switch(in){
        case expr_add: return "expr_add";
        case expr_sub: return "expr_sub";
        case expr_mult: return "expr_mult";
        case expr_div: return "expr_div";
        case expr_incr_pre: return "expr_incr_pre";
        case expr_incr_post: return "expr_incr_post";
        case expr_decr_pre: return "expr_decr_pre";
        case expr_decr_post: return "expr_decr_post";
        case expr_modulo: return "expr_modulo";
        case expr_and_l: return "expr_and_l";
        case expr_and_b: return "expr_and_b";
        case expr_or_l: return "expr_or_l";
        case expr_or_b: return "expr_or_b";
        case expr_not_l: return "expr_not_l";
        case expr_not_b: return "expr_not_b";
        case expr_xor_b: return "expr_xor_b";
        case expr_lsh: return "expr_lsh";
        case expr_rsh: return "expr_rsh";
        case expr_eq: return "expr_eq";
        case expr_neq: return "expr_neq";
        case expr_neg: return "expr_neg";
        case expr_lt: return "expr_lt";
        case expr_gt: return "expr_gt";
        case expr_lte: return "expr_lte";
        case expr_gte: return "expr_gte";
        case expr_assign: return "expr_assign";
        case expr_call: return "expr_call";
        case expr_reciprocal: return "expr_reciprocal";
        case expr_itf: return "expr_itf";
        case expr_fti: return "expr_fti";
        case expr_satp: return "expr_satp";
        case expr_satn: return "expr_satn";
        case expr_abs: return "expr_abs";
        case expr_efi: return "expr_efi";
        case expr_popcnt: return "expr_popcnt";
        case expr_bset: return "expr_bset";
        case expr_bsel: return "expr_bsel";
        case expr_nop: return "expr_nop";
        default: return "unknown expression type";
    }
}


typedef enum {
   regular_assignment = 0,
   addition_assignment = 1,
   subtraction_assignment = 2,
   multiplication_assignment = 3,
   division_assignment = 4,
   modulo_assignment = 5,
   and_assignment = 6,
   or_assignment = 7,
   xor_assignment = 8,
   lsh_assignment = 9,
   rsh_assignment = 10,
} assignment_type_t;

constexpr std::string_view assignment_type_to_string(assignment_type_t in){
    switch(in){
        case regular_assignment: return "regular_assignment";
        case addition_assignment: return "addition_assignment";
        case subtraction_assignment: return "subtraction_assignment";
        case multiplication_assignment: return "multiplication_assignment";
        case division_assignment: return "division_assignment";
        case modulo_assignment: return "modulo_assignment";
        case and_assignment: return "and_assignment";
        case or_assignment: return "or_assignment";
        case xor_assignment: return "xor_assignment";
        case lsh_assignment: return "lsh_assignment";
        case rsh_assignment: return "rsh_assignment";
        default: return "unknown assignment type";
    }
}

class hl_expression_node : public hl_ast_node{
public:
    hl_expression_node( expression_type_t et);
    void set_lhs(const std::shared_ptr<hl_ast_node> &node);
    void set_rhs(const std::shared_ptr<hl_ast_node> &node);
    std::shared_ptr<hl_ast_node> get_lhs();
    std::shared_ptr<hl_ast_node> get_rhs();

    void set_assignment_type(assignment_type_t a) { assignment_type = a;};
    assignment_type_t get_assignment_type() {return assignment_type;};

    expression_type_t get_type();
    std::string pretty_print() override;
    bool is_unary();
    bool is_immediate();
    static bool is_hardware_compatible(expression_type_t et);
    nlohmann::json dump() override;

    bool is_terminal() override {
        return true;
    }
    friend bool operator==(const hl_expression_node& lhs, const hl_expression_node& rhs);

private:
    expression_type_t expr_type;
    assignment_type_t assignment_type;
    std::shared_ptr<hl_ast_node> lhs;
    std::shared_ptr<hl_ast_node> rhs;
    std::map<expression_type_t, std::string> type_print;
    std::map<assignment_type_t, std::string> assign_prefix_print;
};

#endif //FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
