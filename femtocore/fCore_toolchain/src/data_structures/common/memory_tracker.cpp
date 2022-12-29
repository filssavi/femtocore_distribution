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

#include "data_structures/common/memory_tracker.hpp"
memory_tracker::memory_tracker(const std::pair<uint32_t, uint32_t> r){
    free_memory.push_back(r);
}

memory_range_t memory_tracker::get_free_memory_range(uint32_t size){

    for(auto & i : free_memory){
        if(i.second-i.first>=size){
            memory_range_t ret = {i.first, i.first+size};
            i = {i.first+size, i.second};
            return ret;
        }
    }

    throw std::runtime_error("No free memory range of size "+ std::to_string(size) + " found, manual memory management needed.");

};

uint32_t memory_tracker::get_free_memory_cell(){
    memory_range_t r = get_free_memory_range(1);
    return r.first;
}

void memory_tracker::reserve_register(uint32_t r) {
    for(int i = 0;i<free_memory.size();i++){
        if(r>=free_memory[i].first && r<free_memory[i].second){

            if(r==free_memory[i].first){
                free_memory[i] = {free_memory[i].first+1, free_memory[i].second};
            } else if(r==free_memory[i].second){
                free_memory[i] = {free_memory[i].first, free_memory[i].second-1};
            } else{
                uint32_t second_range_end = free_memory[i].second;
                free_memory[i] = {free_memory[i].first, r-1};
                free_memory.insert(free_memory.begin()+i+1,{r+1, second_range_end});
            }
        }
    }
};