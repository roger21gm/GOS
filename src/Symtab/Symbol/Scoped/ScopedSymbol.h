//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_SCOPEDSYMBOL_H
#define CSP2SAT_SCOPEDSYMBOL_H


#include "../../Type.h"
#include <string>
#include <map>

namespace GOS {

class ScopedSymbol : public Scope, public Type  {

protected:
    Scope * enclosingScope;

public:

    ScopedSymbol(int typeIndex, const std::string &name, Scope *enclosingScope) : Type(typeIndex, name),
                                                                             enclosingScope(enclosingScope) {}

    std::string getScopeName() override {
        return this->name;
    }

    Scope *getEnclosingScope() override {
        return this->enclosingScope;
    }

    std::string getFullName() override {
        if(isdigit(this->getScopeName()[0]))
            return  this->enclosingScope->getFullName() + "[" + this->getScopeName() + "]";
        else if(this->enclosingScope->getScopeName() != "global")
            return  this->enclosingScope->getFullName() + "." + this->getScopeName();
        return this->enclosingScope->getFullName() + this->getScopeName();
    }


    virtual void define(Symbol *sym) override = 0;

    virtual Symbol *resolve(const std::string& name) override = 0;

    virtual std::map<std::string, Symbol*> getScopeSymbols() override = 0;

    bool isScoped() override {
        return true;
    }
};

}

#endif //CSP2SAT_SCOPEDSYMBOL_H
