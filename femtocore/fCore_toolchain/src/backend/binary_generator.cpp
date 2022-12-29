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

#include "backend/binary_generator.hpp"

void binary_generator::process_stream(
        const instruction_stream& stream,
        const std::unordered_map<std::string, std::vector<int>>& dma_map,
        const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& allocation_map,
        bool debug_print
) {
    auto code_sect = std::vector<uint32_t>();
    for(const auto& item:stream){
        code_sect.push_back(item->emit());
        progress_counter++;
        if(debug_print) {
            std::cout << progress_counter << std::endl;
            item->print();
        }
    }
    ex.add_code_section(code_sect);

    auto io_mapping = std::set<std::pair<uint16_t, uint16_t>>();
    for(const auto& item:dma_map){
        if(item.second.size() == 1){
            if(allocation_map->contains(item.first)){
                for(auto &allocated_item:allocation_map->at(item.first)){
                    if(allocated_item.second != -1){
                        uint16_t core_reg = allocated_item.first;
                        uint16_t dma_reg = item.second[allocated_item.second];
                        io_mapping.emplace(dma_reg,core_reg);
                    } else {
                        uint16_t core_reg = allocated_item.first;
                        uint16_t dma_reg = item.second[0];
                        io_mapping.emplace(dma_reg,core_reg);
                    }
                }

            }
        } else{
            for(int i = 0; i< item.second.size(); i++){
                auto identifier = item.first+"_"+std::to_string(i);
                if(allocation_map->contains(identifier)){
                    for(auto &allocated_item:allocation_map->at(identifier)){
                        uint16_t core_reg = allocated_item.first;
                        uint16_t dma_reg = item.second[i];
                        io_mapping.emplace(dma_reg,core_reg);
                    }
                }
            }
        }

    }
    ex.add_io_mapping(io_mapping);
    ex.generate_metadata();
}

void binary_generator::process_stream(const instruction_stream &stream, bool debug_print) {
    auto dma_map = std::unordered_map<std::string, std::vector<int>>();
    auto am = std::make_shared<std::unordered_map<std::string, std::vector<std::pair<int, int>>>>();
    process_stream(stream, dma_map, am, debug_print);
}


void binary_generator::write_hex_file(const std::string& filename) {
    std::ofstream output(filename, std::ios::binary | std::ios::out);
    auto executable_vect = ex.get_executable();
    for(auto &it:executable_vect){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void binary_generator::write_mem_file(const std::string& filename) {
    std::ofstream output(filename);
    auto executable_vect = ex.get_executable();
    for(auto &it:executable_vect){
        output<<std::hex<<it<<std::endl;
    }
}


std::vector<uint32_t> binary_generator::generate_hex(bool endian_swap) {
    std::vector<uint32_t> ret;
    auto executable_vect = ex.get_executable();
    for(auto &it:executable_vect){
        if(endian_swap) ret.push_back(Reverse32(it));
        else ret.push_back(it);
    }
    return ret;
}

std::vector<std::string> binary_generator::generate_mem() {
    std::vector<std::string> ret;
    auto executable_vect = ex.get_executable();
    for(auto &it:executable_vect){
        std::stringstream stream;
        stream << std::hex << it;
        ret.push_back(stream.str());
    }
    return ret;
}

std::vector<uint32_t> binary_generator::get_executable() {
    return ex.get_executable();
}


uint32_t binary_generator::get_program_size() {
    return ex.get_executable().size();
}

std::vector<uint32_t> binary_generator::get_code() {
    return ex.get_code();
}

