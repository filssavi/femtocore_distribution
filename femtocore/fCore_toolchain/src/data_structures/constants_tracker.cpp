//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "data_structures/constants_tracker.h"

#include <utility>



void constants_tracker::add_constant(const std::string &s, std::shared_ptr<hl_ast_operand> op, int instr_idx,
                                     std::vector<int> array_idx) {

    auto idx = stringify_index(array_idx);
    if(constants_map.contains(s)){
        if(constants_map[s].contains(idx)){
            if(constants_map[s][idx].back().validity_range.second ==-1){
                constants_map[s][idx].back().validity_range.second = instr_idx;
            }
        }
    }
    constant c;
    c.value = std::move(op);
    c.validity_range = {instr_idx, -1};
    constants_map[s][idx].push_back(c);
    purge_map[s][idx] = false;
}


bool constants_tracker::is_constant(const std::string &s, int instr_idx, std::vector<int> array_idx) {
    if(!constants_map.contains(s)) return false;
    auto idx = stringify_index(array_idx);
    if(!constants_map[s].contains(idx)) return false;
    for(auto &item:constants_map[s][idx]){
        if(instr_idx>=item.validity_range.first && (instr_idx<item.validity_range.second || item.validity_range.second == -1)) return true;
    }
    return false;
}


std::shared_ptr<hl_ast_operand> constants_tracker::get_constant(const std::string &s, int instr_idx, std::vector<int> array_idx) {
    auto idx = stringify_index(array_idx);
    for(auto &item:constants_map[s][idx]){
        if(instr_idx>=item.validity_range.first && (instr_idx<item.validity_range.second || item.validity_range.second == -1)) {
            purge_map[s][idx] = true;
            return item.value;
        }
    }
    throw std::runtime_error("Error: tracked constant not found");
}

void constants_tracker::clear() {
    constants_map.clear();
}

void constants_tracker::terminate_constant_range(const std::string &s, int instr_idx, std::vector<int> array_idx) {

    if(constants_map.contains(s)){
        auto idx = stringify_index(array_idx);
        if(constants_map[s].contains(idx)){
            constants_map[s][idx].back().validity_range.second = instr_idx;
            return;
        } else{
            throw std::runtime_error("Error: attempted termination of a range belonging to a non constant array member");
        }
    } else{
        throw std::runtime_error("Error: constant whose range need termination not found");
    }

}

void constants_tracker::terminate_all_constant_ranges(const std::string &s, int instr_idx) {

    if(constants_map.contains(s)){
        for(auto&range:constants_map[s]){
            if(range.second.back().validity_range.second == -1){
                range.second.back().validity_range.second = instr_idx;
            }
        }
    }
    throw std::runtime_error("Error: constant whose range need termination not found");
}


bool constants_tracker::needs_purging(const std::string &s, std::vector<int> array_idx) {
    return purge_map[s][stringify_index(array_idx)];
}


std::string constants_tracker::stringify_index(const std::vector<int>& v) {
    std::string ret;
    for(auto &item:v){
        ret += std::to_string(item);
    }

    return ret;
}
