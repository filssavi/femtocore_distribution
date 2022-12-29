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

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "passes/ll_passes.hpp"
#include "backend/binary_generator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "data_structures/instruction_stream.hpp"

TEST(llPassesTest, pseudo_inst_pass) {

    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);

    std::shared_ptr<variable> op_a = std::make_shared<variable>("r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b};

    std::shared_ptr<ll_pseudo_instr_node> instr = std::make_shared<ll_pseudo_instr_node>("mov", args);
    AST->add_content(instr);


    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_morphing_passes(AST);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(AST);
    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x80061};
    ASSERT_EQ(result, gold_standard);
}


TEST(llPassesTest, instruction_count_pass) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<variable> op_a = std::make_shared<variable>("r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r4");
    std::shared_ptr<variable> dest = std::make_shared<variable>("r5");
    std::shared_ptr<variable> imm = std::make_shared<variable>("constant", 100);
    std::shared_ptr<variable> fltc = std::make_shared<variable>("constant",(float)1.5464);
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_independent_inst_node> indep_instr = std::make_shared<ll_independent_inst_node>("nop");
    AST->add_content(indep_instr);

    args = {op_a, op_b};
    std::shared_ptr<ll_pseudo_instr_node> pseudo_instr = std::make_shared<ll_pseudo_instr_node>("mov", args); // +1
    AST->add_content(pseudo_instr);

    std::shared_ptr<ll_register_instr_node> reg_instr = std::make_shared<ll_register_instr_node>("add", op_a, op_b, dest); // +1
    AST->add_content(reg_instr);

    args = {dest};
    std::shared_ptr<ll_load_constant_instr_node> ldc_instr = std::make_shared<ll_load_constant_instr_node>("ldc", dest, fltc);// +2
    AST->add_content(ldc_instr);

    std::shared_ptr<ll_intercalated_const_instr_node> load_instr = std::make_shared<ll_intercalated_const_instr_node>(1.456f);// +0
    AST->add_content(load_instr);


    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_analysis_passes(AST);
    int count = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];


    ASSERT_EQ( count, 5);
}

TEST(llPassesTest, loop_less) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::shared_ptr<ll_independent_inst_node> loop_instr = std::make_shared<ll_independent_inst_node>("nop");
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<"};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_morphing_passes(AST);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(AST);
    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0, 0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(llPassesTest, loop_less_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::shared_ptr<ll_independent_inst_node> loop_instr = std::make_shared<ll_independent_inst_node>("nop");
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<="};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_morphing_passes(AST);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(AST);
    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(llPassesTest, loop_more) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::shared_ptr<ll_independent_inst_node> loop_instr = std::make_shared<ll_independent_inst_node>("nop");
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">"};


    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();

    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);


    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_morphing_passes(AST);

    binary_generator writer;
    instruction_stream program_stream = instruction_stream_builder::build_stream(AST);
    writer.process_stream(program_stream, false);
    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(llPassesTest, loop_more_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::shared_ptr<ll_independent_inst_node> loop_instr = std::make_shared<ll_independent_inst_node>("nop");
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">="};


    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    ll_pass_manager manager = create_ll_pass_manager(0);
    manager.run_morphing_passes(AST);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(AST);
    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0,0,0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(llPassesTest, deep_copy_element) {
    loop_start_t start = {"j", 36};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_loop_start(start);
    std::shared_ptr<ll_independent_inst_node> level_2 = std::make_shared<ll_independent_inst_node>("nop");;
    lvl_1->add_content(level_2);
    std::shared_ptr<ll_ast_node> result = ll_ast_node::deep_copy_element(lvl_1);

    ASSERT_EQ(*result, *lvl_1);
}