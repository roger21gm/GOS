//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_VISITORSUTILS_H
#define CSP2SAT_VISITORSUTILS_H

#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Symbol.h"
#include "../Symtab/Symbol/Scoped/StructSymbol.h"
#include "../Symtab/Symbol/Scoped/ArraySymbol.h"
#include "../Symtab/Symbol/Valued/AssignableSymbol.h"
#include "../Symtab/Symbol/formulaReturn.h"
#include "../Symtab/Symbol/Valued/VariableSymbol.h"
#include "Input/Param.h"
#include "../Errors/GOSExceptionsRepository.h"
#include "../Symtab/Value.h"
#include "../GOSUtils.h"
#include <string>
#include <vector>
#include <map>
#include <utility>

namespace GOS {
namespace VisitorsUtils {

using std::string;
using std::vector;
using std::map;
using std::to_string;
using std::pair;

void generateAllPermutations(
    vector<vector<SymbolRef>> input, 
    vector<SymbolRef> current, 
    int k,
    vector<map<string, SymbolRef>> &result, 
    vector<string> names) 
{
    if (k == input.size()) {
        result.emplace_back();
        for (int i = 0; i < k; ++i) {
            result.back()[names[i]] = current[i];
        }
    } else {
        for (int j = 0; j < input[k].size(); ++j) {
            current[k] = input[k][j];
            generateAllPermutations(input, current, k + 1, result, names);
        }
    }
}

void printAll(
    const vector<vector<SymbolRef>> & allVecs, 
    const vector<string> & names, 
    vector<map<string, SymbolRef>> & result, 
    vector<SymbolRef> currComb = vector<SymbolRef>(), 
    int vecIndex = 0) 
{
    if (vecIndex >= allVecs.size()) {
        result.emplace_back();
        for(int i = 0; i < currComb.size(); ++i)
            result.back()[names[i]] = currComb[i];
        return;
    }
    for (size_t i=0; i<allVecs[vecIndex].size(); i++) {
        vector<SymbolRef> curr = vector<SymbolRef>(currComb);
        curr.push_back(allVecs[vecIndex][i]);
        printAll(allVecs, names, result, curr, vecIndex + 1);
    }
}

vector<map<string, SymbolRef>> getAllCombinations(const map<string, ArraySymbolRef> &ranges) {
    vector<vector<SymbolRef>> unnamedRanges;
    vector<string> names;

    for (const auto &localParam : ranges) {
        names.push_back(localParam.first);

        map<string, SymbolRef> currAuxList = localParam.second->getScopeSymbols();

        vector<SymbolRef> curr;
        curr.reserve(currAuxList.size());
        for (auto const &currElem: currAuxList)
            curr.push_back(currElem.second);

        unnamedRanges.push_back(curr);

    }


    vector<map<string, SymbolRef>> result;
    printAll(unnamedRanges, names, result);
    //generateAllPermutations(unnamedRanges, unnamedRanges[0], 0, result, names);

    return result;
}

string getTypeName(const int tType) {
    switch (tType) {
        case SymbolTable::tBool:
            return "bool";
        case SymbolTable::tInt:
            return "int";
        case SymbolTable::tVarBool:
            return "variable";
        case SymbolTable::tArray:
            return "array";
        default:
            return "custom type";
    }
}

vector<literal> getLiteralVectorFromVariableArraySymbol(ArraySymbolRef variableArray) {
    vector<literal> result = vector<literal>();
    map<string, SymbolRef> arrayElems = variableArray->getScopeSymbols();
    if (variableArray->getElementsType()->getTypeIndex() == SymbolTable::tVarBool
        || variableArray->getElementsType()->getTypeIndex() == SymbolTable::tFormula) {
        for (auto currElem : arrayElems) {
            if(currElem.second->getType()->getTypeIndex() == SymbolTable::tVarBool){
                result.push_back(Utils::as<VariableSymbol>(currElem.second)->getVar());
            }
            else {
                formulaReturnRef formula = Utils::as<formulaReturn>(currElem.second);
                if(formula->clauses.size() == 1 && formula->clauses.front().v.size() == 1){
                    result.push_back(formula->clauses.front().v.front());
                }
            }
        }
    } else {
        //cerr << "It must be a literal array" << endl;
        throw GOSException(0, 0, variableArray->getFullName() + " must be a list of literals");
    }
    return result;
}

// Defining before implementing due to cross-call between these functions
StructSymbolRef
definewNewCustomTypeParam(const string &name, StructSymbolRef customType, ScopeRef enclosingScope, 
    SMTFormula *formula, ParamJSONRef inParams);

ArraySymbolRef
defineNewArray(const string &name, ScopeRef enclosingScope, vector<int> dimentions, 
    TypeRef elementsType, SMTFormula *formula, ParamJSONRef inParams);

ArraySymbolRef 
createArrayParamFromArrayType(string name, ScopeRef enclosingScope, 
    ArraySymbolRef arrayType, SMTFormula *formula, ParamJSONRef inParams);



StructSymbolRef
definewNewCustomTypeParam(
    const string &name, 
    StructSymbolRef customType, 
    ScopeRef enclosingScope, 
    SMTFormula *formula,
    ParamJSONRef inParams) 
{
    StructSymbolRef newCustomTypeConst = StructSymbol::Create(
            name,
            customType,
            enclosingScope
    );
    for (pair<string, SymbolRef> sym : customType->getScopeSymbols()) {
        if (sym.second->getType()->getTypeIndex() == SymbolTable::tCustom) {
            StructSymbolRef customTypeAttribtue = Utils::as<StructSymbol>(sym.second);
            StructSymbolRef newVar = definewNewCustomTypeParam(sym.first, customTypeAttribtue, newCustomTypeConst,
                                                                formula, inParams);
            newCustomTypeConst->define(newVar);
        } else if (sym.second->getType()->getTypeIndex() == SymbolTable::tArray) {
            ArraySymbolRef aSy = Utils::as<ArraySymbol>(sym.second);
            ArraySymbolRef newArrayConst = createArrayParamFromArrayType(sym.first, newCustomTypeConst, aSy, formula,
                                                                        inParams);
            newCustomTypeConst->define(newArrayConst);
        } else if (sym.second->getType()->getTypeIndex() == SymbolTable::tVarBool) {
            SymbolRef varSym = VariableSymbol::Create(sym.first, formula);
            newCustomTypeConst->define(varSym);
        } else {
            AssignableSymbolRef newParam = AssignableSymbol::Create(sym.first, sym.second->getType());

            if (!SymbolTable::entityDefinitionBlock) {
                string fullScopedName = newCustomTypeConst->getFullName() + "." + sym.first;
                int value = inParams->resolve(fullScopedName);
                if (sym.second->getType()->getTypeIndex() == SymbolTable::tInt)
                    newParam->setValue(IntValue::Create(value));
                else
                    newParam->setValue(BoolValue::Create(value));
            }

            newCustomTypeConst->define(newParam);
        }
    }

    return newCustomTypeConst;
}

ArraySymbolRef 
defineNewArray(
    const string &name, 
    ScopeRef enclosingScope, 
    vector<int> dimentions, 
    TypeRef elementsType,
    SMTFormula *formula, 
    ParamJSONRef inParams) 
{
    if (dimentions.size() == 1) {
        ArraySymbolRef newArray = ArraySymbol::Create(
                name,
                enclosingScope,
                elementsType,
                dimentions[0]
        );
        for (int i = 0; i < dimentions[0]; ++i) {
            SymbolRef element;
            if (elementsType->getTypeIndex() == SymbolTable::tCustom)
                element = definewNewCustomTypeParam(to_string(i), Utils::as<StructSymbol>(elementsType), newArray, formula,
                                                    inParams);
            else if (elementsType->getTypeIndex() == SymbolTable::tVarBool) {
                element = VariableSymbol::Create(to_string(i), formula);
            } else {
                AssignableSymbolRef newParam = AssignableSymbol::Create(to_string(i), elementsType);
                if (!SymbolTable::entityDefinitionBlock) {
                    string fullScopedName = newArray->getFullName() + "[" + to_string(i) + "]";
                    int value = inParams->resolve(fullScopedName);
                    if (elementsType->getTypeIndex() == SymbolTable::tInt)
                        newParam->setValue(IntValue::Create(value));
                    else
                        newParam->setValue(BoolValue::Create(value));
                }
                element = newParam;
            }
            newArray->define(element);
        }
        return newArray;
    } else {
        vector<int> restOfDimenstions(dimentions.begin() + 1, dimentions.end());
        ArraySymbolRef newDimention = ArraySymbol::Create(
                name,
                enclosingScope,
                elementsType,
                dimentions[0]
        );
        for (int i = 0; i < dimentions[0]; i++) {
            ArraySymbolRef constElement = defineNewArray(to_string(i), newDimention, restOfDimenstions, elementsType,
                                                formula, inParams);
            newDimention->define(constElement);
        }
        return newDimention;
    }

}

ArraySymbolRef
createArrayParamFromArrayType(string name, ScopeRef enclosingScope, ArraySymbolRef arrayType, SMTFormula *formula,
                                ParamJSONRef inParams) {
    vector<int> dimensions;
    SymbolRef currType = arrayType;
    while (currType->getType() && currType->getType()->getTypeIndex() == SymbolTable::tArray) {
        ArraySymbolRef currDimension = Utils::as<ArraySymbol>(currType);
        dimensions.push_back(currDimension->getSize());
        currType = currDimension->resolve("0");
    }
    return defineNewArray(name, enclosingScope, dimensions, arrayType->getElementsType(), formula, inParams);
}




}
}

#endif //CSP2SAT_VISITORSUTILS_H
