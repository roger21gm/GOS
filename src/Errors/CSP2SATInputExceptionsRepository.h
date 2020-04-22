//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_CSP2SATINPUTEXCEPTIONSREPOSITORY_H
#define CSP2SAT_CSP2SATINPUTEXCEPTIONSREPOSITORY_H


#include "CSP2SATException.h"

class CSP2SATBadInputTypeException : public CSP2SATException {
public:
    CSP2SATBadInputTypeException(int line, int pos, const string &name) :
            CSP2SATException(
                    line,
                    pos,
                    "\"" + name + "\":" + "Only int and bool values allowed as params"
            ) {}
};


class CSP2SATInputNotFoundValue : public CSP2SATException {
public:
    CSP2SATInputNotFoundValue(const string &access) :
            CSP2SATException(
                    0,
                    0,
                    "\"" + access + "\":" + " Not found in input file"
            ) {}
};


#endif //CSP2SAT_CSP2SATINPUTEXCEPTIONSREPOSITORY_H
