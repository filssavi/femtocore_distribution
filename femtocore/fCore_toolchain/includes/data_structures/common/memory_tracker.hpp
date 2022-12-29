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

#ifndef FCORE_TOOLCHAIN_MEMORY_TRACKER_HPP
#define FCORE_TOOLCHAIN_MEMORY_TRACKER_HPP

#include <vector>
#include <memory>

typedef std::pair<uint32_t, uint32_t> memory_range_t;

class memory_tracker {
public:
    explicit memory_tracker(memory_range_t r);
    memory_range_t get_free_memory_range(uint32_t size);
    uint32_t get_free_memory_cell();
    void reserve_register(uint32_t r);

private:
    std::vector<memory_range_t> free_memory;
};



#endif //FCORE_TOOLCHAIN_MEMORY_TRACKER_HPP
