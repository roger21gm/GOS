//
// Created by Roger Generoso Masós on 24/04/2020.
//

#ifndef CSP2SAT_GOSOUTPUTVISITOR_H
#define CSP2SAT_GOSOUTPUTVISITOR_H

#include "../GOSCustomBaseVisitor.h"
#include <string>
#include <iostream>

namespace GOS {

class CSP2SATOutputVisitor : public GOSCustomBaseVisitor {

public:
    CSP2SATOutputVisitor(SymbolTable *symbolTable, SMTFormula *f) : GOSCustomBaseVisitor(symbolTable, f) {}

    antlrcpp::Any visitCsp2sat(BUPParser::Csp2satContext *ctx) override {
        if(ctx->outputBlock()){
            BUPBaseVisitor::visitCsp2sat(ctx);
            return true;
        }
        return false;
    }

    antlrcpp::Any visitOutputBlock(BUPParser::OutputBlockContext *ctx) override {
        for(auto str : ctx->string()) {
            try{
                std::string out = visit(str);
                std::cout << out << std::endl;
            }
            catch (GOSException & e) {
                std::cerr << e.getErrorMessage() << std::endl;
                return nullptr;
            }
        }
        return nullptr;
    }

    antlrcpp::Any visitString(BUPParser::StringContext *ctx) override {
        std::string result = "";
        if(ctx->TK_STRING()){
            std::string iniText = ctx->TK_STRING()->getText();
            iniText.erase(std::remove(iniText.begin(),iniText.end(),'\"'),iniText.end());
            result = GOS::Utils::toRawString(iniText);

        }
        else if(ctx->stringTernary()){
            std::string ternaryResult = visit(ctx->stringTernary());
            result = ternaryResult;
        }
        else if(ctx->list()){
            ArraySymbolRef str = visit(ctx->list());
            if(str->getElementsType()->getTypeIndex() == SymbolTable::tString){
                for(auto currStr : str->getSymbolVector())
                    result += currStr->getName();
            }
            else {
                throw CSP2SATStringOnlyOutputException(
                    {
                        st->parsedFiles.front()->getPath(),
                        ctx->list()->start->getLine(),
                        ctx->list()->start->getCharPositionInLine()
                    },
                    ctx->list()->getText()
                );
            }
        }
        else if(ctx->concatString()){
            std::string lString = visit(ctx->string());
            std::string rString = visit(ctx->concatString()->string());
            result = lString + rString;

            auto currentConcat = ctx->concatString()->concatString();
            while(currentConcat){
                std::string current = visit(currentConcat->string());
                result += current;
                currentConcat = currentConcat->concatString();
            }
        }
        else if(ctx->expr()){
            ValueRef val = visit(ctx->expr());
            result = std::to_string(val->getRealValue());
        }
        else if(ctx->varAccess()){
            accessingNotLeafVariable = true;
            SymbolRef var = visit(ctx->varAccess());
            accessingNotLeafVariable = false;
            if(!var->isScoped()){
                if(var->isAssignable())
                    result = std::to_string(Utils::as<AssignableSymbol>(var)->getValue()->getRealValue());
                else
                    result = Utils::as<VariableSymbol>(var)->getModelValue() ? "true" : "false";
            }
            else {
                ArraySymbolRef arrayAccess = Utils::as<ArraySymbol>(var);
                result += "[";
                for(auto elem : arrayAccess->getSymbolVector()){
                    if(elem->isAssignable())
                        result += std::to_string(Utils::as<AssignableSymbol>(elem)->getValue()->getRealValue());
                    else
                        result += Utils::as<VariableSymbol>(elem)->getModelValue() ? "true" : "false";

                    if(elem != arrayAccess->getSymbolVector().back())
                        result += ", ";
                }
                result += "]";
            }

        }
        else if(ctx->TK_LPAREN()){
            std::string innerParen = visit(ctx->string());
            result = innerParen;
        }
        return (std::string) result;
    }

    antlrcpp::Any visitStringTernary(BUPParser::StringTernaryContext *ctx) override {
        ValueRef cond = visit(ctx->condition);

        if(cond->getRealValue())
            return visit(ctx->op1);
        else
            return visit(ctx->op2);
    }

    antlrcpp::Any visitExpr_base(BUPParser::Expr_baseContext *ctx) override {
        if (ctx->expr()) {
            return visit(ctx->expr());
        } else if (ctx->varAccess()) {
            SymbolRef value = visit(ctx->varAccess());
            if (value->isAssignable()) {
                return Utils::as<AssignableSymbol>(value)->getValue();
            } else {
                bool a = Utils::as<VariableSymbol>(value)->getModelValue();
                ValueRef modelValue = BoolValue::Create(a);
                return modelValue;
            }
        }
        return BUPBaseVisitor::visitExpr_base(ctx);
    }
};

}

#endif //CSP2SAT_GOSOUTPUTVISITOR_H
