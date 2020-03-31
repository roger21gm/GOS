//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_UTILS_H
#define CSP2SAT_UTILS_H


#include "../Symtab/Symbol/StructSymbol.h"
#include "../Symtab/Scope/Scope.h"
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Assignable/ConstantSymbol.h"

class Utils {

public:
    static StructSymbol * createCustomTypeConstant(const string& name, StructSymbol * customType, Scope * enclosingScope) {

        StructSymbol * newCustomTypeConst = new StructSymbol(
                name,
                customType,
                enclosingScope
        );
        for(pair<string, Symbol *> sym : customType->getScopeSymbols()){
            if(sym.second->type->getTypeIndex() == SymbolTable::tCustom){
                StructSymbol * customTypeAttribtue = (StructSymbol *) sym.second;
                StructSymbol * newVar = createCustomTypeConstant(sym.first, customTypeAttribtue, newCustomTypeConst);
                newCustomTypeConst->define(newVar);
            }else{
                newCustomTypeConst->define(new ConstantSymbol(sym.first, sym.second->type));
            }
        }

        return  newCustomTypeConst;
    }

};


#endif //CSP2SAT_UTILS_H
