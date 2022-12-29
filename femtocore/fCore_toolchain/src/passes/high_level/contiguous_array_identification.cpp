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

#include "passes/high_level/contiguous_array_identification.hpp"

contiguous_array_identification::contiguous_array_identification() : pass_base<hl_ast_node>("contiguous_array_identification"){
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_loop_content;
    for(auto &item:element->get_content()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_content(new_loop_content);

    // A second pass is necessary to make shure the array definition nodes are marked correctly
    new_loop_content.clear();
    for(auto &item:element->get_content()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_content(new_loop_content);

    return element;
}


std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_ast_node> element) {
        switch (element->node_type) {
            case hl_ast_node_type_expr:
                return process_element(std::static_pointer_cast<hl_expression_node>(element));
            case hl_ast_node_type_definition:
                return process_element(std::static_pointer_cast<hl_definition_node>(element));
            case hl_ast_node_type_operand:
                return process_element(std::static_pointer_cast<hl_ast_operand>(element));
            case hl_ast_node_type_code_block:
                throw std::runtime_error("unexpected code block in contiguous array identification pass");
            case hl_ast_node_type_program_root:
                throw std::runtime_error("unexpected nested program root in contiguous array identification pass");
            default:
                throw std::runtime_error("Internal erorr, this condition should never happern");
        }

}


std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_expression_node> element) {
    if(element->is_immediate()) return element;

    if(element->get_type() == expr_assign){
        if(element->get_rhs()->node_type == hl_ast_node_type_expr){
            auto rhs = std::static_pointer_cast<hl_expression_node>(element->get_rhs());
            if(rhs->get_type()==expr_efi){

                process_efi_arguments(rhs);

                auto efi_return = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
                if(!efi_return->get_variable()->get_array_shape().empty()){
                    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 0);
                    std::shared_ptr<hl_ast_operand> idx = std::make_shared<hl_ast_operand>(var);
                    std::vector<std::shared_ptr<hl_ast_node>> new_idx;
                    for(auto &item:efi_return->get_variable()->get_array_shape()){
                        new_idx.push_back(idx);
                    }
                    efi_return->set_array_index(new_idx);
                    efi_return->get_variable()->set_type(var_type_array);
                }
                efi_return->set_contiguity(true);
                if(!contiguous_arrays.contains(efi_return->get_name())){
                    contiguous_arrays.insert(efi_return->get_name());
                }


                element->set_lhs(efi_return);
                return element;
            }
        }
    } else if(element->get_type()==expr_efi){
        process_efi_arguments(element);
    }

    element->set_rhs(process_element(element->get_rhs()));
    if(!element->is_unary()){
        auto lhs = element->get_lhs();
        element->set_lhs(process_element(lhs));
    }

    return element;
}


void
contiguous_array_identification::process_efi_arguments(std::shared_ptr<hl_expression_node> element) {
    auto efi_arg = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
    efi_arg->set_contiguity(true);
    if(!contiguous_arrays.contains(efi_arg->get_name())){
        contiguous_arrays.insert(efi_arg->get_name());
    }
    if(!efi_arg->get_variable()->get_array_shape().empty()){
        std::shared_ptr<variable> var = std::make_shared<variable>("constant", 0);
        std::shared_ptr<hl_ast_operand> idx = std::make_shared<hl_ast_operand>(var);
        std::vector<std::shared_ptr<hl_ast_node>> new_idx;
        for(auto &item:efi_arg->get_variable()->get_array_shape()){
            new_idx.push_back(idx);
        }
        efi_arg->set_array_index(new_idx);
        efi_arg->get_variable()->set_type(var_type_array);
    }
    element->set_lhs(efi_arg);
}


std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_definition_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_initializer;
    for(auto &item:element->get_array_initializer()){
        auto processed_item = process_element(item);
        if(processed_item->node_type == hl_ast_node_type_expr){
            auto expr = std::static_pointer_cast<hl_expression_node>(processed_item);
            if(expr->get_type() == expr_efi){
                if(!element->is_scalar()){ // SCALARS ARE CONTIGUOUS BY DEFINITION, THUS THEY SHOULD BE TREATED NORMALLY
                    element->get_variable()->set_contiguity(true);
                    contiguous_arrays.insert(element->get_name());
                }
            }
        }
        new_initializer.push_back(processed_item);
    }
    element->set_array_initializer(new_initializer);


    if(contiguous_arrays.contains(element->get_variable()->get_name())){
        element->get_variable()->set_contiguity(true);
    }
    return element;
}


std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_ast_operand> element) {
    if(contiguous_arrays.contains(element->get_name())){
        element->set_contiguity(true);
    }
    return element;
}
