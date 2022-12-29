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

#ifndef FCORE_TOOLCHAIN_FUNCTION_MAPPING_HPP
#define FCORE_TOOLCHAIN_FUNCTION_MAPPING_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

class function_mapping : public pass_base<hl_ast_node> {
    public:
        function_mapping();
        std::vector<std::shared_ptr<hl_ast_node>>process_node(std::shared_ptr<hl_ast_node> element) override;
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> get_map_ref ();
        int get_pass_type() override { return NODE_PASS;};
    protected:
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> functions_map;
};



#endif //FCORE_TOOLCHAIN_FUNCTION_MAPPING_HPP
