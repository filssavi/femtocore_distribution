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

#ifndef FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP
#define FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP

#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <utility>
#include <regex>
#include <gtest/gtest_prod.h>

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "C_Tree_visitor.hpp"
#include "C_ErrorHandling.hpp"
#include "C_pre_processor.hpp"

#include "antlr4-runtime.h"
#include "C_parser/C_grammarLexer.h"
#include "C_parser/C_grammarParser.h"


class C_language_parser{
    public:
    explicit C_language_parser();
    C_language_parser(const std::string &path, std::shared_ptr<define_map> &new_defmap);

    void pre_process(const std::vector<std::string> &abs_includes);
    void parse(std::unordered_map<std::string, variable_class_t> dma_specs);
    std::shared_ptr<hl_ast_node> AST;
    std::string error;

    private:

    C_Tree_visitor visitor;


    std::unique_ptr<C_pre_processor> preproc;
    std::shared_ptr<define_map> dmap;
    // preprocessor test
    FRIEND_TEST( cFrontend, preprocessor_include);
    FRIEND_TEST( cFrontend, preprocessor_pragma);
    // tree visitor test
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

    std::string preprocessed_content;
};


#endif //FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP
