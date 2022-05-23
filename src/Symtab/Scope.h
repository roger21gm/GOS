//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SCOPE_H
#define CSP2SAT_SCOPE_H

#include "./Symbol/Symbol.h"
#include <string>
#include <map>
#include <memory>

namespace GOS {

class Scope;
typedef std::shared_ptr<Scope> ScopeRef;
class Scope {
public:
    virtual ~Scope() {};
    virtual std::string getScopeName() = 0;
    virtual std::string getFullName() = 0;
    virtual ScopeRef getEnclosingScope() = 0;
    virtual void define(SymbolRef sym) = 0;
    virtual SymbolRef resolve(const std::string &name) = 0;
    virtual bool existsInScope(const std::string &name) = 0;
    virtual std::map<std::string, SymbolRef> getScopeSymbols() = 0;
};

class BaseScope;
typedef std::shared_ptr<BaseScope> BaseScopeRef;
class BaseScope : public Scope {
public:
    virtual ~BaseScope() {}

    void define(SymbolRef sym) override {
        symbols[sym->getName()] = sym;
    }

    void define(std::string name, SymbolRef sym) {
        symbols[name] = sym;
    }

    ScopeRef getEnclosingScope() override {
        return this->enclosingScope;
    }

    SymbolRef resolve(const std::string& name) override {
        if ( symbols.find(name) != symbols.end() )
            return symbols[name];
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }

    std::map<std::string, SymbolRef> getScopeSymbols() override {
        return this->symbols;
    }

    bool existsInScope(const std::string &name) override {
        return symbols.find(name) != symbols.end();
    }

private:
    ScopeRef enclosingScope;
    
protected:
    explicit BaseScope(ScopeRef parent) : enclosingScope(parent) {}

    std::map<std::string, SymbolRef> symbols;
};

class GlobalScope;
typedef std::shared_ptr<GlobalScope> GlobalScopeRef;
class GlobalScope: public BaseScope {
public:
    static GlobalScopeRef Create() {
        return GlobalScopeRef(new GlobalScope());
    }

    std::string getScopeName() override {
        return "global";
    }

    std::string getFullName() override {
        return "";
    }
protected:
    GlobalScope() : BaseScope(nullptr) {}
};

class LocalScope;
typedef std::shared_ptr<LocalScope> LocalScopeRef;
class LocalScope : public BaseScope {
public:
    static LocalScopeRef Create(ScopeRef parent) {
        return LocalScopeRef(new LocalScope(parent));
    }

    void assign(std::string name, SymbolRef sym) {
        symbols[name] = sym;
    }

    std::string getScopeName() override {
        return "local";
    }

    std::string getFullName() override {
        return "";
    }

protected:
    LocalScope(ScopeRef parent) : BaseScope(parent) {}
};

}

#endif //CSP2SAT_SCOPE_H
