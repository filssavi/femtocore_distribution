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
#include <fstream>

#include "data_structures/high_level_ast/high_level_ast.hpp"


TEST( HlAstDeepCopy, operand){
    std::vector<std::shared_ptr<hl_ast_node>> init;
    std::shared_ptr<variable> var = std::make_shared<variable>("array");
    std::shared_ptr<hl_ast_operand> gold_standard = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> idx_op1 = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<hl_ast_operand> idx_op2 = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_array_index({idx_op1, idx_op2});

    std::shared_ptr<hl_ast_operand> result = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    //CHECK THAT THE OBJECT PROPERTIES HAVE ACTUALLY BEEN COPIED AND NOT JUST THE POINTERS
    std::vector<std::shared_ptr<hl_ast_node>> res_array_idx = result->get_array_index();
    std::vector<std::shared_ptr<hl_ast_node>> gs_array_idx = gold_standard->get_array_index();

    for(int i = 0; i< res_array_idx.size(); ++i){
        ASSERT_NE(res_array_idx[i], gs_array_idx[i]);
    }

    ASSERT_NE(result->get_variable(), gold_standard->get_variable());
}

TEST( HlAstDeepCopy, expression){
    std::vector<std::shared_ptr<hl_ast_node>> init;

    std::shared_ptr<hl_expression_node> gold_standard = std::make_shared<hl_expression_node>(expr_add);

    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_l = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<hl_ast_operand> op_r = std::make_shared<hl_ast_operand>(var);

    gold_standard->set_lhs(op_l);
    gold_standard->set_rhs(op_r);

    std::shared_ptr<hl_expression_node> result = std::static_pointer_cast<hl_expression_node>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    ASSERT_NE(result->get_lhs(), gold_standard->get_lhs());
    ASSERT_NE(result->get_rhs(), gold_standard->get_rhs());

}

TEST( HlAstDeepCopy, definition){
    std::vector<std::shared_ptr<hl_ast_node>> init;
    std::shared_ptr<variable> var;
    std::shared_ptr<hl_ast_operand> op;
    for(int i = 1; i<6;++i){
        var = std::make_shared<variable>("constant", i);
        op = std::make_shared<hl_ast_operand>(var);
        init.push_back(op);
    }

    var = std::make_shared<variable>("array_test");
    var->set_type(var_type_array);
    std::shared_ptr<hl_definition_node> gold_standard = std::make_shared<hl_definition_node>("array_test", c_type_int, var);
    var = std::make_shared<variable>("constant", 5);
    op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_array_index({op});

    gold_standard->set_array_initializer(init);
    std::vector<int> shape = {5};
    gold_standard->set_array_shape(shape);

    std::shared_ptr<hl_definition_node> result = std::static_pointer_cast<hl_definition_node>(hl_ast_node::deep_copy(gold_standard));

    ASSERT_EQ(*result, *gold_standard);

    ASSERT_NE(result->get_variable(), gold_standard->get_variable());
    ASSERT_NE(result, gold_standard);

    //CHECK THAT THE OBJECT PROPERTIES HAVE ACTUALLY BEEN COPIED AND NOT JUST THE POINTERS
    std::vector<std::shared_ptr<hl_ast_node>> res_array_idx = result->get_array_index();
    std::vector<std::shared_ptr<hl_ast_node>> gs_array_idx = gold_standard->get_array_index();

    for(int i = 0; i< res_array_idx.size(); ++i){
        ASSERT_NE(res_array_idx[i], gs_array_idx[i]);
    }

    std::vector<std::shared_ptr<hl_ast_node>> res_initializer = result->get_array_initializer();
    std::vector<std::shared_ptr<hl_ast_node>> gs_initializer = gold_standard->get_array_initializer();

    for(int i = 0; i< res_initializer.size(); ++i){
        ASSERT_NE(res_initializer[i], gs_initializer[i]);
    }

}

TEST( HlAstDeepCopy, conditional){
    std::vector<std::shared_ptr<hl_ast_node>> init;

    std::shared_ptr<hl_ast_conditional_node> gold_standard = std::make_shared<hl_ast_conditional_node>();

    std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_add);
    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_l = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<hl_ast_operand> op_r = std::make_shared<hl_ast_operand>(var);

    expr->set_lhs(op_l);
    expr->set_rhs(op_r);

    gold_standard->set_condition(expr);

    expr = std::make_shared<hl_expression_node>(expr_add);
    var = std::make_shared<variable>("constant", 7);
    op_r = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_if_block({expr});

    expr = std::make_shared<hl_expression_node>(expr_add);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_else_block({expr});

    std::shared_ptr<hl_ast_conditional_node> result = std::static_pointer_cast<hl_ast_conditional_node>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    ASSERT_NE(result->get_condition(), gold_standard->get_condition());

    std::vector<std::shared_ptr<hl_ast_node>> res_vect = result->get_if_block();
    std::vector<std::shared_ptr<hl_ast_node>> gs_vect = gold_standard->get_if_block();

    for(int i = 0; i< res_vect.size(); ++i){
        ASSERT_NE(res_vect[i], gs_vect[i]);
    }

    res_vect = result->get_else_block();
    gs_vect = gold_standard->get_else_block();

    for(int i = 0; i< res_vect.size(); ++i){
        ASSERT_NE(res_vect[i], gs_vect[i]);
    }
}

TEST( HlAstDeepCopy, loop){
    std::vector<std::shared_ptr<hl_ast_node>> init;

    std::shared_ptr<hl_ast_loop_node> gold_standard = std::make_shared<hl_ast_loop_node>();

    std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_add);
    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_l = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<hl_ast_operand> op_r = std::make_shared<hl_ast_operand>(var);

    expr->set_lhs(op_l);
    expr->set_rhs(op_r);

    gold_standard->set_condition(expr);

    expr = std::make_shared<hl_expression_node>(expr_add);
    var = std::make_shared<variable>("constant", 7);
    op_r = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_iteration_expr(expr);

    expr = std::make_shared<hl_expression_node>(expr_add);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_loop_content({expr});

    var = std::make_shared<variable>("constant", 9);
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("test", c_type_int, var);

    gold_standard->set_init_statement(def);

    std::shared_ptr<hl_ast_loop_node> result = std::static_pointer_cast<hl_ast_loop_node>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    ASSERT_NE(result->get_condition(), gold_standard->get_condition());

    std::vector<std::shared_ptr<hl_ast_node>> res_vect = result->get_loop_content();
    std::vector<std::shared_ptr<hl_ast_node>> gs_vect = gold_standard->get_loop_content();

    for(int i = 0; i< res_vect.size(); ++i){
        ASSERT_NE(res_vect[i], gs_vect[i]);
    }

    ASSERT_NE(result->get_iteration_expr(), gold_standard->get_iteration_expr());
    ASSERT_NE(result->get_init_statement(), gold_standard->get_init_statement());
}


TEST( HlAstDeepCopy, function_call){
    std::vector<std::shared_ptr<hl_ast_node>> init;

    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_l = std::make_shared<hl_ast_operand>(var);
    std::string name = "test";
    std::vector<std::shared_ptr<hl_ast_node>> args = {op_l};
    std::shared_ptr<hl_function_call_node> gold_standard = std::make_shared<hl_function_call_node>(name, args);

    std::shared_ptr<hl_function_call_node> result = std::static_pointer_cast<hl_function_call_node>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    std::vector<std::shared_ptr<hl_ast_node>> res_vect = result->get_arguments();
    std::vector<std::shared_ptr<hl_ast_node>> gs_vect = gold_standard->get_arguments();

    for(int i = 0; i< res_vect.size(); ++i){
        ASSERT_NE(res_vect[i], gs_vect[i]);
    }
}


TEST( HlAstDeepCopy, function_def){
    std::vector<std::shared_ptr<hl_ast_node>> init;

    std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();
    gold_standard->set_name("test");

    std::shared_ptr<variable> var = std::make_shared<variable>("array_test");
    var->set_type(var_type_array);
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("array_test", c_type_int, var);
    gold_standard->set_parameters_list({def});

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_l = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<hl_ast_operand> op_r = std::make_shared<hl_ast_operand>(var);
    exp->set_lhs(op_l);
    exp->set_rhs(op_r);
    gold_standard->set_body({exp});


    exp = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("constant", 7);
    op_l = std::make_shared<hl_ast_operand>(var);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<hl_ast_operand>(var);
    exp->set_lhs(op_l);
    exp->set_rhs(op_r);
    gold_standard->set_return(exp);

    std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(hl_ast_node::deep_copy(gold_standard));

    // CHECK EQUIVALENCE BETWEEN ORIGINAL AND COPY
    ASSERT_EQ(*result, *gold_standard);
    // CHECK THAT THE TWO POINTERS ARE ACTUALLY DIFFERENT
    ASSERT_NE(result, gold_standard);

    std::vector<std::shared_ptr<hl_definition_node>> res_vect = result->get_parameters_list();
    std::vector<std::shared_ptr<hl_definition_node>> gs_vect = gold_standard->get_parameters_list();

    for(int i = 0; i< res_vect.size(); ++i){
        ASSERT_NE(res_vect[i], gs_vect[i]);
    }

    std::vector<std::shared_ptr<hl_ast_node>> res_body = result->get_body();
    std::vector<std::shared_ptr<hl_ast_node>> gs_body = gold_standard->get_body();

    for(int i = 0; i< res_body.size(); ++i){
        ASSERT_NE(res_body[i], gs_body[i]);
    }

    ASSERT_NE(result->get_return(), gold_standard->get_return());


}
