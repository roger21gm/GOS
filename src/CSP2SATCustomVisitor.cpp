
#include <support/Any.h>
#include "CSP2SATCustomVisitor.h"
#include "Symtab/Symbol/VariableSymbol.h"

antlrcpp::Any CSP2SATCustomVisitor::visitCsp2sat(CSP2SATParser::Csp2satContext *ctx) {

    return CSP2SATBaseVisitor::visitCsp2sat(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitTypeDefinitionBlock(CSP2SATParser::TypeDefinitionBlockContext *ctx) {
    return CSP2SATBaseVisitor::visitTypeDefinitionBlock(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitTypeDefinition(CSP2SATParser::TypeDefinitionContext *ctx) {
    return CSP2SATBaseVisitor::visitTypeDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitVarDefinitionBlock(CSP2SATParser::VarDefinitionBlockContext *ctx) {
    return CSP2SATBaseVisitor::visitVarDefinitionBlock(ctx);
}

antlrcpp::Any
CSP2SATCustomVisitor::visitConstraintDefinitionBlock(CSP2SATParser::ConstraintDefinitionBlockContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraintDefinitionBlock(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) {
    return CSP2SATBaseVisitor::visitVarDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstDefinition(CSP2SATParser::ConstDefinitionContext *ctx) {
    return CSP2SATBaseVisitor::visitConstDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitVarConstDef(CSP2SATParser::VarConstDefContext *ctx) {
    VariableSymbol newVar = VariableSymbol(
            ctx->name->getText(),
            (Type *)(st.gloabls.resolve(ctx->type->getText()))
            );


    cout << newVar.getName() << "  " <<  st.gloabls.resolve(ctx->type->getText())->getName() << endl;

    st.gloabls.define(&newVar);

    return CSP2SATBaseVisitor::visitVarConstDef(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitAuxiliarConstDef(CSP2SATParser::AuxiliarConstDefContext *ctx) {
    return CSP2SATBaseVisitor::visitAuxiliarConstDef(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraintDefinition(CSP2SATParser::ConstraintDefinitionContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraintDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitForall(CSP2SATParser::ForallContext *ctx) {
    return CSP2SATBaseVisitor::visitForall(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitIfThenElse(CSP2SATParser::IfThenElseContext *ctx) {
    return CSP2SATBaseVisitor::visitIfThenElse(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitFunctionCall(CSP2SATParser::FunctionCallContext *ctx) {
    return CSP2SATBaseVisitor::visitFunctionCall(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitList(CSP2SATParser::ListContext *ctx) {
    return CSP2SATBaseVisitor::visitList(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitRange(CSP2SATParser::RangeContext *ctx) {
    return CSP2SATBaseVisitor::visitRange(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr(CSP2SATParser::ExprContext *ctx) {
    if (ctx->TK_INTERROGANT()) {
        return 0;
    } else {
        return visit(ctx->expr_6());
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_6(CSP2SATParser::Expr_6Context *ctx) {
    if (ctx->op) {
        if (ctx->TK_OP_LOGIC_AND(0))
            return visit(ctx->expr_5(0)).as<bool>() && visit(ctx->expr_5(1)).as<bool>();
        else if (ctx->TK_OP_LOGIC_OR_PIPE(0))
            return visit(ctx->expr_5(0)).as<bool>() || visit(ctx->expr_5(1)).as<bool>();
    } else {
        return visit(ctx->expr_5(0));
    }
    return visitExpr_6(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_5(CSP2SATParser::Expr_5Context *ctx) {
    if (ctx->op) {
        if (ctx->TK_OP_REL_LT(0))
            return visit(ctx->expr_4(0)).as<bool>() < visit(ctx->expr_4(1)).as<bool>();
        else if (ctx->TK_OP_REL_GT(0))
            return visit(ctx->expr_4(0)).as<bool>() > visit(ctx->expr_4(1)).as<bool>();
        else if (ctx->TK_OP_REL_GE(0))
            return visit(ctx->expr_4(0)).as<bool>() >= visit(ctx->expr_4(1)).as<bool>();
        else if (ctx->TK_OP_REL_LE(0))
            return visit(ctx->expr_4(0)).as<bool>() <= visit(ctx->expr_4(1)).as<bool>();
        else if (ctx->TK_OP_REL_EQ(0))
            return visit(ctx->expr_4(0)).as<bool>() == visit(ctx->expr_4(1)).as<bool>();
        else if (ctx->TK_OP_REL_NEQ(0))
            return visit(ctx->expr_4(0)).as<bool>() != visit(ctx->expr_4(1)).as<bool>();
    } else {
        return visit(ctx->expr_4(0));
    }
    return visitExpr_5(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_4(CSP2SATParser::Expr_4Context *ctx) {
    if (ctx->op) {
        if (ctx->TK_OP_ARIT_SUM(0))
            return visit(ctx->expr_3(0)).as<int>() + visit(ctx->expr_3(1)).as<int>();
        else
            return visit(ctx->expr_3(0)).as<int>() - visit(ctx->expr_3(1)).as<int>();
    } else {
        return visit(ctx->expr_3(0));
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_3(CSP2SATParser::Expr_3Context *ctx) {
    if (ctx->op) {
        if (ctx->TK_OP_ARIT_MULT(0))
            return visit(ctx->expr_2(0)).as<int>() * visit(ctx->expr_2(1)).as<int>();
        else if (ctx->TK_OP_ARIT_DIV(0))
            return visit(ctx->expr_2(0)).as<int>() / visit(ctx->expr_2(1)).as<int>();
        else
            return visit(ctx->expr_2(0)).as<int>() % visit(ctx->expr_2(1)).as<int>();
    } else {
        return visit(ctx->expr_2(0));
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_2(CSP2SATParser::Expr_2Context *ctx) {
    if (ctx->op) {
        return 0;
    } else {
        return visit(ctx->expr_base());
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) {
    if (ctx->valueBaseType()) {
        if (ctx->valueBaseType()->TK_BOOLEAN_VALUE())
            return ctx->valueBaseType()->TK_BOOLEAN_VALUE()->getText() == "true";
        else
            return stoi(ctx->valueBaseType()->TK_INT_VALUE()->getText());
    } else if (ctx->TK_LPAREN())
        return visit(ctx->expr());
    else if (ctx->TK_IDENT())
        return 0; //TODO get ident value
    else {

    }
    return ctx->getText();
}

antlrcpp::Any CSP2SATCustomVisitor::visitValueBaseType(CSP2SATParser::ValueBaseTypeContext *ctx) {
    return CSP2SATBaseVisitor::visitValueBaseType(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitArray_access(CSP2SATParser::Array_accessContext *ctx) {
    return CSP2SATBaseVisitor::visitArray_access(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitObject_attribute(CSP2SATParser::Object_attributeContext *ctx) {
    return CSP2SATBaseVisitor::visitObject_attribute(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraint(CSP2SATParser::ConstraintContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint(ctx);
}

antlrcpp::Any
CSP2SATCustomVisitor::visitConstraint_double_implication(CSP2SATParser::Constraint_double_implicationContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_double_implication(ctx);
}

antlrcpp::Any
CSP2SATCustomVisitor::visitConstraint_and_implication(CSP2SATParser::Constraint_and_implicationContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_and_implication(ctx);
}

antlrcpp::Any
CSP2SATCustomVisitor::visitConstraint_or_implication(CSP2SATParser::Constraint_or_implicationContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_or_implication(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraint_and(CSP2SATParser::Constraint_andContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_and(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraint_or(CSP2SATParser::Constraint_orContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_or(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_literal(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstraint_var(CSP2SATParser::Constraint_varContext *ctx) {
    return CSP2SATBaseVisitor::visitConstraint_var(ctx);
}
