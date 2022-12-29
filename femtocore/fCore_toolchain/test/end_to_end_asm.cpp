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
#include <gtest/gtest.h>
#include <filesystem>

#include "fcore_has.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"


static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST( EndToEndAsm, simple_file ) {
    std::string input_file = "asm/test_add.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};
    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    std::vector<uint32_t> gold_standard = {0x20002, 0x60000, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2b01, 0xc};

    // file parsing and processing

    std::vector<uint32_t> result = uut.get_executable();
    ASSERT_EQ(result, gold_standard);

    //verilog memfile generationc
    uut.write_verilog_memfile(input_file+".mem");

    std::ifstream infile(input_file+".mem");
    std::string a;
    result.clear();
    while (infile >> a)
    {
        result.push_back(std::stoi(a, nullptr, 16));
    }
    ASSERT_EQ(result, gold_standard);

    // hex file generation

    uut.write_hexfile(input_file+".hex");

    std::string filename = input_file+".hex";
    FILE *fptr = fopen(filename.c_str(),"rb");

    uint32_t program_size = uut.get_program_size();
    uint32_t res[1000];
    ssize_t ret = fread(res,sizeof(uint32_t), program_size, fptr);
    if(ret ==0){
        std::cout << "OH SNAP! this should not have happened";
        exit(1);
    }
    result.clear();
    for(int i = 0; i < program_size; i++){
        result.push_back(Reverse32(res[i]));
    }
    ASSERT_EQ(result, gold_standard);//result == gold_standard);


}

TEST( EndToEndAsm, for_file ) {
    std::string input_file = "asm/test_for.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x20002, 0x100000, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2881, 0x86, 0x42c80000, 0xc2881, 0x0000, 0x0000, 0x86, 0x42c80000, 0xc2881, 0x0000, 0x0000, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST( EndToEndAsm, branch_file ) {
    std::string input_file = "asm/test_branch.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x20002, 0x90000, 0x86, 0x42c80000, 0xc2881, 0x80061, 0x21848, 0x21849, 0x2184a, 0x2184b, 0xC};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, variables_file) {
    std::string input_file = "asm/test_variables.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    std::vector<uint32_t> result = uut.get_executable();
    std::vector<uint32_t> gold_standard = {0x20002, 0xe0000,0x26,0x42c80000, 0x46, 0x43480000, 0xA6, 0x43480000, 0xc2881, 0xe4821,0xe4841,0x26,0x42c80000,0xe4821, 0x50b2, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, load_constant_file) {
    std::string input_file = "asm/test_ldc.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x20002, 0x70000, 0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, embeddable_wrapper_pass) {
    std::string input_file = "asm/test_ldc.s";
    int hex_size;
    auto *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));

    fCore_has_embeddable_f(input_file.c_str(),hex_result, &hex_size, false);

    std::vector<uint32_t> result;
    for(int i = 0; i<hex_size;i++){
        result.push_back(hex_result[i]);
    }
    free(hex_result);
    std::vector<uint32_t> gold_standard = {0x20002, 0x70000, 0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}


TEST(EndToEndAsm, load_integer_constant) {
    std::string input_file = "asm/test_ldc_int.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, true);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x20002, 0x30000,0x86, 0x64, 0xc};
    ASSERT_EQ( result, gold_standard);
}


TEST(EndToEndAsm, json_writing) {
    std::string input_file = "asm/test_ldc.s";

    std::string test_json = "/tmp/e2e_asm_json_test.json";
    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir, 0, false);

    uut.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x20002, 0x70000, 0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}