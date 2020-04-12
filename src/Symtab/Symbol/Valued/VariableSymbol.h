//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H


#include "../../../api/smtapi/src/smtformula.h"
#include "ValueSymbol.h"


class VariableSymbol: public ValueSymbol {
public:
    VariableSymbol(const string &name, boolvar varValue) : ValueSymbol(name, SymbolTable::_varbool) {
        this->var = varValue;
    }

    bool isAssignable() override {
        return false;
    }

    boolvar getVar() {
        return var;
    }

private:
    boolvar var;
};


#endif //CSP2SAT_VARIABLESYMBOL_H
