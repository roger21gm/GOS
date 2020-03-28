//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOLTABLE_H
#define CSP2SAT_SYMBOLTABLE_H


#include <iostream>
#include "Scope/GlobalScope.h"
#include "Symbol/BuiltInTypeSymbol.h"


class SymbolTable {

public:
    static const int tCustom = 0;
    static const int tArray = 1;
    static const int tInt = 2;
    static const int tBool = 3;
    GlobalScope * gloabls;

    SymbolTable(){
        BuiltInTypeSymbol *_integer = new BuiltInTypeSymbol("int", tInt);
        BuiltInTypeSymbol *_boolean = new BuiltInTypeSymbol("bool", tBool);

        gloabls = new GlobalScope();
        this->gloabls->define(_integer);
        this->gloabls->define(_boolean);
    }
};


#endif //CSP2SAT_SYMBOLTABLE_H
