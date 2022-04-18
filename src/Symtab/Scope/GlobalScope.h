//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_GLOBALSCOPE_H
#define CSP2SAT_GLOBALSCOPE_H

#include "BaseScope.h"
#include <string>

namespace GOS {

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

}

#endif //CSP2SAT_GLOBALSCOPE_H
