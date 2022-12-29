
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "C_grammarParser.h"


namespace C_parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by C_grammarParser.
 */
class  C_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by C_grammarParser.
   */
    virtual std::any visitCompilationUnit(C_grammarParser::CompilationUnitContext *context) = 0;

    virtual std::any visitPrimaryExpression(C_grammarParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(C_grammarParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext *context) = 0;

    virtual std::any visitUnaryOperator(C_grammarParser::UnaryOperatorContext *context) = 0;

    virtual std::any visitMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitAdditiveOperator(C_grammarParser::AdditiveOperatorContext *context) = 0;

    virtual std::any visitAdditiveExpression(C_grammarParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitShiftOperator(C_grammarParser::ShiftOperatorContext *context) = 0;

    virtual std::any visitShiftExpression(C_grammarParser::ShiftExpressionContext *context) = 0;

    virtual std::any visitRelationalOperator(C_grammarParser::RelationalOperatorContext *context) = 0;

    virtual std::any visitRelationalExpression(C_grammarParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitEqualityOperator(C_grammarParser::EqualityOperatorContext *context) = 0;

    virtual std::any visitEqualityExpression(C_grammarParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitAndExpression(C_grammarParser::AndExpressionContext *context) = 0;

    virtual std::any visitExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext *context) = 0;

    virtual std::any visitInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitConditionalExpression(C_grammarParser::ConditionalExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(C_grammarParser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitAssignmentOperator(C_grammarParser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitExpression(C_grammarParser::ExpressionContext *context) = 0;

    virtual std::any visitConstantExpression(C_grammarParser::ConstantExpressionContext *context) = 0;

    virtual std::any visitDeclaration(C_grammarParser::DeclarationContext *context) = 0;

    virtual std::any visitInitDeclaratorList(C_grammarParser::InitDeclaratorListContext *context) = 0;

    virtual std::any visitInitDeclarator(C_grammarParser::InitDeclaratorContext *context) = 0;

    virtual std::any visitTypeSpecifier(C_grammarParser::TypeSpecifierContext *context) = 0;

    virtual std::any visitSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext *context) = 0;

    virtual std::any visitDeclarator(C_grammarParser::DeclaratorContext *context) = 0;

    virtual std::any visitDirectDeclarator(C_grammarParser::DirectDeclaratorContext *context) = 0;

    virtual std::any visitArrayDeclarator(C_grammarParser::ArrayDeclaratorContext *context) = 0;

    virtual std::any visitNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext *context) = 0;

    virtual std::any visitParameterTypeList(C_grammarParser::ParameterTypeListContext *context) = 0;

    virtual std::any visitParameterList(C_grammarParser::ParameterListContext *context) = 0;

    virtual std::any visitParameterDeclaration(C_grammarParser::ParameterDeclarationContext *context) = 0;

    virtual std::any visitIdentifierList(C_grammarParser::IdentifierListContext *context) = 0;

    virtual std::any visitTypeName(C_grammarParser::TypeNameContext *context) = 0;

    virtual std::any visitTypedefName(C_grammarParser::TypedefNameContext *context) = 0;

    virtual std::any visitInitializer(C_grammarParser::InitializerContext *context) = 0;

    virtual std::any visitFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext *context) = 0;

    virtual std::any visitArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext *context) = 0;

    virtual std::any visitArgumentExpression(C_grammarParser::ArgumentExpressionContext *context) = 0;

    virtual std::any visitInitializerList(C_grammarParser::InitializerListContext *context) = 0;

    virtual std::any visitDesignation(C_grammarParser::DesignationContext *context) = 0;

    virtual std::any visitDesignatorList(C_grammarParser::DesignatorListContext *context) = 0;

    virtual std::any visitDesignator(C_grammarParser::DesignatorContext *context) = 0;

    virtual std::any visitStatement(C_grammarParser::StatementContext *context) = 0;

    virtual std::any visitCompoundStatement(C_grammarParser::CompoundStatementContext *context) = 0;

    virtual std::any visitBlockItem(C_grammarParser::BlockItemContext *context) = 0;

    virtual std::any visitExpressionStatement(C_grammarParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitIfContent(C_grammarParser::IfContentContext *context) = 0;

    virtual std::any visitElseContent(C_grammarParser::ElseContentContext *context) = 0;

    virtual std::any visitConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext *context) = 0;

    virtual std::any visitConditionContent(C_grammarParser::ConditionContentContext *context) = 0;

    virtual std::any visitSelectionStatement(C_grammarParser::SelectionStatementContext *context) = 0;

    virtual std::any visitIterationStatement(C_grammarParser::IterationStatementContext *context) = 0;

    virtual std::any visitForContent(C_grammarParser::ForContentContext *context) = 0;

    virtual std::any visitForBlockItem(C_grammarParser::ForBlockItemContext *context) = 0;

    virtual std::any visitForExitCondition(C_grammarParser::ForExitConditionContext *context) = 0;

    virtual std::any visitForDeclaration(C_grammarParser::ForDeclarationContext *context) = 0;

    virtual std::any visitForIterationExpression(C_grammarParser::ForIterationExpressionContext *context) = 0;

    virtual std::any visitReturnStatement(C_grammarParser::ReturnStatementContext *context) = 0;

    virtual std::any visitTranslationUnit(C_grammarParser::TranslationUnitContext *context) = 0;

    virtual std::any visitExternalDeclaration(C_grammarParser::ExternalDeclarationContext *context) = 0;

    virtual std::any visitFunctionDefinition(C_grammarParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitDeclarationList(C_grammarParser::DeclarationListContext *context) = 0;

    virtual std::any visitConstant(C_grammarParser::ConstantContext *context) = 0;


};

}  // namespace C_parser
