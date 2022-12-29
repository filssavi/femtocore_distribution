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

#ifndef FCORE_TOOLCHAIN_FCORE_ISA_HPP
#define FCORE_TOOLCHAIN_FCORE_ISA_HPP

#include "data_structures/high_level_ast/hl_expression_node.hpp"

#include <map>


typedef enum {
    isa_independent_instruction = 2,
    isa_register_instruction = 3,
    isa_pseudo_instruction = 4,
    isa_conversion_instruction = 6,
    isa_load_constant_instruction = 7,
    isa_intercalated_constant= 8
}isa_instruction_type;

constexpr std::string_view isa_instr_type_to_string(isa_instruction_type t){
    switch (t) {
        case isa_register_instruction: return "isa_register_instruction";
        case isa_independent_instruction: return "isa_independent_instruction";
        case isa_pseudo_instruction: return "isa_pseudo_instruction";
        case isa_conversion_instruction: return "isa_conversion_instruction";
        case isa_load_constant_instruction: return "isa_load_constant_instruction";
        case isa_intercalated_constant: return "isa_intercalated_constant";
        default: return "unknown_isa_instr_type";
    }
}

static const int fcore_register_address_width = 6;
static const int fcore_opcode_width = 5;


static std::map <std::string, uint32_t>  fcore_opcodes {
    std::make_pair ("nop", 0u),
    std::make_pair ("add", 1u),
    std::make_pair ("sub", 2u),
    std::make_pair ("mul", 3u),
    std::make_pair ("itf", 4u),
    std::make_pair ("fti", 5u),
    std::make_pair ("ldc", 6u),
    std::make_pair ("bgt", 8u),
    std::make_pair ("ble", 9u),
    std::make_pair ("beq", 10u),
    std::make_pair ("bne", 11u),
    std::make_pair ("stop", 12u),
    std::make_pair ("and", 13u),
    std::make_pair ("or", 14u),
    std::make_pair ("not", 15u),
    std::make_pair ("satp", 16u),
    std::make_pair ("satn", 17u),
    std::make_pair ("rec", 18u),
    std::make_pair ("popcnt", 19u),
    std::make_pair ("abs", 20u),
    std::make_pair ("efi", 21u),
    std::make_pair("bset", 22u),
    std::make_pair("bsel", 25u),
    std::make_pair("xor", 26u)

};

static std::map <uint32_t, std::string>  fcore_opcodes_reverse {
    std::make_pair (fcore_opcodes["nop"], "nop"),
    std::make_pair (fcore_opcodes["add"], "add"),
    std::make_pair (fcore_opcodes["sub"], "sub"),
    std::make_pair (fcore_opcodes["mul"], "mul"),
    std::make_pair (fcore_opcodes["itf"], "itf"),
    std::make_pair (fcore_opcodes["fti"], "fti"),
    std::make_pair (fcore_opcodes["ldc"], "ldc"),
    std::make_pair (fcore_opcodes["bgt"], "bgt"),
    std::make_pair (fcore_opcodes["ble"], "ble"),
    std::make_pair (fcore_opcodes["beq"], "beq"),
    std::make_pair (fcore_opcodes["bne"], "bne"),
    std::make_pair (fcore_opcodes["stop"], "stop"),
    std::make_pair (fcore_opcodes["and"], "and"),
    std::make_pair (fcore_opcodes["or"], "or"),
    std::make_pair (fcore_opcodes["not"], "not"),
    std::make_pair (fcore_opcodes["satp"], "satp"),
    std::make_pair (fcore_opcodes["satn"], "satn"),
    std::make_pair (fcore_opcodes["rec"], "rec"),
    std::make_pair (fcore_opcodes["abs"], "abs"),
    std::make_pair (fcore_opcodes["efi"], "efi"),
    std::make_pair(fcore_opcodes["popcnt"], "popcnt"),
    std::make_pair(fcore_opcodes["bset"], "bset"),
    std::make_pair(fcore_opcodes["bsel"], "bsel"),
    std::make_pair(fcore_opcodes["xor"], "xor")
};

static std::map <std::string, isa_instruction_type>  fcore_op_types {
    std::make_pair ("nop", isa_independent_instruction),
    std::make_pair ("add", isa_register_instruction),
    std::make_pair ("sub", isa_register_instruction),
    std::make_pair ("mul", isa_register_instruction),
    std::make_pair ("itf", isa_conversion_instruction),
    std::make_pair ("fti", isa_conversion_instruction),
    std::make_pair ("ldc", isa_load_constant_instruction),
    std::make_pair ("bgt", isa_register_instruction),
    std::make_pair ("ble", isa_register_instruction),
    std::make_pair ("beq", isa_register_instruction),
    std::make_pair ("bne", isa_register_instruction),
    std::make_pair ("stop", isa_independent_instruction),
    std::make_pair ("and", isa_register_instruction),
    std::make_pair ("or", isa_register_instruction),
    std::make_pair("xor", isa_register_instruction),
    std::make_pair ("not", isa_conversion_instruction),
    std::make_pair ("satp", isa_register_instruction),
    std::make_pair ("satn", isa_register_instruction),
    std::make_pair ("rec", isa_conversion_instruction),
    std::make_pair ("abs", isa_conversion_instruction),
    std::make_pair ("efi", isa_register_instruction),
    std::make_pair("popcnt", isa_conversion_instruction),
    std::make_pair("bset",isa_register_instruction),
    std::make_pair("bsel",isa_register_instruction),
    std::make_pair("mov", isa_pseudo_instruction),
    std::make_pair("neg", isa_pseudo_instruction)
};


static std::map <expression_type_t, bool> fcore_implemented_operations {
    std::make_pair(expr_add, true),
    std::make_pair(expr_sub, true),
    std::make_pair(expr_mult, true),
    std::make_pair(expr_div, false),
    std::make_pair(expr_incr_pre, true),
    std::make_pair(expr_incr_post, true),
    std::make_pair(expr_decr_pre, true),
    std::make_pair(expr_decr_post, true),
    std::make_pair(expr_modulo, false),
    std::make_pair(expr_and_l, false),
    std::make_pair(expr_and_b, true),
    std::make_pair(expr_or_l, false),
    std::make_pair(expr_or_b, true),
    std::make_pair(expr_not_l, false),
    std::make_pair(expr_not_b, true),
    std::make_pair(expr_xor_b, true),
    std::make_pair(expr_lsh, false),
    std::make_pair(expr_rsh, false),
    std::make_pair(expr_eq, true),
    std::make_pair(expr_neq, true),
    std::make_pair(expr_neg, true),
    std::make_pair(expr_lt, true),
    std::make_pair(expr_gt, true),
    std::make_pair(expr_lte, true),
    std::make_pair(expr_gte, true),
    std::make_pair(expr_reciprocal, true),
    std::make_pair(expr_assign, false),
    std::make_pair(expr_call, false),
    std::make_pair(expr_fti, true),
    std::make_pair(expr_itf, true),
    std::make_pair(expr_satp, true),
    std::make_pair(expr_satn, true),
    std::make_pair(expr_popcnt, true),
    std::make_pair(expr_efi, true),
    std::make_pair(expr_abs, true),
    std::make_pair(expr_bset, true),
    std::make_pair(expr_bsel, true),
    std::make_pair(expr_nop, true)
};

static std::map <std::string, std::string>  fcore_pseudo_op {
        std::make_pair("mov", "add"),
        std::make_pair("neg", "sub")
};



#endif //FCORE_TOOLCHAIN_FCORE_ISA_HPP
