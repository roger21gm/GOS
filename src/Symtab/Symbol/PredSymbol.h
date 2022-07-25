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
    // Signature
    struct Param {
        Param() = default;
        Param(const std::string& name, int type) : name(name), type(type) {}
        virtual ~Param() {}
        virtual std::string toStringSymTable() {
            return std::to_string(type);
        }
        virtual std::string toString() {
            return SymbolTable::typeToString(type);
        }

        std::string name;
        int type;
    };
    typedef std::shared_ptr<Param> ParamRef;
    struct ParamArray : public Param {
        ParamArray() : Param() {}
        ParamArray(const std::string& name, int type, int elemType, int nDimensions) :
            Param(name,type), elemType(elemType), nDimensions(nDimensions) {}
        std::string toStringSymTable() override {
            std::string res = std::to_string(elemType);
            for(int i = 0; i < nDimensions; i++) res += "[]";
            return res;
        }
        std::string toString() override {
            std::string res = SymbolTable::typeToString(elemType);
            for(int i = 0; i < nDimensions; i++) res += "[]";
            return res;
        }

        int elemType;
        int nDimensions;
    };
    typedef std::shared_ptr<ParamArray> ParamArrayRef;
    struct Signature {
        const std::string toStringSymTable() {
            std::string res = name + "(";
            for (ParamRef p : params)  res += p->toStringSymTable();
            res += ")";
            return res;
        }
        const std::string toString() {
            std::string res = name + "(";
            for (int i = 0; i < params.size()-1; i++)
                res += params[i]->toString() + ", ";
            res += params[params.size()-1]->toString() + ")";
            return res;
        }

        std::string name;
        std::vector<ParamRef> params;

    };
    typedef std::shared_ptr<Signature> SignatureRef;

    // PredSymbol
    struct Location {
        std::filesystem::path file;
        size_t line;
        size_t col;
    };

    static PredSymbolRef Create(Signature sig, Location loc, BUPParser::PredDefContext* predDefTree)
    {
        return PredSymbolRef(new PredSymbol(sig, loc, predDefTree));
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

    Location getLocation() const {
        return _loc;
    }

protected:
    PredSymbol(Signature sig, Location loc, BUPParser::PredDefContext* predDefTree) :
        Symbol(sig.toStringSymTable(), SymbolTable::_varbool),
        _signature(sig), _predDefTree(predDefTree), _loc(loc)
    {
    }

private:
    Location _loc;
    Signature _signature;
    std::vector<clause> _clauses;
    BUPParser::PredDefContext* _predDefTree;
};

}

#endif //GOS_PREDSYMBOL_H
