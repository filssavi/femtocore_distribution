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

#ifndef FCORE_TOOLCHAIN_ARRAY_LINEARIZER_HPP
#define FCORE_TOOLCHAIN_ARRAY_LINEARIZER_HPP

#include <vector>
#include <cstdint>
#include <numeric>


int linearize_array(std::vector<int> shape, std::vector<int> indices);
std::vector<int> array_delinearize(const std::vector<int>& shape, int index);

#endif //FCORE_TOOLCHAIN_ARRAY_LINEARIZER_HPP
