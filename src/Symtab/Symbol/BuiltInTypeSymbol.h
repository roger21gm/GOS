//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_BUILTINTYPESYMBOL_H
#define CSP2SAT_BUILTINTYPESYMBOL_H

#include "../Type.h"
#include <string>
#include <memory>

namespace GOS {

class BuiltInTypeSymbol;
typedef std::shared_ptr<BuiltInTypeSymbol> BuiltInTypeSymbolRef;
class BuiltInTypeSymbol: public Type {
public:
    static BuiltInTypeSymbolRef Create(const std::string &name, int typeIndex) {
        return BuiltInTypeSymbolRef(new BuiltInTypeSymbol(name, typeIndex));
    }

    bool isAssignable() override {
        return false;
    }
protected:
    BuiltInTypeSymbol(const std::string &name, int typeIndex) : Type(typeIndex, name) {}
};

}

#endif //CSP2SAT_BUILTINTYPESYMBOL_H
