//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_GLOBALSCOPE_H
#define CSP2SAT_GLOBALSCOPE_H


#include "BaseScope.h"

class GlobalScope: public BaseScope {
public:
    GlobalScope() : BaseScope(nullptr) {}

    string getScopeName() override {
        return "global";
    }

    string getFullName() override {
        return "";
    }

};


#endif //CSP2SAT_GLOBALSCOPE_H
