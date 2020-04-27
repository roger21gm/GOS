//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOLTABLE_H
#define CSP2SAT_SYMBOLTABLE_H


#include <iostream>
#include "Scope/GlobalScope.h"
#include "Symbol/BuiltInTypeSymbol.h"
#include "../api/smtapi/src/smtformula.h"
#include "Symbol/Scoped/ScopedSymbol.h"
#include "Value/Value.h"
#include "Symbol/Valued/AssignableSymbol.h"

class SymbolTable {

public:

    //Flag to indicate if the flow is defining entities.
    static bool entityDefinitionBlock;

    static const int tCustom = 0;
    static const int tArray = 1;
    static const int tInt = 2;
    static const int tBool = 3;
    static const int tVarBool = 4;
    static const int tString = 5;
    GlobalScope * gloabls;

    static BuiltInTypeSymbol *_integer;
    static BuiltInTypeSymbol *_boolean;
    static BuiltInTypeSymbol *_varbool;
    static BuiltInTypeSymbol *_string;

    SymbolTable(){
        gloabls = new GlobalScope();
        this->gloabls->define(_integer);
        this->gloabls->define(_boolean);
        this->gloabls->define(_varbool);
        this->gloabls->define(_string);
    }

    void showAllDefinedVariables(){
        iShowAllDefinedVariable(this->gloabls);
    }

    static bool errors;

private:
    static void iShowAllDefinedVariable(Scope * currentScope, const string& prefix = ""){
        map<string, Symbol*> currentScopeSymbols = currentScope->getScopeSymbols();

        for(pair<string, Symbol *> sym : currentScopeSymbols){
            if(sym.second->type){
                if(sym.second->type->getTypeIndex() == SymbolTable::tCustom || sym.second->type->getTypeIndex() == SymbolTable::tArray)
                    if(!isdigit(sym.first[0]))
                        iShowAllDefinedVariable( (ScopedSymbol*) sym.second, prefix + "." + sym.first );
                    else
                        iShowAllDefinedVariable( (ScopedSymbol*) sym.second, isdigit(sym.first[0]) ? prefix + "[" + sym.first + "]" : prefix + sym.first);
                else{
                    string output = sym.second->type->getTypeIndex() != SymbolTable::tVarBool ?  "param -> " : "var -> ";
                    if(!prefix.empty() && prefix[0] == '.')
                        output += prefix.substr(1, prefix.length()-1);
                    else
                        output += prefix;

                    if(isdigit(sym.first[0])){
                        output += "[" + sym.first + "]";
                    }
                    else {
                        output += "." + sym.first ;
                    }

                    if(sym.second->type->getTypeIndex() != SymbolTable::tVarBool){
                        Value * val = ((AssignableSymbol*)sym.second)->getValue();
                        cout << output  << " -> " << (val ? to_string(val->getRealValue()) : "_") << endl;
                    }
                    else {
                        cout << output  << endl;
                    }

                }
            }
            else {
                cout << "defined type -> " << prefix +  sym.first << endl;
            }
        }
    }

};

BuiltInTypeSymbol * SymbolTable::_integer = new BuiltInTypeSymbol("int", SymbolTable::tInt);
BuiltInTypeSymbol * SymbolTable::_boolean = new BuiltInTypeSymbol("bool", SymbolTable::tBool);
BuiltInTypeSymbol * SymbolTable::_varbool = new BuiltInTypeSymbol("varbool", SymbolTable::tVarBool);
BuiltInTypeSymbol * SymbolTable::_string = new BuiltInTypeSymbol("string", SymbolTable::tString);
bool SymbolTable::entityDefinitionBlock = false;
bool SymbolTable::errors = false;



#endif //CSP2SAT_SYMBOLTABLE_H
