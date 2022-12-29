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

#ifndef FCORE_TOOLCHAIN_LL_CONVERSION_INSTR_NODE_HPP
#define FCORE_TOOLCHAIN_LL_CONVERSION_INSTR_NODE_HPP

#include <utility>

#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include <utility>

class ll_conversion_instr_node: public ll_instruction_node {
public:
    ll_conversion_instr_node(std::string op, std::shared_ptr<variable> s, std::shared_ptr<variable> d);
    uint32_t emit() override;
    void print() override;
    std::string disassemble() override;
    int instruction_count() override;

    std::shared_ptr<variable> get_source() {return source;};
    std::shared_ptr<variable> get_destination() {return destination;};
    std::vector<std::shared_ptr<variable>> get_arguments() override {return {source, destination};};
    void set_arguments(const std::vector<std::shared_ptr<variable>> &a) override;

    nlohmann::json dump() override;
    friend bool operator==(const ll_conversion_instr_node& lhs, const ll_conversion_instr_node& rhs);
private:
    std::shared_ptr<variable> source;
    std::shared_ptr<variable> destination;
};


#endif //FCORE_TOOLCHAIN_LL_CONVERSION_INSTR_NODE_HPP
