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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H

#include <string>
#include <fstream>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "schema_validator_base.h"

class emulator_schema_validator : public schema_validator_base {
    public:
        emulator_schema_validator();
};

class compiler_schema_validator : public schema_validator_base {
public:
    compiler_schema_validator();
};

class assembler_schema_validator : public schema_validator_base {
public:
    assembler_schema_validator();
};
#endif //FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H
