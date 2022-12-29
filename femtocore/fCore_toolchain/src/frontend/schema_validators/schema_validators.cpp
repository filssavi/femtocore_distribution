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


#include "frontend/schema_validators/schema_validators.h"

emulator_schema_validator::emulator_schema_validator() : schema_validator_base("emulator_spec_schema.json","Emulator"){
}

compiler_schema_validator::compiler_schema_validator() : schema_validator_base("compiler_spec_schema.json","Compiler"){
}
