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
    ParamJSONRef base;
    ParamScopedRef current;
    std::filesystem::path _file;

public:

    GOSJSONInputVisitor(const std::filesystem::path& file) : _file(file) {
        base = ParamJSON::Create("base");
        current = base;
    }


    antlrcpp::Any visitPair(JSONParser::PairContext *ctx) override {
        std::string varName = ctx->STRING()->getText();
        varName.erase(remove(varName.begin(), varName.end(), '"'), varName.end());

        ParamScopedRef curr = current;
        if (ctx->value()->NUMBER()) {
            current->add(
                    ParamInt::Create(
                            varName,
                            stoi(ctx->value()->NUMBER()->getText())
                    )
            );
        } else if (ctx->value()->getText() == "true" || ctx->value()->getText() == "false") {
            current->add(
                    ParamBool::Create(
                            varName,
                            ctx->value()->getText() == "true"
                    )
            );
        } else if (ctx->value()->arr()) {
            ParamArrayRef array = ParamArray::Create(varName);
            current->add(array);
            // TODO Why not add(visit(ctx->value()->arr()))?? (if visit returned the appropiate object instead of nullptr)
            current = array;
            visit(ctx->value()->arr());
            current = curr;

        } else if (ctx->value()->obj()) {
            ParamJSONRef strct = ParamJSON::Create(varName);
            current->add(strct);
            current = strct;
            visit(ctx->value()->obj());
            current = curr;
        } else {
            throw CSP2SATBadInputTypeException(
                {
                    _file,
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                },
                varName
            );
        }


        return nullptr;
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        int index = 0;
        ParamScopedRef curr = current;
        for (auto currVal : ctx->value()) {
            if (currVal->NUMBER()) {
                current->add(
                        ParamInt::Create(
                                std::to_string(index),
                                stoi(currVal->NUMBER()->getText())
                        )
                );
                index++;
            } else if (currVal->getText() == "true" || currVal->getText() == "false") {
                current->add(
                        ParamBool::Create(
                                std::to_string(index),
                                currVal->getText() == "true"
                        )
                );
            } else if (currVal->arr()) {
                ParamArrayRef array = ParamArray::Create(std::to_string(index));
                current->add(array);
                current = array;
                visit(currVal->arr());
                current = curr;
                index++;

            } else if (currVal->obj()) {
                ParamJSONRef strct = ParamJSON::Create(std::to_string(index));
                current->add(strct);
                current = strct;
                visit(currVal->obj());
                current = curr;
                index++;
            } else {
                throw CSP2SATBadInputTypeException(
                    {
                        _file,
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                    },
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
