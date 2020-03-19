//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMTBOLTABLE_H
#define CSP2SAT_SYMTBOLTABLE_H


#include "Scope/GlobalScope.h"
#include "Symbol/BuildInTypeSymbol.h"

class SymtbolTable {

public:
    GlobalScope gloabls;

    SymtbolTable(){
        gloabls = GlobalScope();
        this->gloabls.define(new BuildInTypeSymbol("int"));
        this->gloabls.define(new BuildInTypeSymbol("bool"));
    }

};


#endif //CSP2SAT_SYMTBOLTABLE_H
