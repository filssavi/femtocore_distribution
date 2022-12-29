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

#ifndef FCORE_TOOLCHAIN_AST_NODE_BASE_HPP
#define FCORE_TOOLCHAIN_AST_NODE_BASE_HPP

#include <vector>
#include <memory>

template<class E>
class ast_node_base {
    public:


        // CONTENT MANIPULATION
        void add_content(const std::shared_ptr<E>& element);
        void set_content(const std::vector<std::shared_ptr<E>>& c);
        void prepend_content(const std::vector<std::shared_ptr<E>>& c);
        void append_content(const std::vector<std::shared_ptr<E>>& c);

        // CONTENT ACCESS
        bool has_content();
        std::vector<std::shared_ptr<E>> get_content();


protected:
    std::vector<std::shared_ptr<E>> content;
};




template<class E>
void ast_node_base<E>::add_content(const std::shared_ptr<E> &element) {
    content.push_back(element);
}

template<class E>
std::vector<std::shared_ptr<E>> ast_node_base<E>::get_content() {
    return content;
}

template<class E>
bool ast_node_base<E>::has_content() {
    return !content.empty();
}

template<class E>
void ast_node_base<E>::append_content(const std::vector<std::shared_ptr<E>> &c) {
    content.insert(content.end(), c.begin(), c.end());
}

template<class E>
void ast_node_base<E>::prepend_content(const std::vector<std::shared_ptr<E>> &c) {
    content.insert(content.begin(), c.begin(), c.end());
}

template<class E>
void ast_node_base<E>::set_content(const std::vector<std::shared_ptr<E>> &c) {
    content = c;
}


#endif //FCORE_TOOLCHAIN_AST_NODE_BASE_HPP
