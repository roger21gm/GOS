//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"

class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}

    antlrcpp::Any visitConstraintDefinition(CSP2SATParser::ConstraintDefinitionContext *ctx) override {
        if(ctx->expr()){
            Value * val = visit(ctx->expr());
            cout << val->getRealValue() << endl;
        }
        return nullptr;
    }
};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
