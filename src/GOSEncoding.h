//
// Created by Roger Generoso Masós on 16/04/2020.
//

#ifndef CSP2SAT_CSP2SATENCODING_H
#define CSP2SAT_CSP2SATENCODING_H


#include <encoding.h>
#include "Symtab/SymbolTable.h"
#include "Symtab/Symbol/Scoped/ScopedSymbol.h"
#include "Symtab/Symbol/PredSymbol.h"
#include "Symtab/Symbol/Valued/ValueSymbol.h"
#include "Symtab/Symbol/Valued/VariableSymbol.h"
#include "GOSUtils.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>

namespace GOS {

class GOSEncoding : public Encoding {

private:
    SMTFormula *f;
    SymbolTable *st;
    bool sat = false;

    void fillModelValuesResult(ScopeRef currentScope, const EncodedFormula formula, const std::vector<bool> & bmodel) {
        std::map<std::string, SymbolRef> currentScopeSymbols = currentScope->getScopeSymbols();

        for (std::pair<std::string, SymbolRef> sym : currentScopeSymbols) {
            if (sym.second->getType() && !Utils::is<PredSymbol>(sym.second)) {
                if (sym.second->isScoped())
                    fillModelValuesResult(Utils::as<ScopedSymbol>(sym.second), formula, bmodel);
                else if (sym.second->getType()->getTypeIndex() == SymbolTable::tVarBool) {
                    VariableSymbolRef currentVariable = Utils::as<VariableSymbol>(sym.second);

                    bool modelValue = SMTFormula::getBValue(currentVariable->getVar().v, bmodel);

                    currentVariable->setModelValue(modelValue);
                }
            }
        }
    }

    void printModelSolution(ScopeRef currentScope, std::ostream &os, std::string prefix = "") const {
        std::map<std::string, SymbolRef> currentScopeSymbols = currentScope->getScopeSymbols();

        for(std::pair<std::string, SymbolRef> sym : currentScopeSymbols){
            if(sym.second->getType()){
                if(sym.second->getType()->getTypeIndex() == SymbolTable::tCustom || sym.second->getType()->getTypeIndex() == SymbolTable::tArray) {
                    if (!isdigit(sym.first[0]))
                        printModelSolution(Utils::as<ScopedSymbol>(sym.second), os, prefix + "." + sym.first);
                    else
                        printModelSolution(Utils::as<ScopedSymbol>(sym.second), os,
                                           isdigit(sym.first[0]) ? prefix + "[" + sym.first + "]" : prefix + sym.first);
                }
                else{
                    std::string output = "var -> ";
                    if(!prefix.empty() && prefix[0] == '.')
                        output += prefix.substr(1, prefix.length()-1);
                    else
                        output += prefix;

                    if(isdigit(sym.first[0])){
                        output += "[" + sym.first + "]";
                    }
                    else {
                        output += "." + sym.first ;
                    }

                    if(sym.second->getType()->getTypeIndex() == SymbolTable::tVarBool){
                        VariableSymbolRef currentVariable = Utils::as<VariableSymbol>(sym.second);
                        os << output  << " -> " << (currentVariable->getModelValue() ? "true" : "false") << std::endl;
                    }
                }
            }
        }
    }

public:

    GOSEncoding(SMTFormula *formula, SymbolTable *st) {
        this->f = formula;
        this->st = st;
    }

    SMTFormula *encode(int LB = 0, int UB = 0) override {
        return f;
    }

    bool printModelSolution(std::ostream &os) const {
        printModelSolution(this->st->gloabls, os);
        return true;
    }

    bool printSolution(std::ostream &os) const override {
        //printModelSolution(this->st->gloabls, os);
        return true;
    }

    void setModel(const EncodedFormula &ef, int lb, int ub, const std::vector<bool> &bmodel, const std::vector<int> &imodel) override {
        sat = true;
        fillModelValuesResult(this->st->gloabls, ef, bmodel);
    }

    bool isSat(){
        return sat;
    }
};

}

#endif //CSP2SAT_CSP2SATENCODING_H
