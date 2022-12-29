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

#ifndef FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP
#define FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP

#include <string>

#include "ll_ast_node.hpp"

class ll_ast_pragma :public ll_ast_node{
public:
    ll_ast_pragma();
    explicit ll_ast_pragma(std::string directive);
    std::string get_directive();
    bool is_terminal() override;
    friend bool operator==(const ll_ast_pragma& lhs, const ll_ast_pragma& rhs);
    void print();
    nlohmann::json dump() override;
private:
    std::string directive;
};


#endif //FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP
