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

#include <fstream>

#include <gtest/gtest.h>
#include "fcore_cc.hpp"
#include "data_structures/instruction_stream.hpp"


TEST(EndToEndC, fcore_cc) {

    std::string input_file = "c_e2e/test_normalization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x20003,0x30001, 0x1000a, 0x26, 1104150528, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, end_to_end_intrinsics) {


    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x20003,0x70001,0x1000A,0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, exceptionHandling) {
    std::string input_file = "c_e2e/test_exception.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":59},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::string result = compiler.get_errors();

    ASSERT_EQ(result, "Strings are not supported by the fCore toolchain");
}

TEST(EndToEndC, json_writing) {
    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::string test_json = "/tmp/e2e_c_json_test.json";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x20003,0x70001,0x1000A,0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}

TEST(EndToEndC, iom) {
    std::string input_file = "c_e2e/test_pragma_io.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "memory","address":1},
                    "b":{"type": "input","address":2},
                    "c":{"type": "memory","address":4},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x80004, 0x3e0001, 0x10002,0x3f0004,0x3000A, 0x7e0fc1, 0x26, 0x40A00000, 0x40fe3, 0x26, 0x3e2aaaab, 0x60843, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, conditional) {
    std::string input_file = "c_e2e/test_full_conditional.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test":{"type": "output","address":7}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x30001,0x10007, 0x26, 0x40C00000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, loop) {
    std::string input_file = "c_e2e/test_full_loop.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":[1,2,3,4]},
                    "k":{"type": "input","address":[5,6,7,8]},
                    "b":{"type": "output","address":[9,10,11,12]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x30006,0x30003,0x10004,0x20007,0x40008, 0x5000B, 0x2000c, 0xa1061, 0x42021, 0xc};

   ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, nested_loop) {
    std::string input_file = "c_e2e/test_full_nested_loop.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":[1,2,3,4]},
                    "a":{"type": "input","address":[5,6,7,8]},
                    "c":{"type": "output","address":[9,10,11,12]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0x50006, 0x30003, 0x10004, 0x20005, 0x40006, 0x5000B, 0x3000c, 0xa1061, 0xa2061, 0x61021, 0x62021, 0xc};

     ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization) {
    std::string input_file = "c_e2e/test_array_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":7}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x50001,0x20007,0x26, 0x41300000, 0x61023, 0x21063, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, array_initialization_through_function) {
    std::string input_file = "c_e2e/test_array_initialization_through_function.c";

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x30001,0x10012,0x26, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, constant_argument_inlining) {
    std::string input_file = "c_e2e/test_constant_argument_inlining.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x30001,0x10012,0x26, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_io_definition) {
    std::string input_file = "c_e2e/test_array_io_definition.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "b":{"type": "output","address":3},
                    "c":{"type": "output","address":[8,9]},
                    "d":{"type": "memory","address":[10,11]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x60007,0x30003,0x10004,0x20007,0x40008,0x50009,0x3e000A,0x3f000B,
                                           0x61021, 0x81021, 0xa1022, 0x7c1023, 0x7e1823, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, multidimensional_array_io_definition) {
    std::string input_file = "c_e2e/test_multidim_array_io_definition.c";

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "c":{"type": "output","address":[8,9,10,11]},
                    "d":{"type": "memory","address":[12,13,16,18]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xA000A,0x10004, 0x20007, 0x40008, 0x60009, 0x5000A, 0x7000B,
                                           0x3d000C, 0x3E000D, 0x3c0010,0x3f0012,0x61021, 0x81021, 0xa1022,
                                           0xc1021, 0xe1022, 0x7a1023, 0x781823, 0x7c1023, 0x7e1823, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, iom_initialization){
    std::string input_file = "c_e2e/test_iom_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":[8,9,10,11]},
                    "b":{"type": "output","address":20}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xb0005, 0x10008, 0x20009, 0x3000A, 0x4000B, 0x50014, 0x26,0x3F800000,0x46, 0x40000000, 0x66, 0x40400000, 0x86, 0x40800000, 0xa6, 0x40800000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, test_move){
    std::string input_file = "c_e2e/test_move.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x20002,0x10001,0x2000a, 0x40021, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, test_complex_normalization){
    std::string input_file = "c_e2e/test_complex_normalization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "b":{"type": "input","address":2},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x90003,0x20001,0x10002,0x3f000a,0x66, 0x40A00000, 0x81821, 0x26, 0x41880000, 0x60843, 0x22063, 0x7e0fe1, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, register_allocation){
    std::string input_file = "c_e2e/test_register_allocation.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x40002,0x10001,0x3f000a,0x46, 0x41880000, 0x7e1023, 0xc};

    ASSERT_EQ(gold_standard, result);
}



TEST(EndToEndC, functionInliningExpression) {

    std::string input_file = "c_e2e/test_function_inline_expression.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "integ":{"type": "memory","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xF0002, 0x3f0006, 0x10019,0x46, 0x40A00000, 0x61023, 0x26, 0x3727C5AC, 0x41823, 0x217e1, 0x46, 0xC3160000, 0x21031, 0x46, 0x43160000, 0x21030, 0x40021, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, essential_variable_initialization) {

    std::string input_file = "c_e2e/test_essential_variable_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "test_out":{"type": "output","address":5},
                    "test_var":{"type": "output","address":7},
                    "factor_1":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();

    //TODO:test var viene caricato due volte
    std::vector<uint32_t> gold_standard = {0x20003,0x80004,0x10005,0x30006,0x50007,0x10019,0x46, 0x3F800000,
                                           0x60849,0x86, 0x3F800000, 0xa0881, 0x200a1, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, test_constant_propagation) {

    std::string input_file = "c_e2e/test_constant_propagation.c";
    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":5},
                    "switching_cell":{"type": "memory","address":[17,18]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x50003, 0x10005, 0x3e0011,0x3f0012,
                                           0x7a6,0x3F800000, 0x7c0fa1, 0x7e0fa1, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, negative_leading_sum) {

    std::string input_file = "c_e2e/test_negative_leading_sum.c";

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":2},
                    "b":{"type": "input","address":3},
                    "c":{"type": "output","address":7}
                }})"
            );
    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x30003,0x20002,0x10003,0x20007,0x61002, 0x40863, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, function_vars_mangling) {

    std::string input_file = "c_e2e/test_function_vars_mangling.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "b":{"type": "input","address":2},
                    "a":{"type": "input","address":1},
                    "c":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = { 0x20003,0x90003,0x20001,0x10002,0x3000A, 0x66, 4, 0x81823, 0x26, 2, 0x60843, 0x21881, 0x61021, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, constant_merging) {

    std::string input_file = "c_e2e/test_constant_merging.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[10,11]},
                    "b":{"type": "output","address":[12,13]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x50004,0x1000A, 0x2000B,0x4000C, 0x3000D,  0x66, 0x42340000,  0x81823, 0x60843, 0xc};

    ASSERT_EQ(gold_standard, result);

}



TEST(EndToEndC, zero_assignment_removal) {

    std::string input_file = "c_e2e/test_zero_assignment_removal.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":10},
                    "b":{"type": "output","address":12}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x20002,0x1000a,0x2000c,0x40021, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, loop_index_expression) {

    std::string input_file = "c_e2e/test_loop_index_expression.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x70004,0x20032,0x10033, 0x3003C, 0x5003d, 0x66, 0, 0x86, 0x0, 0xa1081, 0xa08a1, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, loop_index_expression_multidim) {

    std::string input_file = "c_e2e/test_loop_index_expression_multidim.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x70004,0x10031,0x20035, 0x3003c, 0x5003d, 0x66, 0, 0x86, 0x0, 0xa0881, 0xa10a1, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, contiguos_array_allocation) {

    std::string input_file = "c_e2e/test_contiguous_array_allocation.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "input","address":2},
                    "out_1":{"type": "output","address":7},
                    "out_2":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x60003, 0x10002, 0x30006, 0x20007, 0x85855,0x40881, 0x26,0x2,0x608a1,0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, efi_load_elimination) {

    std::string input_file = "c_e2e/test_efi_load_elimination.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "theta":{"type": "input","address":1},
                    "s_th":{"type": "output","address":15},
                    "c_th":{"type": "output","address":17}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xb0003, 0x10001, 0x1000f, 0x20011, 0x60021,  0x46, 0x0, 0x21055, 0x46,0x38000074,0x20843, 0x46, 0x1, 0x41055,0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, efi_load_elimination_in_func) {

    std::string input_file = "c_e2e/test_efi_load_elimination_in_func.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "theta":{"type": "input","address":1},
                    "s_th":{"type": "output","address":15},
                    "c_th":{"type": "output","address":17}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xF0003, 0x10001, 0x2000f, 0x30011, 0x46, 0x0, 0x60021, 0x81055,
                                           0x2084, 0x46,0x38000074, 0x82043, 0x40081, 0x66,1,0x80021,0x21075, 0x60021, 0xc};

    ASSERT_EQ(gold_standard, result);

}


/*
TEST(EndToEndC, post_assignment_propagation) {

    std::string input_file = "c_e2e/test_post_assignment_propagation.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":1},
                    "test_out":{"type": "output","address":2}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0xF0003, 0x10001, 0x2000f, 0x30011, 0x46, 0x0, 0x60021, 0x81055,
                                           0x2084, 0x46,0x38000074, 0x82043, 0x40081, 0x66,1,0x80021,0x21075, 0x60021, 0xc};

    ASSERT_EQ(gold_standard, result);

}
*/