//
// Created by David on 27/06/2022.
//

#ifndef GOS_PREDSYMBOL_H
#define GOS_PREDSYMBOL_H

#include "ScopedSymbol.h"
#include "../../../GOSUtils.h"
#include "../../SymbolTable.h"
#include <BUPParser.h>
#include <utility>
#include <map>
#include <string>
#include <memory>

namespace GOS {

class PredSymbol;
typedef std::shared_ptr<PredSymbol> PredSymbolRef;
class PredSymbol : public LocalScope, public Symbol {
public:
    struct Param {
        std::string name;
        int type;
    };
    typedef std::shared_ptr<Param> ParamRef;

    struct Signature {
        std::string name;
        std::vector<Param> params;
    };
    typedef std::shared_ptr<Signature> SignatureRef;

    static std::string signatureToSymbolTableName(Signature sig) {
        std::string paramsStr = "";
        for (Param p : sig.params)
            paramsStr += std::to_string(p.type);
        return sig.name + '(' + paramsStr + ')';
    }

    static PredSymbolRef Create(Signature sig, BUPParser::PredDefContext* predDefTree, ScopeRef enclosingScope)
    {
        return PredSymbolRef(new PredSymbol(sig, predDefTree, enclosingScope));
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

    Signature getSignature() const {
        return _signature;
    }

    BUPParser::PredDefContext* _tree;

protected:
    PredSymbol(Signature sig, BUPParser::PredDefContext* predDefTree, ScopeRef enclosingScope) :
        LocalScope(enclosingScope),
        Symbol(signatureToSymbolTableName(sig), SymbolTable::_varbool),
        _signature(sig), _tree(predDefTree)
    {
    }

private:
    Signature _signature;
    std::vector<clause> _clauses;
};

}

#endif //GOS_PREDSYMBOL_H
