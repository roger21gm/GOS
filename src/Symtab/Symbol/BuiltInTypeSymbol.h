//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BUILTINTYPESYMBOL_H
#define CSP2SAT_BUILTINTYPESYMBOL_H

#include "../Type.h"

class BuiltInTypeSymbol: public Type {
public:
    BuiltInTypeSymbol(const string &name, int typeIndex) : Type(typeIndex, name) {}

    bool isAssignable() override {
        return false;
    }
};


#endif //CSP2SAT_BUILTINTYPESYMBOL_H
