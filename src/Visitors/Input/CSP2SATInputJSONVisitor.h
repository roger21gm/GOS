//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATINPUTJSONVISITOR_H
#define CSP2SAT_CSP2SATINPUTJSONVISITOR_H

#include "JSONBaseVisitor.h"
#include "../../Symtab/SymbolTable.h"
#include "../../Symtab/Symbol/Assignable/AssignableSymbol.h"
#include "../../Symtab/Value/IntValue.h"
#include "../../Symtab/Value/StructValue.h"
#include "../../Symtab/Value/ArrayValue.h"
#include "../../Symtab/Symbol/StructSymbol.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATInputJSONVisitor : public JSONBaseVisitor {
private:
    SymbolTable * st;
    Scope * currentScope;


public:
    explicit CSP2SATInputJSONVisitor(SymbolTable *st) : st(st) {
        currentScope = st->gloabls;
    }

    antlrcpp::Any visitJson(JSONParser::JsonContext *ctx) override {
        return JSONBaseVisitor::visitJson(ctx);
    }

    antlrcpp::Any visitObj(JSONParser::ObjContext *ctx) override {
        return JSONBaseVisitor::visitObj(ctx);
    }

    antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override {
        string varName = ctx->STRING()->getText();
        varName.erase(remove(varName.begin(), varName.end(), '"'), varName.end());
        Symbol * var = currentScope->resolve(varName);

        if(ctx->value()->obj()) {
            StructSymbol* a = (StructSymbol*) var;
            this->currentScope = a;
            JSONBaseVisitor::visitPair(ctx);
            this->currentScope = a->getEnclosingScope();
        }
        else{
            Value * val = JSONBaseVisitor::visitPair(ctx);
            ((AssignableSymbol*)var)->setValue(val);
        }
        return nullptr;
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        JSONBaseVisitor::visitArr(ctx);

        return nullptr;
    }

    antlrcpp::Any visitValue(JSONParser::ValueContext *ctx) override {
        if(ctx->NUMBER())
            return (Value*) new IntValue(stoi(ctx->getText()));
        else if(ctx->obj()){
            JSONBaseVisitor::visitValue(ctx);
        }else{
            JSONBaseVisitor::visitValue(ctx);
        }
//        else if(ctx->arr()){
//            return (Value*) new ArrayValue();
//        }
//        else{
//            cerr << "Error!" << endl;
//        }

        return nullptr;
    }
};


#endif //CSP2SAT_CSP2SATINPUTJSONVISITOR_H
