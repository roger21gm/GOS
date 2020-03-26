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
    GlobalScope * gloabls;

    SymtbolTable(){
        BuildInTypeSymbol *_integer = new BuildInTypeSymbol("int", tInt);
        BuildInTypeSymbol *_boolean = new BuildInTypeSymbol("bool", tBool);

        gloabls = new GlobalScope();
        this->gloabls->define(_integer);
        this->gloabls->define(_boolean);

        Type* a = (Type*) gloabls->resolve("int");
        cout << a->getTypeIndex() << endl; // 0
        Type* b = (BuildInTypeSymbol*) gloabls->resolve("int");
        cout << b->getTypeIndex() << endl; // 1
    }
};


#endif //CSP2SAT_SYMTBOLTABLE_H
