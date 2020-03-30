//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATINPUTJSONVISITOR_H
#define CSP2SAT_CSP2SATINPUTJSONVISITOR_H

#include "JSONBaseVisitor.h"
#include "../../Symtab/SymbolTable.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATInputJSONVisitor : public JSONBaseVisitor {
private:
    SymbolTable * st;


public:
    explicit CSP2SATInputJSONVisitor(SymbolTable *st) : st(st) {}

    antlrcpp::Any visitJson(JSONParser::JsonContext *ctx) override {
        cout << ctx->getText() <<endl;
        return JSONBaseVisitor::visitJson(ctx);
    }

    antlrcpp::Any visitObj(JSONParser::ObjContext *ctx) override {
        cout << ctx->getText() <<endl;
        return JSONBaseVisitor::visitObj(ctx);
    }

    antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override {
        cout << ctx->getText() <<endl;
        return JSONBaseVisitor::visitPair(ctx);
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        cout << ctx->getText() <<endl;
        return JSONBaseVisitor::visitArr(ctx);
    }

    antlrcpp::Any visitValue(JSONParser::ValueContext *ctx) override {
        cout << ctx->getText() <<endl;
        return JSONBaseVisitor::visitValue(ctx);
    }
};


#endif //CSP2SAT_CSP2SATINPUTJSONVISITOR_H
