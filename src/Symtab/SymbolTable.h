//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOLTABLE_H
#define CSP2SAT_SYMBOLTABLE_H


#include <iostream>
#include "Scope.h"
#include "Symbol/BuiltInTypeSymbol.h"
#include "../api/smtformula.h"
#include "Symbol/Scoped/ScopedSymbol.h"
#include "Symbol/Valued/AssignableSymbol.h"
#include "Value.h"
#include "Symbol/Symbol.h"
#include "../GOSUtils.h"
#include "../BUPFile.h"
#include <map>
#include <string>
#include <utility>
#include <filesystem>

namespace GOS {

class SymbolTable {
public:
    //Flag to indicate if the flow is defining entities.
    static bool entityDefinitionBlock;

    static const int tCustom = 0; // TODO enum?
    static const int tArray = 1;
    static const int tInt = 2;
    static const int tBool = 3;
    static const int tVarBool = 4;
    static const int tString = 5;
    static const int tFormula = 5;
    GlobalScopeRef gloabls;

    static BuiltInTypeSymbolRef _integer;
    static BuiltInTypeSymbolRef _boolean;
    static BuiltInTypeSymbolRef _varbool;
    static BuiltInTypeSymbolRef _string;
    static BuiltInTypeSymbolRef _formula;

    SymbolTable(){
        gloabls = GlobalScope::Create();
        this->gloabls->define(_integer);
        this->gloabls->define(_boolean);
        this->gloabls->define(_varbool);
        this->gloabls->define(_string);
        this->gloabls->define(_formula);
        parsedFiles = std::vector<BUPFileRef>();
    }

    void showAllDefinedVariables(){
        iShowAllDefinedVariable(this->gloabls);
    }

    static bool errors;

    std::vector<BUPFileRef> parsedFiles;

    static std::string typeToString(int tType) {
        switch (tType) {
            case SymbolTable::tBool:
                return "bool";
            case SymbolTable::tInt:
                return "int";
            case SymbolTable::tVarBool:
                return "varBool";
            case SymbolTable::tArray:
                return "array";
            case SymbolTable::tCustom:
                return "customType";
            default:
                throw std::invalid_argument("Type " + std::to_string(tType) + " not supported");
        }
    }

private:
    static void iShowAllDefinedVariable(ScopeRef currentScope, const std::string& prefix = ""){
        std::map<std::string, SymbolRef> currentScopeSymbols = currentScope->getScopeSymbols();

        for(std::pair<std::string, SymbolRef> sym : currentScopeSymbols){
            if(sym.second->getType()){
                if(sym.second->getType()->getTypeIndex() == SymbolTable::tCustom || sym.second->getType()->getTypeIndex() == SymbolTable::tArray)
                    if(!isdigit(sym.first[0]))
                        iShowAllDefinedVariable( Utils::as<ScopedSymbol>(sym.second), prefix + "." + sym.first );
                    else
                        iShowAllDefinedVariable( Utils::as<ScopedSymbol>(sym.second), isdigit(sym.first[0]) ? prefix + "[" + sym.first + "]" : prefix + sym.first);
                else{
                    std::string output = sym.second->getType()->getTypeIndex() != SymbolTable::tVarBool ?  "param -> " : "var -> ";
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

                    if(sym.second->getType()->getTypeIndex() != SymbolTable::tVarBool){
                        ValueRef val = Utils::as<AssignableSymbol>(sym.second)->getValue();
                        std::cout << output  << " -> " << (val ? std::to_string(val->getRealValue()) : "_") << std::endl;
                    }
                    else {
                        std::cout << output  << std::endl;
                    }

                }
            }
            else {
                std::cout << "defined type -> " << prefix +  sym.first << std::endl;
            }
        }
    }

};

BuiltInTypeSymbolRef SymbolTable::_integer = BuiltInTypeSymbol::Create("int", SymbolTable::tInt);
BuiltInTypeSymbolRef SymbolTable::_boolean = BuiltInTypeSymbol::Create("bool", SymbolTable::tBool);
BuiltInTypeSymbolRef SymbolTable::_varbool = BuiltInTypeSymbol::Create("varbool", SymbolTable::tVarBool);
BuiltInTypeSymbolRef SymbolTable::_string = BuiltInTypeSymbol::Create("string", SymbolTable::tString);
BuiltInTypeSymbolRef SymbolTable::_formula = BuiltInTypeSymbol::Create("formula", SymbolTable::tFormula);
bool SymbolTable::entityDefinitionBlock = false;
bool SymbolTable::errors = false;
const int SymbolTable::tCustom;
const int SymbolTable::tArray;
const int SymbolTable::tInt;
const int SymbolTable::tBool;
const int SymbolTable::tVarBool;
const int SymbolTable::tString;
const int SymbolTable::tFormula;

}

#endif //CSP2SAT_SYMBOLTABLE_H
