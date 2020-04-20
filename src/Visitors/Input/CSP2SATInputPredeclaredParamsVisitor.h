//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_CSP2SATINPUTPREDECLAREDPARAMSVISITOR_H
#define CSP2SAT_CSP2SATINPUTPREDECLAREDPARAMSVISITOR_H

#include <JSONBaseVisitor.h>
#include "ParamsPredeclare/Param.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATInputPredeclaredParamsVisitor : public JSONBaseVisitor {

private:
    ParamJSON *base;
    ParamScoped *current;

public:

    CSP2SATInputPredeclaredParamsVisitor() {
        base = new ParamJSON("base");
        current = base;
    }

    antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override {
        string varName = ctx->STRING()->getText();
        varName.erase(remove(varName.begin(), varName.end(), '"'), varName.end());

        ParamScoped * curr = current;
        if (ctx->value()->NUMBER()) {
            current->add(
                    new ParamInt(
                            varName,
                            stoi(ctx->value()->NUMBER()->getText())
                    )
            );
        } else if (ctx->value()->arr()) {
            ParamArray * array = new ParamArray(varName);
            current->add(array);
            current = array;
            visit(ctx->value()->arr());
            current = curr;

        } else if (ctx->value()->obj()){
            ParamJSON * strct = new ParamJSON(varName);
            current->add(strct);
            current = strct;
            visit(ctx->value()->obj());
            current = curr;
        }
        return nullptr;
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        int index = 0;
        ParamScoped * curr = current;
        for(auto currVal : ctx->value()){
            if (currVal->NUMBER()) {
                current->add(
                        new ParamInt(
                                to_string(index),
                                stoi(currVal->NUMBER()->getText())
                        )
                );
                index++;
            } else if (currVal->arr()) {
                ParamArray * array = new ParamArray(to_string(index));
                current->add(array);
                current = array;
                visit(currVal->arr());
                current = curr;
                index++;

            } else if (currVal->obj()){
                ParamJSON * strct = new ParamJSON(to_string(index));
                current->add(strct);
                current = strct;
                visit(currVal->obj());
                current = curr;
                index++;
            }
        }
        return nullptr;
    }


    antlrcpp::Any visitJson(JSONParser::JsonContext *ctx) override {
        cout << 1 << endl;
        JSONBaseVisitor::visitJson(ctx);
        cout << 2 << endl;
        return base;
    }
};


#endif //CSP2SAT_CSP2SATINPUTPREDECLAREDPARAMSVISITOR_H
