//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_STRUCTSYMBOL_H
#define CSP2SAT_STRUCTSYMBOL_H

#include "ScopedSymbol.h"
#include "../../SymbolTable.h"
#include <utility>
#include <map>
#include <string>
#include <memory>

namespace GOS {

class StructSymbol;
typedef std::shared_ptr<StructSymbol> StructSymbolRef;
class StructSymbol : public ScopedSymbol {
public:
    static StructSymbolRef Create(std::string name, TypeRef type, ScopeRef enclosingScope) {
        return StructSymbolRef(new StructSymbol(name, type, enclosingScope));
    }

    static StructSymbolRef Create(const std::string& name, ScopeRef enclosingScope) {
        return StructSymbolRef(new StructSymbol(name, enclosingScope));
    }

    void define(SymbolRef sym) override {
        fields.insert(std::pair<std::string, SymbolRef>(sym->getName(), sym));
    }

    SymbolRef resolve(const std::string& name) override {
        if ( fields.find(name) != fields.end() )
            return fields.find(name)->second;
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    std::map<std::string, SymbolRef> getScopeSymbols() override {
        return this->fields;
    }

    bool existsInScope(const std::string &name) override {
        return fields.find(name) != fields.end();
    }

protected:
    //Constructor for creating typed constants of this custom type.
    StructSymbol(std::string name, TypeRef type, ScopeRef enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {
        this->type = type;
    }

    //Constructor for creating the definition of the custom type.
    StructSymbol(const std::string& name, ScopeRef enclosingScope) : ScopedSymbol(SymbolTable::tCustom, name, enclosingScope) {}

private:
    std::map<std::string, SymbolRef> fields = {};
};

}

#endif //CSP2SAT_STRUCTSYMBOL_H
