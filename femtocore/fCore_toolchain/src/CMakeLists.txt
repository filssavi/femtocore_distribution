set(FCORE_COMMON_SRCS_I
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/binary_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/backend/binary_generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/executable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_instruction_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_register_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_conversion_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_independent_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_intercalated_const_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_load_constant_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_pseudo_instr_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_loop_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_ast_pragma.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_ast_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/instruction_stream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/common/memory_tracker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/instruction_stream_builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/define.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/register_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/common/variable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/variable_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/define_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/array_linearizer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/ll_pass_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/loop_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/pseudo_instructions_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/instruction_counting_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/load_intercalation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/io_constant_tracking.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/stream_pass_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/variable_lifetime_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/variable_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/register_allocation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/constant_merging.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/zero_assignment_removal_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/instruction_stream/bound_register_mapping.cpp
        )



set(FCORE_CC_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_language_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_pre_processor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_ErrorHandling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_Tree_visitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_definition_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_function_def_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_loop_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_conditional_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_expression_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_function_call_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_operand.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/constants_tracker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/array_index_lowering.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/dead_load_elimination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/constant_folding_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/constant_propagation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/array_initialization_substitution.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/hl_pass_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/hl_variable_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/fuction_mangling_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/operating_assignment_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/inlined_function_elimination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/inline_constant_extraction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/intrinsics_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/function_inlining_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/division_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/code_block_inlining_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/dead_variable_elimination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/conditional_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/loop_unrolling_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/normalization_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/contiguous_array_identification.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fcore_cc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/high_level_ast_lowering.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/expression_evaluator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/schema_validators/schema_validator_base.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/schema_validators/schema_validators.cpp
        )


set(FCORE_AS_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/AsmTree_visitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/asm_language_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/AsmErrorHandling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fcore_has.cpp
        )


set(FCORE_DIS_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/backend/assembly_generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fcore_dis.cpp
        )

set(FCORE_EMU_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/backend/emulator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/backend/efi_implementations/efi_dispatcher.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/emulator_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/schema_validators/schema_validators.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/schema_validators/schema_validator_base.cpp
        )

set(FCORE_DEVTOOLS_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/dev_server/rest_handler.cpp
        )

set(FCORE_SRCS ${FCORE_COMMON_SRCS_I} ${FCORE_CC_SRCS} ${FCORE_AS_SRCS} ${FCORE_DIS_SRCS} ${FCORE_EMU_SRCS} PARENT_SCOPE)

add_library(common_srcs ${FCORE_COMMON_SRCS_I})
target_link_libraries(common_srcs PRIVATE nlohmann_json::nlohmann_json)

add_executable(fCore_has ${FCORE_AS_SRCS} ${ASM_PARSER_SRCS} fcore_has_main.cpp)
target_link_libraries(fCore_has PRIVATE
        common_srcs
        nlohmann_json::nlohmann_json
        CLI11::CLI11
        antlr4_static
        spdlog
        nlohmann_json_schema_validator
        )

add_executable(fCore_cc ${FCORE_CC_SRCS} ${C_PARSER_SRCS} fcore_cc_main.cpp)
target_link_libraries(fCore_cc PRIVATE common_srcs
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator
        CLI11::CLI11
        antlr4_static
        spdlog)

add_executable(fCore_dis ${FCORE_DIS_SRCS} fcore_dis_main.cpp)
target_link_libraries(fCore_dis PRIVATE
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator
        CLI11::CLI11
        common_srcs
        spdlog)

add_custom_target(toolchain)
add_dependencies(toolchain fCore_has fCore_cc fCore_dis)


install(DIRECTORY ../schemas/ DESTINATION /usr/local/etc/fcore_toolchain)

install(TARGETS fCore_has DESTINATION /usr/bin)
install(TARGETS fCore_cc DESTINATION /usr/bin)
install(TARGETS fCore_dis DESTINATION /usr/bin)

if(${INCLUDE_EMULATOR})
    add_executable(fCore_emu ${FCORE_EMU_SRCS} fcore_emu_main.cpp)
    target_link_libraries(fCore_emu Ip_floating_point_v7_1_bitacc_cmodel
            common_srcs
            spdlog
            nlohmann_json::nlohmann_json
            CLI11::CLI11
            nlohmann_json_schema_validator
            )

    install(TARGETS fCore_emu DESTINATION /usr/bin)
    install(FILES ../third_party/fp_ip_cmodel/lib/libIp_floating_point_v7_1_bitacc_cmodel.so
            DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif(${INCLUDE_EMULATOR})


if(${INCLUDE_DEVTOOLS})
    add_executable(fCore_dev_server  ${FCORE_CC_SRCS} ${FCORE_DEVTOOLS_SRCS} ${C_PARSER_SRCS} fCore_dev_server.cpp)
    target_link_libraries(fCore_dev_server PRIVATE
            cpprestsdk::cpprest
            spdlog
            nlohmann_json::nlohmann_json
            CLI11::CLI11
            crypto
            antlr4_static
            nlohmann_json_schema_validator
            common_srcs
            )

endif(${INCLUDE_DEVTOOLS})

