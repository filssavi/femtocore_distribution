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

#include "data_structures/low_level_ast/ll_conversion_instr_node.hpp"


ll_conversion_instr_node::ll_conversion_instr_node(std::string op, std::shared_ptr<variable> s, std::shared_ptr<variable> d) : ll_instruction_node(isa_conversion_instruction){
    source = std::move(s);
    destination = std::move(d);
    opcode = std::move(op);
}

uint32_t ll_conversion_instr_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    raw_instr += (source->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (destination->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    return raw_instr;
}

void ll_conversion_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " SOURCE: " << source->to_str() << " DESTINATION: " << destination->to_str()<<std::endl;
}

int ll_conversion_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_conversion_instr_node &lhs, const ll_conversion_instr_node &rhs) {
    bool retval = true;

    retval &= *lhs.source == *rhs.source;
    retval &= *lhs.destination == *rhs.destination;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}

void ll_conversion_instr_node::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
    source = a[0];
    destination = a[1];
}

std::string ll_conversion_instr_node::disassemble() {
    return opcode + " " + source->get_name() + ", " + destination->get_name();
}

nlohmann::json ll_conversion_instr_node::dump() {
    nlohmann::json retval = ll_instruction_node::dump();
    retval["source"] = source->dump();
    retval["destination"] = destination->dump();
    return retval;
}
