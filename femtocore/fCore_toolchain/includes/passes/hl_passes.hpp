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

#ifndef FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
#define FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP

#include "pass_manager_base.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
//HL PASSES
#include "passes/high_level/function_inlining_pass.hpp"
#include "passes/high_level/division_implementation_pass.hpp"
#include "passes/high_level/function_mapping.hpp"
#include "passes/high_level/inlined_function_elimination.hpp"
#include "passes/high_level/normalization_pass.hpp"
#include "passes/high_level/hl_variable_mapping.hpp"
#include "passes/high_level/intrinsics_implementation_pass.hpp"
#include "passes/high_level/dead_variable_elimination.hpp"
#include "passes/high_level/constant_folding_pass.hpp"
#include "passes/high_level/constant_propagation.hpp"
#include "passes/high_level/inline_constant_extraction.hpp"
#include "passes/high_level/conditional_implementation_pass.h"
#include "passes/high_level/loop_unrolling_pass.hpp"
#include "passes/high_level/array_scalarization_pass.hpp"
#include "passes/high_level/code_block_inlining_pass.hpp"
#include "passes/high_level/operating_assignment_implementation_pass.hpp"
#include "passes/high_level/dead_load_elimination.hpp"
#include "passes/high_level/array_index_lowering.hpp"
#include "passes/high_level/fuction_mangling_pass.hpp"
#include "passes/instruction_stream/zero_assignment_removal_pass.hpp"
#include "passes/high_level/contiguous_array_identification.hpp"
#include "passes/high_level/array_index_lowering.hpp"
#include "passes/high_level/array_initialization_substitution.h"

#include "tools/variable_map.hpp"
#include "data_structures/high_level_ast/hl_ast_node.hpp"


static hl_pass_manager create_hl_pass_manager(
        std::string& entry_point,
        const std::vector<int>& order,
        int dump_ast_level
){
    hl_pass_manager manager(dump_ast_level);

    manager.add_morphing_pass(std::make_shared<division_implementation_pass>()); // pass #1
    manager.add_morphing_pass(std::make_shared<intrinsics_implementation_pass>()); // pass #2

    manager.add_morphing_pass(std::make_shared<operating_assignment_implementation_pass>()); // pass #3
    manager.add_morphing_pass(std::make_shared<fuction_mangling_pass>()); // pass #4
    manager.add_morphing_pass(std::make_shared<function_inlining_pass>());  // pass #5

    manager.add_morphing_pass(std::make_shared<inlined_function_elimination>(entry_point)); // pass #6

    manager.add_morphing_pass(std::make_shared<code_block_inlining_pass>()); // pass #7

    manager.add_morphing_pass(std::make_shared<loop_unrolling_pass>()); // pass #8
    manager.add_morphing_pass(std::make_shared<array_initialization_substitution>()); // pass #9
    manager.add_morphing_pass(std::make_shared<conditional_implementation_pass>()); // pass #10
    manager.add_morphing_pass(std::make_shared<normalization_pass>()); // pass #11

    manager.add_morphing_pass(std::make_shared<contiguous_array_identification>()); // pass #12

    manager.add_morphing_pass(std::make_shared<dead_variable_elimination>());  // pass #13
    std::shared_ptr<constant_folding_pass> const_fold = std::make_shared<constant_folding_pass>();
    std::shared_ptr<constant_propagation> const_prop = std::make_shared<constant_propagation>();

    manager.add_morphing_pass_group({const_fold, const_prop}); // group #-1
    manager.add_morphing_pass(std::make_shared<inline_constant_extraction>()); // pass #14
    manager.add_morphing_pass(std::make_shared<array_index_lowering>()); // pass #15
    manager.add_morphing_pass(std::make_shared<dead_load_elimination>()); // pass #16

    if(order.empty()){
        manager.set_pass_order({1,2,3,4,5,6,7,8,9,10,11,12,13,-1,14,15,16});
    } else {
        manager.set_pass_order(order);
    }

    return manager;
}



#endif //FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
