//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SCOPE_H
#define CSP2SAT_SCOPE_H

#include "../Symbol/Symbol.h"
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

}

#endif //CSP2SAT_SCOPE_H
