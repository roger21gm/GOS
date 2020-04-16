//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_UTILS_H
#define CSP2SAT_UTILS_H


#include "../Symtab/Symbol/Scoped/StructSymbol.h"
#include "../Symtab/Scope/Scope.h"
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Valued/AssignableSymbol.h"
#include "../Symtab/Symbol/Scoped/ArraySymbol.h"
#include "../Symtab/Value/IntValue.h"

class Utils {

private:

    static void generateAllPermutations(vector<vector<Symbol*>> input, vector<Symbol*> current, int k, vector<map<string, Symbol*>> & result, vector<string> names){
        if(k == input.size()){
            result.emplace_back();
            for (int i = 0; i < k; ++i) {
                result.back()[names[i]] = current[i];
            }
        } else {
            for (int j = 0; j < input[k].size(); ++j) {
                current[k] = input[k][j];
                generateAllPermutations(input, current, k+1, result, names);
            }
        }
    }

public:


    static StructSymbol *definewNewCustomTypeParam(const string &name, StructSymbol *customType, Scope *enclosingScope) {

        StructSymbol *newCustomTypeConst = new StructSymbol(
                name,
                customType,
                enclosingScope
        );
        for (pair<string, Symbol *> sym : customType->getScopeSymbols()) {
            if (sym.second->type->getTypeIndex() == SymbolTable::tCustom) {
                StructSymbol *customTypeAttribtue = (StructSymbol *) sym.second;
                StructSymbol *newVar = definewNewCustomTypeParam(sym.first, customTypeAttribtue, newCustomTypeConst);
                newCustomTypeConst->define(newVar);
            } else if (sym.second->type->getTypeIndex() == SymbolTable::tArray) {
                ArraySymbol *aSy = (ArraySymbol *) sym.second;
                ArraySymbol * newArrayConst = createArrayParamFromArrayType(sym.first, newCustomTypeConst, aSy);
                newCustomTypeConst->define(newArrayConst);
            } else if (sym.second->type->getTypeIndex() == SymbolTable::tVarBool) {
                Symbol * varSym = new VariableSymbol(sym.first);

                newCustomTypeConst->define(varSym);

            }
            else{
                newCustomTypeConst->define(new AssignableSymbol(sym.first, sym.second->type));
            }
        }

        return newCustomTypeConst;
    }

    static ArraySymbol *createArrayParamFromArrayType(string name, Scope *enclosingScope, ArraySymbol *arrayType) {
        vector<int> dimensions;
        Symbol * currType = arrayType;
        while(currType->type && currType->type->getTypeIndex() == SymbolTable::tArray){
            ArraySymbol * currDimension = (ArraySymbol*) currType;
            dimensions.push_back(currDimension->getSize());
            currType = currDimension->resolve("0");
        }
        return defineNewArray(name, enclosingScope, dimensions, arrayType->getElementsType());
    }

    static ArraySymbol *
    defineNewArray(const string &name, Scope *enclosingScope, vector<int> dimentions, Type *elementsType) {

        if (dimentions.size() == 1) {
            ArraySymbol *newArray = new ArraySymbol(
                    name,
                    enclosingScope,
                    elementsType,
                    dimentions[0]
            );
            for (int i = 0; i < dimentions[0]; ++i) {
                Symbol *element;
                if (elementsType->getTypeIndex() == SymbolTable::tCustom)
                    element = definewNewCustomTypeParam(to_string(i), (StructSymbol *) elementsType, newArray);
                else if (elementsType->getTypeIndex() == SymbolTable::tVarBool){
                    element =new VariableSymbol(to_string(i));
                }
                else {
                    element = new AssignableSymbol(to_string(i), elementsType);
                }
                newArray->define(element);
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
                auto *constElement = defineNewArray(to_string(i), newDimention, restOfDimenstions, elementsType);
                newDimention->define(constElement);
            }
            return newDimention;
        }
    }


    static vector<map<string, Symbol*>> getAllCombinations(const map<string, ArraySymbol*>& ranges){
        vector<vector<Symbol*>> unnamedRanges;
        vector<string> names;

        for(const auto& localParam : ranges){
            names.push_back(localParam.first);

            map<string, Symbol*> currAuxList = localParam.second->getScopeSymbols();

            vector<Symbol*> curr;
            curr.reserve(currAuxList.size());
            for(auto const& currElem: currAuxList)
                curr.push_back(currElem.second);

            unnamedRanges.push_back(curr);

        }
        vector<map<string, Symbol*>> result;
        generateAllPermutations(unnamedRanges, unnamedRanges[0], 0, result, names);

        return result;
    }

    static vector<literal> getLiteralVectorFromVariableArraySymbol(ArraySymbol * variableArray) {
        vector<literal> result = vector<literal>();
        map<string, Symbol *> arrayElems = variableArray->getScopeSymbols();
        if (variableArray->getElementsType()->getTypeIndex() == SymbolTable::tVarBool) {
            for (auto currElem : arrayElems) {
                VariableSymbol * currVar = (VariableSymbol *) currElem.second;
                result.push_back(((VariableSymbol *) currElem.second)->getVar());
            }
        } else {
            cerr << "It must be a literal array" << endl;
            throw;
        }
        return result;
    }
;

};


#endif //CSP2SAT_UTILS_H
