set(ASM_PARSER_GEN_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarBaseListener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarBaseVisitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarLexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarListener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammarVisitor.cpp
        )

set(ASM_PARSER_SRCS
        ${ASM_PARSER_GEN_SRCS}
        PARENT_SCOPE)

set(ANTLR_OUTPUT -o ${PROJECT_SOURCE_DIR}/includes/asm_parser)

add_custom_command(
        OUTPUT ${ASM_PARSER_GEN_SRCS}
        DEPENDS ${PROJECT_SOURCE_DIR}/src/frontend/asm_grammar.g4
        COMMAND java -cp "${ANTLR_CLASSPATH}" org.antlr.v4.Tool -package asm_parser ${ANTLR_OPTIONS} ${ANTLR_OUTPUT} ${PROJECT_SOURCE_DIR}/src/frontend/asm_grammar.g4
        COMMENT "generating sources for fCore assembly"
)

add_custom_target(asm_parser_gen DEPENDS  ${ASM_PARSER_GEN_SRCS})
