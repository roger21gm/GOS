//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_VARIABLESYMBOL_H
#define CSP2SAT_VARIABLESYMBOL_H

#include "ValueSymbol.h"
#include <string>

namespace GOS {

class VariableSymbol;
typedef std::shared_ptr<VariableSymbol> VariableSymbolRef;
class VariableSymbol : public ValueSymbol {
public:
    static VariableSymbolRef Create(const std::string &name, SMTFormula *f) {
        return VariableSymbolRef(new VariableSymbol(name, f));
    }
    
    static VariableSymbolRef Create(const std::string &name, literal lit) {
        return VariableSymbolRef(new VariableSymbol(name, lit));
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

protected:
    VariableSymbol(const std::string &name, SMTFormula *f) : ValueSymbol(name, SymbolTable::_varbool) {
        if(!SymbolTable::entityDefinitionBlock)
            var = f->newBoolVar();
    }

    VariableSymbol(const std::string &name, literal lit) : ValueSymbol(name, SymbolTable::_varbool) {
        var = lit;
    }

private:
    literal var;
    bool modelValue;
};

}

#endif //CSP2SAT_VARIABLESYMBOL_H
