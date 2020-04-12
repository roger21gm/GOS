//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_ASSIGNABLESYMBOL_H
#define CSP2SAT_ASSIGNABLESYMBOL_H


#include "../Valued/ValueSymbol.h"

class AssignableSymbol: public ValueSymbol {
public:
    AssignableSymbol(const string &name, Type *type) : ValueSymbol(name, type) {
        this->val = nullptr;
    }

    bool isAssignable() override {
        return true;
    }

    Value * getValue() {
        return val;
    }

    void setValue(Value * value) {
        this->val = value;
    }

private:
    Value * val;
};


#endif //CSP2SAT_ASSIGNABLESYMBOL_H
