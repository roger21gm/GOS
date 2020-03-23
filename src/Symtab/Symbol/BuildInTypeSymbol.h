//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BUILDINTYPESYMBOL_H
#define CSP2SAT_BUILDINTYPESYMBOL_H


#include "Symbol.h"

class BuildInTypeSymbol: public Symbol, public Type  {
public:
    explicit BuildInTypeSymbol(const string &name) : Symbol(name) {}
    BuildInTypeSymbol(const string &name, int typeIndex) : Symbol(name) {
        this->typeIndex = typeIndex;
    }

    string getName() override {
        return Symbol::getName();
    }

    int getTypeIndex() override {
        return this->typeIndex;
    }

private:
    int typeIndex {};
};


#endif //CSP2SAT_BUILDINTYPESYMBOL_H
