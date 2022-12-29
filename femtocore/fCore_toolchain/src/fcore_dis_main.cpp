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

#include <iostream>
#include <string>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>

#include "fcore_dis.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore disassembler"};

    bool input_hex = false;
    bool input_mem = false;
    bool output_json = false;
    bool output_force = false;;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", input_mem, "the input is a verilog mem file");
    app.add_flag("--hex", input_hex, "the input is a binary file");
    app.add_flag("--json", output_json, "produce a json file for output");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    CLI11_PARSE(app, argc, argv);

    if(!input_hex && !input_mem){
        spdlog::critical("The input file type should be specified (use either the --mem or --hex flags)");
        exit(-1);
    } else if (input_hex && input_mem){
        spdlog::critical("Both input file type specifiers are present on the command line, only one should be used");
        exit(-1);
    }

    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            spdlog::critical("The Specified output file already exists, to force the file to be rewritten use the --f flag");
            exit(-1);
        }
    }

    std::ifstream stream;


    bin_loader_input_type_t in_type;
    if(input_mem) {
        stream.open(input_file);
        in_type = bin_loader_mem_input;
    } else {
        stream.open(input_file, std::ifstream::binary);
        in_type = bin_loader_hex_input;
    }

    fcore_dis dis_engine(stream, in_type);
    if(output_json){
        dis_engine.write_json(output_file);
    } else {
        dis_engine.write_disassembled_program(output_file);
    }

    return 0;
}

