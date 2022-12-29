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

#include <string>
#include <vector>
#include "frontend/schema_validators/schema_validators.h"
#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include "fcore_cc.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore C compiler"};

    std::string input_file;
    app.add_option("input_file", input_file, "Input spec file")->required()->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    std::ifstream ifs(input_file);
    nlohmann::json spec = nlohmann::json::parse(ifs);
    try{
        compiler_schema_validator validator;
        validator.validate(spec);
    } catch(std::invalid_argument &ex){
        exit(-1);
    }


    bool output_hex = spec["output"]["format"] == "hex";
    bool output_mem = spec["output"]["format"] == "mem";
    bool output_json = spec["output"]["format"] == "json";
    bool output_force = spec["force"];

    std::string output_file = spec["output"]["file"];
    int dump_ast_level = 0;

    if(spec.contains("dump_ast")){
        dump_ast_level = spec["dump_ast"];
    }

    input_file = spec["input_file"];

    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            spdlog::critical("The Specified output file already exists, to force the file to be rewritten use the --f flag");
            exit(-1);
        }
    }

    std::vector<std::string> include_files = {""};
    fcore_cc cc_engine(input_file, include_files, false, dump_ast_level);

    if(spec.contains("dma_io")){
        cc_engine.set_dma_map(spec["dma_io"]);
    }
    cc_engine.compile();

    if(output_hex){
        cc_engine.write_hexfile(output_file);
    }

    if(output_mem){
        cc_engine.write_verilog_memfile(output_file);
    }

    if(output_json){
        cc_engine.write_json(output_file);
    }

    if(dump_ast_level>0){
        std::string str = cc_engine.get_dump().dump();
        std::ofstream ss(output_file+"_dump.json");
        ss<<str;
        ss.close();
    }

    if(!cc_engine.get_errors().empty()){
        spdlog::critical(cc_engine.get_errors());
    }

    return 0;
}

