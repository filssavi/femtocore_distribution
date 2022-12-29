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
// limitations under the License.29/06/2021.
//

#include "frontend/C/C_language_parser.hpp"
#include <gtest/gtest.h>

#include <stdexcept>

TEST( cFrontend, preprocessor_decomment) {
    std::string input_file = "c_prep/test_comments.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file,result_def);
    parser.pre_process({});

    define def_1(0, "TEST", "15");
    define def_2(0, "TESTT", "1 ");
    define def_3(0, "TESTQ", "5");
    define res_1 = *result_def->at("TEST");
    define res_2 = *result_def->at("TESTT");
    define res_3 = *result_def->at("TESTQ");


    ASSERT_EQ(def_1, res_1);
    ASSERT_EQ(def_2, res_2);
    ASSERT_EQ(def_3, res_3);
}


TEST( cFrontend, preprocessor_define) {
    std::string input_file = "c_prep/test_define.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();


    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = variable_input_type;

    C_language_parser parser(input_file,result_def);
    parser.pre_process({});

    parser.parse(io_spec);

    std::shared_ptr<hl_definition_node> result = std::static_pointer_cast<hl_definition_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_variable_class(variable_input_type);
    std::shared_ptr<hl_definition_node> gold_standard = std::make_shared<hl_definition_node>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 15);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_scalar_initializer(op);

    ASSERT_EQ(*result, *gold_standard);
}

TEST( cFrontend, preprocessor_include) {
    std::string input_file = "c_prep/test_include.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = variable_input_type;

    C_language_parser parser(input_file,result_def);
    parser.pre_process({});
    parser.parse(io_spec);

    std::shared_ptr<hl_definition_node> result = std::static_pointer_cast<hl_definition_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_variable_class(variable_input_type);
    std::shared_ptr<hl_definition_node> gold_standard = std::make_shared<hl_definition_node>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 42);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_scalar_initializer(op);


    EXPECT_EQ(*gold_standard, *result);
}

TEST( cFrontend, preprocessor_include_fail) {
    std::string input_file = "c_prep/test_include_fail.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
    C_language_parser parser(input_file,result_def);
    EXPECT_THROW(parser.pre_process({}), std::runtime_error);

}
