//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
#define CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"
#include "Input/ParamsPredeclare/Param.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATTypeVarDefinitionVisitor : public CSP2SATCustomBaseVisitor {
private:
    ParamJSON * params;

public:
    explicit CSP2SATTypeVarDefinitionVisitor(SymbolTable *symbolTable, SMTFormula * f, ParamJSON * params) : CSP2SATCustomBaseVisitor(symbolTable, f) {
        this->params = params;
    }

    antlrcpp::Any visitEntityDefinitionBlock(CSP2SATParser::EntityDefinitionBlockContext *ctx) override {
        SymbolTable::entityDefinitionBlock = true;
        CSP2SATBaseVisitor::visitEntityDefinitionBlock(ctx);
        SymbolTable::entityDefinitionBlock = false;
        return nullptr;
    }


    antlrcpp::Any visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) override {

        CSP2SATBaseVisitor::visitVarDefinition(ctx);

        Symbol *newVar;
        string name = ctx->name->getText();
        if(ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty()) {
            vector<int> dimentions;
            for( auto expr : ctx->arrayDefinition()->expr()) {
                Value * a = visit(expr);
                dimentions.push_back(a->getRealValue());
            }
            newVar = Utils::defineNewArray(ctx->name->getText(), currentScope, dimentions, SymbolTable::_varbool, this->_f);
        }
        else {
            newVar = new VariableSymbol(ctx->name->getText(), this->_f);
        }
        currentScope->define(newVar);

        return nullptr;

    }

    antlrcpp::Any visitParamDefinition(CSP2SATParser::ParamDefinitionContext *ctx) override {
        CSP2SATBaseVisitor::visitParamDefinition(ctx);

        Type *type = (Type *) currentScope->resolve(ctx->type->getText());
        Symbol *newConst;

        string name = ctx->name->getText();

        if(ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty()) {
            vector<int> dimentions;
            for( auto expr : ctx->arrayDefinition()->expr()) {
                Value * a = visit(expr);
                dimentions.push_back(a->getRealValue());
            }
            newConst = Utils::defineNewArray(ctx->name->getText(), currentScope, dimentions, type, this->_f);
        }
        else if (type->getTypeIndex() == SymbolTable::tCustom) {
            newConst = Utils::definewNewCustomTypeParam(ctx->name->getText(), (StructSymbol *) type, currentScope, this->_f);
        }
        else {
            newConst = new AssignableSymbol(
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

    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        int value = this->params->resolve(ctx->getText());
        AssignableSymbol * access = new AssignableSymbol(ctx->getText(), SymbolTable::_integer);
        access->setValue(new IntValue(value));
        return (Symbol *) access;
    }

    antlrcpp::Any visitConstraintDefinitionBlock(CSP2SATParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }

};


#endif //CSP2SAT_CSP2SATTYPEVARDEFINITIONVISITOR_H
