//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_STRUCTSYMBOL_H
#define CSP2SAT_STRUCTSYMBOL_H

#include "ScopedSymbol.h"
#include <utility>
#include <map>
#include <string>

namespace GOS {

class StructSymbol : public ScopedSymbol {

private:
    std::map<std::string, Symbol*> fields = {};

public:

    //Constructor for creating typed constants of this custom type.
    StructSymbol(std::string name, Type * type, Scope * enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {
        this->type = type;
    }

    //Constructor for creating the definition of the custom type.
    StructSymbol(const std::string& name, Scope * enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {}

    void define(Symbol *sym) override {
        fields.insert(std::pair<std::string, Symbol*>(sym->getName(), sym));
    }

    Symbol *resolve(const std::string& name) override {
        if ( fields.find(name) != fields.end() )
            return fields.find(name)->second;
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    std::map<std::string, Symbol*> getScopeSymbols() override {
        return this->fields;
    }

    bool existsInScope(const std::string &name) override {
        return fields.find(name) != fields.end();
    }
};

}

#endif //CSP2SAT_STRUCTSYMBOL_H
