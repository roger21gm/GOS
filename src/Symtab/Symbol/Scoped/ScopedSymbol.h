//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_SCOPEDSYMBOL_H
#define CSP2SAT_SCOPEDSYMBOL_H


#include "../../Type.h"
#include "../../Scope.h"
#include <string>
#include <map>
#include <memory>

namespace GOS {

class ScopedSymbol : public Scope, public Type  {
protected:
    ScopeRef enclosingScope;

public:
    ScopedSymbol(int typeIndex, const std::string &name, ScopeRef enclosingScope) : Type(typeIndex, name),
                                                                             enclosingScope(enclosingScope) {}
    
    virtual ~ScopedSymbol() {}

    std::string getScopeName() override {
        return this->name;
    }

    ScopeRef getEnclosingScope() override {
        return this->enclosingScope;
    }

    std::string getFullName() override {
        if(isdigit(this->getScopeName()[0]))
            return  this->enclosingScope->getFullName() + "[" + this->getScopeName() + "]";
        else if(this->enclosingScope->getScopeName() != "global")
            return  this->enclosingScope->getFullName() + "." + this->getScopeName();
        return this->enclosingScope->getFullName() + this->getScopeName();
    }


    virtual void define(SymbolRef sym) override = 0;

    virtual SymbolRef resolve(const std::string& name) override = 0;

    virtual std::map<std::string, SymbolRef> getScopeSymbols() override = 0;

    bool isScoped() override {
        return true;
    }
};
typedef std::shared_ptr<ScopedSymbol> ScopedSymbolRef;

}

#endif //CSP2SAT_SCOPEDSYMBOL_H
