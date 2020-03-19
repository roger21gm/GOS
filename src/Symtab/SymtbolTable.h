//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMTBOLTABLE_H
#define CSP2SAT_SYMTBOLTABLE_H


#include "Scope/GlobalScope.h"

class SymtbolTable {

public:

    GlobalScope gloabls;

    SymtbolTable(){
        gloabls = GlobalScope();
    }

};


#endif //CSP2SAT_SYMTBOLTABLE_H
