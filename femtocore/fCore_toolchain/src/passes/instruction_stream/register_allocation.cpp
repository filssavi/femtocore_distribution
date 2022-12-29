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

#include "passes/instruction_stream/register_allocation.hpp"


register_allocation::register_allocation(
        std::shared_ptr<variable_map> vmap,
        std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &ebm,
        const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
        ) : stream_pass_base("register allocation") {

    allocation_map = all_map;
    var_map = std::move(vmap);

    int n_regs = 2<<(fcore_register_address_width-1);
    //pre_initialize the registers statuses, excluding form allocation pool the registers explicitly by the user
    excluded.reserve(n_regs);
    for(int i = 0; i< n_regs; ++i) {
        excluded.push_back(var_map->at("r"+std::to_string(i))->is_used());
    }


    excluded[0] = true;
}

void register_allocation::setup() {
    int memory_idx = 0;
    int inputs_idx = 1;

    int n_regs = 2 << (fcore_register_address_width - 1);

    for(auto &item: *var_map) {
        auto vc = item.second->get_variable_class();
        if (vc == variable_memory_type) {
            if (!excluded[n_regs - 1 - memory_idx]) {
                memory_vars[item.first] = n_regs - memory_idx - 1;
                excluded[n_regs - memory_idx - 1] = true;
            }
            memory_idx++;
        } else if (vc == variable_input_type) {
            if(!allocation_map->contains(item.first)){
                if((item.second->get_type() == var_type_array) && item.second->is_contiguous()){

                    allocate_array(item.second, inputs_idx);
                    inputs_idx += item.second->get_size();
                } else {
                    allocate_register(item.second, inputs_idx);
                    inputs_idx++;
                }
            }
        }
    }
}



std::shared_ptr<ll_instruction_node> register_allocation::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    std::shared_ptr<ll_instruction_node> ret_val = element;

    auto arguments = element->get_arguments();
    for(auto &item:arguments){
        std::regex re("r(\\d\\d?)");
        std::smatch m;
        std::string var_name = item->to_str();
        std::regex_match(var_name, m, re);

        auto bound_reg = item->get_bound_reg();

        if(bound_reg != -1){
            reg_map.add_bound_identifier(item, bound_reg);
            item = reg_map.get_identifier(item);
        } else if (memory_vars.contains(item->get_linear_identifier())) {
            allocate_register(item, memory_vars[item->get_linear_identifier()]);
            item = reg_map.get_identifier(item);
        } else{
            if(reg_map.is_allocated(item)){
                item = reg_map.get_identifier(item);
            }else if(m.empty() && !item->is_constant()){
                bool found = false;
                for(int i = 0; i<pow(2, fcore_register_address_width);i++){
                    if(!item->get_array_shape().empty() && item->is_contiguous()){
                        if(!reg_map.is_used({i,item->get_size()}, item->get_first_occurrence(), item->get_last_occurrence()) & !excluded[i]){
                            found = true;
                            allocate_array(item, i);
                            item = reg_map.get_identifier(item);
                            break;
                        }
                    } else{
                        if(!reg_map.is_used(i, item->get_first_occurrence(), item->get_last_occurrence()) & !excluded[i]){
                            found = true;
                            allocate_register(item, i);
                            item = reg_map.get_identifier(item);
                            break;
                        }
                    }
                }
                if(!found){
                    std::cout<<"ERROR: The register assignment phase run out of registers with variables still to assign."<< std::endl;
                    exit(-1);
                }
            }
        }
    }
    ret_val->set_arguments(arguments);
    ret_val = element;

    return ret_val;
}

void register_allocation::allocate_register(std::shared_ptr<variable> &var, int reg_addr) {
    reg_map.insert(var, reg_addr, var->get_first_occurrence(), var->get_last_occurrence());
    auto lin_identifier = var->get_linear_identifier();
    if(allocation_map->contains(lin_identifier)){
        allocation_map->at(lin_identifier).emplace_back(reg_addr, var->get_linear_index());
    } else {
        auto item = std::vector<std::pair<int, int>>();
        item.emplace_back(reg_addr, var->get_linear_index());
        allocation_map->emplace(lin_identifier, item);
    }
    if(var->get_variable_class() == variable_output_type){
        excluded[reg_addr] = true;
    }
}

void register_allocation::allocate_array(std::shared_ptr<variable> &var, int reg_addr) {

    std::pair<int, int> reg_pair = {reg_addr, var->get_size()};
    reg_map.insert(var, reg_pair, var->get_first_occurrence(), var->get_last_occurrence());
    allocated_contiguous_arrays[var->get_name()] = {reg_addr, reg_addr+var->get_size()-1};

    for(int i=0; i<var->get_size(); i++){

        auto lin_identifier = var->get_linear_identifier(i);

        if(allocation_map->contains(lin_identifier)){
            allocation_map->at(lin_identifier).emplace_back(reg_addr+i, i);
        } else {
            auto item = std::vector<std::pair<int, int>>();
            item.emplace_back(reg_addr+i, i);
            allocation_map->emplace(lin_identifier, item);
        }

    }
    for(int i=0; i<var->get_size(); i++){
        if(var->get_variable_class() == variable_output_type){
            excluded[reg_addr+i] = true;
        }
    }

}

