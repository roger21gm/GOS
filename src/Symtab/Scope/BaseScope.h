//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BASESCOPE_H
#define CSP2SAT_BASESCOPE_H


#include <map>
#include "Scope.h"

using namespace std;

class BaseScope: public Scope {

public:
    void define(Symbol *sym) override {
        sym->scope = this;
        symbols[sym->getName()] = sym;
    }

    explicit BaseScope(Scope *parent) : enclosingScope(parent) {}

    Scope * getEnclosingScope() override {
        return this->enclosingScope;
    }

    Symbol * resolve(const string& name) override {
        if ( symbols.find(name) != symbols.end() )
            return symbols[name];
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

private:
    Scope * enclosingScope;
    map<string, Symbol*> symbols;
};


#endif //CSP2SAT_BASESCOPE_H
