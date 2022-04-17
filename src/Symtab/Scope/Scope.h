//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SCOPE_H
#define CSP2SAT_SCOPE_H

#include <string>
#include "../Symbol/Symbol.h"

namespace GOS {

class Scope {
public:
    virtual string getScopeName() = 0;
    virtual string getFullName() = 0;
    virtual Scope * getEnclosingScope() = 0;
    virtual void define(Symbol * sym) = 0;
    virtual Symbol * resolve(const string &name) = 0;
    virtual bool existsInScope(const string &name) = 0;
    virtual map<string, Symbol*> getScopeSymbols() = 0;
};

}

#endif //CSP2SAT_SCOPE_H
