//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_GOSEXCEPTIONSREPOSITORY_H
#define CSP2SAT_GOSEXCEPTIONSREPOSITORY_H

#include "GOSException.h"
#include <string>

namespace GOS {

class CSP2SATBadAccessException : public GOSException {
public:
    CSP2SATBadAccessException(int line, int pos, const std::string &badAccess) :
            GOSException(
                    line,
                    pos,
                    "Invalid access: \"" + badAccess + "\" is not a variable or param"
            ) {}
};

class CSP2SATStringOnlyOutputException : public GOSException {
public:
    CSP2SATStringOnlyOutputException(int line, int pos, const std::string &str) :
            GOSException(
                    line,
                    pos,
                    "\"" + str + "\": String only allowed on output"
            ) {}
};

class CSP2SATNotExistsException : public GOSException {
public:
    CSP2SATNotExistsException(int line, int pos, const std::string &badAccess) :
            GOSException(
                    line,
                    pos,
                    "Invalid: \"" + badAccess + "\" don't exists"
            ) {}
};


class CSP2SATInvalidExpressionTypeException : public GOSException {
public:
    CSP2SATInvalidExpressionTypeException(int line, int pos, std::string expr, std::string typeFound, std::string typeExpected) :
            GOSException(
                    line,
                    pos,
                    "Invalid expression type \"" + expr + "\": found " + typeFound + " vs expected " + typeExpected
            ) {}
};


class CSP2SATParamAsConstraintException : public GOSException {
public:
    CSP2SATParamAsConstraintException(int line, int pos, std::string expr) :
            GOSException(
                    line,
                    pos,
                    "\"" + expr + "\": Params not allowed as constraints"
            ) {}
};

class CSP2SATAlreadyExistException : public GOSException {
public:
    CSP2SATAlreadyExistException(int line, int pos, std::string expr) :
            GOSException(
                    line,
                    pos,
                    "\"" + expr + "\" already exists"
            ) {}
};

class CSP2SATOutOfRangeException : public GOSException {
public:
    CSP2SATOutOfRangeException(int line, int pos, std::string expr) :
            GOSException(
                    line,
                    pos,
                    "\"" + expr + "\" access out of range"
            ) {}
};

class CSP2SATTypeNotMatchException : public GOSException {
public:
    CSP2SATTypeNotMatchException(int line, int pos, std::string expr) :
            GOSException(
                    line,
                    pos,
                    "Types not matching \"" + expr + "\""
            ) {}
};

class CSP2SATInvalidOperationException : public GOSException {
public:
    CSP2SATInvalidOperationException(int line, int pos, std::string expr) :
            GOSException(
                    line,
                    pos,
                    "Invalid operation \"" + expr + "\""
            ) {}
};


class CSP2SATInvalidFormulaException : public GOSException {
public:
    CSP2SATInvalidFormulaException(int line, int pos, std::string formula, std::string message = "") :
            GOSException(
                    line,
                    pos,
                    "Invalid formula \"" + formula + "\": " + message
            ) {}
};

}

#endif //CSP2SAT_GOSEXCEPTIONSREPOSITORY_H
