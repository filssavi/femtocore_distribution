
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "C_grammarParser.h"


namespace C_parser {

/**
 * This interface defines an abstract listener for a parse tree produced by C_grammarParser.
 */
class  C_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterCompilationUnit(C_grammarParser::CompilationUnitContext *ctx) = 0;
  virtual void exitCompilationUnit(C_grammarParser::CompilationUnitContext *ctx) = 0;

  virtual void enterPrimaryExpression(C_grammarParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(C_grammarParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(C_grammarParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(C_grammarParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext *ctx) = 0;
  virtual void exitArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext *ctx) = 0;

  virtual void enterUnaryOperator(C_grammarParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(C_grammarParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext *ctx) = 0;
  virtual void exitMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterAdditiveOperator(C_grammarParser::AdditiveOperatorContext *ctx) = 0;
  virtual void exitAdditiveOperator(C_grammarParser::AdditiveOperatorContext *ctx) = 0;

  virtual void enterAdditiveExpression(C_grammarParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(C_grammarParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterShiftOperator(C_grammarParser::ShiftOperatorContext *ctx) = 0;
  virtual void exitShiftOperator(C_grammarParser::ShiftOperatorContext *ctx) = 0;

  virtual void enterShiftExpression(C_grammarParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(C_grammarParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterRelationalOperator(C_grammarParser::RelationalOperatorContext *ctx) = 0;
  virtual void exitRelationalOperator(C_grammarParser::RelationalOperatorContext *ctx) = 0;

  virtual void enterRelationalExpression(C_grammarParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(C_grammarParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterEqualityOperator(C_grammarParser::EqualityOperatorContext *ctx) = 0;
  virtual void exitEqualityOperator(C_grammarParser::EqualityOperatorContext *ctx) = 0;

  virtual void enterEqualityExpression(C_grammarParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(C_grammarParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterAndExpression(C_grammarParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(C_grammarParser::AndExpressionContext *ctx) = 0;

  virtual void enterExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext *ctx) = 0;
  virtual void exitExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext *ctx) = 0;

  virtual void enterInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext *ctx) = 0;
  virtual void exitInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterConditionalExpression(C_grammarParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(C_grammarParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(C_grammarParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(C_grammarParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(C_grammarParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(C_grammarParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterExpression(C_grammarParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(C_grammarParser::ExpressionContext *ctx) = 0;

  virtual void enterConstantExpression(C_grammarParser::ConstantExpressionContext *ctx) = 0;
  virtual void exitConstantExpression(C_grammarParser::ConstantExpressionContext *ctx) = 0;

  virtual void enterDeclaration(C_grammarParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(C_grammarParser::DeclarationContext *ctx) = 0;

  virtual void enterInitDeclaratorList(C_grammarParser::InitDeclaratorListContext *ctx) = 0;
  virtual void exitInitDeclaratorList(C_grammarParser::InitDeclaratorListContext *ctx) = 0;

  virtual void enterInitDeclarator(C_grammarParser::InitDeclaratorContext *ctx) = 0;
  virtual void exitInitDeclarator(C_grammarParser::InitDeclaratorContext *ctx) = 0;

  virtual void enterTypeSpecifier(C_grammarParser::TypeSpecifierContext *ctx) = 0;
  virtual void exitTypeSpecifier(C_grammarParser::TypeSpecifierContext *ctx) = 0;

  virtual void enterSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext *ctx) = 0;
  virtual void exitSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext *ctx) = 0;

  virtual void enterDeclarator(C_grammarParser::DeclaratorContext *ctx) = 0;
  virtual void exitDeclarator(C_grammarParser::DeclaratorContext *ctx) = 0;

  virtual void enterDirectDeclarator(C_grammarParser::DirectDeclaratorContext *ctx) = 0;
  virtual void exitDirectDeclarator(C_grammarParser::DirectDeclaratorContext *ctx) = 0;

  virtual void enterArrayDeclarator(C_grammarParser::ArrayDeclaratorContext *ctx) = 0;
  virtual void exitArrayDeclarator(C_grammarParser::ArrayDeclaratorContext *ctx) = 0;

  virtual void enterNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext *ctx) = 0;
  virtual void exitNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext *ctx) = 0;

  virtual void enterParameterTypeList(C_grammarParser::ParameterTypeListContext *ctx) = 0;
  virtual void exitParameterTypeList(C_grammarParser::ParameterTypeListContext *ctx) = 0;

  virtual void enterParameterList(C_grammarParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(C_grammarParser::ParameterListContext *ctx) = 0;

  virtual void enterParameterDeclaration(C_grammarParser::ParameterDeclarationContext *ctx) = 0;
  virtual void exitParameterDeclaration(C_grammarParser::ParameterDeclarationContext *ctx) = 0;

  virtual void enterIdentifierList(C_grammarParser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(C_grammarParser::IdentifierListContext *ctx) = 0;

  virtual void enterTypeName(C_grammarParser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(C_grammarParser::TypeNameContext *ctx) = 0;

  virtual void enterTypedefName(C_grammarParser::TypedefNameContext *ctx) = 0;
  virtual void exitTypedefName(C_grammarParser::TypedefNameContext *ctx) = 0;

  virtual void enterInitializer(C_grammarParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(C_grammarParser::InitializerContext *ctx) = 0;

  virtual void enterFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext *ctx) = 0;
  virtual void exitFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext *ctx) = 0;

  virtual void enterArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext *ctx) = 0;
  virtual void exitArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext *ctx) = 0;

  virtual void enterArgumentExpression(C_grammarParser::ArgumentExpressionContext *ctx) = 0;
  virtual void exitArgumentExpression(C_grammarParser::ArgumentExpressionContext *ctx) = 0;

  virtual void enterInitializerList(C_grammarParser::InitializerListContext *ctx) = 0;
  virtual void exitInitializerList(C_grammarParser::InitializerListContext *ctx) = 0;

  virtual void enterDesignation(C_grammarParser::DesignationContext *ctx) = 0;
  virtual void exitDesignation(C_grammarParser::DesignationContext *ctx) = 0;

  virtual void enterDesignatorList(C_grammarParser::DesignatorListContext *ctx) = 0;
  virtual void exitDesignatorList(C_grammarParser::DesignatorListContext *ctx) = 0;

  virtual void enterDesignator(C_grammarParser::DesignatorContext *ctx) = 0;
  virtual void exitDesignator(C_grammarParser::DesignatorContext *ctx) = 0;

  virtual void enterStatement(C_grammarParser::StatementContext *ctx) = 0;
  virtual void exitStatement(C_grammarParser::StatementContext *ctx) = 0;

  virtual void enterCompoundStatement(C_grammarParser::CompoundStatementContext *ctx) = 0;
  virtual void exitCompoundStatement(C_grammarParser::CompoundStatementContext *ctx) = 0;

  virtual void enterBlockItem(C_grammarParser::BlockItemContext *ctx) = 0;
  virtual void exitBlockItem(C_grammarParser::BlockItemContext *ctx) = 0;

  virtual void enterExpressionStatement(C_grammarParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(C_grammarParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfContent(C_grammarParser::IfContentContext *ctx) = 0;
  virtual void exitIfContent(C_grammarParser::IfContentContext *ctx) = 0;

  virtual void enterElseContent(C_grammarParser::ElseContentContext *ctx) = 0;
  virtual void exitElseContent(C_grammarParser::ElseContentContext *ctx) = 0;

  virtual void enterConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext *ctx) = 0;
  virtual void exitConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext *ctx) = 0;

  virtual void enterConditionContent(C_grammarParser::ConditionContentContext *ctx) = 0;
  virtual void exitConditionContent(C_grammarParser::ConditionContentContext *ctx) = 0;

  virtual void enterSelectionStatement(C_grammarParser::SelectionStatementContext *ctx) = 0;
  virtual void exitSelectionStatement(C_grammarParser::SelectionStatementContext *ctx) = 0;

  virtual void enterIterationStatement(C_grammarParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(C_grammarParser::IterationStatementContext *ctx) = 0;

  virtual void enterForContent(C_grammarParser::ForContentContext *ctx) = 0;
  virtual void exitForContent(C_grammarParser::ForContentContext *ctx) = 0;

  virtual void enterForBlockItem(C_grammarParser::ForBlockItemContext *ctx) = 0;
  virtual void exitForBlockItem(C_grammarParser::ForBlockItemContext *ctx) = 0;

  virtual void enterForExitCondition(C_grammarParser::ForExitConditionContext *ctx) = 0;
  virtual void exitForExitCondition(C_grammarParser::ForExitConditionContext *ctx) = 0;

  virtual void enterForDeclaration(C_grammarParser::ForDeclarationContext *ctx) = 0;
  virtual void exitForDeclaration(C_grammarParser::ForDeclarationContext *ctx) = 0;

  virtual void enterForIterationExpression(C_grammarParser::ForIterationExpressionContext *ctx) = 0;
  virtual void exitForIterationExpression(C_grammarParser::ForIterationExpressionContext *ctx) = 0;

  virtual void enterReturnStatement(C_grammarParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(C_grammarParser::ReturnStatementContext *ctx) = 0;

  virtual void enterTranslationUnit(C_grammarParser::TranslationUnitContext *ctx) = 0;
  virtual void exitTranslationUnit(C_grammarParser::TranslationUnitContext *ctx) = 0;

  virtual void enterExternalDeclaration(C_grammarParser::ExternalDeclarationContext *ctx) = 0;
  virtual void exitExternalDeclaration(C_grammarParser::ExternalDeclarationContext *ctx) = 0;

  virtual void enterFunctionDefinition(C_grammarParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(C_grammarParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterDeclarationList(C_grammarParser::DeclarationListContext *ctx) = 0;
  virtual void exitDeclarationList(C_grammarParser::DeclarationListContext *ctx) = 0;

  virtual void enterConstant(C_grammarParser::ConstantContext *ctx) = 0;
  virtual void exitConstant(C_grammarParser::ConstantContext *ctx) = 0;


};

}  // namespace C_parser
