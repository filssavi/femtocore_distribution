
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "C_grammarVisitor.h"


namespace C_parser {

/**
 * This class provides an empty implementation of C_grammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  C_grammarBaseVisitor : public C_grammarVisitor {
public:

  virtual std::any visitCompilationUnit(C_grammarParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(C_grammarParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(C_grammarParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccessExpression(C_grammarParser::ArrayAccessExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperator(C_grammarParser::UnaryOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeOperator(C_grammarParser::MultiplicativeOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveOperator(C_grammarParser::AdditiveOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(C_grammarParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftOperator(C_grammarParser::ShiftOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShiftExpression(C_grammarParser::ShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalOperator(C_grammarParser::RelationalOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(C_grammarParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityOperator(C_grammarParser::EqualityOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(C_grammarParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpression(C_grammarParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalExpression(C_grammarParser::ConditionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpression(C_grammarParser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(C_grammarParser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(C_grammarParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantExpression(C_grammarParser::ConstantExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(C_grammarParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitDeclaratorList(C_grammarParser::InitDeclaratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitDeclarator(C_grammarParser::InitDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpecifier(C_grammarParser::TypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarator(C_grammarParser::DeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirectDeclarator(C_grammarParser::DirectDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDeclarator(C_grammarParser::ArrayDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterTypeList(C_grammarParser::ParameterTypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(C_grammarParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDeclaration(C_grammarParser::ParameterDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(C_grammarParser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeName(C_grammarParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedefName(C_grammarParser::TypedefNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializer(C_grammarParser::InitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallExpression(C_grammarParser::FunctionCallExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentExpressionList(C_grammarParser::ArgumentExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentExpression(C_grammarParser::ArgumentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializerList(C_grammarParser::InitializerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDesignation(C_grammarParser::DesignationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDesignatorList(C_grammarParser::DesignatorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDesignator(C_grammarParser::DesignatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(C_grammarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompoundStatement(C_grammarParser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(C_grammarParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(C_grammarParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfContent(C_grammarParser::IfContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseContent(C_grammarParser::ElseContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalBlockItem(C_grammarParser::ConditionalBlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionContent(C_grammarParser::ConditionContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectionStatement(C_grammarParser::SelectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(C_grammarParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForContent(C_grammarParser::ForContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForBlockItem(C_grammarParser::ForBlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForExitCondition(C_grammarParser::ForExitConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForDeclaration(C_grammarParser::ForDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForIterationExpression(C_grammarParser::ForIterationExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(C_grammarParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTranslationUnit(C_grammarParser::TranslationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternalDeclaration(C_grammarParser::ExternalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(C_grammarParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationList(C_grammarParser::DeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstant(C_grammarParser::ConstantContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace C_parser
