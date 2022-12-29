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

#ifndef FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "frontend/binary_loader.hpp"
#include "frontend/schema_validators/schema_validators.h"
#include "../third_party/csv.hpp"
#include "backend/emulator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"

typedef struct{
    unsigned int channel;
    unsigned int address;
} register_spec_t;

typedef struct{
    std::string source;
    std::string destination;
    std::vector<std::pair<register_spec_t, register_spec_t>> connections;
}interconnect_t;

typedef struct {
    unsigned int reg_n;
    std::vector<uint32_t> data;
    unsigned int channel;
    std::string name;
}inputs_t;

typedef struct {
    std::vector<inputs_t> input;
    std::vector<emulator_output_t> output_specs;
    std::unordered_map<unsigned int, std::pair<std::string, std::string>> output_types;
    std::unordered_map<unsigned int, uint32_t> memory_init;
    std::shared_ptr<emulator> emu;
    int active_channels;
    std::string efi_implementation;
    std::string comparator_type;
    bool io_remapping_active;
    std::unordered_map<uint16_t, uint16_t> io_map;
    std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outputs;
}emulator_metadata;

typedef  enum {explicit_ordering=1,implicit_ordering=2,no_ordering=0}cores_ordering_t;

class emulator_manager {
public:
    emulator_manager(nlohmann::json &spec_file);
    void emulate();
    std::shared_ptr<std::vector<uint32_t>> get_memory_snapshot(const std::string &core_id, int channel);
    std::string get_results();

private:
    emulator_metadata load_program(nlohmann::json &core);
    std::vector<inputs_t> load_input(nlohmann::json &core);
    std::vector<emulator_output_t> load_output_specs(nlohmann::json &core);
    std::unordered_map<unsigned int, uint32_t> load_memory_init(nlohmann::json &mem_init);
    std::unordered_map<unsigned int, uint32_t> load_memory_init(nlohmann::json &mem_init, std::unordered_map<uint16_t, uint16_t> io_map);
    std::vector<interconnect_t> load_interconnects(nlohmann::json &interconnects);

    void run_cores();

    nlohmann::json get_channel_outputs(std::vector<emulator_output_t> specs, int ch, std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outs);

    static std::vector<float> uint32_to_float(std::vector<uint32_t> &vect);
    std::map<int, std::string> cores_ordering;

    std::unordered_map<std::string, emulator_metadata> emulators;
    std::vector<interconnect_t> interconnects;
    int emu_length;
    cores_ordering_t ordering_style;
    int implicit_order_idx;
    std::unordered_map<std::string, std::string> errors;

};


#endif //FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
