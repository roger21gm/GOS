//
// Created by David on 27/06/2022.
//

#ifndef GOS_PREDSYMBOL_H
#define GOS_PREDSYMBOL_H

#include "../../GOSUtils.h"
#include "../SymbolTable.h"
#include "Symbol.h"
#include <BUPParser.h>
#include <utility>
#include <map>
#include <string>
#include <memory>

namespace GOS {

class PredSymbol;
typedef std::shared_ptr<PredSymbol> PredSymbolRef;
class PredSymbol : public Symbol {
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

    static PredSymbolRef Create(Signature sig, BUPParser::PredDefContext* predDefTree)
    {
        return PredSymbolRef(new PredSymbol(sig, predDefTree));
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

    BUPParser::PredDefContext* getPredDefTree() {
        return _predDefTree;
    }

protected:
    PredSymbol(Signature sig, BUPParser::PredDefContext* predDefTree) :
        Symbol(signatureToSymbolTableName(sig), SymbolTable::_varbool),
        _signature(sig), _predDefTree(predDefTree)
    {
    }

private:
    Signature _signature;
    std::vector<clause> _clauses;
    BUPParser::PredDefContext* _predDefTree;
};

}

#endif //GOS_PREDSYMBOL_H