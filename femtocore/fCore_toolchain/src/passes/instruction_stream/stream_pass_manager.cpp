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

#include "passes/instruction_stream/stream_pass_manager.hpp"


stream_pass_manager::stream_pass_manager(int dal,
        std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
        const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
        ) {
    constructs_pass_manager(dal, bm, all_map);
}

stream_pass_manager::stream_pass_manager(std::vector<int> &io_res, int dal) {

    auto bm = std::make_shared<std::unordered_map<std::string, memory_range_t>>();
    auto am = std::make_shared<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>();
    constructs_pass_manager( dal, bm, am);
}


void
stream_pass_manager::constructs_pass_manager(int dal,
                                             std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
                                             const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
                                             ) {

    dump_ast_level = dal;
    std::shared_ptr<variable_map> var_map = std::make_shared<variable_map>();
    auto  io_assignment_map = std::make_shared<std::unordered_map<std::string, std::pair<int, int>>>();
    passes.push_back(std::make_shared<io_constant_tracking>(io_assignment_map));
    passes.push_back(std::make_shared<constant_merging>(io_assignment_map));
    passes.push_back(std::make_shared<variable_mapping>(var_map));
    passes.push_back(std::make_shared<variable_lifetime_mapping>(var_map));
    passes.push_back(std::make_shared<register_allocation>(var_map, bm,all_map));
    passes.push_back(std::make_shared<zero_assignment_removal_pass>());
    passes.push_back(std::make_shared<bound_register_mapping_pass>());
    enabled_passes = {true, true, true, true, true, true, false};

}


instruction_stream stream_pass_manager::process_stream(instruction_stream stream) {
    int pass_n = 0;
    if(dump_ast_level>0) pre_opt_dump = stream.dump();
    instruction_stream ret_val = std::move(stream);
    for(auto &pass:passes){
        if(enabled_passes[pass_n]){
            ret_val = apply_pass(ret_val, pass);
            if(dump_ast_level>1){
                nlohmann::json ast_dump;
                ast_dump["pass_name"] = pass->get_name();
                ast_dump["ast"]= ret_val.dump();
                in_opt_dump.push_back(ast_dump);
            }
        }
        pass_n++;
    }
    if(dump_ast_level>0) post_opt_dump = ret_val.dump();
    return ret_val;
}

instruction_stream
stream_pass_manager::apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass) {
    instruction_stream retval;
    pass->setup();
    for(auto &instr:in_stream){
        auto proc_val = pass->apply_pass(instr);
        if(proc_val!= nullptr)
            retval.push_back(proc_val);
    }
    return retval;
}

nlohmann::json stream_pass_manager::get_dump() {
    nlohmann::json retval;

    retval["pre-opt"] = pre_opt_dump;
    retval["in-opt"] = in_opt_dump;
    retval["post-opt"] = post_opt_dump;

    return retval;
}

