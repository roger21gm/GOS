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

    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        cout << ctx->getText() << " -> ";
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
