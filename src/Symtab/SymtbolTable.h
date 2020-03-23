//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMTBOLTABLE_H
#define CSP2SAT_SYMTBOLTABLE_H


#include "Scope/GlobalScope.h"
#include "Symbol/BuildInTypeSymbol.h"



class SymtbolTable {



public:

    static const int tCustom = 0;
    static const int tInt = 1;
    static const int tBool = 2;

    BuildInTypeSymbol _integer = BuildInTypeSymbol("int", tInt);
    BuildInTypeSymbol _boolean = BuildInTypeSymbol("bool", tBool);

    GlobalScope gloabls;

    SymtbolTable(){
        gloabls = GlobalScope();
        this->gloabls.define(&_integer);
        this->gloabls.define(&_boolean);
    }

};


#endif //CSP2SAT_SYMTBOLTABLE_H
