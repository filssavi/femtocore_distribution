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

#include "dev_server/rest_handler.hpp"


void rest_handler::handle_get(const web::http::http_request& message) {

    auto ep = message.relative_uri().path();
    auto body = get_request_body(message);

    if(ep == "/dump"){
        message.reply(construct_response(web::http::status_codes::OK,to_string(dump)));
    } else {
        message.reply(construct_response(web::http::status_codes::InternalError,"Endpoint not found"));
    }

}

void rest_handler::handle_post(const web::http::http_request& message) {

    auto ep = message.relative_uri().path();
    auto body = get_request_body(message);

    std::string error = "Endpoint not found";
    web::http::status_code ret_code = web::http::status_codes::InternalError;
    if(ep == "/compile"){
        ret_code = handle_compile_request(body, error);
    }

    message.reply(construct_response(ret_code,error));
}

web::http::status_code rest_handler::handle_compile_request(const web::json::value &prog, std::string &error) {


    std::string working_source = prog.at("path").as_string();
    std::string current_path = std::filesystem::current_path();
    chdir(std::filesystem::path(working_source).parent_path().c_str());
    std::vector<std::string> include_files = {""};

    std::string working_spec = prog.at("spec").as_string();
    nlohmann::json spec;
    if(!working_spec.empty()) {
        try {
            spec = get_specs(working_spec);
        } catch (std::exception &e) {
            return web::http::status_codes::InternalError;
        }
    }


    fcore_cc cc_engine(working_source, include_files, false, 2);
    if(spec.contains("dma_io")){
        cc_engine.set_dma_map(spec["dma_io"]);
    }
    cc_engine.compile();
    error = cc_engine.get_errors();
    dump = cc_engine.get_dump();
    chdir(current_path.c_str());
    if(error.empty()){
        return web::http::status_codes::OK;
    }else{
        return web::http::status_codes::InternalError;
    }

}

web::json::value rest_handler::get_request_body(const web::http::http_request& message) {
    web::json::value jsonObject;
    try{
        message.extract_json()
                .then([&jsonObject](const web::json::value& jo){
                    jsonObject = jo;
                })
                .wait();
    }
    catch (const std::exception & e) {
        printf("Error exception:%s\n", e.what());
    }
    return jsonObject;
}

web::http::http_response rest_handler::construct_response(const web::http::status_code &sc, const std::string &resp) {
    web::http::http_response response(sc);
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.set_body(resp);
    return response;
}

void rest_handler::handle_option(const web::http::http_request &message) {
    web::http::http_response sp(web::http::status_codes::OK);
    sp.headers().add("Access-Control-Allow-Origin","*");
    sp.headers().add("Access-Control-Allow-Methods","*");
    sp.headers().add("Access-Control-Allow-Headers","*");
    sp.headers().add("Access-Control-Max-Age","6400");
    message.reply(sp);
}

nlohmann::json rest_handler::get_specs(const std::string &path) {
    std::ifstream ifs(path);
    nlohmann::json spec = nlohmann::json::parse(ifs);
    try{
        compiler_schema_validator validator;
        validator.validate(spec);
    } catch(std::invalid_argument &ex){
        throw std::runtime_error("");
    }
    return spec;
}

