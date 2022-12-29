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

#ifndef FCORE_TOOLCHAIN_C_TREE_VISITOR_HPP
#define FCORE_TOOLCHAIN_C_TREE_VISITOR_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <exception>
#include <stdexcept>

#include "C_parser/C_grammarBaseListener.h"
#include "C_parser/C_grammarParser.h"
#include "data_structures/common/variable.hpp"


#include "data_structures/high_level_ast/hl_function_def_node.hpp"
#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_ast_operand.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/high_level_ast/hl_function_call_node.hpp"
#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"
#include "data_structures/high_level_ast/hl_ast_loop_node.h"

#include <gtest/gtest_prod.h>

typedef enum {
    dma_type_in=0,
    dma_type_out=1,
    dma_type_mem=2,
} dma_type;

typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class C_Tree_visitor : public  C_parser::C_grammarBaseListener{
public:
    explicit C_Tree_visitor();
    void enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitBlockItem(C_parser::C_grammarParser::BlockItemContext *ctx) override;

    void enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;
    void exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;

    void exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) override;
    void exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) override;
    void exitDirectDeclarator(C_parser::C_grammarParser::DirectDeclaratorContext *ctx) override;
    void enterInitializerList(C_parser::C_grammarParser::InitializerListContext *ctx) override;
    void exitInitializerList(C_parser::C_grammarParser::InitializerListContext *ctx) override;
    void exitInitializer(C_parser::C_grammarParser::InitializerContext *ctx) override;

    void enterArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *ctx) override;
    void exitArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *ctx) override;
    void exitPrimaryExpression(C_parser::C_grammarParser::PrimaryExpressionContext *ctx) override;
    void exitUnaryExpression(C_parser::C_grammarParser::UnaryExpressionContext *ctx) override;


    void exitMultiplicativeExpression(C_parser::C_grammarParser::MultiplicativeExpressionContext *ctx) override;
    void exitAdditiveExpression(C_parser::C_grammarParser::AdditiveExpressionContext *ctx) override;
    void exitShiftExpression(C_parser::C_grammarParser::ShiftExpressionContext *ctx) override;
    void exitEqualityExpression(C_parser::C_grammarParser::EqualityExpressionContext *ctx) override;
    void exitRelationalExpression(C_parser::C_grammarParser::RelationalExpressionContext *ctx) override;
    void exitInclusiveOrExpression(C_parser::C_grammarParser::InclusiveOrExpressionContext *ctx) override;
    void exitExclusiveOrExpression(C_parser::C_grammarParser::ExclusiveOrExpressionContext *ctx) override;
    void exitAndExpression(C_parser::C_grammarParser::AndExpressionContext *ctx) override;
    void exitLogicalOrExpression(C_parser::C_grammarParser::LogicalOrExpressionContext *ctx) override;
    void exitLogicalAndExpression(C_parser::C_grammarParser::LogicalAndExpressionContext *ctx) override;
    void exitAssignmentExpression(C_parser::C_grammarParser::AssignmentExpressionContext *ctx) override;
    void exitArgumentExpression(C_parser::C_grammarParser::ArgumentExpressionContext *ctx) override;

    void exitStatement(C_parser::C_grammarParser::StatementContext *ctx) override;
    void exitFunctionCallExpression(C_parser::C_grammarParser::FunctionCallExpressionContext *ctx) override;

    void exitSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *ctx) override;
    void enterSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *ctx) override;
    void exitElseContent(C_parser::C_grammarParser::ElseContentContext *ctx) override;
    void exitIfContent(C_parser::C_grammarParser::IfContentContext *ctx) override;
    void exitConditionContent(C_parser::C_grammarParser::ConditionContentContext *ctx) override;
    void exitConditionalBlockItem(C_parser::C_grammarParser::ConditionalBlockItemContext *ctx) override;

    void exitForBlockItem(C_parser::C_grammarParser::ForBlockItemContext *ctx) override;
    void enterIterationStatement(C_parser::C_grammarParser::IterationStatementContext *ctx) override;
    void exitIterationStatement(C_parser::C_grammarParser::IterationStatementContext *ctx) override;
    void exitForIterationExpression(C_parser::C_grammarParser::ForIterationExpressionContext *ctx) override;
    void exitForExitCondition(C_parser::C_grammarParser::ForExitConditionContext *ctx) override;
    void exitForDeclaration(C_parser::C_grammarParser::ForDeclarationContext *ctx) override;
    void enterForContent(C_parser::C_grammarParser::ForContentContext *ctx) override;
    void exitForContent(C_parser::C_grammarParser::ForContentContext *ctx) override;
    void exitCompilationUnit(C_parser::C_grammarParser::CompilationUnitContext *ctx) override;

    void set_dma_specs(std::unordered_map<std::string, variable_class_t> ds) {dma_specs = std::move(ds);};
    std::shared_ptr<hl_ast_node> get_ast(){
        return root;
    };

private:
    FRIEND_TEST( cTreeVisitor, unaryExpressions);
    FRIEND_TEST( cTreeVisitor, multiplicativeExpressions);
    FRIEND_TEST( cTreeVisitor, additiveExpressions);
    FRIEND_TEST(cTreeVisitor, shiftExpressions);
    FRIEND_TEST(cTreeVisitor, relationalExpressions);
    FRIEND_TEST(cTreeVisitor, equalityExpressions);
    FRIEND_TEST(cTreeVisitor, exOrBinExpressions);
    FRIEND_TEST(cTreeVisitor, andBinExpressions);
    FRIEND_TEST(cTreeVisitor, orBinExpressions);
    FRIEND_TEST(cTreeVisitor, andLogExpressions);
    FRIEND_TEST(cTreeVisitor, orLogExpressions);
    FRIEND_TEST( cTreeVisitor, assignmentExpressions);
    FRIEND_TEST(cTreeVisitor, definition);
    FRIEND_TEST(cTreeVisitor, function_def);
    FRIEND_TEST(cTreeVisitor, function_call);
    FRIEND_TEST(cTreeVisitor, returnTest);

    template<typename T>
    void processExpression(unsigned int expression_size, const T& operands_array, std::map<std::string, expression_type_t> &expr_map);
    void save_current_block_context();
    std::string restore_current_block_context();

    std::vector<std::shared_ptr<hl_ast_node>> ext_decl;
    std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
    std::vector<std::shared_ptr<hl_ast_node>> functions;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;

    std::stack<std::shared_ptr<hl_ast_node>> expressions_stack;
    std::vector<std::shared_ptr<hl_ast_node>> argument_vector;
    std::vector<std::shared_ptr<hl_ast_node>> array_dimentions;

    std::unordered_map<std::string, std::vector<int>> array_shapes_map;

    std::shared_ptr<hl_function_def_node> current_function;

    std::shared_ptr<hl_ast_node> current_initializer;
    std::shared_ptr<hl_ast_node> current_block_item;

    std::shared_ptr<hl_ast_conditional_node> conditional;
    std::vector<std::shared_ptr<hl_ast_node>> conditional_body;


    std::shared_ptr<hl_ast_loop_node> loop;
    std::vector<std::shared_ptr<hl_ast_node>> loop_body;

    std::shared_ptr<hl_ast_node> root;

    std::stack<std::shared_ptr<hl_ast_node>> outer_block_nodes;
    std::stack<std::vector<std::shared_ptr<hl_ast_node>>> outer_block_contents;

    std::stack<std::shared_ptr<hl_ast_node>> outer_block_current_item;

    std::stack<std::string> outer_block_types;
    std::unordered_map<std::string, variable_class_t> dma_specs;

    bool in_function_declaration;
    bool in_function_body;
    bool in_array_declaration;
    bool in_array_access;
    bool in_foor_loop_block;
    bool in_conditional_block;
    bool in_initializer_list;

    std::vector<std::shared_ptr<hl_ast_node>> array_initializer_data;
    int initializer_array_level;
};

#endif //FCORE_TOOLCHAIN_C_TREE_VISITOR_HPP
