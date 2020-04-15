//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H


#include "../../../api/smtapi/src/smtformula.h"
#include "ValueSymbol.h"


class VariableSymbol: public ValueSymbol {
public:
    VariableSymbol(const string &name) : ValueSymbol(name, SymbolTable::_varbool) {
        if(!SymbolTable::entityDefinitionBlock)
            var = SymbolTable::_f->newBoolVar();
    }

    VariableSymbol(const string &name, literal lit) : ValueSymbol(name, SymbolTable::_varbool) {
        var = lit;
    }


    bool isAssignable() override {
        return false;
    }

    literal getVar() {
        return var;
    }

private:
    literal var;
};


#endif //CSP2SAT_VARIABLESYMBOL_H
