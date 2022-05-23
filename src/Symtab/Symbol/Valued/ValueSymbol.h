//
// Created by Roger Generoso Masós on 12/04/2020.
//

#ifndef CSP2SAT_VALUESYMBOL_H
#define CSP2SAT_VALUESYMBOL_H

#include "../Symbol.h"
#include "../../Value.h"
#include <string>

namespace GOS {

class ValueSymbol;
typedef std::shared_ptr<ValueSymbol> ValueSymbolRef;
class ValueSymbol : public Symbol {
public:
    static ValueSymbolRef Create(const std::string &name, TypeRef type) {
        return ValueSymbolRef(new ValueSymbol(name, type));
    }

protected:
    ValueSymbol(const std::string &name, TypeRef type) : Symbol(name, type) {}
};

}

#endif //CSP2SAT_VALUESYMBOL_H
