//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_STRUCTSYMBOL_H
#define CSP2SAT_STRUCTSYMBOL_H


#include "ScopedSymbol.h"

class StructSymbol : public ScopedSymbol {

private:
    map<string, Symbol*> fields = {};

public:

    //Constructor for creating typed constants of this custom type.
    StructSymbol(string name, Type * type, Scope * enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {
        this->type = type;
    }

    //Constructor for creating the definition of the custom type.
    StructSymbol(const string& name, Scope * enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {}

    void define(Symbol *sym) override {
        fields.insert(pair<string, Symbol*>(sym->getName(), sym));
    }

    Symbol *resolve(const string& name) override {
        if ( fields.find(name) != fields.end() )
            return fields.find(name)->second;
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    map<string, Symbol*> getScopeSymbols() override {
        return this->fields;
    }

    bool existsInScope(const string &name) override {
        return fields.find(name) != fields.end();
    }
};


#endif //CSP2SAT_STRUCTSYMBOL_H
