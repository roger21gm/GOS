//
// Created by Roger Generoso Masós on 31/03/2020.
//

#ifndef CSP2SAT_ARRAYSYMBOL_H
#define CSP2SAT_ARRAYSYMBOL_H

#include "../../../GOSUtils.h"
#include "../../../Errors/GOSExceptionsRepository.h"
#include "../../SymbolTable.h"
#include "ScopedSymbol.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace GOS {

class ArraySymbol;
typedef std::shared_ptr<ArraySymbol> ArraySymbolRef;
class ArraySymbol : public ScopedSymbol {
public:
    static ArraySymbolRef Create(const std::string &name, ScopeRef enclosingScope, TypeRef arrayElementsType, int size, int nDimensions) {
        return ArraySymbolRef(new ArraySymbol(name, enclosingScope, arrayElementsType, size, nDimensions));
    }
    static ArraySymbolRef Create(const std::string &name, ScopeRef enclosingScope, TypeRef arrayElementsType) {
        return ArraySymbolRef(new ArraySymbol(name, enclosingScope, arrayElementsType));
    }

    void define(SymbolRef sym) override {
        elements.push_back(sym);
    }

    SymbolRef resolve(const std::string& name) override {
        bool isNumber = Utils::check_number(name);

        if(isNumber){
            int index = stoi(name);
            if(index < size && index >= 0){
                return elements[index];
            }
            throw CSP2SATOutOfRangeException({"", 0, 0}, getFullName() + "[" + name + "]");
        }
        else
            return enclosingScope->resolve(name);
    }

    bool existsInScope(const std::string &name) override {
        bool isNumber = Utils::check_number(name);
        if(isNumber){
            int index = stoi(name);
            return index < size;
        }
        else return false;
    }

    std::map<std::string, SymbolRef> getScopeSymbols() override {
        std::map<std::string, SymbolRef> scopeSymbols;
        for (int i = 0; i < size; i++) {
            scopeSymbols[std::to_string(i)] = elements[i];
        }
        return scopeSymbols;
    }

    std::vector<SymbolRef> getSymbolVector() {
        return elements;
    }

    void setSize(int siz){
        this->size = siz;
    }

    int getSize() {
        return this->size;
    }

    int getNDimensions() {
        return this->nDimensions;
    }

    TypeRef getElementsType () {
        return this->elementsType;
    }

    bool isAssignable() override {
        return false;
    }

    void add(SymbolRef sym) {
        elements.push_back(sym);
        size++;
    }

protected:
    ArraySymbol(const std::string &name, ScopeRef enclosingScope, TypeRef arrayElementsType, int size, int nDimensions) :
        ScopedSymbol(SymbolTable::tArray, name, enclosingScope)
    {
        this->nDimensions = nDimensions;
        this->size = size;
        this->elementsType = arrayElementsType;
        this->type = Type::Create(SymbolTable::tArray, name); // Trick! creating another instance of Type since shared_from_this cannot be called from a constructor
    }

    ArraySymbol(const std::string &name, ScopeRef enclosingScope, TypeRef arrayElementsType) : 
        ScopedSymbol(SymbolTable::tArray, name, enclosingScope) 
    {
        this->nDimensions = 1;
        this->size = 0;
        this->elementsType = arrayElementsType;
        this->type = Type::Create(SymbolTable::tArray, name);
    }

private:
    std::vector<SymbolRef> elements;
    TypeRef elementsType;
    int size;
    int nDimensions;
};

}

#endif //CSP2SAT_ARRAYSYMBOL_H
