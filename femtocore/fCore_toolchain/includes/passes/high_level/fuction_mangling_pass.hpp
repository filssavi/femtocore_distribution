// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//

#ifndef FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H
#define FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"


class fuction_mangling_pass  : public pass_base<hl_ast_node>{
public:
    fuction_mangling_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::shared_ptr<hl_ast_node> mangle_node(const std::shared_ptr<hl_ast_node>& node, const std::string &function);
    std::shared_ptr<hl_expression_node> mangle_node(std::shared_ptr<hl_expression_node> node, const std::string& function);
    std::shared_ptr<hl_ast_conditional_node> mangle_node(std::shared_ptr<hl_ast_conditional_node> node, const std::string& function);
    std::shared_ptr<hl_function_call_node> mangle_node(const std::shared_ptr<hl_function_call_node>& node, const std::string& function);
    std::shared_ptr<hl_definition_node> mangle_node(const std::shared_ptr<hl_definition_node>& node, const std::string& function);
    std::shared_ptr<hl_ast_loop_node> mangle_node(std::shared_ptr<hl_ast_loop_node> node, const std::string& function);
    std::shared_ptr<hl_ast_operand> mangle_node(const std::shared_ptr<hl_ast_operand>& node, const std::string& function);
    std::vector<std::shared_ptr<hl_ast_node>> mangle_vector(const std::vector<std::shared_ptr<hl_ast_node>> &v, const std::string& function);
    std::shared_ptr<variable> mangle_variable(const std::shared_ptr<variable> &v, const std::string &function);
    std::string mangle_string(const std::string& s, const std::string& function);
};


#endif //FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H
