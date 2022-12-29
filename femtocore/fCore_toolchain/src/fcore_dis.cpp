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

#include "fcore_dis.hpp"

fcore_dis::fcore_dis(std::istream &input, bin_loader_input_type_t in_type) {
    error_code = "";
    try{

        binary_loader dis(input, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();
        instruction_stream program_stream = instruction_stream_builder::build_stream(ast);
        std::vector<int> io_res;

        stream_pass_manager sman(io_res,0);
        program_stream = sman.process_stream(program_stream);
        gen = std::make_unique<assembly_generator>(program_stream);
        gen->set_io_map(dis.get_io_mapping());
    } catch(std::runtime_error &e){
        error_code = e.what();
    }
}

std::string fcore_dis::get_errors() {
    return error_code;
}

void fcore_dis::write_json(const std::string &output_file) {
    nlohmann::json j;
    j["error_code"] = error_code;
    if(error_code.empty()){
        j["disassembled_program"] = gen->get_program();
    } else{
        j["disassembled_program"] = "";
    }
    std::string str = j.dump();
    std::ofstream ss(output_file);
    ss<<str;
    ss.close();
}

std::string fcore_dis::get_disassenbled_program() {
    return gen->get_program();
}

void fcore_dis::write_disassembled_program(const std::string &output_file) {
    gen->write_program(output_file);
}


