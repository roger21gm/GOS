//
// Created by Roger Generoso Masós on 31/03/2020.
//

#ifndef CSP2SAT_ARRAYSYMBOL_H
#define CSP2SAT_ARRAYSYMBOL_H


#include "../../../Helpers.h"

class ArraySymbol : public ScopedSymbol {

private:
    vector<Symbol*> elements;
    Type * elementsType;
    int size;

public:
    ArraySymbol(const string &name, Scope * enclosingScope, Type * arrayElementsType, int size) : ScopedSymbol(SymbolTable::tArray, name, enclosingScope) {
        this->size = size;
        this->elementsType = arrayElementsType;
        this->type = this;
    }

    ArraySymbol(const string &name, Scope * enclosingScope, Type * arrayElementsType) : ScopedSymbol(SymbolTable::tArray, name, enclosingScope) {
        this->size = 0;
        this->elementsType = arrayElementsType;
        this->type = this;
    }

    string getFullName() override {
        if(this->getEnclosingScope()->getScopeName() != "global")
            return  this->enclosingScope->getFullName() + "[" + this->getScopeName() + "]";
        return this->getScopeName();
    }

    void define(Symbol *sym) override {
        elements.push_back(sym);
    }

    Symbol *resolve(const string& name) override {
        bool isNumber = Helpers::check_number(name);

        if(isNumber){
            int index = stoi(name);
            if(index < size){
                return elements[index];
            }
            cerr << "Accessing array out of range";
            throw;
        }
        else
            return enclosingScope->resolve(name);

    }

    map<string, Symbol*> getScopeSymbols() override {
        map<string, Symbol*> scopeSymbols;
        for (int i = 0; i < size; i++) {
            scopeSymbols[to_string(i)] = elements[i];
        }
        return scopeSymbols;
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


#endif //CSP2SAT_ARRAYSYMBOL_H
