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

#ifndef FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H
#define FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H

#include <fstream>

#include "data_structures/instruction_stream.hpp"

class assembly_generator {
public:
    explicit assembly_generator(const instruction_stream& stream);
    void set_io_map(const std::unordered_map<uint16_t, uint16_t> &iom){io_map = iom;};
    void write_program(const std::string& filename);
    std::string get_program() {return  program;};
private:
    std::unordered_map<uint16_t, uint16_t> io_map;
    std::string program;
};


#endif //FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H
