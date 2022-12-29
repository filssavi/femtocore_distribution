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

#ifndef FCORE_TOOLCHAIN_EMULATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_H

#include <utility>
#include <spdlog/spdlog.h>

#include "efi_implementations/efi_dispatcher.h"
#include "data_structures/instruction_stream.hpp"
#include "floating_point_v7_1_bitacc_cmodel.h"
#include "fCore_isa.hpp"


typedef enum {
    type_uint32 = 1,
    type_float = 2,
} emulator_types_t;

typedef struct {
    int reg_n;
    emulator_types_t type;
    std::string name;
} emulator_output_t;

class emulator {
public:
    emulator(instruction_stream &s, int n_channels, const std::string &core);

    void init_memory(std::unordered_map<unsigned int, uint32_t> &mem_init);
    void apply_inputs(uint32_t addr, uint32_t data, unsigned int channel);
    uint32_t get_output(uint32_t addr, int channel);

    void set_comparator_type(std::string &t){comparator_type = t;};
    void run_round(int channel);
    void set_efi_selector(std::string sel){ efi_selector = std::move(sel);};
    std::shared_ptr<std::vector<uint32_t>> get_memory(int channel) { return memory_pool[channel];};
    std::unordered_map<int, std::shared_ptr<std::vector<uint32_t>>> get_memory_pool() { return memory_pool;};

    std::string get_name() {return core_name;};

    static uint32_t float_to_uint32(float f);
    static float uint32_to_float(uint32_t u);
private:
    void run_instruction_by_type(const std::shared_ptr<ll_instruction_node>& node);

    void run_register_instruction(const std::shared_ptr<ll_register_instr_node>& node);
    void run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node);
    void run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node);
    void run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node);

    uint32_t execute_add(uint32_t a, uint32_t b);
    uint32_t execute_sub(uint32_t a, uint32_t b);
    uint32_t execute_mul(uint32_t a, uint32_t b);
    uint32_t execute_rec(uint32_t a);
    uint32_t execute_fti(uint32_t a);
    uint32_t execute_itf(uint32_t a);
    static uint32_t execute_not(uint32_t a);
    static uint32_t execute_and(uint32_t a, uint32_t b);
    uint32_t execute_abs(uint32_t a);
    uint32_t execute_popcnt(uint32_t a);
    uint32_t execute_satp(uint32_t a, uint32_t b);
    uint32_t execute_satn(uint32_t a, uint32_t b);
    uint32_t execute_bset(uint32_t a, uint32_t b, uint32_t c);
    uint32_t execute_bsel(uint32_t a, uint32_t b);
    static uint32_t execute_or(uint32_t a, uint32_t b);
    static uint32_t execute_xor(uint32_t a, uint32_t b);
    uint32_t execute_compare_gt(uint32_t a, uint32_t b);
    uint32_t execute_compare_le(uint32_t a, uint32_t b);
    uint32_t execute_compare_eq(uint32_t a, uint32_t b);
    uint32_t execute_compare_ne(uint32_t a, uint32_t b);
    void execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest);
    xip_fpo_t xil_a, xil_b, xil_res;
    xip_fpo_fix_t xil_a_fixed_point;
    instruction_stream stream;

    bool stop_requested;

    std::string efi_selector;
    efi_dispatcher efi_implementation;
    std::string comparator_type;

    std::string core_name;

    std::shared_ptr<std::vector<uint32_t>> working_memory;
    std::unordered_map<int, std::shared_ptr<std::vector<uint32_t>>> memory_pool;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_H
