//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
#define CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H

#include "CSP2SATBaseVisitor.h"
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Assignable/VariableSymbol.h"
#include "../Symtab/Symbol/Assignable/ConstantSymbol.h"
#include "../Symtab/Symbol/Scoped/StructSymbol.h"
#include "CSP2SATCustomBaseVisitor.h"
#include "Utils.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATTypeVarDefinitionVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATTypeVarDefinitionVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}

    antlrcpp::Any visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) override {
        VariableSymbol *newVar;
        newVar = new VariableSymbol(
                ctx->name->getText(),
                (Type *) (currentScope->resolve(ctx->type->getText()))
        );
        currentScope->define(newVar);
        return CSP2SATBaseVisitor::visitVarDefinition(ctx);
    }

    antlrcpp::Any visitParamDefinition(CSP2SATParser::ParamDefinitionContext *ctx) override {
        CSP2SATBaseVisitor::visitParamDefinition(ctx);

        Type *type = (Type *) currentScope->resolve(ctx->type->getText());
        Symbol *newConst;

        string name = ctx->name->getText();

        if(!ctx->expr().empty()) {
            vector<int> dimentions;
            for( auto expr : ctx->expr()) {
                Value * a = visit(expr);
                dimentions.push_back(a->getRealValue());
            }
            newConst = Utils::createArrayConstant(ctx->name->getText(), currentScope, dimentions, type);
        }
        else if (type->getTypeIndex() == SymbolTable::tCustom) {
            newConst = Utils::createCustomTypeConstant(ctx->name->getText(), (StructSymbol *) type, currentScope);
        }
        else {
            newConst = new ConstantSymbol(
                    ctx->name->getText(),
                    type
            );
        }
        currentScope->define(newConst);
        return nullptr;
    }

    antlrcpp::Any visitEntityDefinition(CSP2SATParser::EntityDefinitionContext *ctx) override {
        StructSymbol *newType;
        newType = new StructSymbol(ctx->name->getText(), currentScope);
        currentScope->define(newType);

        currentScope = newType;
        CSP2SATBaseVisitor::visitEntityDefinition(ctx);
        currentScope = currentScope->getEnclosingScope();
        return nullptr;
    }

    antlrcpp::Any visitConstraintDefinitionBlock(CSP2SATParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }


};


#endif //CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
