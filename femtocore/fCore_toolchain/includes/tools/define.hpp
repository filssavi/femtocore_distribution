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

#ifndef FCORE_TOOLCHAIN_DEFINE_HPP
#define FCORE_TOOLCHAIN_DEFINE_HPP

#include <string>
#include <utility>

class define {
public:
    define(int l, std::string n, std::string c);
    std::string get_content() {return content;};
    friend bool operator==(const define& lhs, const define& rhs);
private:
    int line;
    std::string name;
    std::string content;
};


#endif //FCORE_TOOLCHAIN_DEFINE_HPP
