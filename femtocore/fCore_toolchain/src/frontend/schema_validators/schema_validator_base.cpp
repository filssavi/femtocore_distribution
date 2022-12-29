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


#include "frontend/schema_validators/schema_validator_base.h"

schema_validator_base::schema_validator_base(const std::string& schema_file, std::string validator_name) {
    std::string schemas_path = SCHEMAS_FOLDER;
    std::string full_schema_path = schemas_path  + "/" + schema_file;
    std::ifstream ifs(full_schema_path);
    schema = nlohmann::json::parse(ifs);
    schema_name = std::move(validator_name);

}


void schema_validator_base::validate(nlohmann::json &spec_file) {

    nlohmann::json_schema::json_validator validator;
    validator.set_root_schema(schema);
    validator.validate(spec_file, err);
    if(err){
        std::basic_string<char> err_loc = "/";
        if(!err.error_ptr.to_string().empty()){
            err_loc = err.error_ptr.to_string();
        }

        std::string err_msg = schema_name + " specification file error:\n\tError location: " + err_loc + "\n\t" +"Error message: "+err.error_message;
        spdlog::critical(err_msg);
        throw std::invalid_argument(err_msg);
    }
}
