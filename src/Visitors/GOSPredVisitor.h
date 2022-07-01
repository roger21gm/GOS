#ifndef CSP2SAT_GOSPREDVISITOR_H
#define CSP2SAT_GOSPREDVISITOR_H

#include "GOSCustomBaseVisitor.h"
#include "../Symtab/Symbol/Scoped/PredSymbol.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

namespace GOS {

class GOSPredVisitor : public GOSCustomBaseVisitor {
public:
    explicit GOSPredVisitor(SymbolTable *symbolTable, SMTFormula *f) :
        GOSCustomBaseVisitor(symbolTable, f)
    {
    }

    antlrcpp::Any visitEntityDefinitionBlock(BUPParser::EntityDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitViewpointBlock(BUPParser::ViewpointBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitOutputBlock(BUPParser::OutputBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitConstraintDefinitionBlock(BUPParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitPredDefBlock(BUPParser::PredDefBlockContext *ctx) override {

        for (auto pred : ctx->predDef()) {
            try {
                visit(pred);
            } catch (GOSException &e) {
                std::cerr << e.getErrorMessage() << std::endl;
            }
        }
        return nullptr;


        //return BUPBaseVisitor::visitPredDefBlock(ctx);
    }

    antlrcpp::Any visitVarDefinition(BUPParser::VarDefinitionContext *ctx) override {
        TypeRef type = SymbolTable::_varbool;
        SymbolRef newVar;
        std::string name = ctx->name->getText();
        return type;
    }

    antlrcpp::Any visitParamDefinition(BUPParser::ParamDefinitionContext *ctx) override {
        TypeRef type = Utils::as<Type>(currentScope->resolve(ctx->type->getText()));
        SymbolRef newConst;
        std::string name = ctx->name->getText();
        return type;
    }

    antlrcpp::Any visitPredDef(BUPParser::PredDefContext *ctx) override {
        std::string name = ctx->name->getText();

        // Get whole predicate signature
        PredSymbol::Signature signature;
        signature.first = name;
        for(auto def : ctx->predDefParams()->definition()) {
            // visit definition to define ident in context
            TypeRef type = visit(def);
            signature.second.push_back(type);
        }

        // Check if a predicate with same signature is already declared
        PredSymbolRef pred = PredSymbol::Create(signature, this->currentScope);
        if(this->currentScope->existsInScope(pred->getName())) {
            throw CSP2SATAlreadyExistException(
                    ctx->name->getLine(),
                    ctx->name->getCharPositionInLine(),
                    name
            );
        }
        currentScope->define(pred);
        currentScope = pred;
        BUPBaseVisitor::visitPredDef(ctx);
        currentScope = currentScope->getEnclosingScope();
        return nullptr;
    }

    antlrcpp::Any visitPredDefParams(BUPParser::PredDefParamsContext *ctx) override {
        std::cout << "visitPredDefParams" << std::endl;
        return BUPBaseVisitor::visitPredDefParams(ctx);
    }

    antlrcpp::Any visitPredDefBody(BUPParser::PredDefBodyContext *ctx) override {
        return visitChildren(ctx);
    }

};

}

#endif //CSP2SAT_GOSPREDVISITOR_H
