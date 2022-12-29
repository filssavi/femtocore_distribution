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
// limitations under the License.29/06/2021.
//

#include "tools/array_linearizer.hpp"

int linearize_array(std::vector<int> shape, std::vector<int> indices){

    int linearized_idx = indices.back();
    for(int i = indices.size()-2; i>=0; --i){
        int interm_factor = 1;
        for(int j = shape.size()-1; j>i; --j){
            interm_factor *= indices[i]*shape[j];
        }
        linearized_idx += interm_factor;
    }
    return linearized_idx;
}



std::vector<int> array_delinearize(const std::vector<int>& shape, int index){
    std::vector<int> multidim_index;

    if(shape.size()==1) return {index};

    std::vector<int>strides;
    for(int i = 1; i<shape.size(); ++i){
        strides.push_back(std::accumulate(shape.begin()+i, shape.end(), 1,  std::multiplies<>()));
    }

    multidim_index.push_back(index/strides[0]);
    for(int i = 1; i<strides.size(); ++i){
        multidim_index.push_back(index/strides[i]%shape[i]);
    }
    multidim_index.push_back(index%shape.back());

    return multidim_index;
}