//
// Created by Roger Generoso Masós on 31/03/2020.
//

#ifndef CSP2SAT_ARRAYSYMBOL_H
#define CSP2SAT_ARRAYSYMBOL_H


#include "../Type.h"
#include "../Scope/Scope.h"
#include "../SymbolTable.h"
#include <list>
#include <vector>

class ArraySymbol : public Scope, public Type {

private:
    Scope * enclosingScope;
    vector<Symbol*> elements;
    Type * elementsType;
    int size;

public:
    ArraySymbol(const string &name, Scope * enclosingScope, Type * arrayElementsType, int size) : Type(SymbolTable::tArray, name) {
        this->size = size;
        this->elementsType = arrayElementsType;
        this->enclosingScope = enclosingScope;
        this->type = this;
    }

    string getScopeName() override {
        return this->name;
    }

    Scope *getEnclosingScope() override {
        return this->enclosingScope;
    }

    void define(Symbol *sym) override {
        sym->scope = this;
        elements.push_back(sym);
    }

    Symbol *resolve(const string& name) override {
        int index = stoi(name);
        if(index < size){
            return elements[index];
        }
        return nullptr;
    }

    map<string, Symbol*> getScopeSymbols() override {
        map<string, Symbol*> scopeSymbols;
        for (int i = 0; i < size; i++) {
            scopeSymbols[to_string(i)] = elements[i];
        }
        return scopeSymbols;
    }

    int getSize() {
        return this->size;
    }

    Type * getElementsType () {
        return this->elementsType;
    }
};


#endif //CSP2SAT_ARRAYSYMBOL_H
