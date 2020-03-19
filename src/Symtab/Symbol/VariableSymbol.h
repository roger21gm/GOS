//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H


#include "Symbol.h"

class VariableSymbol: public Symbol {
public:
    VariableSymbol(const string &name, Type *type) : Symbol(name, type) {}
};


#endif //CSP2SAT_VARIABLESYMBOL_H
