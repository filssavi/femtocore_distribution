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

#include "data_structures/low_level_ast/ll_independent_instr_node.hpp"




ll_independent_inst_node::ll_independent_inst_node(std::string op) : ll_instruction_node(isa_independent_instruction) {
    opcode = std::move(op);
}


uint32_t ll_independent_inst_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    return raw_instr;
}

void ll_independent_inst_node::print() {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << emit() << " -> OPCODE: " << opcode << std::endl;
}

int ll_independent_inst_node::instruction_count() {
    return 1;
}

bool operator==(const ll_independent_inst_node &lhs, const ll_independent_inst_node &rhs) {
    return rhs.opcode == lhs.opcode;
}

std::string ll_independent_inst_node::disassemble() {
    return opcode;
}

nlohmann::json ll_independent_inst_node::dump() {
    nlohmann::json retval = ll_instruction_node::dump();
    return retval;
}
