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

#ifndef FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
#define FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"

class stream_pass_base {
public:
    explicit stream_pass_base(std::string n) {name = std::move(n);};

    virtual void setup() {};
    virtual std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) {
        return element;
    };
    std::string get_name() {return name;};
private:
    std::string name;
};

#endif //FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
