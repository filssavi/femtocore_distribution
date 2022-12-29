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

#include "data_structures/instruction_stream.hpp"

void instruction_stream::push_back(const std::shared_ptr<ll_instruction_node>& item) {
 stream_store.push_back(item);
}

void instruction_stream::push_back(const instruction_stream &stream_in) {
    stream_store.insert(stream_store.end(), stream_in.begin(), stream_in.end());
}

bool instruction_stream::empty(instruction_stream &store) {
    return store.empty();
}

unsigned long instruction_stream::size(instruction_stream &store) {
    return store.size();
}

bool instruction_stream::empty() {
    return stream_store.empty();
}

unsigned long instruction_stream::size() {
    return stream_store.size();
}

bool operator==(const instruction_stream &lhs, const instruction_stream &rhs) {
    bool retval = true;

    if(lhs.stream_store.size() != rhs.stream_store.size()){
        retval = false;
    } else{
        for(unsigned long i = 0; i<lhs.stream_store.size();++i){
            retval &= ll_instruction_node::compare_content_by_type(lhs.stream_store[i],rhs.stream_store[i]);
        }
    }
    return retval;
}

nlohmann::json instruction_stream::dump() {
    nlohmann::json retval;
    std::vector<nlohmann::json> stream;
    for(const auto &i:stream_store){
        stream.push_back(ll_instruction_node::dump_instruction_by_type(i));
    }
    retval["type"] = "stream_ast";
    retval["content"] = stream;
    return retval;
}


