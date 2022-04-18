//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOL_H
#define CSP2SAT_SYMBOL_H

#include <string>
#include <utility>

namespace GOS {

class Scope; // TODO redefinition??
class Type;

class Symbol {
public:
    Symbol(std::string name) : name(std::move(name)) {} //For constructing Type symbols
    Symbol(std::string name, Type *type) : name(std::move(name)), type(type) {} //For constructing var/const declarations

    std::string getName() {
        return this->name;
    }

    virtual bool isAssignable() {
        return false;
    };
    virtual bool isScoped() {
        return false;
    }

    std::string name;
    Type *type = nullptr;
};

}

#endif //CSP2SAT_SYMBOL_H
