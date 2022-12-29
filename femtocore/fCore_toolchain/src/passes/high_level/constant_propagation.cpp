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
//

#include "passes/high_level/constant_propagation.hpp"

constant_propagation::constant_propagation() : pass_base<hl_ast_node>("Constant Propagation Pass"){
}

std::shared_ptr<hl_ast_node> constant_propagation::process_global(std::shared_ptr<hl_ast_node> element) {

    tracker.clear();

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
    int instr_idx = 0;

    for(auto & i : content){
        bool const_found = map_constants(i, instr_idx);
        if(!const_found) {
            new_content.push_back(i);
            instr_idx++;
       } else {
            if(i->node_type == hl_ast_node_type_definition){
                auto def_class = std::static_pointer_cast<hl_definition_node>(i)->get_variable()->get_variable_class();
                if( def_class == variable_memory_type || def_class == variable_output_type){
                    new_content.push_back(i);
                    instr_idx++;
                }
            }
        }
    }

    content.clear();
    content.reserve(new_content.size());

    for(int i = 0; i<new_content.size(); ++i){
        auto new_item = propagate_constant(new_content[i],i);
        content.push_back(new_item);
    }
    new_content.clear();
    new_content.reserve(content.size());

    for(auto &item:content){
        new_content.push_back(purge_definition(item));
    }

    element->set_content(new_content);

    return element;

}

std::shared_ptr<hl_ast_node> constant_propagation::purge_definition(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type==hl_ast_node_type_definition){
        auto def = std::static_pointer_cast<hl_definition_node>(element);
        if(def->is_scalar()){
            if(tracker.needs_purging(def->get_name(), {0})){
                def->set_array_initializer({});
            }
        }else {
            bool array_needs_purging = true;
            auto init_list = def->get_array_initializer();
            for(int i = 0; i<init_list.size(); ++i){
                array_needs_purging &= tracker.needs_purging(def->get_name(), {i});
            }
            if(array_needs_purging){
                def->set_array_initializer({});
            }
        }

    }
    return element;
}


std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_ast_node> element, int instr_idx) {

    if(element->node_type == hl_ast_node_type_expr){
        return propagate_constant(std::static_pointer_cast<hl_expression_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_definition){
        return propagate_constant(std::static_pointer_cast<hl_definition_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_operand){
        return propagate_constant(std::static_pointer_cast<hl_ast_operand>(element), instr_idx);
    } else{
        return element;
    }
}

std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_expression_node> element, int instr_idx) {
    if(element->is_immediate()){
        return element;
    }

    std::shared_ptr<hl_ast_node> new_rhs;

    if(element->get_rhs()->node_type == hl_ast_node_type_operand) {
        new_rhs = propagate_constant(std::static_pointer_cast<hl_ast_operand>(element->get_rhs()), instr_idx);
    } else {
        new_rhs = propagate_constant(element->get_rhs(), instr_idx);
    }
    element->set_rhs(new_rhs);

    if(!element->is_unary()){
        if(element->get_type() != expr_assign){
            std::shared_ptr<hl_ast_node> new_lhs;
            if(element->get_lhs()->node_type == hl_ast_node_type_operand) {
                std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
                new_lhs = propagate_constant(lhs, instr_idx);
            } else {
                new_lhs = propagate_constant(element->get_lhs(), instr_idx);
            }
            element->set_lhs(new_lhs);
        } else{
            auto lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
            std::vector<std::shared_ptr<hl_ast_node>> new_idx;
            for (auto &item: lhs->get_array_index()) {
                new_idx.push_back(propagate_constant(item, instr_idx));
            }
            lhs->set_array_index(new_idx);
        }


    }
    return element;
}

std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_definition_node> element, int instr_idx) {
    if(element->is_initialized()){
        std::shared_ptr<hl_ast_node> initializer = element->get_scalar_initializer();
        //TODO: CHECK if this if is actually needed, as it smells of bug
        if(initializer->node_type != hl_ast_node_type_operand){
            std::shared_ptr<hl_ast_node> new_init = propagate_constant(initializer, instr_idx);
            element->set_scalar_initializer(new_init);
        }
    }
    return element;
}

std::shared_ptr<hl_ast_operand> constant_propagation::propagate_constant(std::shared_ptr<hl_ast_operand> element, int instr_idx) {

    std::shared_ptr<hl_ast_operand> ret_operand;

    if(element->get_type() != var_type_int_const && element->get_type() != var_type_float_const){
        if(element->get_type()==var_type_array){
            std::vector<std::shared_ptr<hl_ast_node>> new_idx;
            for (auto &item: element->get_array_index()) {
                new_idx.push_back(propagate_constant(item, instr_idx));
            }
            element->set_array_index(new_idx);
            ret_operand = element;
            std::vector<int> indices = get_index_array(element);
            if(!indices.empty()){
                if(tracker.is_constant(element->get_name(), instr_idx, indices)){

                    std::shared_ptr<hl_ast_operand> new_const = tracker.get_constant(element->get_name(), instr_idx,
                                                                                     indices);
                    new_const->get_variable()->set_variable_class(element->get_variable()->get_variable_class());
                    std::string var_name = element->get_name();
                    for(auto &item:indices){
                        var_name += "_" + std::to_string(item);
                    }
                    new_const->set_name(var_name);
                    ret_operand =  new_const;
                }
            }


        } else{
            if(tracker.is_constant(element->get_name(), instr_idx , {0})){
                std::shared_ptr<hl_ast_operand> new_const = tracker.get_constant(element->get_name(), instr_idx, {0});
                new_const->set_name(element->get_name());
                new_const->get_variable()->set_variable_class(element->get_variable()->get_variable_class());
                ret_operand =  new_const;
            } else{
                ret_operand =  element;
            }
        }

    } else{
        ret_operand =  element;
    }

    if(element->get_variable()->get_bound_reg() != -1){
        ret_operand->get_variable()->set_bound_reg(element->get_variable()->get_bound_reg());
    }
    return ret_operand;
}

bool constant_propagation::map_constants(const std::shared_ptr<hl_ast_node>& element, int instr_idx) {

    if(element->node_type == hl_ast_node_type_definition) {
        return map_constants(std::static_pointer_cast<hl_definition_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_expr){
        return map_constants(std::static_pointer_cast<hl_expression_node>(element), instr_idx);
    } else
        return false;

}

bool constant_propagation::map_constants(const std::shared_ptr<hl_definition_node>& element, int instr_idx) {
    if (
        element->get_variable()->get_variable_class() != variable_input_type &&
        element->is_initialized() &&
        element->get_scalar_initializer()->node_type == hl_ast_node_type_operand
    ) {
        if(element->is_scalar()){
            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element->get_scalar_initializer());
            if (op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                tracker.add_constant(element->get_name(), op, instr_idx, {0});
                return true;
            }
        } else {
            auto array_init = element->get_array_initializer();
            for(int i = 0; i<array_init.size(); i++){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(array_init[i]);
                if (op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                    tracker.add_constant(element->get_name(), op, instr_idx, {i});
                }
            }
            return true;
        }

    }

    return false;
}

bool constant_propagation::map_constants(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {


    if(element->get_type() == expr_assign){
        std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
        analyze_assignment(element, instr_idx);
        if(
            !lhs->get_contiguity()
        ){
            if(element->get_rhs()->node_type == hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element->get_rhs());
                std::shared_ptr<hl_ast_operand> target = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
                return map_constants(op, target, instr_idx);
            }
        }
    }
    return false;
}


bool constant_propagation::map_constants(const std::shared_ptr<hl_ast_operand> &op, const std::shared_ptr<hl_ast_operand> &target, int instr_idx) {
    if(op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
        if(target->is_scalar()){
            tracker.add_constant(target->get_name(), op, instr_idx, {0});
        } else {
            std::vector<int> indices = get_index_array(target);
            if(!indices.empty()){
                tracker.add_constant(target->get_name(), op, instr_idx, indices);
            }
        }
        auto var_class = target->get_variable()->get_variable_class();
        if( var_class!= variable_memory_type && var_class != variable_output_type){
            return true;
        } else {
            return false;
        }
    }
    return false;
}

std::vector<int> constant_propagation::get_index_array(const std::shared_ptr<hl_ast_operand> &target) {
    std::vector<int> indices = {};
    for(auto &item: target->get_array_index()){
        if(item->node_type == hl_ast_node_type_operand){
            if(std::static_pointer_cast<hl_ast_operand>(item)->get_variable()->is_constant()){
                indices.push_back(std::static_pointer_cast<hl_ast_operand>(item)->get_int_value());
            }
        }
    }
    if(indices.size() == target->get_array_index().size()){
        return indices;
    } else {
        return {};
    }
}



void constant_propagation::analyze_assignment(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {
    std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());

    if(needs_termination(element, instr_idx)){
        if(!lhs->get_array_index().empty()){
            if(lhs->get_array_index()[0]->node_type != hl_ast_node_type_operand){
                tracker.terminate_all_constant_ranges(lhs->get_name(), instr_idx+1);
            } else{
                std::vector<int> indices = get_index_array(lhs);
                if(!indices.empty()){
                    tracker.terminate_constant_range(lhs->get_name(), instr_idx+1, indices);
                }
            }
        } else {
            tracker.terminate_constant_range(lhs->get_name(), instr_idx+1, {0});
        }
    }
}


bool constant_propagation::needs_termination(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {
    bool needs_termination = false;
    bool analyze_rhs;
    auto dest = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());

    if(dest->get_variable()->get_type() == var_type_array){
        std::vector<int> indices = get_index_array(dest);
        if(!indices.empty()){
            analyze_rhs = tracker.is_constant(dest->get_name(), instr_idx, {indices});
        } else {
            analyze_rhs = false;
        }

    } else {
        analyze_rhs = tracker.is_constant(dest->get_name(), instr_idx, {0});
    }

    if(analyze_rhs){
        if(element->get_rhs()->node_type != hl_ast_node_type_operand){
            // ONLY OPERANDS CAN BE CONSTANT, THUS TERMINATE THE RANGE
            needs_termination = true;
        } else {
            if(!std::static_pointer_cast<hl_ast_operand>(element->get_rhs())->get_variable()->is_constant()){
                // TERMINATE THE RANGE AS THE ASSIGNMENT IS NOT CONSTANT
                needs_termination = true;
            }
        }
    }
    return needs_termination;
}

