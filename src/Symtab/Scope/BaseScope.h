//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BASESCOPE_H
#define CSP2SAT_BASESCOPE_H


#include <map>
#include "Scope.h"

using namespace std;

class BaseScope: public Scope {

private:
    Scope * enclosingScope;
    map<string, Symbol*> symbols;

public:
    explicit BaseScope(Scope *parent) : enclosingScope(parent) {}

    Scope *getEnclosingScope() override {
        return this->enclosingScope;
    }

    Symbol * resolve(string name) override {
        if ( symbols.find(name) != symbols.end() ) return symbols[name];
        if ( enclosingScope != nullptr ) return enclosingScope->resolve(name);
        return nullptr;
    }

    void define(Symbol *sym) override {
        sym->scope = this;
        symbols[sym->getName()] = sym;
    }

};


#endif //CSP2SAT_BASESCOPE_H
