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

#include "backend/assembly_generator.hpp"

assembly_generator::assembly_generator(const instruction_stream &stream) {
    std::ostringstream disassembled_program;

    for(const auto& item:stream){
        disassembled_program << item->disassemble() << std::endl;
    }
    program = disassembled_program.str();
}

void assembly_generator::write_program(const std::string &filename) {
    std::ofstream output(filename);

    if(!io_map.empty()){
        output<<"///////////////////////////////////////////"<<std::endl;
        output<<"//               IO MAPPING              //"<<std::endl;
        output<<"//    io address <---> core address      //"<<std::endl;
        output<<"///////////////////////////////////////////"<<std::endl;
        for(auto &pair:io_map){
            output<<"//    " << pair.first <<"  <--->  "<< pair.second<<"      //"<<std::endl;
        }
        output<<"///////////////////////////////////////////"<<std::endl;
    }

    for(auto &instr:program){
        output << instr;
    }
}
