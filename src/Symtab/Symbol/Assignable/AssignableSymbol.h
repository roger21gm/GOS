//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_ASSIGNABLESYMBOL_H
#define CSP2SAT_ASSIGNABLESYMBOL_H


#include "../Symbol.h"

class AssignableSymbol : public Symbol {

public:
    AssignableSymbol(const string &name, Type *type) : Symbol(name, type) {}

    Value *getValue(){
        return this->val;
    }

    void setValue(Value * value) {
        this->val = value;
    }

private:
    Value * val{};
};


#endif //CSP2SAT_ASSIGNABLESYMBOL_H
