//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
#define CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H

#include <CSP2SATLexer.h>
#include "../Symtab/SymbolTable.h"
#include "CSP2SATBaseVisitor.h"
#include "../Symtab/Value/IntValue.h"
#include "../Symtab/Value/BoolValue.h"
#include "../Symtab/Scope/LocalScope.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATCustomBaseVisitor: public CSP2SATBaseVisitor {

protected:
    SymbolTable * st;
    Scope *currentScope;


public:

    explicit CSP2SATCustomBaseVisitor(SymbolTable * symbolTable) {
        this->st = symbolTable;
        this->currentScope = this->st->gloabls;
    }

    antlrcpp::Any visitExprTernary(CSP2SATParser::ExprTernaryContext *ctx) override {
        Value * condition = visit(ctx->condition);
        if(condition->getRealValue())
            return visit(ctx->op1);
        else
            return visit(ctx->op2);
    }

    antlrcpp::Any visitExprAnd(CSP2SATParser::ExprAndContext *ctx) override {
        Value * result = visit(ctx->exprOr(0));
        if(ctx->exprOr().size() > 1){
            BoolValue * res = new BoolValue(true);
            for(int i=0; i < ctx->exprOr().size(); i++){
                Value * currValue = visit(ctx->exprOr(i));
                res->setRealValue(res->getRealValue() && currValue->getRealValue());
            }
            return (Value*) res;
        }
        return result;
    }

    antlrcpp::Any visitExprOr(CSP2SATParser::ExprOrContext *ctx) override {
        Value * result = visit(ctx->exprEq(0));
        if(ctx->exprEq().size() > 1){
            BoolValue * res = new BoolValue(false);
            for(int i=0; i < ctx->exprEq().size(); i++){
                Value * currValue = visit(ctx->exprEq(i));
                if(currValue->isBoolean())
                    res->setRealValue(res->getRealValue() || currValue->getRealValue());
                else {
                    cerr << ctx->exprEq(i)->getText() << " is not a boolean value" << endl;
                    throw;
                }
            }
            return (Value*) res;
        }
        return result;
    }


    antlrcpp::Any visitExprEq(CSP2SATParser::ExprEqContext *ctx) override {
        Value * lVal = visit(ctx->exprRel(0));
        if (ctx->exprRel().size() == 2) {
            Value * rVal = visit(ctx->exprRel(1));
            if(lVal->isBoolean() == rVal->isBoolean()){
                BoolValue *res = new BoolValue();
                if (ctx->opEquality(0)->getText() == "==")
                    res->setRealValue(lVal->getRealValue() == rVal->getRealValue());
                else
                    res->setRealValue(lVal->getRealValue() != rVal->getRealValue());
                return (Value *) res;
            } else {
                cerr << "Equality operation types don't match" << endl;
                throw;
            }
        }
        else if(ctx->exprRel().size() > 2) {
            cerr << "Invalid equality operation int vs bool" << endl;
            throw;
        }
        return lVal;
    }


    antlrcpp::Any visitExprRel(CSP2SATParser::ExprRelContext *ctx) override {
        Value * lVal = visit(ctx->exprSumDiff(0));
        if (ctx->exprSumDiff().size() == 2) {
            Value *rVal = visit(ctx->exprSumDiff(1));
            if(lVal->isBoolean() == rVal->isBoolean()){
                BoolValue *res = new BoolValue();
                if (ctx->opRelational(0)->getText() == "<")
                    res->setRealValue(lVal->getRealValue() < rVal->getRealValue());
                else if (ctx->opRelational(0)->getText() == ">")
                    res->setRealValue(lVal->getRealValue() > rVal->getRealValue());
                else if (ctx->opRelational(0)->getText() == "<=")
                    res->setRealValue(lVal->getRealValue() <= rVal->getRealValue());
                else
                    res->setRealValue(lVal->getRealValue() >= rVal->getRealValue());
                return (Value *) res;
            } else {
                cerr << "Relational operation types don't match" << endl;
                throw;
            }
        }
        else if(ctx->exprSumDiff().size() > 2) {
            cerr << "Invalid relational operation int vs bool" << endl;
            throw;
        }
        return lVal;
    }

    antlrcpp::Any visitExprSumDiff(CSP2SATParser::ExprSumDiffContext *ctx) override {
        Value * result = visit(ctx->exprMulDivMod(0));
        if(ctx->exprMulDivMod().size() > 1){
            IntValue * res = new IntValue(result->getRealValue());
            for(int i=0; i < ctx->opSumDiff().size(); i++){
                Value * currValue = visit(ctx->exprMulDivMod(i+1));
                if(!currValue->isBoolean()){
                    if(ctx->opSumDiff(i)->getText() == "+")
                        res->setRealValue(res->getRealValue() + currValue->getRealValue());
                    else
                        res->setRealValue(res->getRealValue() - currValue->getRealValue());
                }
                else {
                    cerr << ctx->exprMulDivMod(i+1)->getText() << " is not an int value" << endl;
                    throw;
                }

            }
            return (Value*) res;
        }
        return result;
    }

    antlrcpp::Any visitExprMulDivMod(CSP2SATParser::ExprMulDivModContext *ctx) override {
        Value * result = visit(ctx->exprNot(0));
        if(ctx->exprNot().size() > 1){
            IntValue * res = new IntValue(result->getRealValue());
            for(int i=0; i < ctx->opMulDivMod().size(); i++){
                Value * currValue = visit(ctx->exprNot(i+1));
                if(!currValue->isBoolean()){
                    if(ctx->opMulDivMod(i)->getText() == "*")
                        res->setRealValue(res->getRealValue() * currValue->getRealValue());
                    else if (ctx->opMulDivMod(i)->getText() == "/")
                        res->setRealValue(res->getRealValue() / currValue->getRealValue());
                    else
                        res->setRealValue(res->getRealValue() % currValue->getRealValue());
                }
                else {

                }
            }
            return (Value*) res;
        }
        return result;
    }

    antlrcpp::Any visitExprNot(CSP2SATParser::ExprNotContext *ctx) override {
        Value * result = visit(ctx->expr_base());
        if(ctx->op){
            if(result->isBoolean()){
                return (Value*) new BoolValue(!result->getRealValue());
            } else {
                cerr << ctx->getText() << ": can't negate a non-boolean value" << endl;
                throw;
            }
        }
        return result;
    }


    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override {
        if(ctx->expr()){
            return visit(ctx->expr());
        }
        return CSP2SATBaseVisitor::visitExpr_base(ctx);
    }


    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        string a = ctx->id->getText();
        Symbol * var = this->currentScope->resolve(ctx->id->getText());
        if(!ctx->varAccessObjectOrArray().empty()){
            Value * val = nullptr;
            ScopedSymbol * nestedScope = (ScopedSymbol *) var;
            this->currentScope = nestedScope;
            for(int i = 0; i < ctx->varAccessObjectOrArray().size(); i++){
                auto nestedElem = ctx->varAccessObjectOrArray()[i];
                string nestedElementToFind;
                if(nestedElem->index){
                    nestedElementToFind = to_string(((Value*) visit(nestedElem->index))->getRealValue());
                }
                else{
                    nestedElementToFind = nestedElem->attr->getText();
                }

                if(i == ctx->varAccessObjectOrArray().size()-1){
                    Symbol * valueSymbol = this->currentScope->resolve(nestedElementToFind);
                    if(valueSymbol->isAssignable()){
                        val = ((AssignableSymbol*) valueSymbol)->getValue();
                    }
                    else throw runtime_error(ctx->getText() + " is not a variable/constant");
                }
                else {
                    this->currentScope = (ScopedSymbol*) this->currentScope->resolve(nestedElementToFind);
                }
            }
            this->currentScope = nestedScope->getEnclosingScope();
            return val;
        } else {
            AssignableSymbol * a = (AssignableSymbol*) var;
            return (Value*) a->getValue();
        }
    }

    antlrcpp::Any visitValueBaseType(CSP2SATParser::ValueBaseTypeContext *ctx) override {
        if (ctx->integer) {
            return (Value*) new IntValue(stoi(ctx->integer->getText()));
        } else {
            return (Value*) new BoolValue(ctx->boolean->getText() == "true");
        }
    }
};


#endif //CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
