//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOLTABLE_H
#define CSP2SAT_SYMBOLTABLE_H


#include <iostream>
#include "Scope/GlobalScope.h"
#include "Symbol/BuiltInTypeSymbol.h"
#include "../api/smtapi/src/smtformula.h"

class SymbolTable {

public:

    //Flag to indicate if the flow is defining entities.
    static bool entityDefinitionBlock;

    static const int tCustom = 0;
    static const int tArray = 1;
    static const int tInt = 2;
    static const int tBool = 3;
    static const int tVarBool = 4;
    GlobalScope * gloabls;

    static BuiltInTypeSymbol *_integer;
    static BuiltInTypeSymbol *_boolean;
    static BuiltInTypeSymbol *_varbool;

    SymbolTable(){
        gloabls = new GlobalScope();
        this->gloabls->define(_integer);
        this->gloabls->define(_boolean);
        this->gloabls->define(_varbool);
    }
};

BuiltInTypeSymbol * SymbolTable::_integer = new BuiltInTypeSymbol("int", SymbolTable::tInt);
BuiltInTypeSymbol * SymbolTable::_boolean = new BuiltInTypeSymbol("bool", SymbolTable::tBool);
BuiltInTypeSymbol * SymbolTable::_varbool = new BuiltInTypeSymbol("varbool", SymbolTable::tVarBool);
bool SymbolTable::entityDefinitionBlock = false;

#endif //CSP2SAT_SYMBOLTABLE_H
