//
// Created by Roger Generoso Masós on 31/03/2020.
//

#ifndef CSP2SAT_ARRAYSYMBOL_H
#define CSP2SAT_ARRAYSYMBOL_H

#include "../../../GOSUtils.h"
#include "../../../Errors/GOSExceptionsRepository.h"
#include <string>
#include <map>
#include <vector>

namespace GOS {

class ArraySymbol : public ScopedSymbol {

private:
    std::vector<Symbol*> elements;
    Type * elementsType;
    int size;

public:
    ArraySymbol(const std::string &name, Scope * enclosingScope, Type * arrayElementsType, int size) : ScopedSymbol(SymbolTable::tArray, name, enclosingScope) {
        this->size = size;
        this->elementsType = arrayElementsType;
        this->type = this;
    }

    ArraySymbol(const std::string &name, Scope * enclosingScope, Type * arrayElementsType) : ScopedSymbol(SymbolTable::tArray, name, enclosingScope) {
        this->size = 0;
        this->elementsType = arrayElementsType;
        this->type = this;
    }



    void define(Symbol *sym) override {
        elements.push_back(sym);
    }

    Symbol *resolve(const std::string& name) override {
        bool isNumber = Utils::check_number(name);

        if(isNumber){
            int index = stoi(name);
            if(index < size && index >= 0){
                return elements[index];
            }
            throw CSP2SATOutOfRangeException(0, 0, getFullName() + "[" + name + "]");
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


    std::map<std::string, Symbol*> getScopeSymbols() override {
        std::map<std::string, Symbol*> scopeSymbols;
        for (int i = 0; i < size; i++) {
            scopeSymbols[std::to_string(i)] = elements[i];
        }
        return scopeSymbols;
    }

    std::vector<Symbol*> getSymbolVector() {
        return elements;
    }

    void setSize(int siz){
        this->size = siz;
    }

    int getSize() {
        return this->size;
    }

    Type * getElementsType () {
        return this->elementsType;
    }

    bool isAssignable() override {
        return false;
    }


    void add(Symbol *sym) {
        elements.push_back(sym);
        size++;
    }
};

}

#endif //CSP2SAT_ARRAYSYMBOL_H
