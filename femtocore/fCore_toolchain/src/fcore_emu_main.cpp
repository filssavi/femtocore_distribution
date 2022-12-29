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
#include <spdlog/sinks/stdout_color_sinks.h>

#include <CLI/CLI.hpp>
#include "fcore_emu.hpp"
#include "frontend/emulator_manager.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore Emulator"};

    bool output_force = false;
    bool verbose_logging = false;
    std::string input_program;
    std::string inputs_file;
    std::string output_file;
    std::string spec_file;
    app.add_option("input_program", input_program, "Input program path");
    app.add_flag("--log", verbose_logging, "Enable verbose logging.");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    app.add_option("--spec", spec_file , "JSON specification file path")->check(CLI::ExistingFile);
    app.add_option("--inputs_csv", inputs_file, "Path of a csv file containing input vectors for the emulated core")->check(CLI::ExistingFile);
    CLI11_PARSE(app, argc, argv);

    std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("logger", spdlog::color_mode::automatic);


    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            spdlog::critical("The Specified output file already exists, to force the file to be rewritten use the --f flag");
            exit(-1);
        }
    }

    std::ifstream stream;

    if(spec_file.empty()){
        spdlog::critical("The provvided specifications file is empty");
        exit(-1);
    }


    if(verbose_logging){
        spdlog::set_level(spdlog::level::info);
    } else {
        spdlog::set_level(spdlog::level::critical);
    }

    nlohmann::json specs;
    std::ifstream spec_stream(spec_file);
    spec_stream >> specs;

    std::string results;

    emulator_manager emu_manager(specs);
    emu_manager.emulate();
    results = emu_manager.get_results();

    std::ofstream ss(output_file);
    ss<< results;
    ss.close();


    return 0;
}