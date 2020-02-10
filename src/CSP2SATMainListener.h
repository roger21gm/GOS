//
// Created by Roger Generoso Masós on 06/02/2020.
//

#ifndef CSP2SAT_CSP2SATMAINLISTENER_H
#define CSP2SAT_CSP2SATMAINLISTENER_H

#include "CSP2SATBaseListener.h"

using namespace CSP2SAT;
using namespace std;


class CSP2SATMainListener : public CSP2SATBaseListener {
public:
    void enterInit(CSP2SATParser::InitContext *context) override;

    void exitInit(CSP2SATParser::InitContext *context) override;

    void enterDefConst(CSP2SATParser::DefConstContext *context) override;

    void exitDefConst(CSP2SATParser::DefConstContext *context) override;

    void enterDefVariable(CSP2SATParser::DefVariableContext *context) override;

    void exitDefVariable(CSP2SATParser::DefVariableContext *context) override;

    void enterDefVariableAux(CSP2SATParser::DefVariableAuxContext *context) override;

    void exitDefVariableAux(CSP2SATParser::DefVariableAuxContext *context) override;

    void enterDefArray(CSP2SATParser::DefArrayContext *context) override;

    void exitDefArray(CSP2SATParser::DefArrayContext *context) override;

    void enterDefClass(CSP2SATParser::DefClassContext *context) override;

    void exitDefClass(CSP2SATParser::DefClassContext *context) override;

    void enterDefNamedConstraint(CSP2SATParser::DefNamedConstraintContext *context) override;

    void exitDefNamedConstraint(CSP2SATParser::DefNamedConstraintContext *context) override;

    void enterDefConstraint(CSP2SATParser::DefConstraintContext *context) override;

    void exitDefConstraint(CSP2SATParser::DefConstraintContext *context) override;

    void enterForall(CSP2SATParser::ForallContext *context) override;

    void exitForall(CSP2SATParser::ForallContext *context) override;

    void enterConditional(CSP2SATParser::ConditionalContext *context) override;

    void exitConditional(CSP2SATParser::ConditionalContext *context) override;

    void enterRang(CSP2SATParser::RangContext *context) override;

    void exitRang(CSP2SATParser::RangContext *context) override;

    void enterFunctionCall(CSP2SATParser::FunctionCallContext *context) override;

    void exitFunctionCall(CSP2SATParser::FunctionCallContext *context) override;

    void enterList(CSP2SATParser::ListContext *context) override;

    void exitList(CSP2SATParser::ListContext *context) override;

    void enterComprehensionList(CSP2SATParser::ComprehensionListContext *context) override;

    void exitComprehensionList(CSP2SATParser::ComprehensionListContext *context) override;

    void enterValueBaseType(CSP2SATParser::ValueBaseTypeContext *context) override;

    void exitValueBaseType(CSP2SATParser::ValueBaseTypeContext *context) override;

    void enterArray_access(CSP2SATParser::Array_accessContext *context) override;

    void exitArray_access(CSP2SATParser::Array_accessContext *context) override;

    void enterObject_attribute(CSP2SATParser::Object_attributeContext *context) override;

    void exitObject_attribute(CSP2SATParser::Object_attributeContext *context) override;

    void enterExpr(CSP2SATParser::ExprContext *context) override;

    void exitExpr(CSP2SATParser::ExprContext *context) override;

    void enterExpr_6(CSP2SATParser::Expr_6Context *context) override;

    void exitExpr_6(CSP2SATParser::Expr_6Context *context) override;

    void enterExpr_5(CSP2SATParser::Expr_5Context *context) override;

    void exitExpr_5(CSP2SATParser::Expr_5Context *context) override;

    void enterExpr_4(CSP2SATParser::Expr_4Context *context) override;

    void exitExpr_4(CSP2SATParser::Expr_4Context *context) override;

    void enterExpr_3(CSP2SATParser::Expr_3Context *context) override;

    void exitExpr_3(CSP2SATParser::Expr_3Context *context) override;

    void enterExpr_2(CSP2SATParser::Expr_2Context *context) override;

    void exitExpr_2(CSP2SATParser::Expr_2Context *context) override;

    void enterExpr_base(CSP2SATParser::Expr_baseContext *context) override;

    void exitExpr_base(CSP2SATParser::Expr_baseContext *context) override;

    void enterEveryRule(antlr4::ParserRuleContext *context) override;

    void exitEveryRule(antlr4::ParserRuleContext *context) override;

    void visitTerminal(antlr4::tree::TerminalNode *node) override;

    void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};


#endif //CSP2SAT_CSP2SATMAINLISTENER_H
