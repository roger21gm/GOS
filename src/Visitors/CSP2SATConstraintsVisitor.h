//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"
#include "smtformula.h"


class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}


    antlrcpp::Any visitConstraint(CSP2SATParser::ConstraintContext *ctx) override {
        if(ctx->cLit){
            ValueSymbol * val = visit(ctx->cLit);
            SymbolTable::_f->addClause(((VariableSymbol*) val)->getVar());
        }
        else {
            CSP2SATBaseVisitor::visitConstraint(ctx);
        }
        return nullptr;
    }

    antlrcpp::Any visitConstraint_or(CSP2SATParser::Constraint_orContext *ctx) override {
        ValueSymbol * firstValue = visit(ctx->constraint_literal(0));
        VariableSymbol * firstLiteral = (VariableSymbol*) firstValue;
        clause orClause = firstLiteral->getVar();

        for(int i=1; i < ctx->constraint_literal().size(); i++){
            ValueSymbol * currValue = visit(ctx->constraint_literal(i));
            VariableSymbol * currLiteral = (VariableSymbol*) currValue;
            orClause |= currLiteral->getVar();
        }
        SymbolTable::_f->addClause(orClause);
        return CSP2SATBaseVisitor::visitConstraint_or(ctx);
    }

    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override {
        ValueSymbol * valSym = visit(ctx->varAccess());
        if(!valSym->isAssignable()){
            VariableSymbol * var = (VariableSymbol*) valSym;
            if(ctx->TK_CONSTRAINT_NOT())
                return (ValueSymbol*) new VariableSymbol("!" + var->name, !(var->getVar()));
            return valSym;
        }
        else {
            cerr << ctx->getText() << ": constraints only can be variables" << endl;
            throw;
        }

    }



};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
