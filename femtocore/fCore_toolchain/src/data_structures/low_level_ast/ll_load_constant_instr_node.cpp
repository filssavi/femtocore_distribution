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

#include "data_structures/low_level_ast/ll_load_constant_instr_node.hpp"



ll_load_constant_instr_node::ll_load_constant_instr_node(std::string op, std::shared_ptr<variable> dest, std::shared_ptr<variable> c)
: ll_instruction_node(isa_load_constant_instruction){
    destination = std::move(dest);
    constant = std::move(c);
    opcode = std::move(op);
}

uint32_t ll_load_constant_instr_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    raw_instr += (destination->get_value() & register_mask) << fcore_opcode_width;
    return raw_instr;
}

void ll_load_constant_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " DESTINATION: " << destination->to_str() << " CONSTANT(NEXT INSTRUCTION): " << constant->to_str()<<std::endl;
}

int ll_load_constant_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_load_constant_instr_node &lhs, const ll_load_constant_instr_node &rhs) {
    bool retval = true;

    retval &= *lhs.constant == *rhs.constant;
    retval &= *lhs.destination == *rhs.destination;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}

float ll_load_constant_instr_node::get_constant_f() {
    return constant->get_const_f();
}

void ll_load_constant_instr_node::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
    destination = a[0];
    constant = a[1];
}

int ll_load_constant_instr_node::get_constant_i() {
    return constant->get_const_i();
}

std::string ll_load_constant_instr_node::disassemble() {
    return opcode + " " + destination->get_name() + ", " + std::to_string(constant->get_const_f());
}

nlohmann::json ll_load_constant_instr_node::dump() {
    nlohmann::json retval = ll_instruction_node::dump();
    retval["destination"] = destination->dump();
    retval["constant"] = constant->dump();
    return retval;
}

bool ll_load_constant_instr_node::is_float() {
    return constant->is_float();
}
