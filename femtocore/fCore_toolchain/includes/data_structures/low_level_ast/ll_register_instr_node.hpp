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

#ifndef FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
#define FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H

#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include "data_structures/common/variable.hpp"

class ll_register_instr_node: public ll_instruction_node {
public:
    ll_register_instr_node(std::string op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b, std::shared_ptr<variable> dest);
    uint32_t emit() override;
    std::string disassemble() override;
    void print() override;
    int instruction_count() override;

    nlohmann::json dump();

    friend bool operator==(const ll_register_instr_node& lhs, const ll_register_instr_node& rhs);

    std::shared_ptr<variable> get_operand_a() {return operand_a;};
    std::shared_ptr<variable> get_operand_b() {return operand_b;};
    std::shared_ptr<variable> get_destination() {return destination;};
    std::vector<std::shared_ptr<variable>> get_arguments() override {return {operand_a, operand_b, destination};};
    void set_arguments(const std::vector<std::shared_ptr<variable>> &a) override;
private:
    std::shared_ptr<variable> operand_a;
    std::shared_ptr<variable> operand_b;
    std::shared_ptr<variable> destination;
};


#endif //FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
