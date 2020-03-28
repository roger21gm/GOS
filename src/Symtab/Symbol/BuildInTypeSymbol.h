//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BUILDINTYPESYMBOL_H
#define CSP2SAT_BUILDINTYPESYMBOL_H


#include "Symbol.h"
#include "../Type.h"

class BuildInTypeSymbol: public Type {
public:
    BuildInTypeSymbol(const string &name, int typeIndex) : Type(typeIndex, name) {}
};


#endif //CSP2SAT_BUILDINTYPESYMBOL_H
