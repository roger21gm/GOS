//
// Created by Roger Generoso Masós on 08/04/2020.
//

#ifndef CSP2SAT_LOCALSCOPE_H
#define CSP2SAT_LOCALSCOPE_H

#include "BaseScope.h"
#include <string>

namespace GOS {

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

#endif //CSP2SAT_LOCALSCOPE_H
