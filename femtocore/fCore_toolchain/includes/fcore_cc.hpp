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

#ifndef FCORE_TOOLCHAIN_FCORE_CC_HPP
#define FCORE_TOOLCHAIN_FCORE_CC_HPP

#include <istream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "backend/binary_generator.hpp"
#include "passes/hl_passes.hpp"
#include "passes/ll_passes.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/low_level/ll_pass_manager.hpp"
#include "tools/high_level_ast_lowering.hpp"
#include "data_structures/instruction_stream.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"



class fcore_cc {
public:
    fcore_cc(std::string &path, std::vector<std::string> &inc, bool print_debug, int dump_lvl);
    void parse(std::unordered_map<std::string, variable_class_t> dma_specs);
    void optimize(std::unordered_map<std::string, std::vector<int>> &dma_map);
    void parse_dma_spec();
    void compile();

    std::vector<uint32_t> get_raw_code();
    std::vector<uint32_t> get_executable();
    std::string get_errors();
    void write_hexfile(const std::string& ouput_file);
    void write_verilog_memfile(const std::string& ouput_file);
    void write_json(const std::string& output_file);
    nlohmann::json get_dump() {return dump;};
    void set_dma_map(nlohmann::json &map){dma_spec = map;};
private:
    std::string input_file;
    std::vector<std::string> includes;
    bool logging;
    int dump_ast_level;
    nlohmann::json dma_spec;
    std::shared_ptr<hl_ast_node> hl_ast;
    std::shared_ptr<ll_ast_node> ll_ast;
    binary_generator writer;
    hl_pass_manager  hl_manager;
    ll_pass_manager ll_manager;
    std::string error_code;
    nlohmann::json dump;

    std::unordered_map<std::string, std::vector<int>> dma_io_map;
    std::unordered_map<std::string, variable_class_t> dma_io_spec;


};



#endif //FCORE_TOOLCHAIN_FCORE_CC_HPP
