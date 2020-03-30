//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
#define CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H

#include "CSP2SATBaseVisitor.h"
#include "Symtab/SymbolTable.h"
#include "Symtab/Symbol/Assignable/VariableSymbol.h"
#include "Symtab/Symbol/Assignable/ConstantSymbol.h"
#include "Symtab/Symbol/StructSymbol.h"
#include "CSP2SATCustomBaseVisitor.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATTypeVarDefinitionVisitor: public CSP2SATCustomBaseVisitor {

public:
    antlrcpp::Any visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) override {
        VariableSymbol *newVar;
        newVar = new VariableSymbol(
                ctx->name->getText(),
                (Type *) (currentScope->resolve(ctx->type->getText()))
        );
        currentScope->define(newVar);
        return CSP2SATBaseVisitor::visitVarDefinition(ctx);
    }

    antlrcpp::Any visitConstDefinition(CSP2SATParser::ConstDefinitionContext *ctx) override {
        ConstantSymbol *newConst;
        newConst = new ConstantSymbol(
                ctx->name->getText(),
                (Type*) currentScope->resolve(ctx->type->getText())
        );
        currentScope->define(newConst);
        return CSP2SATBaseVisitor::visitConstDefinition(ctx);
    }

    antlrcpp::Any visitTypeDefinition(CSP2SATParser::TypeDefinitionContext *ctx) override {
        StructSymbol *newType;
        newType = new StructSymbol(ctx->name->getText(), currentScope);
        currentScope->define(newType);

        currentScope = newType;
        CSP2SATBaseVisitor::visitTypeDefinition(ctx);
        currentScope = currentScope->getEnclosingScope();

        return nullptr;
    }
};


#endif //CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
