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

#ifndef FCORE_TOOLCHAIN_DEFINE_MAP_HPP
#define FCORE_TOOLCHAIN_DEFINE_MAP_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>

#include "tools/define.hpp"

class define_map {
public:

    std::shared_ptr<define> operator[](const std::string& key);
    std::shared_ptr<define> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<define>item);
    unsigned int count(const std::string& key);

    unsigned int size() {return defines.size();};
    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> begin() {return defines.begin();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> begin() const { return defines.begin();}
    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> end() {return defines.end();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> end() const { return defines.end();}

private:
    std::unordered_map<std::string, std::shared_ptr<define>> defines;
};


#endif //FCORE_TOOLCHAIN_DEFINE_MAP_HPP
