//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H


#include "AssignableSymbol.h"

class VariableSymbol: public AssignableSymbol {
public:
    VariableSymbol(const string &name, Type *type) : AssignableSymbol(name, type) {}


private:
    Value * val{};

};


#endif //CSP2SAT_VARIABLESYMBOL_H
