set(C_PARSER_GEN_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarBaseListener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarBaseVisitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarLexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarListener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_grammarVisitor.cpp
        )

set(C_PARSER_SRCS
        ${C_PARSER_GEN_SRCS}
        PARENT_SCOPE)

set(ANTLR_OUTPUT -o ${PROJECT_SOURCE_DIR}/includes/C_parser)

add_custom_command(
        OUTPUT ${C_PARSER_GEN_SRCS}
        DEPENDS ${PROJECT_SOURCE_DIR}/src/frontend/C_grammar.g4
        COMMAND java -cp "${ANTLR_CLASSPATH}" org.antlr.v4.Tool -package C_parser ${ANTLR_OPTIONS} ${ANTLR_OUTPUT} ${PROJECT_SOURCE_DIR}/src/frontend/C_grammar.g4
        COMMENT "generating sources for fCore assembly"
)

add_custom_target(c_parser_gen DEPENDS  ${C_PARSER_GEN_SRCS})
