//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_GOSJSONINPUTVISITOR_H
#define CSP2SAT_GOSJSONINPUTVISITOR_H

#include <JSONBaseVisitor.h>
#include "Param.h"
#include "../../Errors/GOSInputExceptionsRepository.h"
#include <string>
#include <utility>

namespace GOS {

class GOSJSONInputVisitor : public JSONBaseVisitor {

private:
    ParamJSON *base;
    ParamScoped *current;

public:

    GOSJSONInputVisitor() {
        base = new ParamJSON("base");
        current = base;
    }


    antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override {
        std::string varName = ctx->STRING()->getText();
        varName.erase(remove(varName.begin(), varName.end(), '"'), varName.end());

        ParamScoped *curr = current;
        if (ctx->value()->NUMBER()) {
            current->add(
                    new ParamInt(
                            varName,
                            stoi(ctx->value()->NUMBER()->getText())
                    )
            );
        } else if (ctx->value()->getText() == "true" || ctx->value()->getText() == "false") {
            current->add(
                    new ParamBool(
                            varName,
                            ctx->value()->getText() == "true"
                    )
            );
        } else if (ctx->value()->arr()) {
            ParamArray *array = new ParamArray(varName);
            current->add(array);
            // TODO Why not add(visit(ctx->value()->arr()))?? (if visit returned the appropiate object instead of nullptr)
            current = array;
            visit(ctx->value()->arr());
            current = curr;

        } else if (ctx->value()->obj()) {
            ParamJSON *strct = new ParamJSON(varName);
            current->add(strct);
            current = strct;
            visit(ctx->value()->obj());
            current = curr;
        } else {
            throw CSP2SATBadInputTypeException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    varName
            );
        }


        return nullptr;
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        int index = 0;
        ParamScoped *curr = current;
        for (auto currVal : ctx->value()) {
            if (currVal->NUMBER()) {
                current->add(
                        new ParamInt(
                                std::to_string(index),
                                stoi(currVal->NUMBER()->getText())
                        )
                );
                index++;
            } else if (currVal->getText() == "true" || currVal->getText() == "false") {
                current->add(
                        new ParamBool(
                                std::to_string(index),
                                currVal->getText() == "true"
                        )
                );
            } else if (currVal->arr()) {
                ParamArray *array = new ParamArray(std::to_string(index));
                current->add(array);
                current = array;
                visit(currVal->arr());
                current = curr;
                index++;

            } else if (currVal->obj()) {
                ParamJSON *strct = new ParamJSON(std::to_string(index));
                current->add(strct);
                current = strct;
                visit(currVal->obj());
                current = curr;
                index++;
            } else {
                throw CSP2SATBadInputTypeException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        std::to_string(index)
                );

            }
        }
        return nullptr;
    }

    antlrcpp::Any visitJson(JSONParser::JsonContext *ctx) override {
        JSONBaseVisitor::visitJson(ctx);
        return base;
    }
};

}

#endif //CSP2SAT_GOSJSONINPUTVISITOR_H
