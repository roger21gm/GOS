//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SCOPE_H
#define CSP2SAT_SCOPE_H

#include "./Symbol/Symbol.h"
#include <string>
#include <map>

namespace GOS {

class Scope {
public:
    virtual std::string getScopeName() = 0;
    virtual std::string getFullName() = 0;
    virtual Scope * getEnclosingScope() = 0;
    virtual void define(Symbol * sym) = 0;
    virtual Symbol * resolve(const std::string &name) = 0;
    virtual bool existsInScope(const std::string &name) = 0;
    virtual std::map<std::string, Symbol*> getScopeSymbols() = 0;
};

class BaseScope: public Scope {
public:
    void define(Symbol *sym) override {
        symbols[sym->getName()] = sym;
    }

    void define(std::string name, Symbol *sym) {
        symbols[name] = sym;
    }

    explicit BaseScope(Scope *parent) : enclosingScope(parent) {}

    Scope * getEnclosingScope() override {
        return this->enclosingScope;
    }

    Symbol * resolve(const std::string& name) override {
        if ( symbols.find(name) != symbols.end() )
            return symbols[name];
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    std::map<std::string, Symbol*> getScopeSymbols() override {
        return this->symbols;
    }


    bool existsInScope(const std::string &name) override {
        return symbols.find(name) != symbols.end();
    }

private:
    Scope * enclosingScope;
protected:
    std::map<std::string, Symbol*> symbols;
};

class GlobalScope: public BaseScope {
public:
    GlobalScope() : BaseScope(nullptr) {}

    std::string getScopeName() override {
        return "global";
    }

    std::string getFullName() override {
        return "";
    }

};

class LocalScope: public BaseScope {
public:
    explicit LocalScope(Scope *parent) : BaseScope(parent) {}

    void assign(std::string name, Symbol *sym) {
        symbols[name] = sym;
    }

    std::string getScopeName() override {
        return "local";
    }

    std::string getFullName() override {
        return "";
    }
};

}

#endif //CSP2SAT_SCOPE_H
