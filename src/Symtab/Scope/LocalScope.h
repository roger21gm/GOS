//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_LOCALSCOPE_H
#define CSP2SAT_LOCALSCOPE_H


#include "BaseScope.h"

class LocalScope: public BaseScope {

public:
    explicit LocalScope(Scope *parent) : BaseScope(parent) {}

    string getScopeName() override {
        return "local";
    }
};


#endif //CSP2SAT_LOCALSCOPE_H
