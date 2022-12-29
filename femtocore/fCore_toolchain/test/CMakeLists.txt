set(TEST_SOURCES
        Instruction_classes.cpp
        ll_passes.cpp
        end_to_end_asm.cpp
        testing_main.cpp
        end_to_end_C.cpp
        C_preprocessor.cpp
        C_tree_visitor_testing.cpp
        hl_passes.cpp
        disassembler_testing.cpp
        deep_copy.cpp
        emulator_testing.cpp
        emulator_execution.cpp
        emulator_schema_validation.cpp)





add_executable(test_target ${FCORE_SRCS} ${TEST_SOURCES} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS})
target_link_libraries(test_target PUBLIC ${GTEST_LIBRARIES}
        pthread
        antlr4_static
        Ip_floating_point_v7_1_bitacc_cmodel
        spdlog
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator
        GTest::gtest_main
        )

include(GoogleTest)
gtest_discover_tests(test_target)

# ASM TESTING FILES
set(ASM_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/asm)
file(MAKE_DIRECTORY ${ASM_TEST_FILES_DIR})
configure_file(asm_files/test_add.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_for.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_global.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_variables.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_branch.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_ldc.s ${ASM_TEST_FILES_DIR} COPYONLY)
configure_file(asm_files/test_ldc_int.s ${ASM_TEST_FILES_DIR} COPYONLY)

# Preprocessor
set(C_PREP_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/c_prep)
file(MAKE_DIRECTORY ${C_PREP_TEST_FILES_DIR})
configure_file(C_files/preprocessor/test_comments.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_pragmas.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_define.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_include_fail.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_include.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/include_test.h ${C_PREP_TEST_FILES_DIR} COPYONLY)

# Tree visitor (ANTLR <-> AST)
set(C_AST_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/c_ast)
file(MAKE_DIRECTORY ${C_AST_TEST_FILES_DIR})
configure_file(C_files/tree_visitor/test_unary_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_multiplicative_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_array.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_additive_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_shift_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_equality_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_relational_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_andb_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_orb_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_exorb_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_orl_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_andl_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_assignment_expressions.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_definition.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_function_call.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_return.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_conditional.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_loop.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_nested_loop.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_array_init.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_function_def.c ${C_AST_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_float_constant.c ${C_AST_TEST_FILES_DIR} COPYONLY)

#OPTIMIZATION PASSES
set(HL_OPT_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/hl_opt)
file(MAKE_DIRECTORY ${HL_OPT_TEST_FILES_DIR})
configure_file(C_files/hl_passes/test_normalization.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_contiguous_array_detection.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_loop_unrolling.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_matrix_scalarization.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_function_inlining_array.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_return_inlining.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_nested_function_inlining.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/hl_passes/test_complex_division_implementation.c ${HL_OPT_TEST_FILES_DIR} COPYONLY)

# FULL PROGRAMS
set(C_E2E_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/c_e2e)
file(MAKE_DIRECTORY ${C_E2E_TEST_FILES_DIR})
configure_file(C_files/hl_passes/test_normalization.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_intrinsics_implementation.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_full_conditional.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_full_loop.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_full_nested_loop.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_pragma_io.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_array_initialization.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_array_initialization_through_function.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_constant_argument_inlining.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_array_io_definition.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_multidim_array_io_definition.c  ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_iom_initialization.c  ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_move.c  ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_complex_normalization.c  ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_register_allocation.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_function_inline_expression.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_essential_variable_initialization.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_negative_leading_sum.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_function_vars_mangling.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_loop_index_expression.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_exception.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_loop_index_expression_multidim.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_contiguous_array_allocation.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_constant_propagation.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_efi_load_elimination.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/end_to_end/test_efi_load_elimination_in_func.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/instruction_passes/test_constant_merging.c ${C_E2E_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/instruction_passes/test_zero_assignment_removal.c ${C_E2E_TEST_FILES_DIR} COPYONLY)

# DISASSEMBLER TESTING FILES
set(DIS_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/dis)
file(MAKE_DIRECTORY ${DIS_TEST_FILES_DIR})
configure_file(disassembler_files/test_add.hex ${DIS_TEST_FILES_DIR} COPYONLY)
configure_file(disassembler_files/test_add.mem ${DIS_TEST_FILES_DIR} COPYONLY)
configure_file(disassembler_files/test_error.mem ${DIS_TEST_FILES_DIR} COPYONLY)

# EMULATOR TESTING FILES
set(EMU_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/emu)
file(MAKE_DIRECTORY ${EMU_TEST_FILES_DIR})
configure_file(emulator_files/backend/test_add.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_load.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_sub.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_mul.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_rec.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_fti.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_itf.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_and.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_or.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_not.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_satp.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_satn.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_beq.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_bne.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_bgt.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_ble.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_bset.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_stop.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/backend/test_efi.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_inputs.csv ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_inputs.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_interconnect.mem ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_inputs_spec.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_interconnect_spec.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/exec_format/test_exec_format.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/exec_format/test_exec_format.mem ${EMU_TEST_FILES_DIR} COPYONLY)

set(EMU_TEST_SCHEMAS_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/emu/schemas)
file(MAKE_DIRECTORY ${EMU_TEST_SCHEMAS_FILES_DIR})
configure_file(schemas/valid_emulator_schema.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)
configure_file(schemas/valid_compiler_schema.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)