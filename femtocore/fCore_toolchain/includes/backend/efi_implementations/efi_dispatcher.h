// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//


#ifndef FCORE_TOOLCHAIN_EFI_DISPATCHER_H
#define FCORE_TOOLCHAIN_EFI_DISPATCHER_H

#include <string>
#include <memory>
#include <cmath>
#include <utility>
#include <vector>
#include <cstring>


class cell {
public:
    cell(double v, int s, bool o) {
        voltage = v;
        idx = s;
        order = o;
    };
    bool operator <(const cell &b) const {
        if(order)
            return voltage > b.voltage;
        else
            return b.voltage > voltage;
    };
    double voltage;
    float idx;  // Does not participate in comparisons
    bool order;
};

class efi_dispatcher {

public:
    explicit efi_dispatcher(const std::string &core);
    void emulate_efi(const std::string& function, uint32_t op_a, uint32_t op_b, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m);
private:
    void efi_sort(uint32_t op_a, uint32_t op_b, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m);
    static uint32_t float_to_uint32(float f);
    static float uint32_to_float(uint32_t u);
    void efi_trig(uint32_t op_a, uint32_t op_b, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m);
    std::string core_name;
};


#endif //FCORE_TOOLCHAIN_EFI_DISPATCHER_H
