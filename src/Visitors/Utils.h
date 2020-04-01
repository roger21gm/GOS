//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_UTILS_H
#define CSP2SAT_UTILS_H


#include "../Symtab/Symbol/StructSymbol.h"
#include "../Symtab/Scope/Scope.h"
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Assignable/ConstantSymbol.h"
#include "../Symtab/Symbol/ArraySymbol.h"
#include "../Symtab/Value/IntValue.h"

class Utils {

public:
    static StructSymbol *createCustomTypeConstant(const string &name, StructSymbol *customType, Scope *enclosingScope) {

        StructSymbol *newCustomTypeConst = new StructSymbol(
                name,
                customType,
                enclosingScope
        );
        for (pair<string, Symbol *> sym : customType->getScopeSymbols()) {
            if (sym.second->type->getTypeIndex() == SymbolTable::tCustom) {
                StructSymbol *customTypeAttribtue = (StructSymbol *) sym.second;
                StructSymbol *newVar = createCustomTypeConstant(sym.first, customTypeAttribtue, newCustomTypeConst);
                newCustomTypeConst->define(newVar);
            } else {
                newCustomTypeConst->define(new ConstantSymbol(sym.first, sym.second->type));
            }
        }

        return newCustomTypeConst;
    }

    static ArraySymbol *
    createArrayConstant(const string &name, Scope *enclosingScope, vector<int> dimentions, Type *elementsType) {

        if (dimentions.size() == 1) {
            ArraySymbol *newArray = new ArraySymbol(
                    name,
                    enclosingScope,
                    elementsType,
                    dimentions[0]
            );
            for (int i = 0; i < dimentions[0]; ++i) {
                Symbol *constElement;
                if (elementsType->getTypeIndex() == SymbolTable::tCustom)
                    constElement = createCustomTypeConstant(to_string(i), (StructSymbol *) elementsType, newArray);
                else {
                    constElement = new ConstantSymbol(to_string(i), elementsType);
                }
                newArray->define(constElement);
            }
            return newArray;
        } else {
            vector<int> restOfDimenstions(dimentions.begin() + 1, dimentions.end());
            auto *newDimention = new ArraySymbol(
                    name,
                    enclosingScope,
                    elementsType,
                    dimentions[0]
            );
            for (int i = 0; i < dimentions[0]; i++) {
                auto *constElement = createArrayConstant(to_string(i), newDimention, restOfDimenstions, elementsType);
                newDimention->define(constElement);
            }
            return newDimention;
        }
    }

};


#endif //CSP2SAT_UTILS_H
