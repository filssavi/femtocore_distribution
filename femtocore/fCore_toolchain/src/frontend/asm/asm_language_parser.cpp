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

#include "frontend/asm/asm_language_parser.hpp"



using namespace antlr4;


asm_language_parser::asm_language_parser(std::istream &stream) {
    variable_map varmap;

    construct_parser(stream, std::make_shared<variable_map>(varmap));
}

asm_language_parser::asm_language_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap) {

    construct_parser(stream, std::move(existing_varmap));
}

void asm_language_parser::construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap){


    ANTLRInputStream input(stream);
    asm_parser::asm_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    asm_parser::asm_grammarParser parser(&tokens);
    AsmErrorHandling handler;
    parser.addErrorListener(&handler);
    tree::ParseTree *Tree = parser.program();
    AsmTree_visitor visitor(std::move(existing_varmap));
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_program();

}