//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include "frontend/emulator_manager.hpp"

TEST(Emulator, emulator_executable_format) {

std::ifstream ifs("emu/test_exec_format.json");
nlohmann::json specs = nlohmann::json::parse(ifs);
emulator_manager manager(specs);
manager.emulate();
auto res_obj = nlohmann::json::parse(manager.get_results());

auto s = res_obj.dump();

std::vector<float>  result = std::vector<float>(res_obj["test"]["outputs"]["test_out"][0]);
std::vector<float> reference = {58.62, 61.6};
for(int i = 0; i<result.size(); ++i){
    ASSERT_FLOAT_EQ(result[i], reference[i]);
}

}
