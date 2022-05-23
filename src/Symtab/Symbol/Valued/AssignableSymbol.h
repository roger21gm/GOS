//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_ASSIGNABLESYMBOL_H
#define CSP2SAT_ASSIGNABLESYMBOL_H

#include "ValueSymbol.h"
#include <string>

namespace GOS {

class AssignableSymbol;
typedef std::shared_ptr<AssignableSymbol> AssignableSymbolRef;
class AssignableSymbol : public ValueSymbol {
public:
    static AssignableSymbolRef Create(const std::string &name, TypeRef type) {
        return AssignableSymbolRef(new AssignableSymbol(name, type));
    }

    bool isAssignable() override {
        return true;
    }

    ValueRef getValue() {
        return val;
    }

    void setValue(ValueRef value) {
        this->val = value;
    }

protected:
    AssignableSymbol(const std::string &name, TypeRef type) : ValueSymbol(name, type) {
        this->val = nullptr;
    }

private:
    ValueRef val;
};

}

#endif //CSP2SAT_ASSIGNABLESYMBOL_H
