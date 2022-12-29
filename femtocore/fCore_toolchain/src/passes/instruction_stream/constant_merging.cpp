// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//

#include "passes/instruction_stream/constant_merging.hpp"

#include <utility>

constant_merging::constant_merging(std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> lam) : stream_pass_base("constant merging pass"){
    delete_intercalated_const = false;
    assignments_map = std::move(lam);
    idx = 0;
}

std::shared_ptr<ll_instruction_node> constant_merging::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    map_exclusions(element);
    std::shared_ptr<ll_instruction_node> ret_val;
    switch (element->get_type()) {
        case isa_register_instruction:
            ret_val =  merge_register_inst(std::static_pointer_cast<ll_register_instr_node>(element));
            break;
        case isa_conversion_instruction:
            ret_val =  merge_conv_instr(std::static_pointer_cast<ll_conversion_instr_node>(element));
            break;
        case isa_independent_instruction:
            ret_val = element;
            break;
        case isa_intercalated_constant:
            ret_val =  merge_interc_const(std::static_pointer_cast<ll_intercalated_const_instr_node>(element));
            break;
        case isa_load_constant_instruction:
            ret_val =  merge_load_const_instr(std::static_pointer_cast<ll_load_constant_instr_node>(element));
            break;
        default:
            throw std::runtime_error("Invalid instruction type reached variable mapping stage");
    }

    idx++;
    return ret_val;

}

void constant_merging::map_exclusions(std::shared_ptr<ll_instruction_node> element) {
    std::shared_ptr<variable> dest;
    switch (element->get_type()) {
        case isa_register_instruction:
            dest = std::static_pointer_cast<ll_register_instr_node>(element)->get_destination();
            break;
        case isa_conversion_instruction:
            dest = std::static_pointer_cast<ll_conversion_instr_node>(element)->get_destination();
            break;
        case isa_load_constant_instruction:
            dest = std::static_pointer_cast<ll_load_constant_instr_node>(element)->get_destination();
            break;
        case isa_intercalated_constant:
        case isa_independent_instruction:
        case isa_pseudo_instruction:
            return;
    }
    if(processed_constants.contains(dest->get_identifier())){
        processed_constants.erase(dest->get_identifier());
    }

}

std::shared_ptr<ll_instruction_node> constant_merging::merge_register_inst(const std::shared_ptr<ll_register_instr_node> &instr) {
    std::vector<std::shared_ptr<variable>> new_args;
    if(is_last_io_assignment(instr->get_destination())){
        return instr;
    }

    auto op = instr->get_operand_a();
    if(op->is_constant() || processed_constants.contains(op->get_identifier())){
        new_args.push_back(get_merged_constant(op));
    } else{
        new_args.push_back(op);
    }

    op = instr->get_operand_b();
    if(instr->get_operand_b()->is_constant() || processed_constants.contains(op->get_identifier())){
       new_args.push_back(get_merged_constant(op));
    } else{
       new_args.push_back(op);
    }
    new_args.push_back(instr->get_destination());
    instr->set_arguments(new_args);
    return instr;
}

std::shared_ptr<ll_instruction_node> constant_merging::merge_conv_instr(const std::shared_ptr<ll_conversion_instr_node> &instr) {
    std::vector<std::shared_ptr<variable>> new_args;
    if(is_last_io_assignment(instr->get_destination())){
        return instr;
    }

    auto op = instr->get_source();
    if(op->is_constant() || processed_constants.contains(op->get_identifier())){
        new_args.push_back(get_merged_constant(op));
    } else{
        new_args.push_back(op);
    }
    new_args.push_back(instr->get_destination());
    instr->set_arguments(new_args);
    return instr;
}

std::shared_ptr<ll_instruction_node> constant_merging::merge_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node> &instr) {
    std::shared_ptr<ll_instruction_node> ret;
    if(is_last_io_assignment(instr->get_destination())){
        return instr;
    }

    if(instr->is_float()){
        if(float_const_map.contains(instr->get_constant_f())){
            ret = nullptr;
            reassignments_map[instr->get_destination()->get_identifier()] = float_const_map[instr->get_constant_f()];
            delete_intercalated_const = true;
        } else {
            float_const_map[instr->get_constant_f()] = instr->get_destination();
            reassignments_map[instr->get_destination()->get_identifier()] = instr->get_destination();
            ret = instr;
        }
    } else{
        if(int_const_map.contains(instr->get_constant_i())){
            ret = nullptr;
            reassignments_map[instr->get_destination()->get_identifier()] = int_const_map[instr->get_constant_i()];
            delete_intercalated_const = true;
        } else {
            int_const_map[instr->get_constant_i()] = instr->get_destination();
            reassignments_map[instr->get_destination()->get_identifier()] = instr->get_destination();
            ret = instr;
        }
    }
    processed_constants.insert(instr->get_destination()->get_identifier());
    return ret;
}

std::shared_ptr<ll_instruction_node>
constant_merging::merge_interc_const(const std::shared_ptr<ll_intercalated_const_instr_node> &instr) {
    if(!delete_intercalated_const){
        return instr;
    } else {
        delete_intercalated_const = false;
        return nullptr;
    }

}

std::shared_ptr<variable> constant_merging::get_merged_constant(std::shared_ptr<variable> v) {
    auto var_name = v->get_identifier();
    if(!processed_constants.contains(var_name)){
        return v;
    }
    if(reassignments_map.contains(var_name)){
        auto reass = reassignments_map[var_name];
        return reassignments_map[var_name];
    }
    if(v->is_float()) {
        return float_const_map[v->get_const_f()];
    } else{
        return int_const_map[v->get_const_i()];
    }

}

bool constant_merging::is_last_io_assignment(const std::shared_ptr<variable> &dest) {
    if(dest->get_variable_class() == variable_output_type || dest->get_variable_class() == variable_memory_type){
        if(assignments_map->contains(dest->get_identifier())){
            auto last_assignment_idx = assignments_map->at(dest->get_identifier()).second;
            if( last_assignment_idx== idx || last_assignment_idx == -1){
                return true;
            }
        }
    }
    return false;
}
