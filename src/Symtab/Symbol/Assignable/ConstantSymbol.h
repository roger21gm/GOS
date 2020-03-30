//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_CONSTANTSYMBOL_H
#define CSP2SAT_CONSTANTSYMBOL_H


#include "../Symbol.h"
#include "AssignableSymbol.h"

class ConstantSymbol: public AssignableSymbol {
public:
    ConstantSymbol(const string &name, Type *type) : AssignableSymbol(name, type) {
        this->val = nullptr;
    }


private:
    Value * val;
};


#endif //CSP2SAT_CONSTANTSYMBOL_H
