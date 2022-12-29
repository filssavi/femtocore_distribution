
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "C_grammarListener.h"


namespace C_parser {

/**
 * This class provides an empty implementation of C_grammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  C_grammarBaseListener : public C_grammarListener {
public:

  virtual void enterCompilationUnit(C_grammarParser::CompilationUnitContext * /*ctx*/) override { }
  virtual void exitCompilationUnit(C_grammarParser::CompilationUnitContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(C_grammarParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(C_grammarParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(C_grammarParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(C_grammarParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext * /*ctx*/) override { }
  virtual void exitArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(C_grammarParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(C_grammarParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext * /*ctx*/) override { }
  virtual void exitMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveOperator(C_grammarParser::AdditiveOperatorContext * /*ctx*/) override { }
  virtual void exitAdditiveOperator(C_grammarParser::AdditiveOperatorContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(C_grammarParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(C_grammarParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterShiftOperator(C_grammarParser::ShiftOperatorContext * /*ctx*/) override { }
  virtual void exitShiftOperator(C_grammarParser::ShiftOperatorContext * /*ctx*/) override { }

  virtual void enterShiftExpression(C_grammarParser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(C_grammarParser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalOperator(C_grammarParser::RelationalOperatorContext * /*ctx*/) override { }
  virtual void exitRelationalOperator(C_grammarParser::RelationalOperatorContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(C_grammarParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(C_grammarParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityOperator(C_grammarParser::EqualityOperatorContext * /*ctx*/) override { }
  virtual void exitEqualityOperator(C_grammarParser::EqualityOperatorContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(C_grammarParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(C_grammarParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(C_grammarParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(C_grammarParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext * /*ctx*/) override { }
  virtual void exitInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(C_grammarParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(C_grammarParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(C_grammarParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(C_grammarParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(C_grammarParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(C_grammarParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterExpression(C_grammarParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(C_grammarParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterConstantExpression(C_grammarParser::ConstantExpressionContext * /*ctx*/) override { }
  virtual void exitConstantExpression(C_grammarParser::ConstantExpressionContext * /*ctx*/) override { }

  virtual void enterDeclaration(C_grammarParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(C_grammarParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterInitDeclaratorList(C_grammarParser::InitDeclaratorListContext * /*ctx*/) override { }
  virtual void exitInitDeclaratorList(C_grammarParser::InitDeclaratorListContext * /*ctx*/) override { }

  virtual void enterInitDeclarator(C_grammarParser::InitDeclaratorContext * /*ctx*/) override { }
  virtual void exitInitDeclarator(C_grammarParser::InitDeclaratorContext * /*ctx*/) override { }

  virtual void enterTypeSpecifier(C_grammarParser::TypeSpecifierContext * /*ctx*/) override { }
  virtual void exitTypeSpecifier(C_grammarParser::TypeSpecifierContext * /*ctx*/) override { }

  virtual void enterSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext * /*ctx*/) override { }
  virtual void exitSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext * /*ctx*/) override { }

  virtual void enterDeclarator(C_grammarParser::DeclaratorContext * /*ctx*/) override { }
  virtual void exitDeclarator(C_grammarParser::DeclaratorContext * /*ctx*/) override { }

  virtual void enterDirectDeclarator(C_grammarParser::DirectDeclaratorContext * /*ctx*/) override { }
  virtual void exitDirectDeclarator(C_grammarParser::DirectDeclaratorContext * /*ctx*/) override { }

  virtual void enterArrayDeclarator(C_grammarParser::ArrayDeclaratorContext * /*ctx*/) override { }
  virtual void exitArrayDeclarator(C_grammarParser::ArrayDeclaratorContext * /*ctx*/) override { }

  virtual void enterNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext * /*ctx*/) override { }
  virtual void exitNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext * /*ctx*/) override { }

  virtual void enterParameterTypeList(C_grammarParser::ParameterTypeListContext * /*ctx*/) override { }
  virtual void exitParameterTypeList(C_grammarParser::ParameterTypeListContext * /*ctx*/) override { }

  virtual void enterParameterList(C_grammarParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(C_grammarParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterParameterDeclaration(C_grammarParser::ParameterDeclarationContext * /*ctx*/) override { }
  virtual void exitParameterDeclaration(C_grammarParser::ParameterDeclarationContext * /*ctx*/) override { }

  virtual void enterIdentifierList(C_grammarParser::IdentifierListContext * /*ctx*/) override { }
  virtual void exitIdentifierList(C_grammarParser::IdentifierListContext * /*ctx*/) override { }

  virtual void enterTypeName(C_grammarParser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(C_grammarParser::TypeNameContext * /*ctx*/) override { }

  virtual void enterTypedefName(C_grammarParser::TypedefNameContext * /*ctx*/) override { }
  virtual void exitTypedefName(C_grammarParser::TypedefNameContext * /*ctx*/) override { }

  virtual void enterInitializer(C_grammarParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(C_grammarParser::InitializerContext * /*ctx*/) override { }

  virtual void enterFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext * /*ctx*/) override { }

  virtual void enterArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext * /*ctx*/) override { }
  virtual void exitArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext * /*ctx*/) override { }

  virtual void enterArgumentExpression(C_grammarParser::ArgumentExpressionContext * /*ctx*/) override { }
  virtual void exitArgumentExpression(C_grammarParser::ArgumentExpressionContext * /*ctx*/) override { }

  virtual void enterInitializerList(C_grammarParser::InitializerListContext * /*ctx*/) override { }
  virtual void exitInitializerList(C_grammarParser::InitializerListContext * /*ctx*/) override { }

  virtual void enterDesignation(C_grammarParser::DesignationContext * /*ctx*/) override { }
  virtual void exitDesignation(C_grammarParser::DesignationContext * /*ctx*/) override { }

  virtual void enterDesignatorList(C_grammarParser::DesignatorListContext * /*ctx*/) override { }
  virtual void exitDesignatorList(C_grammarParser::DesignatorListContext * /*ctx*/) override { }

  virtual void enterDesignator(C_grammarParser::DesignatorContext * /*ctx*/) override { }
  virtual void exitDesignator(C_grammarParser::DesignatorContext * /*ctx*/) override { }

  virtual void enterStatement(C_grammarParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(C_grammarParser::StatementContext * /*ctx*/) override { }

  virtual void enterCompoundStatement(C_grammarParser::CompoundStatementContext * /*ctx*/) override { }
  virtual void exitCompoundStatement(C_grammarParser::CompoundStatementContext * /*ctx*/) override { }

  virtual void enterBlockItem(C_grammarParser::BlockItemContext * /*ctx*/) override { }
  virtual void exitBlockItem(C_grammarParser::BlockItemContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(C_grammarParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(C_grammarParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterIfContent(C_grammarParser::IfContentContext * /*ctx*/) override { }
  virtual void exitIfContent(C_grammarParser::IfContentContext * /*ctx*/) override { }

  virtual void enterElseContent(C_grammarParser::ElseContentContext * /*ctx*/) override { }
  virtual void exitElseContent(C_grammarParser::ElseContentContext * /*ctx*/) override { }

  virtual void enterConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext * /*ctx*/) override { }
  virtual void exitConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext * /*ctx*/) override { }

  virtual void enterConditionContent(C_grammarParser::ConditionContentContext * /*ctx*/) override { }
  virtual void exitConditionContent(C_grammarParser::ConditionContentContext * /*ctx*/) override { }

  virtual void enterSelectionStatement(C_grammarParser::SelectionStatementContext * /*ctx*/) override { }
  virtual void exitSelectionStatement(C_grammarParser::SelectionStatementContext * /*ctx*/) override { }

  virtual void enterIterationStatement(C_grammarParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(C_grammarParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterForContent(C_grammarParser::ForContentContext * /*ctx*/) override { }
  virtual void exitForContent(C_grammarParser::ForContentContext * /*ctx*/) override { }

  virtual void enterForBlockItem(C_grammarParser::ForBlockItemContext * /*ctx*/) override { }
  virtual void exitForBlockItem(C_grammarParser::ForBlockItemContext * /*ctx*/) override { }

  virtual void enterForExitCondition(C_grammarParser::ForExitConditionContext * /*ctx*/) override { }
  virtual void exitForExitCondition(C_grammarParser::ForExitConditionContext * /*ctx*/) override { }

  virtual void enterForDeclaration(C_grammarParser::ForDeclarationContext * /*ctx*/) override { }
  virtual void exitForDeclaration(C_grammarParser::ForDeclarationContext * /*ctx*/) override { }

  virtual void enterForIterationExpression(C_grammarParser::ForIterationExpressionContext * /*ctx*/) override { }
  virtual void exitForIterationExpression(C_grammarParser::ForIterationExpressionContext * /*ctx*/) override { }

  virtual void enterReturnStatement(C_grammarParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(C_grammarParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterTranslationUnit(C_grammarParser::TranslationUnitContext * /*ctx*/) override { }
  virtual void exitTranslationUnit(C_grammarParser::TranslationUnitContext * /*ctx*/) override { }

  virtual void enterExternalDeclaration(C_grammarParser::ExternalDeclarationContext * /*ctx*/) override { }
  virtual void exitExternalDeclaration(C_grammarParser::ExternalDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(C_grammarParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(C_grammarParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterDeclarationList(C_grammarParser::DeclarationListContext * /*ctx*/) override { }
  virtual void exitDeclarationList(C_grammarParser::DeclarationListContext * /*ctx*/) override { }

  virtual void enterConstant(C_grammarParser::ConstantContext * /*ctx*/) override { }
  virtual void exitConstant(C_grammarParser::ConstantContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace C_parser
