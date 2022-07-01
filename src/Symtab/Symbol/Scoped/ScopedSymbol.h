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

    bool isScoped() override {
        return true;
    }
};
typedef std::shared_ptr<ScopedSymbol> ScopedSymbolRef;

}

#endif //CSP2SAT_SCOPEDSYMBOL_H
