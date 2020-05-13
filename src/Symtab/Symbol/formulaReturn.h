//
// Created by Roger Generoso Masós on 13/05/2020.
//

#ifndef CSP2SAT_FORMULARETURN_H
#define CSP2SAT_FORMULARETURN_H


#include <string>
#include "Symbol.h"
#include "../SymbolTable.h"
#include "smtapi.h"

class formulaReturn : public Symbol {

public:
    formulaReturn() : Symbol("", SymbolTable::_formula) {}

    formulaReturn(clause claus) : Symbol("", SymbolTable::_formula) {
        clauses.push_back(claus);
    }

    void addClause(clause claus) {
        clauses.push_back(claus);
    }

    void addClauses(vector<clause> claus) {
        for (clause curr : claus)
            clauses.push_back(curr);
    }

    vector<clause> clauses;
};


#endif //CSP2SAT_FORMULARETURN_H
