//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_CSP2SATCUSTOMVISITOR_H
#define CSP2SAT_CSP2SATCUSTOMVISITOR_H

#include "CSP2SATBaseVisitor.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATCustomVisitor: public CSP2SATBaseVisitor {

public:
    antlrcpp::Any visitCsp2sat(CSP2SATParser::Csp2satContext *ctx) override;

    antlrcpp::Any visitTypeDefinitionBlock(CSP2SATParser::TypeDefinitionBlockContext *ctx) override;

    antlrcpp::Any visitTypeDefinition(CSP2SATParser::TypeDefinitionContext *ctx) override;

    antlrcpp::Any visitVarDefinitionBlock(CSP2SATParser::VarDefinitionBlockContext *ctx) override;

    antlrcpp::Any visitConstraintDefinitionBlock(CSP2SATParser::ConstraintDefinitionBlockContext *ctx) override;

    antlrcpp::Any visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) override;

    antlrcpp::Any visitConstDefinition(CSP2SATParser::ConstDefinitionContext *ctx) override;

    antlrcpp::Any visitVarConstDef(CSP2SATParser::VarConstDefContext *ctx) override;

    antlrcpp::Any visitAuxiliarConstDef(CSP2SATParser::AuxiliarConstDefContext *ctx) override;

    antlrcpp::Any visitConstraintDefinition(CSP2SATParser::ConstraintDefinitionContext *ctx) override;

    antlrcpp::Any visitForall(CSP2SATParser::ForallContext *ctx) override;

    antlrcpp::Any visitIfThenElse(CSP2SATParser::IfThenElseContext *ctx) override;

    antlrcpp::Any visitFunctionCall(CSP2SATParser::FunctionCallContext *ctx) override;

    antlrcpp::Any visitList(CSP2SATParser::ListContext *ctx) override;

    antlrcpp::Any visitRange(CSP2SATParser::RangeContext *ctx) override;

    antlrcpp::Any visitExpr(CSP2SATParser::ExprContext *ctx) override;

    antlrcpp::Any visitExpr_6(CSP2SATParser::Expr_6Context *ctx) override;

    antlrcpp::Any visitExpr_5(CSP2SATParser::Expr_5Context *ctx) override;

    antlrcpp::Any visitExpr_4(CSP2SATParser::Expr_4Context *ctx) override;

    antlrcpp::Any visitExpr_3(CSP2SATParser::Expr_3Context *ctx) override;

    antlrcpp::Any visitExpr_2(CSP2SATParser::Expr_2Context *ctx) override;

    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override;

    antlrcpp::Any visitValueBaseType(CSP2SATParser::ValueBaseTypeContext *ctx) override;

    antlrcpp::Any visitArray_access(CSP2SATParser::Array_accessContext *ctx) override;

    antlrcpp::Any visitObject_attribute(CSP2SATParser::Object_attributeContext *ctx) override;

    antlrcpp::Any visitConstraint(CSP2SATParser::ConstraintContext *ctx) override;

    antlrcpp::Any visitConstraint_double_implication(CSP2SATParser::Constraint_double_implicationContext *ctx) override;

    antlrcpp::Any visitConstraint_and_implication(CSP2SATParser::Constraint_and_implicationContext *ctx) override;

    antlrcpp::Any visitConstraint_or_implication(CSP2SATParser::Constraint_or_implicationContext *ctx) override;

    antlrcpp::Any visitConstraint_and(CSP2SATParser::Constraint_andContext *ctx) override;

    antlrcpp::Any visitConstraint_or(CSP2SATParser::Constraint_orContext *ctx) override;

    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override;

    antlrcpp::Any visitConstraint_var(CSP2SATParser::Constraint_varContext *ctx) override;
};


#endif //CSP2SAT_CSP2SATCUSTOMVISITOR_H
