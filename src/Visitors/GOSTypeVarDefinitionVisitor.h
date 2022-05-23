//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_GOSTYPEVARDEFINITIONVISITOR_H
#define CSP2SAT_GOSTYPEVARDEFINITIONVISITOR_H

#include "GOSCustomBaseVisitor.h"
#include "Input/Param.h"
#include <string>
#include <vector>

namespace GOS {

class GOSTypeVarDefinitionVisitor : public GOSCustomBaseVisitor {
private:
    ParamJSONRef params;

public:
    explicit GOSTypeVarDefinitionVisitor(SymbolTable *symbolTable, SMTFormula *f, ParamJSONRef params)
            : GOSCustomBaseVisitor(symbolTable, f) {
        this->params = params;
    }

    antlrcpp::Any visitEntityDefinitionBlock(BUPParser::EntityDefinitionBlockContext *ctx) override {
        SymbolTable::entityDefinitionBlock = true;
        BUPBaseVisitor::visitEntityDefinitionBlock(ctx);
        SymbolTable::entityDefinitionBlock = false;
        return nullptr;
    }

    antlrcpp::Any visitViewpointBlock(BUPParser::ViewpointBlockContext *ctx) override {
        return BUPBaseVisitor::visitViewpointBlock(ctx);
    }

    antlrcpp::Any visitConstraintDefinitionBlock(BUPParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitOutputBlock(BUPParser::OutputBlockContext *ctx) override {
        return nullptr;
    }


    antlrcpp::Any visitDefinition(BUPParser::DefinitionContext *ctx) override {
        try {
            return BUPBaseVisitor::visitDefinition(ctx);
        }
        catch (GOSException &e) {
            std::cerr << e.getErrorMessage() << std::endl;
            return nullptr;
        }
    }


    antlrcpp::Any visitVarDefinition(BUPParser::VarDefinitionContext *ctx) override {
        BUPBaseVisitor::visitVarDefinition(ctx);
        SymbolRef newVar;
        std::string name = ctx->name->getText();

        if(this->currentScope->existsInScope(name)) {
            throw CSP2SATAlreadyExistException(
                    ctx->name->getLine(),
                    ctx->name->getCharPositionInLine(),
                    name
            );
        }

        if (ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty()) {
            std::vector<int> dimentions;
            for (auto expr : ctx->arrayDefinition()->expr()) {
                ValueRef a = visit(expr);
                dimentions.push_back(a->getRealValue());
            }
            newVar = VisitorsUtils::defineNewArray(ctx->name->getText(), currentScope, dimentions, SymbolTable::_varbool,
                                           this->_f, this->params);
        } else {
            newVar = VariableSymbol::Create(ctx->name->getText(), this->_f);
        }
        currentScope->define(newVar);

        return nullptr;

    }

    antlrcpp::Any visitParamDefinition(BUPParser::ParamDefinitionContext *ctx) override {
        BUPBaseVisitor::visitParamDefinition(ctx);

        TypeRef type = Utils::as<Type>(currentScope->resolve(ctx->type->getText()));
        SymbolRef newConst;

        std::string name = ctx->name->getText();

        if(this->currentScope->existsInScope(name)) {
            throw CSP2SATAlreadyExistException(
                    ctx->name->getLine(),
                    ctx->name->getCharPositionInLine(),
                    name
            );
        }


        if (ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty()) {
            std::vector<int> dimentions;
            for (auto expr : ctx->arrayDefinition()->expr()) {
                ValueRef a = visit(expr);
                dimentions.push_back(a->getRealValue());
            }

            newConst = VisitorsUtils::defineNewArray(ctx->name->getText(), currentScope, dimentions, type, this->_f,
                                             this->params);
        } else if (type->getTypeIndex() == SymbolTable::tCustom) {
            newConst = VisitorsUtils::definewNewCustomTypeParam(ctx->name->getText(), Utils::as<StructSymbol>(type), currentScope,
                                                        this->_f, this->params);
        } else {
            AssignableSymbolRef element = AssignableSymbol::Create(
                    ctx->name->getText(),
                    type
            );
            if (!SymbolTable::entityDefinitionBlock) {
                std::string paramFullName = this->currentScope->getFullName() + ctx->name->getText();
                int value = this->params->resolve(paramFullName);
                if (type->getTypeIndex() == SymbolTable::tInt)
                    element->setValue(IntValue::Create(value));
                else
                    element->setValue(BoolValue::Create(value));
            }
            newConst = element;
        }
        currentScope->define(newConst);
        return nullptr;
    }

    antlrcpp::Any visitEntityDefinition(BUPParser::EntityDefinitionContext *ctx) override {
        StructSymbolRef newType;
        newType = StructSymbol::Create(ctx->name->getText(), currentScope);
        currentScope->define(newType);

        currentScope = newType;
        BUPBaseVisitor::visitEntityDefinition(ctx);
        currentScope = currentScope->getEnclosingScope();
        return nullptr;
    }

    antlrcpp::Any visitVarAccess(BUPParser::VarAccessContext *ctx) override {
        try {
            int value = this->params->resolve(ctx->getText());
            AssignableSymbolRef access = AssignableSymbol::Create(ctx->getText(), SymbolTable::_integer);
            access->setValue(IntValue::Create(value));
            return Utils::as<Symbol>(access);
        }
        catch (GOSException &e) {
            throw CSP2SATNotExistsException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
        }
    }

    antlrcpp::Any visitListResultExpr(BUPParser::ListResultExprContext *ctx) override {
        if (!ctx->string()) {
            return GOSCustomBaseVisitor::visitListResultExpr(ctx);
        } else {
            throw CSP2SATStringOnlyOutputException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
        }
    }
};

}

#endif //CSP2SAT_GOSTYPEVARDEFINITIONVISITOR_H
