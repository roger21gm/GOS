//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H

#include "ValueSymbol.h"
#include <string>

namespace GOS {

class VariableSymbol: public ValueSymbol {
public:
    VariableSymbol(const std::string &name, SMTFormula *f) : ValueSymbol(name, SymbolTable::_varbool) {
        if(!SymbolTable::entityDefinitionBlock)
            var = f->newBoolVar();
    }

    VariableSymbol(const std::string &name, literal lit) : ValueSymbol(name, SymbolTable::_varbool) {
        var = lit;
    }

    bool isAssignable() override {
        return false;
    }

    literal getVar() {
        return var;
    }

    bool getModelValue() const {
        return modelValue;
    }

    void setModelValue(bool modelValue) {
        VariableSymbol::modelValue = modelValue;
    }


private:
    literal var;
    bool modelValue;
};

}

#endif //CSP2SAT_VARIABLESYMBOL_H
