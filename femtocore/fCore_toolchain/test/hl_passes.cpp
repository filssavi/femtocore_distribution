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
//

#include <gtest/gtest.h>
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"
#include "data_structures/common/variable.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "passes/hl_passes.hpp"
#include "passes/high_level/function_mapping.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/high_level/normalization_pass.hpp"
#include "tools/high_level_ast_lowering.hpp"

#include <memory>
#include <fstream>


TEST(HlPassesTest, divisionImplementation) {


    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");

    std::shared_ptr<hl_definition_node> define = std::make_shared<hl_definition_node>("a", c_type_float, var);

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_div);
    var = std::make_shared<variable>("constant", 4);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    exp->set_lhs(op);
    var = std::make_shared<variable>("constant", 6);
    op = std::make_shared<hl_ast_operand>(var);
    exp->set_rhs(op);

    define->set_scalar_initializer(exp);

    input_root->add_content(define);
    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep, {1}, 0);
    manager.run_morphing_passes(input_root);

    std::shared_ptr<hl_ast_node> result =  input_root;

    std::shared_ptr<hl_expression_node> mult_exp = std::make_shared<hl_expression_node>(expr_mult);


    var = std::make_shared<variable>("constant", 4);
    std::shared_ptr<hl_ast_operand> op_1= std::make_shared<hl_ast_operand>(var);
    mult_exp->set_lhs(op_1);

    var = std::make_shared<variable>("constant",6);
    op_1= std::make_shared<hl_ast_operand>(var);
    std::shared_ptr<hl_expression_node> rec_exp = std::make_shared<hl_expression_node>(expr_reciprocal);
    rec_exp->set_rhs(op_1);

    mult_exp->set_rhs(rec_exp);

    var = std::make_shared<variable>("a");
    std::shared_ptr<hl_definition_node> mult_def = std::make_shared<hl_definition_node>("a", c_type_float, var);
    mult_def->set_scalar_initializer(mult_exp);


    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->add_content(mult_def);

    EXPECT_EQ( *gold_standard, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }
}

TEST(HlPassesTest, intrinsics_implementation) {


    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_function_def_node> main_fcn = std::make_shared<hl_function_def_node>();
    main_fcn->set_name("main");
    main_fcn->set_return_type(c_type_int);

    std::shared_ptr<variable> var = std::make_shared<variable>("b");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("b", c_type_float, var);
    var = std::make_shared<variable>("c");
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("c", c_type_float, var);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);

    std::vector<std::shared_ptr<hl_ast_node>> args = {op};
    std::shared_ptr<hl_function_call_node> call_1 = std::make_shared<hl_function_call_node>("itf", args);
    def_1->set_scalar_initializer(call_1);
    function_body.push_back(def_1);


    args = {op};
    var = std::make_shared<variable>("constant", 100);
    op = std::make_shared<hl_ast_operand>(var);
    args.push_back(op);
    std::shared_ptr<hl_function_call_node> call_2 = std::make_shared<hl_function_call_node>("satp", args);
    def_2->set_scalar_initializer(call_2);
    function_body.push_back(def_2);

    main_fcn->set_body(function_body);
    input_root->add_content(main_fcn);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{3}, 0);
    manager.run_morphing_passes(input_root);

    std::shared_ptr<hl_ast_node> result = input_root;

    var = std::make_shared<variable>("b");
    std::shared_ptr<hl_definition_node> def_3 = std::make_shared<hl_definition_node>("b", c_type_float, var);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_itf);
    ex_1->set_rhs(op_1);
    def_3->set_scalar_initializer(ex_1);

    var = std::make_shared<variable>("c");
    std::shared_ptr<hl_definition_node> def_4 = std::make_shared<hl_definition_node>("c", c_type_float, var);


    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant",100);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_satp);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_4->set_scalar_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    main_fcn->set_body({def_3, def_4});
    gold_standard->add_content(main_fcn);

    ASSERT_EQ(*gold_standard, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }

}

TEST(HlPassesTest, test_operating_assignments_implementation) {

    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_function_def_node> main_fcn = std::make_shared<hl_function_def_node>();
    main_fcn->set_name("main");
    main_fcn->set_return_type(c_type_int);

    std::shared_ptr<variable> var = std::make_shared<variable>("b");
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_assign);
    exp->set_assignment_type(addition_assignment);
    exp->set_lhs(op);

    std::shared_ptr<hl_expression_node> expmul = std::make_shared<hl_expression_node>(expr_mult);
    expmul->set_lhs(op);
    var = std::make_shared<variable>("constant", 3);
    op = std::make_shared<hl_ast_operand>(var);
    expmul->set_rhs(op);
    exp->set_rhs(expmul);

    main_fcn->set_body({exp});
    input_root->add_content(main_fcn);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{3}, 0);
    manager.run_morphing_passes(input_root);

    std::shared_ptr<hl_ast_node> result = input_root;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    var = std::make_shared<variable>("c");
    std::shared_ptr<hl_expression_node> exadd = std::make_shared<hl_expression_node>(expr_add);

    std::shared_ptr<hl_expression_node> exmul = std::make_shared<hl_expression_node>(expr_mult);

    var = std::make_shared<variable>("b");
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 3);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    exmul->set_lhs(op_1);
    exmul->set_rhs(op_2);

    exadd->set_lhs(op_1);
    exadd->set_rhs(exmul);

    std::shared_ptr<hl_expression_node> exassign = std::make_shared<hl_expression_node>(expr_assign);
    exassign->set_lhs(op_1);
    exassign->set_rhs(exadd);

    main_fcn->set_body({exassign});
    gold_standard->add_content(main_fcn);

    ASSERT_EQ(*result, *gold_standard);
}

TEST(HlPassesTest, function_inlining) {

    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> function_body;

    std::shared_ptr<hl_function_def_node> function = std::make_shared<hl_function_def_node>();
    function->set_name("add_1");
    function->set_return_type(c_type_int);

    std::vector<std::shared_ptr<hl_definition_node>> parameters;

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("a", c_type_int, var);
    parameters.push_back(def);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("b");
    def = std::make_shared<hl_definition_node>("b", c_type_int, var);
    parameters.push_back(def);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> exp_1 = std::make_shared<hl_expression_node>(expr_add);
    exp_1->set_lhs(op_1);
    exp_1->set_rhs(op_2);

    var = std::make_shared<variable>("c");
    def = std::make_shared<hl_definition_node>("c", c_type_int, var);
    def->set_scalar_initializer(exp_1);

    op_1 = std::make_shared<hl_ast_operand>(var);
    exp_1 = std::make_shared<hl_expression_node>(expr_add);
    exp_1->set_lhs(op_1);
    exp_1->set_rhs(op_2);

    function->set_parameters_list(parameters);
    function->set_body({def});
    function->set_return(exp_1);
    input_root->add_content(function);



    function= std::make_shared<hl_function_def_node>();
    function->set_name("add_2");
    function->set_return_type(c_type_int);

    parameters.clear();

    var = std::make_shared<variable>("e");
    def = std::make_shared<hl_definition_node>("e", c_type_int, var);
    parameters.push_back(def);
    std::shared_ptr<hl_ast_operand> op_e = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("f");
    def = std::make_shared<hl_definition_node>("f", c_type_int, var);
    parameters.push_back(def);
    std::shared_ptr<hl_ast_operand> op_f = std::make_shared<hl_ast_operand>(var);

    exp_1 = std::make_shared<hl_expression_node>(expr_add);
    exp_1->set_lhs(op_e);
    exp_1->set_rhs(op_f);

    std::shared_ptr<hl_expression_node> exp_2 = std::make_shared<hl_expression_node>(expr_add);
    exp_2->set_lhs(exp_1);
    exp_2->set_rhs(op_f);

    function->set_parameters_list(parameters);
    function->set_return(exp_2);
    input_root->add_content(function);

    function = std::make_shared<hl_function_def_node>();
    function->set_name("main");
    function->set_return_type(c_type_int);

    var = std::make_shared<variable>("constant", 2);
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("t");
    op_2 = std::make_shared<hl_ast_operand>(var);

    std::vector<std::shared_ptr<hl_ast_node>> args = {op_1, op_2};
    std::shared_ptr<hl_function_call_node> call_1 = std::make_shared<hl_function_call_node>("add_1", args);
    std::shared_ptr<hl_function_call_node> call_2 = std::make_shared<hl_function_call_node>("add_2", args);

    function->set_body({call_1, call_2});
    input_root->add_content(function);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{4,5,6,7}, 0);

    manager.run_morphing_passes(input_root);

    std::shared_ptr<hl_ast_node> res = input_root;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    // CALL BODY
    var = std::make_shared<variable>("_fcmglr_function_add_1_c");
    def = std::make_shared<hl_definition_node>("_fcmglr_function_add_1_c", c_type_int, var);
    std::shared_ptr<hl_expression_node> exadd = std::make_shared<hl_expression_node>(expr_add);

    var = std::make_shared<variable>("constant",2);
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("t");
    op_2 = std::make_shared<hl_ast_operand>(var);

    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    def->set_scalar_initializer(exadd);

    gold_standard->add_content(def);

    std::shared_ptr<hl_expression_node> ex_add2 = std::make_shared<hl_expression_node>(expr_add);
    ex_add2->set_lhs(exadd);
    ex_add2->set_rhs(op_2);

    exadd = std::make_shared<hl_expression_node>(expr_add);

    var = std::make_shared<variable>("_fcmglr_function_add_1_c");
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("t");
    op_2 = std::make_shared<hl_ast_operand>(var);

    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);

    gold_standard->add_content(exadd);
    gold_standard->add_content(ex_add2);


    EXPECT_EQ(*res, *gold_standard);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << res->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }

}

TEST(HlPassesTest, function_elimination) {


    std::string input_file = "hl_opt/test_normalization.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
    
    C_language_parser parser(input_file, result_def);
    std::unordered_map<std::string, variable_class_t> io_spec;
    parser.pre_process({});
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8,11,12,13}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> raw_result =parser.AST;

    std::shared_ptr<variable> var = std::make_shared<variable>("intermediate_expression_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expression_0", c_type_float, var);


    var = std::make_shared<variable>("constant", 4.0f);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant", 5.0f);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_scalar_initializer(ex_1);

    var = std::make_shared<variable>("a");
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int, var);


    var = std::make_shared<variable>("intermediate_expression_0");
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant",6.0f);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_scalar_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}

TEST(HlPassesTest, simple_normalization) {


    std::string input_file = "hl_opt/test_normalization.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = variable_output_type;

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,8,9,10,11,12,13}, 0);
    manager.run_morphing_passes(parser.AST);

    normalization_pass p;
    std::shared_ptr<hl_ast_node> raw_result = p.process_global(parser.AST);

    std::shared_ptr<variable> var = std::make_shared<variable>("intermediate_expression_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expression_0", c_type_float, var);



    var = std::make_shared<variable>("constant", 4.0f);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);



    var = std::make_shared<variable>("constant", 5.0f);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_scalar_initializer(ex_1);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int, var);


    var = std::make_shared<variable>("intermediate_expression_0");
    op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant",6.0f);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_scalar_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}


TEST(HlPassesTest, hl_ast_lowering) {


    std::string input_file = "hl_opt/test_normalization.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});

    std::unordered_map<std::string, variable_class_t> io_spec;
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,8,9,11,12,13}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    high_level_ast_lowering tranlator;

    tranlator.set_input_ast(normalized_ast);
    tranlator.translate();
    std::shared_ptr<ll_ast_node> result = tranlator.get_output_ast();


    std::shared_ptr<variable> op_a = std::make_shared<variable>("constant", 4);
    std::shared_ptr<variable> op_b = std::make_shared<variable>("constant", 5);
    std::shared_ptr<variable> dest = std::make_shared<variable>("intermediate_expression_0");

    std::shared_ptr<ll_register_instr_node> op_1 = std::make_shared<ll_register_instr_node>("mul", op_a, op_b, dest);


    op_a = std::make_shared<variable>("intermediate_expression_0");
    op_b = std::make_shared<variable>("constant", 6);
    dest = std::make_shared<variable>("a");

    std::shared_ptr<ll_register_instr_node> op_2 = std::make_shared<ll_register_instr_node>( "add", op_a, op_b, dest);

    std::shared_ptr<ll_ast_node> golden_standard = std::make_shared<ll_ast_node>(ll_type_program_head);
    golden_standard->set_content({op_1, op_2});

    ASSERT_EQ(*golden_standard, *result);
}


TEST(HlPassesTest, loop_unrolling_array) {


    std::string input_file = "hl_opt/test_loop_unrolling.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    std::unordered_map<std::string, variable_class_t> io_spec;
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8,11,12,13}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    for(int i = 5; i<7; ++i){
        //assignment
        std::shared_ptr<hl_expression_node> assign_exp = std::make_shared<hl_expression_node>(expr_assign);

        std::shared_ptr<variable> def_var = std::make_shared<variable>("j");
        def_var->set_type(var_type_array);
        std::shared_ptr<hl_ast_operand> assign_op = std::make_shared<hl_ast_operand>(def_var);
        std::shared_ptr<variable> idx_var = std::make_shared<variable>("i", i);
        std::shared_ptr<hl_ast_operand> op_idx = std::make_shared<hl_ast_operand>(idx_var);
        assign_op->set_array_index({op_idx});
        assign_exp->set_lhs(assign_op);

        //INITIALIZER
        std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_add);
        // LHS
        def_var = std::make_shared<variable>("a");
        def_var->set_type(var_type_array);
        std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(def_var);
        idx_var = std::make_shared<variable>("i", i);
        op_idx = std::make_shared<hl_ast_operand>(idx_var);
        op->set_array_index({op_idx});
        expr->set_lhs(op);
        //RHS
        def_var = std::make_shared<variable>("h");
        def_var->set_type(var_type_array);
        op = std::make_shared<hl_ast_operand>(def_var);
        idx_var = std::make_shared<variable>("i", i);
        op_idx = std::make_shared<hl_ast_operand>(idx_var);
        op->set_array_index({op_idx});
        expr->set_rhs(op);
        assign_exp->set_rhs(expr);
        gold_standard->add_content(assign_exp);
    }
    ASSERT_EQ(*normalized_ast, *gold_standard);
}


TEST(HlPassesTest, test_matrix_scalarization) {


    std::string input_file = "hl_opt/test_matrix_scalarization.c";


    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    std::unordered_map<std::string, variable_class_t> io_spec;
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8,15}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    //A VECTOR DEFINITION
    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_type(var_type_array);
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("a", c_type_int, var);
    std::vector<int> shape = {10,2};
    def->set_array_shape(shape);
    var = std::make_shared<variable>("constant", 10);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("constant", 2);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);
    def->set_array_index({op_1, op_2});
    gold_standard->add_content(def);
    //B VECTOR DEFINITION
    var = std::make_shared<variable>("b");
    var->set_type(var_type_array);
    def = std::make_shared<hl_definition_node>("b", c_type_int, var);
    shape = {3};
    def->set_array_shape(shape);
    var = std::make_shared<variable>("constant", 3);
    op_1 = std::make_shared<hl_ast_operand>(var);
    def->set_array_index({op_1});
    gold_standard->add_content(def);

    std::shared_ptr<hl_expression_node> ex = std::make_shared<hl_expression_node>(expr_assign);
    // FIRST EXPRESSION LHS
    var = std::make_shared<variable>("a");
    var->set_type(var_type_array);
    var->set_array_shape({10,2});
    var->set_array_index({0,1});
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    ex->set_lhs(op);
    // FIRST EXPRESSION RHS
    std::shared_ptr<hl_expression_node> ex_inner = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("b");
    var->set_type(var_type_array);
    var->set_array_shape({3});
    var->set_array_index({0});
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_lhs(op);
    var = std::make_shared<variable>("constant", 2);
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_rhs(op);
    ex->set_rhs(ex_inner);
    gold_standard->add_content(ex);

    ex = std::make_shared<hl_expression_node>(expr_assign);
    // SECOND EXPRESSION LHS
    var = std::make_shared<variable>("b");
    var->set_type(var_type_array);
    var->set_array_shape({3});
    var->set_array_index({2});
    op = std::make_shared<hl_ast_operand>(var);
    ex->set_lhs(op);
    // SECOND EXPRESSION RHS
    ex_inner = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("a");
    var->set_type(var_type_array);
    var->set_array_shape({10,2});
    var->set_array_index({1,1});
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_lhs(op);
    var = std::make_shared<variable>("constant", 2);
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_rhs(op);
    ex->set_rhs(ex_inner);
    gold_standard->add_content(ex);
    ASSERT_EQ(*normalized_ast, *gold_standard);
}


TEST(HlPassesTest, function_inlining_array) {

    std::string input_file = "hl_opt/test_function_inlining_array.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    std::unordered_map<std::string, variable_class_t> io_spec;
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST->get_content()[5];

    std::shared_ptr<hl_expression_node> gold_standard = std::make_shared<hl_expression_node>(expr_assign);

    std::shared_ptr<variable> var = std::make_shared<variable>("_fcmglr_flattened_array_c_1_1");
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_lhs(op);

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_add);
    var = std::make_shared<variable>("constant", 5.0f);
    op = std::make_shared<hl_ast_operand>(var);
    exp->set_lhs(op);

    var = std::make_shared<variable>("constant", 2.0f);
    op = std::make_shared<hl_ast_operand>(var);
    exp->set_rhs(op);

    ASSERT_EQ(*normalized_ast, *gold_standard);

}

TEST(HlPassesTest, function_return_inlining) {

    std::string input_file = "hl_opt/test_return_inlining.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["ret"] = variable_output_type;
    io_spec["test_in"] = variable_input_type;

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<variable> var = std::make_shared<variable>("inlined_variable_0");
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("inlined_variable_0", c_type_float, var);
    var = std::make_shared<variable>("_fcmglr_function_inlining_target_c", 807.000977f);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    def->set_scalar_initializer(op);
    gold_standard->add_content(def);

    var = std::make_shared<variable>("ret");
    var->set_variable_class(variable_output_type);
    def = std::make_shared<hl_definition_node>("ret", c_type_float, var);
    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_add);

    var = std::make_shared<variable>("inlined_variable_0");
    op = std::make_shared<hl_ast_operand>(var);
    exp->set_lhs(op);

    var = std::make_shared<variable>("test_in");
    var->set_variable_class(variable_input_type);
    op = std::make_shared<hl_ast_operand>(var);
    exp->set_rhs(op);

    def->set_scalar_initializer(exp);
    gold_standard->add_content(def);

    ASSERT_EQ(*normalized_ast, *gold_standard);
}


TEST(HlPassesTest, complex_normalization) {
    // INNER MULTIPLICATION
    std::shared_ptr<hl_expression_node> expr_1 = std::make_shared<hl_expression_node>(expr_mult);

    std::shared_ptr<variable> var = std::make_shared<variable>("fwd_in");
    std::shared_ptr<hl_ast_operand> fwd_op = std::make_shared<hl_ast_operand>(var);
    expr_1->set_rhs(fwd_op);

    var = std::make_shared<variable>("Ts");
    std::shared_ptr<hl_ast_operand> ts_op = std::make_shared<hl_ast_operand>(var);
    expr_1->set_lhs(ts_op);
    // OUTER MULTIPLICATION
    std::shared_ptr<hl_expression_node> expr_2 = std::make_shared<hl_expression_node>(expr_mult);
    expr_2->set_lhs(expr_1);

    var = std::make_shared<variable>("omega");
    std::shared_ptr<hl_ast_operand> w_op = std::make_shared<hl_ast_operand>(var);
    expr_2->set_rhs(w_op);
    // ADDITION
    expr_1 = std::make_shared<hl_expression_node>(expr_add);
    expr_1->set_rhs(expr_2);

    var = std::make_shared<variable>("integ_1");
    std::shared_ptr<hl_ast_operand> integ_op = std::make_shared<hl_ast_operand>(var);
    expr_1->set_lhs(integ_op);

    expr_2 = std::make_shared<hl_expression_node>(expr_assign);
    expr_2->set_rhs(expr_1);
    expr_2->set_lhs(integ_op);


    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);


    input_root->add_content(expr_2);
    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{11}, 0);
    manager.run_morphing_passes(input_root);


    var = std::make_shared<variable>("intermediate_expression_0");
    std::shared_ptr<hl_definition_node> ie0_def = std::make_shared<hl_definition_node>("intermediate_expression_0", c_type_float, var);
    std::shared_ptr<hl_ast_operand> ie0_op = std::make_shared<hl_ast_operand>(var);
    std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_mult);
    expr->set_rhs(fwd_op);
    expr->set_lhs(ts_op);
    ie0_def->set_scalar_initializer(expr);

    var = std::make_shared<variable>("intermediate_expression_1");
    std::shared_ptr<hl_definition_node> ie1_def = std::make_shared<hl_definition_node>("intermediate_expression_1", c_type_float, var);
    std::shared_ptr<hl_ast_operand> ie1_op = std::make_shared<hl_ast_operand>(var);
    expr = std::make_shared<hl_expression_node>(expr_mult);
    expr->set_rhs(w_op);
    expr->set_lhs(ie0_op);
    ie1_def->set_scalar_initializer(expr);


    expr = std::make_shared<hl_expression_node>(expr_add);
    expr->set_rhs(ie1_op);
    expr->set_lhs(integ_op);


    std::shared_ptr<hl_expression_node> expr_as = std::make_shared<hl_expression_node>(expr_assign);
    expr_as->set_rhs(expr);
    expr_as->set_lhs(integ_op);

    std::shared_ptr<hl_ast_node> gold_standard= std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->add_content(ie0_def);
    gold_standard->add_content(ie1_def);
    gold_standard->add_content(expr_as);

    ASSERT_EQ(*gold_standard, *input_root);
}


TEST(HlPassesTest, dead_load_elimination) {

    std::shared_ptr<hl_ast_node> input_root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<variable> ts_var = std::make_shared<variable>("Ts", 15.7f);
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("Ts", c_type_float, ts_var);
    input_root->add_content(def);

    std::shared_ptr<variable> cvar = std::make_shared<variable>("constant", 158.6f);
    std::shared_ptr<hl_ast_operand> constant_op = std::make_shared<hl_ast_operand>(cvar);
    std::shared_ptr<hl_ast_operand> dest_op = std::make_shared<hl_ast_operand>(ts_var);
    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_assign);
    exp->set_rhs(constant_op);
    exp->set_lhs(dest_op);
    input_root->add_content(exp);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{16}, 0);
    manager.run_morphing_passes(input_root);


    std::shared_ptr<hl_ast_node> gold_standard= std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->add_content(exp);
    ASSERT_EQ(*gold_standard, *input_root);
}




TEST(HlPassesTest, nested_function_inlining) {
    std::string input_file = "hl_opt/test_nested_function_inlining.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["input_1"] = variable_input_type;
    io_spec["memory_2"] = variable_memory_type;

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{}, 0);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    ///////////////////////////////////////////////////////////////////////////
    ///                                  ADD                                ///
    ///////////////////////////////////////////////////////////////////////////

    std::shared_ptr<variable> var = std::make_shared<variable>("input_1");
    var->set_variable_class(variable_input_type);
    std::shared_ptr<hl_ast_operand> in_1_op = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("memory_2");
    var->set_variable_class(variable_memory_type);
    std::shared_ptr<hl_ast_operand> mem_2_op = std::make_shared<hl_ast_operand>(var);



    std::shared_ptr<hl_expression_node> exp_add = std::make_shared<hl_expression_node>(expr_add);
    exp_add->set_rhs(mem_2_op);
    exp_add->set_lhs(in_1_op);


    var = std::make_shared<variable>("_fcmglr_function_level_2_out");
    std::shared_ptr<hl_definition_node> def_0 = std::make_shared<hl_definition_node>("_fcmglr_function_level_2_out", c_type_float, var);
    def_0->set_scalar_initializer(exp_add);
    gold_standard->add_content(def_0);

    ///////////////////////////////////////////////////////////////////////////
    ///                             CONSTANT LOAD                           ///
    ///////////////////////////////////////////////////////////////////////////

    var = std::make_shared<variable>("inlined_variable_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("inlined_variable_0", c_type_int, var);

    std::shared_ptr<variable> var_const = std::make_shared<variable>("_fcmglr_function_level_2_constant", 120);
    std::shared_ptr<hl_ast_operand> const_op = std::make_shared<hl_ast_operand>(var_const);
    def_1->set_scalar_initializer(const_op);

    gold_standard->add_content(def_1);


    ///////////////////////////////////////////////////////////////////////////
    ///                             SATURATE                                ///
    ///////////////////////////////////////////////////////////////////////////

    var = std::make_shared<variable>("_fcmglr_function_level_2_out");
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("inlined_variable_0");
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);


    std::shared_ptr<hl_expression_node> expr_sat = std::make_shared<hl_expression_node>(expr_satp);
    expr_sat->set_rhs(op_2);
    expr_sat->set_lhs(op_1);


    var = std::make_shared<variable>("memory_2");
    var->set_variable_class(variable_memory_type);
    std::shared_ptr<hl_ast_operand> op_dest = std::make_shared<hl_ast_operand>(var);


    std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_assign);
    expr->set_rhs(expr_sat);
    expr->set_lhs(op_dest);
    gold_standard->add_content(expr);

    ASSERT_EQ(*normalized_ast, *gold_standard);
}



TEST(HlPassesTest, complex_division_implementation) {
    std::string input_file = "hl_opt/test_complex_division_implementation.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = variable_input_type;

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    parser.parse(io_spec);

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1}, 0);
    manager.run_morphing_passes(parser.AST);

    auto result = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard= std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<hl_function_def_node> main = std::make_shared<hl_function_def_node>();
    main->set_name("main");
    main->set_return_type(c_type_int);
    gold_standard->add_content(main);

    std::vector<std::shared_ptr<hl_ast_node>> main_body;

    std::shared_ptr<variable> a = std::make_shared<variable>("a");
    a->set_variable_class(variable_input_type);
    std::shared_ptr<hl_definition_node> a_def = std::make_shared<hl_definition_node>("a", c_type_float, a);
    main_body.push_back(a_def);

    std::shared_ptr<variable> b = std::make_shared<variable>("b");
    std::shared_ptr<hl_definition_node> b_def = std::make_shared<hl_definition_node>("b", c_type_float, b);
    std::shared_ptr<variable> b_const = std::make_shared<variable>("constant", 52.6f);
    std::shared_ptr<hl_ast_operand> b_op = std::make_shared<hl_ast_operand>(b_const);
    b_def->set_scalar_initializer(b_op);
    main_body.push_back(b_def);

    std::shared_ptr<variable> c = std::make_shared<variable>("c");
    std::shared_ptr<hl_definition_node> c_def = std::make_shared<hl_definition_node>("c", c_type_int, c);

    std::shared_ptr<hl_expression_node> mul_exp = std::make_shared<hl_expression_node>(expr_mult);
    mul_exp->set_lhs(std::make_shared<hl_ast_operand>(a));


    mul_exp->set_lhs(std::make_shared<hl_ast_operand>(a));

    std::shared_ptr<hl_expression_node> rec_exp = std::make_shared<hl_expression_node>(expr_reciprocal);
    rec_exp->set_rhs(std::make_shared<hl_ast_operand>(b));
    mul_exp->set_rhs(rec_exp);

    std::vector<std::shared_ptr<hl_ast_node>> args = {mul_exp};
    std::shared_ptr<hl_function_call_node> fti_call = std::make_shared<hl_function_call_node>("fti", args);


    c_def->set_scalar_initializer(fti_call);

    main_body.push_back(c_def);

    main->set_body(main_body);

    ASSERT_EQ(*result, *gold_standard);

}

