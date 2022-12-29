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

#include "frontend/C/C_ErrorHandling.hpp"

void C_ErrorHandling::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                                size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
    throw std::runtime_error(msg);
}

void C_ErrorHandling::reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                    size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts,
                                    antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void
C_ErrorHandling::reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                           size_t stopIndex, const antlrcpp::BitSet &conflictingAlts,
                                           antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void C_ErrorHandling::reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                             size_t stopIndex, size_t prediction, antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}
