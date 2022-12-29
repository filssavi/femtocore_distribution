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

#ifndef FCORE_TOOLCHAIN_REGISTER_MAP_HPP
#define FCORE_TOOLCHAIN_REGISTER_MAP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "fCore_isa.hpp"

#define N_REGISTERS 2<<fcore_register_address_width

typedef struct{
    int start;
    int end;
} range_t;

class register_map {
public:
    register_map();
    bool is_used(int reg, int from_inst, int to_inst);
    bool is_used(std::pair<int,int> array, int from_inst, int to_inst);
    void insert(std::shared_ptr<variable> var, int reg, int from_inst, int to_inst);
    void insert(std::shared_ptr<variable> var, std::pair<int,int> reg, int from_inst, int to_inst);

    std::shared_ptr<variable> get_identifier(const std::shared_ptr<variable>& var);
    void add_bound_identifier(const std::shared_ptr<variable> & var, int reg);
    bool is_allocated(const std::shared_ptr<variable> &var) {return identifiers_map.contains(var->get_identifier());};
private:
    std::unordered_map<std::string, std::shared_ptr<variable>> identifiers_map;
    std::vector<std::vector<range_t>> reg_map;
};


#endif //FCORE_TOOLCHAIN_REGISTER_MAP_HPP
