//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BUILDINTYPESYMBOL_H
#define CSP2SAT_BUILDINTYPESYMBOL_H


#include "Symbol.h"

class BuildInTypeSymbol: public Symbol, public Type  {
public:
    BuildInTypeSymbol(const string &name, int typeIndex) : Symbol(name), Type(typeIndex) {}

    string getName() override {
        return Symbol::getName();
    }
};


#endif //CSP2SAT_BUILDINTYPESYMBOL_H
