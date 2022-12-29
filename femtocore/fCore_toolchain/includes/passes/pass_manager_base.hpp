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

#ifndef FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
#define FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP

#include <memory>
#include <utility>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "pass_base.hpp"

#include <nlohmann/json.hpp>

template<class E>
class pass_manager_base {;
public:
    // API FOR MORPHING PASSES
    void add_morphing_pass(const std::shared_ptr<pass_base<E>>& pass);
    void add_morphing_pass_group(const std::vector<std::shared_ptr<pass_base<E>>>& group);
    void run_morphing_passes(std::shared_ptr<E> AST);
    virtual void run_morphing_pass(std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass) {};
    virtual std::vector<nlohmann::json> run_morphing_pass_group(std::shared_ptr<E> &subtree, const std::vector<std::shared_ptr<pass_base<E>>>& group, int dal) {return nlohmann::json();};

    std::vector<int> get_pass_order() { return pass_order;};
    void set_pass_order(std::vector<int> order) {pass_order = std::move(order);};

    nlohmann::json get_dump();

    std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<E>& AST);
    void analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass);
    std::unordered_map<std::string, std::shared_ptr<pass_base<E>>> analysis_passes;
protected:
    std::vector<std::shared_ptr<pass_base<E>>> morphing_passes = {};
    std::vector<int> pass_order;
    std::vector<std::vector<std::shared_ptr<pass_base<E>>>> morphing_passes_groups{};
    nlohmann::json pre_opt_dump;
    std::vector<nlohmann::json> in_opt_dump;
    nlohmann::json post_opt_dump;
    int dump_ast_level = 0;
};


template<class E>
void pass_manager_base<E>::add_morphing_pass(const std::shared_ptr<pass_base<E>>& pass) {
    morphing_passes.push_back(pass);
}


template<class E>
void pass_manager_base<E>::run_morphing_passes(std::shared_ptr<E> AST) {
    if(dump_ast_level>0) {
        pre_opt_dump = AST->dump();
    }
    for(auto& idx:pass_order){
        if(idx>=0){
            int pass_index = idx-1;
            std::shared_ptr<pass_base<E>> pass = morphing_passes[pass_index];
            run_morphing_pass(AST, pass);
            if(dump_ast_level>1){
                nlohmann::json ast_dump;
                ast_dump["pass_name"] = pass->get_name();
                ast_dump["ast"]= AST->dump();
                in_opt_dump.push_back(ast_dump);
            }

        } else {
            int pass_index = -idx -1;
            std::vector<nlohmann::json> result = run_morphing_pass_group(AST, morphing_passes_groups[pass_index], dump_ast_level);
            in_opt_dump.insert(in_opt_dump.end(), result.begin(), result.end());
        }

    }
    if(dump_ast_level>0)  post_opt_dump = AST->dump();
}

template<class E>
std::vector<std::vector<int>> pass_manager_base<E>::run_analysis_passes(const std::shared_ptr<E>& AST) {
    std::vector<std::vector<int>> results;
    for( auto& pass:morphing_passes){
        if(pass->get_pass_type() == ANALYSIS_PASS){
            analyze_tree(AST, pass);
            results.push_back(pass->get_analysis_result());
        }
    }
    return results;
}


template<class E>
void
pass_manager_base<E>::analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>> &pass) {
    for(auto &i : subtree->get_content()){
        analyze_tree(i,pass);
    }
    pass->analyze_element(subtree);
}

template<class E>
void pass_manager_base<E>::add_morphing_pass_group(const std::vector<std::shared_ptr<pass_base<E>>> &group) {
    morphing_passes_groups.push_back(group);
}

template<class E>
nlohmann::json pass_manager_base<E>::get_dump() {
    nlohmann::json retval;

    retval["pre-opt"] = pre_opt_dump;
    retval["in-opt"] = in_opt_dump;
    retval["post-opt"] = post_opt_dump;

    return retval;
}


#endif //FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
