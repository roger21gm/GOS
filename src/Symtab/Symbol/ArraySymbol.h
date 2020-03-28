//
// Created by Roger Generoso Masós on 28/03/2020.
//

#ifndef CSP2SAT_ARRAYSYMBOL_H
#define CSP2SAT_ARRAYSYMBOL_H


#include "../Type.h"
#include "../SymbolTable.h"

class ArraySymbol: public Type {
public:
    explicit ArraySymbol(const string &name) : Type(SymbolTable::tArray, name) {}

};


#endif //CSP2SAT_ARRAYSYMBOL_H
