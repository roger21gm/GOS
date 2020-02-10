//
// Created by Roger Generoso Masós on 06/02/2020.
//

#include "CSP2SATMainListener.h"

using namespace CSP2SAT;

void CSP2SATMainListener::enterInit(CSP2SATParser::InitContext *context) {
    cout << "ueei!" << endl;
    CSP2SATBaseListener::enterInit(context);
}

void CSP2SATMainListener::exitInit(CSP2SATParser::InitContext *context) {
    CSP2SATBaseListener::exitInit(context);
}

void CSP2SATMainListener::enterDefConst(CSP2SATParser::DefConstContext *context) {
    CSP2SATBaseListener::enterDefConst(context);
}

void CSP2SATMainListener::exitDefConst(CSP2SATParser::DefConstContext *context) {
    CSP2SATBaseListener::exitDefConst(context);
}

void CSP2SATMainListener::enterDefVariable(CSP2SATParser::DefVariableContext *context) {
    CSP2SATBaseListener::enterDefVariable(context);
}

void CSP2SATMainListener::exitDefVariable(CSP2SATParser::DefVariableContext *context) {
    CSP2SATBaseListener::exitDefVariable(context);
}

void CSP2SATMainListener::enterDefVariableAux(CSP2SATParser::DefVariableAuxContext *context) {
    CSP2SATBaseListener::enterDefVariableAux(context);
}

void CSP2SATMainListener::exitDefVariableAux(CSP2SATParser::DefVariableAuxContext *context) {
    CSP2SATBaseListener::exitDefVariableAux(context);
}

void CSP2SATMainListener::enterDefArray(CSP2SATParser::DefArrayContext *context) {
    CSP2SATBaseListener::enterDefArray(context);
}

void CSP2SATMainListener::exitDefArray(CSP2SATParser::DefArrayContext *context) {
    CSP2SATBaseListener::exitDefArray(context);
}

void CSP2SATMainListener::enterDefClass(CSP2SATParser::DefClassContext *context) {
    cout << "def class!" << endl;
    CSP2SATBaseListener::enterDefClass(context);
}

void CSP2SATMainListener::exitDefClass(CSP2SATParser::DefClassContext *context) {
    CSP2SATBaseListener::exitDefClass(context);
}

void CSP2SATMainListener::enterDefNamedConstraint(CSP2SATParser::DefNamedConstraintContext *context) {
    CSP2SATBaseListener::enterDefNamedConstraint(context);
}

void CSP2SATMainListener::exitDefNamedConstraint(CSP2SATParser::DefNamedConstraintContext *context) {
    CSP2SATBaseListener::exitDefNamedConstraint(context);
}

void CSP2SATMainListener::enterDefConstraint(CSP2SATParser::DefConstraintContext *context) {
    CSP2SATBaseListener::enterDefConstraint(context);
}

void CSP2SATMainListener::exitDefConstraint(CSP2SATParser::DefConstraintContext *context) {
    CSP2SATBaseListener::exitDefConstraint(context);
}

void CSP2SATMainListener::enterForall(CSP2SATParser::ForallContext *context) {
    CSP2SATBaseListener::enterForall(context);
}

void CSP2SATMainListener::exitForall(CSP2SATParser::ForallContext *context) {
    CSP2SATBaseListener::exitForall(context);
}

void CSP2SATMainListener::enterConditional(CSP2SATParser::ConditionalContext *context) {
    CSP2SATBaseListener::enterConditional(context);
}

void CSP2SATMainListener::exitConditional(CSP2SATParser::ConditionalContext *context) {
    CSP2SATBaseListener::exitConditional(context);
}

void CSP2SATMainListener::enterRang(CSP2SATParser::RangContext *context) {
    CSP2SATBaseListener::enterRang(context);
}

void CSP2SATMainListener::exitRang(CSP2SATParser::RangContext *context) {
    CSP2SATBaseListener::exitRang(context);
}

void CSP2SATMainListener::enterFunctionCall(CSP2SATParser::FunctionCallContext *context) {
    CSP2SATBaseListener::enterFunctionCall(context);
}

void CSP2SATMainListener::exitFunctionCall(CSP2SATParser::FunctionCallContext *context) {
    CSP2SATBaseListener::exitFunctionCall(context);
}

void CSP2SATMainListener::enterList(CSP2SATParser::ListContext *context) {
    CSP2SATBaseListener::enterList(context);
}

void CSP2SATMainListener::exitList(CSP2SATParser::ListContext *context) {
    CSP2SATBaseListener::exitList(context);
}

void CSP2SATMainListener::enterComprehensionList(CSP2SATParser::ComprehensionListContext *context) {
    CSP2SATBaseListener::enterComprehensionList(context);
}

void CSP2SATMainListener::exitComprehensionList(CSP2SATParser::ComprehensionListContext *context) {
    CSP2SATBaseListener::exitComprehensionList(context);
}

void CSP2SATMainListener::enterValueBaseType(CSP2SATParser::ValueBaseTypeContext *context) {
    CSP2SATBaseListener::enterValueBaseType(context);
}

void CSP2SATMainListener::exitValueBaseType(CSP2SATParser::ValueBaseTypeContext *context) {
    CSP2SATBaseListener::exitValueBaseType(context);
}

void CSP2SATMainListener::enterArray_access(CSP2SATParser::Array_accessContext *context) {
    CSP2SATBaseListener::enterArray_access(context);
}

void CSP2SATMainListener::exitArray_access(CSP2SATParser::Array_accessContext *context) {
    CSP2SATBaseListener::exitArray_access(context);
}

void CSP2SATMainListener::enterObject_attribute(CSP2SATParser::Object_attributeContext *context) {
    CSP2SATBaseListener::enterObject_attribute(context);
}

void CSP2SATMainListener::exitObject_attribute(CSP2SATParser::Object_attributeContext *context) {
    CSP2SATBaseListener::exitObject_attribute(context);
}

void CSP2SATMainListener::enterExpr(CSP2SATParser::ExprContext *context) {
    CSP2SATBaseListener::enterExpr(context);
}

void CSP2SATMainListener::exitExpr(CSP2SATParser::ExprContext *context) {
    CSP2SATBaseListener::exitExpr(context);
}

void CSP2SATMainListener::enterExpr_6(CSP2SATParser::Expr_6Context *context) {
    CSP2SATBaseListener::enterExpr_6(context);
}

void CSP2SATMainListener::exitExpr_6(CSP2SATParser::Expr_6Context *context) {
    CSP2SATBaseListener::exitExpr_6(context);
}

void CSP2SATMainListener::enterExpr_5(CSP2SATParser::Expr_5Context *context) {
    CSP2SATBaseListener::enterExpr_5(context);
}

void CSP2SATMainListener::exitExpr_5(CSP2SATParser::Expr_5Context *context) {
    CSP2SATBaseListener::exitExpr_5(context);
}

void CSP2SATMainListener::enterExpr_4(CSP2SATParser::Expr_4Context *context) {
    CSP2SATBaseListener::enterExpr_4(context);
}

void CSP2SATMainListener::exitExpr_4(CSP2SATParser::Expr_4Context *context) {
    CSP2SATBaseListener::exitExpr_4(context);
}

void CSP2SATMainListener::enterExpr_3(CSP2SATParser::Expr_3Context *context) {
    CSP2SATBaseListener::enterExpr_3(context);
}

void CSP2SATMainListener::exitExpr_3(CSP2SATParser::Expr_3Context *context) {
    CSP2SATBaseListener::exitExpr_3(context);
}

void CSP2SATMainListener::enterExpr_2(CSP2SATParser::Expr_2Context *context) {
    CSP2SATBaseListener::enterExpr_2(context);
}

void CSP2SATMainListener::exitExpr_2(CSP2SATParser::Expr_2Context *context) {
    CSP2SATBaseListener::exitExpr_2(context);
}

void CSP2SATMainListener::enterExpr_base(CSP2SATParser::Expr_baseContext *context) {
    CSP2SATBaseListener::enterExpr_base(context);
}

void CSP2SATMainListener::exitExpr_base(CSP2SATParser::Expr_baseContext *context) {
    CSP2SATBaseListener::exitExpr_base(context);
}

void CSP2SATMainListener::enterEveryRule(antlr4::ParserRuleContext *context) {
    CSP2SATBaseListener::enterEveryRule(context);
}

void CSP2SATMainListener::exitEveryRule(antlr4::ParserRuleContext *context) {
    CSP2SATBaseListener::exitEveryRule(context);
}

void CSP2SATMainListener::visitTerminal(antlr4::tree::TerminalNode *node) {
    CSP2SATBaseListener::visitTerminal(node);
}

void CSP2SATMainListener::visitErrorNode(antlr4::tree::ErrorNode *node) {
    CSP2SATBaseListener::visitErrorNode(node);
}
