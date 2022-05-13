//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_ASSIGNABLESYMBOL_H
#define CSP2SAT_ASSIGNABLESYMBOL_H

#include "../Valued/ValueSymbol.h"
#include <string>

namespace GOS {

class AssignableSymbol: public ValueSymbol {
public:
    AssignableSymbol(const std::string &name, Type *type) : ValueSymbol(name, type) {
        this->val = nullptr;
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

private:
    ValueRef val;
};

}

#endif //CSP2SAT_ASSIGNABLESYMBOL_H
