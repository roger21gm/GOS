//
// Created by Roger Generoso Masós on 12/04/2020.
//

#ifndef CSP2SAT_VALUESYMBOL_H
#define CSP2SAT_VALUESYMBOL_H

#include "../Symbol.h"
#include <string>

namespace GOS {

class ValueSymbol : public Symbol {
public:
    ValueSymbol(const std::string &name, Type *type) : Symbol(name, type) {}
};

}

#endif //CSP2SAT_VALUESYMBOL_H
