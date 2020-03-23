//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_STRUCTSYMBOL_H
#define CSP2SAT_STRUCTSYMBOL_H


#include "ScopedSymbol.h"

class StructSymbol : public ScopedSymbol, public Type {

private:
    map<string, Symbol*> fields;

public:
    StructSymbol(const string& name, Scope * parent) : ScopedSymbol(name, parent) {}

    Symbol * resolveMember(const string& name) {
        return fields[name];
    }

    Symbol *resolve(const string &name) override {
        return ScopedSymbol::resolve(name);
    }

    string getName() override {
        return ScopedSymbol::getName();
    }

    int getTypeIndex() override {
        return SymtbolTable::tCustom;
    }


    map<string, Symbol *> getMembers() override {
        return fields;
    }
};


#endif //CSP2SAT_STRUCTSYMBOL_H
