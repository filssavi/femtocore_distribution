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

#ifndef FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP

#include <utility>

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "data_structures/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_base.hpp"

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "passes/instruction_stream/variable_mapping.hpp"
#include "passes/instruction_stream/register_allocation.hpp"
#include "passes/instruction_stream/constant_merging.hpp"
#include "passes/instruction_stream/zero_assignment_removal_pass.hpp"
#include "passes/instruction_stream/bound_register_mapping.hpp"
#include "passes/instruction_stream/io_constant_tracking.hpp"
#include "data_structures/common/memory_tracker.hpp"

class stream_pass_manager {
public:
    stream_pass_manager(
            int dal,
            std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
            const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
            );
    stream_pass_manager(
            std::vector<int> &io_res,
            int dal
    );
    void constructs_pass_manager(
            int dal,
            std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
            const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
    );
    instruction_stream process_stream(instruction_stream stream);
    instruction_stream apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass);
    nlohmann::json get_dump();
    void set_enabled_passes(std::vector<bool> ep) {enabled_passes = ep;};
private:
    std::vector<std::shared_ptr<stream_pass_base>> passes;
    std::vector<bool> enabled_passes;
    int dump_ast_level;
    nlohmann::json pre_opt_dump;
    std::vector<nlohmann::json> in_opt_dump;
    nlohmann::json post_opt_dump;
};


#endif //FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
