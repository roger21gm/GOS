//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_CONSTANTSYMBOL_H
#define CSP2SAT_CONSTANTSYMBOL_H


#include "Symbol.h"

class ConstantSymbol: public Symbol {
public:
    ConstantSymbol(const string &name, Type *type) : Symbol(name) {}
};


#endif //CSP2SAT_CONSTANTSYMBOL_H
