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


#include "frontend/C/C_pre_processor.hpp"

#include <utility>

C_pre_processor::C_pre_processor(const std::string &path, std::shared_ptr<define_map> &defmap) {
    std::ifstream file(path);
    file_path = path;
    working_content = std::string((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    dmap = defmap;
}

std::string  C_pre_processor::get_preprocessed_file() {
    return working_content;
}

void C_pre_processor::process_file() {
    std::string line;
    std::string decommented_line;
    std::istringstream ss(working_content);
    std::ostringstream processed_file_ss;

    std::regex line_comment("\\/\\/.*");
    std::regex multiline_start("\\/\\*(.*)");
    std::regex multiline_stop("(.*)\\*\\/");

    bool in_muliline_comment = false;

    while (std::getline(ss,line)){
        bool skip_line = false;
        bool ignore_cond_1 = std::regex_match(line, line_comment);
        bool ignore_cond_2 = line.empty();
        bool contain_multiline_start = std::regex_search(line, multiline_start);
        bool contain_multiline_stop = std::regex_search(line, multiline_stop);
        if(contain_multiline_start & !contain_multiline_stop){
            in_muliline_comment = true;
            decommented_line =  std::regex_replace(line, std::regex(multiline_start), "");
        } else if(!contain_multiline_start & contain_multiline_stop){
            in_muliline_comment = false;
            decommented_line =  std::regex_replace(line, std::regex(multiline_stop), "");
        }else if(!(ignore_cond_1 | ignore_cond_2 | in_muliline_comment)){
            decommented_line= std::regex_replace(line, std::regex(R"(\/\*(.*)\*\/)"), "");
        }else if(ignore_cond_2 | ignore_cond_1 | in_muliline_comment){
            continue;
        }
        skip_line |= process_define(decommented_line);

        std::string rel_include_text = process_rel_includes(decommented_line);
        std::string abs_include_text = process_abs_includes(decommented_line);

        if(!rel_include_text.empty()){
            processed_file_ss << rel_include_text << std::endl;
        } else if(!abs_include_text.empty()){
            processed_file_ss << abs_include_text << std::endl;
        } else{
            if(!skip_line){
                processed_file_ss << line << std::endl;
            }
        }

    }
    working_content = processed_file_ss.str();
}

bool C_pre_processor::process_define(const std::string& line) {
    bool line_contains_str = false;
    std::regex define_regex(R"(#define\s+([A-Za-z0-9_]*)\s+(.*))");
    std::smatch match;
    if(std::regex_search( line,match,define_regex)){
        std::string name = match.str(1);
        std::string value = match.str(2);
        std::shared_ptr<define> def = std::make_shared<define>(0, name, value);
        dmap->insert(name, def);
        line_contains_str = true;
    }
    return line_contains_str;
}

std::string C_pre_processor::process_rel_includes(const std::string& line) {
    std::regex rel_include_regex(R"(#include\s*\"(.*)\")");
    std::smatch match;
    if(std::regex_search( line,match,rel_include_regex)){
        std::string target = match.str(1);
        if(!target.empty()){
            std::string target_path = std::filesystem::canonical("./" + target);
            C_pre_processor include_preproc(target_path, dmap);
            include_preproc.set_absolute_includes(allowed_absolute_includes);
            include_preproc.process_file();
            return include_preproc.get_preprocessed_file();
        }
    }
    return "";
}

std::string C_pre_processor::process_abs_includes(const std::string &line) {
    std::regex abs_include_regex(R"(#include\s*<(.*)>)");
    std::smatch match;
    if(std::regex_search( line,match,abs_include_regex)){
        std::string target = match.str(1);
        if(!target.empty()){
            if(std::find(allowed_absolute_includes.begin(), allowed_absolute_includes.end(), target) != allowed_absolute_includes.end()){
                //TODO: implement absolute includes
            } else {
                throw std::runtime_error("included file: " + target + " not supported");
            }
        }
    }
    return "";
}


void C_pre_processor::set_absolute_includes(std::vector<std::string> list) {
    allowed_absolute_includes = std::move(list);
}

void C_pre_processor::substitute_defines() {

    std::string line;
    std::istringstream ss(working_content);
    std::ostringstream processed_file_ss;



    while (std::getline(ss,line)){
        std::string new_line = line;
        for(auto &item:*dmap){
           new_line = substitute_defines_in_line(new_line, item);
        }
        processed_file_ss << new_line << std::endl;
    }

    working_content = processed_file_ss.str();

}

std::string C_pre_processor::substitute_defines_in_line(std::string &line, const std::pair<std::string, std::shared_ptr<define>>& item) {

    std::string operating_line;
    std::vector<std::smatch> false_positives = {};

    std::vector<unsigned int> positions;
    std::vector<unsigned int> lengths;
    std::regex define_regex(item.first);
    for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), define_regex);
    i != std::sregex_iterator(); ++i) {
        std::smatch m = *i;
        positions.push_back(m.position());
        lengths.push_back(m.length());
    }

    //USE POSITIONS AND LENGTHS
    unsigned int substring_start = 0;
    for(int i = 0; i<positions.size(); i++){
        std::string preceding_symbol = {line[positions[i]-1]};
        std::string following_symbol = {line[positions[i]+lengths[i]]};

        operating_line += line.substr(substring_start, positions[i]-substring_start);

        if(!(std::regex_match(preceding_symbol, std::regex("[a-zA-Z_]")) || std::regex_match(following_symbol, std::regex("[a-zA-Z_]"))) ){
            operating_line += item.second->get_content();
        } else{
            operating_line += item.first;
        }
        substring_start = positions[i]+lengths[i];
    }
    operating_line += line.substr(substring_start, line.size()-substring_start);
    return operating_line;
}
