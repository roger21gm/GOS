//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATINPUTJSONVISITOR_H
#define CSP2SAT_CSP2SATINPUTJSONVISITOR_H

#include "JSONBaseVisitor.h"
#include "../../Symtab/SymbolTable.h"
#include "../../Symtab/Value/IntValue.h"
#include "../../Symtab/Symbol/Scoped/StructSymbol.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATInputJSONVisitor : public JSONBaseVisitor {
private:
    SymbolTable *st;
    Scope *currentScope;


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
        Symbol *var = currentScope->resolve(varName);

        if (var) {
            if (ctx->value()->obj()) {
                StructSymbol *a = (StructSymbol *) var;
                this->currentScope = a;
                JSONBaseVisitor::visitPair(ctx);
                this->currentScope = a->getEnclosingScope();
            } else if (ctx->value()->arr()) {
                ArraySymbol *a = (ArraySymbol *) var;
                this->currentScope = a;
                JSONBaseVisitor::visitPair(ctx);
                this->currentScope = a->getEnclosingScope();
            } else {
                Value *val = JSONBaseVisitor::visitPair(ctx);
                ((AssignableSymbol *) var)->setValue(val);
            }
        } else {
            throw CSP2SATException(
                    0, 0,
                    "You are assigning '" + varName + "' and it doesn't exist as a param in the viewpoint"
            );
        }


        return nullptr;
    }

    antlrcpp::Any visitArr(JSONParser::ArrContext *ctx) override {
        for (int i = 0; i < ctx->value().size(); ++i) {
            if (ctx->value()[i]->obj()) {
                StructSymbol *arrElem = (StructSymbol *) this->currentScope->resolve(to_string(i));
                this->currentScope = arrElem;
                visit(ctx->value()[i]);
                this->currentScope = arrElem->getEnclosingScope();
            } else if (ctx->value()[i]->arr()) {
                ArraySymbol *arrElem = (ArraySymbol *) this->currentScope->resolve(to_string(i));
                this->currentScope = arrElem;
                visit(ctx->value()[i]);
                this->currentScope = arrElem->getEnclosingScope();
            } else if (ctx->value()[i]->getText() == "null") {
                ((AssignableSymbol *) this->currentScope->resolve(to_string(i)))->setValue(nullptr);
            } else {
                Value *val = JSONBaseVisitor::visit(ctx->value()[i]);
                ((AssignableSymbol *) this->currentScope->resolve(to_string(i)))->setValue(val);
            }
        }
        return nullptr;
    }

    antlrcpp::Any visitValue(JSONParser::ValueContext *ctx) override {
        if (ctx->NUMBER())
            return (Value *) new IntValue(stoi(ctx->getText()));
        else if (ctx->getText() == "true")
            return (Value *) new BoolValue(true);
        else if (ctx->getText() == "false")
            return (Value *) new BoolValue(false);
        else if (ctx->obj()) {
            JSONBaseVisitor::visitValue(ctx);
        } else if (ctx->arr()) {
            return JSONBaseVisitor::visitValue(ctx);
        } else {
            JSONBaseVisitor::visitValue(ctx);
        }
        return nullptr;
    }
};


#endif //CSP2SAT_CSP2SATINPUTJSONVISITOR_H
