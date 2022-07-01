//
// Created by David on 27/06/2022.
//

#ifndef GOS_PREDSYMBOL_H
#define GOS_PREDSYMBOL_H

#include "ScopedSymbol.h"
#include "../../../GOSUtils.h"
#include "../../SymbolTable.h"
#include <utility>
#include <map>
#include <string>
#include <memory>

namespace GOS {

class PredSymbol;
typedef std::shared_ptr<PredSymbol> PredSymbolRef;
class PredSymbol : public LocalScope, public Symbol {
public:
    typedef std::pair<std::string, std::vector<TypeRef>> Signature;

    static PredSymbolRef Create(Signature sig, ScopeRef enclosingScope)
    {
        return PredSymbolRef(new PredSymbol(sig, enclosingScope));
    }

    std::vector<clause> getClauses() const {
        return _clauses;
    }

    std::string getNameExt() const
    {
        return getName() + std::to_string(type->getTypeIndex());
    }

    std::string getIdent() const
    {
        std::vector<std::string> splitted = GOS::Utils::string_split2(getName(), '(');
        return splitted[0] + std::to_string(type->getTypeIndex());
    }

protected:
    PredSymbol(Signature sig,  ScopeRef enclosingScope) :
        LocalScope(enclosingScope),
        Symbol(signature2string(sig), SymbolTable::_varbool),
        _paramTypes(sig.second)
    {
    }

private:
    std::vector<TypeRef> _paramTypes;
    std::vector<clause> _clauses;

    static std::string signature2string(Signature sig) {
        std::string paramsStr = "";
        for(TypeRef t : sig.second)
            paramsStr += std::to_string(t->getTypeIndex());
        return sig.first + '(' + paramsStr + ')';
    }
};

}

#endif //GOS_PREDSYMBOL_H
