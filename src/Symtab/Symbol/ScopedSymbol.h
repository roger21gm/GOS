//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SCOPEDSYMBOL_H
#define CSP2SAT_SCOPEDSYMBOL_H


#include "Symbol.h"
#include "../Scope/Scope.h"
#include <map>


using namespace std;

class ScopedSymbol: public Symbol, public Scope {
private:
    Scope * enclosingScope = nullptr;

public:
    ScopedSymbol(const string& name, Type * type, Scope * enclosingScope) : Symbol (name, type) {
        this->enclosingScope = enclosingScope;
    }

    ScopedSymbol(const string& name, Scope * enclosingScope) : Symbol (name) {
        this->enclosingScope = enclosingScope;
    }

    string getScopeName() override {
        return this->name;
    }

    Scope *getEnclosingScope() override {
        return this->enclosingScope;
    }

    void define(Symbol *sym) override {
        sym->scope = this;
        map<string, Symbol*> * fields = getMembers();
        fields->insert(pair<string, Symbol*>(sym->getName(), sym));
    }

    Symbol *resolve(const string& name) override {
        map<string, Symbol*> *fields = getMembers();
        if ( fields->find(name) != fields->end() )
            return fields->find(name)->second;
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    virtual map<string, Symbol*> * getMembers() = 0;
};


#endif //CSP2SAT_SCOPEDSYMBOL_H
