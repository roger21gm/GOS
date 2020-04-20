//
// Created by Roger Generoso Masós on 16/04/2020.
//

#ifndef CSP2SAT_CSP2SATENCODING_H
#define CSP2SAT_CSP2SATENCODING_H


#include <encoding.h>
#include "Symtab/SymbolTable.h"
#include "Symtab/Symbol/Scoped/ScopedSymbol.h"
#include "Symtab/Symbol/Valued/VariableSymbol.h"

class CSP2SATEncoding : public Encoding {

private:
    SMTFormula *f;
    SymbolTable *st;

    void fillModelValuesResult(Scope *currentScope, const EncodedFormula formula, const vector<bool> bmodel) {
        map<string, Symbol *> currentScopeSymbols = currentScope->getScopeSymbols();

        for (pair<string, Symbol *> sym : currentScopeSymbols) {
            if (sym.second->type) {
                if (sym.second->isScoped())
                    fillModelValuesResult((ScopedSymbol *) sym.second, formula, bmodel);
                else if (sym.second->type->getTypeIndex() == SymbolTable::tVarBool) {
                    VariableSymbol * currentVariable = (VariableSymbol *)sym.second;

                    bool modelValue = SMTFormula::getBValue(currentVariable->getVar().v, bmodel);

                    currentVariable->setModelValue(modelValue);
                }
            }
        }
    }

    void printModelSolution(Scope *currentScope, ostream &os, string prefix = "") const {
        map<string, Symbol *> currentScopeSymbols = currentScope->getScopeSymbols();

        for(pair<string, Symbol *> sym : currentScopeSymbols){
            if(sym.second->type){
                if(sym.second->type->getTypeIndex() == SymbolTable::tCustom || sym.second->type->getTypeIndex() == SymbolTable::tArray)
                    if(!isdigit(sym.first[0]))
                        printModelSolution( (ScopedSymbol*) sym.second, os, prefix + "." + sym.first );
                    else
                        printModelSolution( (ScopedSymbol*) sym.second, os, isdigit(sym.first[0]) ? prefix + "[" + sym.first + "]" : prefix + sym.first);
                else{
                    string output = "var -> ";
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

                    if(sym.second->type->getTypeIndex() == SymbolTable::tVarBool){
                        VariableSymbol * currentVariable = (VariableSymbol *)sym.second;


                        os << output  << " -> " << (currentVariable->getModelValue() ? "true" : "false") << endl;
                    }
                }
            }
        }
    }

public:

    CSP2SATEncoding(SMTFormula *formula, SymbolTable *st) {
        this->f = formula;
        this->st = st;
    }

    SMTFormula *encode(int LB = 0, int UB = 0) override {
        return f;
    }

    bool printSolution(ostream &os) const override {

        printModelSolution(this->st->gloabls, os);


        return true;
    }

    void setModel(const EncodedFormula &ef, int lb, int ub, const vector<bool> &bmodel, const vector<int> &imodel) override {
        fillModelValuesResult(this->st->gloabls, ef, bmodel);
        Encoding::setModel(ef, lb, ub, bmodel, imodel);
    }
};


#endif //CSP2SAT_CSP2SATENCODING_H
