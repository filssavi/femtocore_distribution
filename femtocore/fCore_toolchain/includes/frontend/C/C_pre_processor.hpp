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

#ifndef FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP
#define FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP

#include <istream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>

#include "data_structures/common/variable.hpp"
#include "tools/define.hpp"
#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"

class C_pre_processor {
public:
    explicit C_pre_processor(const std::string &path,  std::shared_ptr<define_map> &defmap);
    std::string get_preprocessed_file();
    void set_absolute_includes(std::vector<std::string> list);
    void process_file();
    void substitute_defines();
    static std::string substitute_defines_in_line(std::string &line, const std::pair<std::string, std::shared_ptr<define>>& item);
private:

    std::string file_path;

    void process_pragmas(const std::string& line);
    bool process_define(const std::string& line);
    std::string process_rel_includes(const std::string& line);
    std::string process_abs_includes(const std::string& line);

    std::vector<std::string> allowed_absolute_includes = {};
    std::string working_content;
    std::shared_ptr<define_map> dmap;
};


#endif //FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP
