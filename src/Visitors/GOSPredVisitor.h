#ifndef CSP2SAT_GOSPREDVISITOR_H
#define CSP2SAT_GOSPREDVISITOR_H

#include "GOSCustomBaseVisitor.h"
#include "../Symtab/Symbol/Scoped/PredSymbol.h"
#include "../Symtab/SymbolTable.h"
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

    antlrcpp::Any visitPredDefBlock(BUPParser::PredDefBlockContext *ctx) override {

        int i = 0;
        for (auto pred : ctx->predDef()) {
            try {
                if (i == 0) {
                    globalCtx = ctx;
                }
                visit(pred);
                i++;
            } catch (GOSException &e) {
                std::cerr << e.getErrorMessage() << std::endl;
            }
        }
        return nullptr;


        //return BUPBaseVisitor::visitPredDefBlock(ctx);
    }

    antlrcpp::Any visitVarDefinition(BUPParser::VarDefinitionContext *ctx) override {
        PredSymbol::ParamRef param(new PredSymbol::Param);
        param->name = ctx->name->getText();

        const bool isArray = ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty();
        if (isArray)
            param->type = SymbolTable::tArray;
        param->type = SymbolTable::tVarBool;

        return param;
    }

    antlrcpp::Any visitParamDefinition(BUPParser::ParamDefinitionContext *ctx) override {
        PredSymbol::ParamRef param(new PredSymbol::Param);
        param->name = ctx->name->getText();

        const bool isArray = ctx->arrayDefinition() && !ctx->arrayDefinition()->expr().empty();
        if (isArray)
            param->type = SymbolTable::tArray;
        else
            param->type = Utils::as<Type>(currentScope->resolve(ctx->type->getText()))->getTypeIndex();

        return param;
    }

    antlrcpp::Any visitPredDef(BUPParser::PredDefContext *ctx) override {
        std::string name = ctx->name->getText();

        // Get whole predicate signature
        PredSymbol::Signature signature;
        signature.name = name;
        if(ctx->predDefParams()) {
            for (auto defCtx: ctx->predDefParams()->definition()) {
                PredSymbol::ParamRef param = visit(defCtx);
                signature.params.push_back(*param);
            }
        }

        // Check if a predicate with same signature is already declared
        if(this->currentScope->existsInScope(PredSymbol::signatureToSymbolTableName(signature))) {
            throw CSP2SATAlreadyExistException(
                    ctx->name->getLine(),
                    ctx->name->getCharPositionInLine(),
                    name
            );
        }

        PredSymbolRef pred = PredSymbol::Create(signature, ctx, this->currentScope);
        currentScope->define(pred);
        //currentScope = pred;
        //SMTFormula* currentFormula = _f;
        //_f = new SMTFormula();
        //GOSConstraintsVisitor::visitConstraintDefinition(ctx->predDefBody()->constraintDefinition());
        //_f = currentFormula;
        //currentScope = currentScope->getEnclosingScope();

        return nullptr;
    }

    antlrcpp::Any visitPredDefParams(BUPParser::PredDefParamsContext *ctx) override {
        std::cout << "visitPredDefParams" << std::endl;
        return BUPBaseVisitor::visitPredDefParams(ctx);
    }

    antlrcpp::Any visitPredDefBody(BUPParser::PredDefBodyContext *ctx) override {
        return BUPBaseVisitor::visitPredDefBody(ctx);
    }

};

}

#endif //CSP2SAT_GOSPREDVISITOR_H
