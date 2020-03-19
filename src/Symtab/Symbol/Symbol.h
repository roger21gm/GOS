//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_SYMBOL_H
#define CSP2SAT_SYMBOL_H

#include <string>
#include <utility>
#include "../Scope/Scope.h"
#include "../Type.h"

using namespace std;

class Scope;

class Symbol {
public:
    Symbol(string name) : name(std::move(name)) {}
    Symbol(string name, Type *type) : name(std::move(name)), type(type) {}

    string getName() {
        return this->name;
    }

    string name;
    Type *type = nullptr;
    Scope *scope = nullptr;
};


#endif //CSP2SAT_SYMBOL_H
