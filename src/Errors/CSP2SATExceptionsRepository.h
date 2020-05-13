//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_CSP2SATEXCEPTIONSREPOSITORY_H
#define CSP2SAT_CSP2SATEXCEPTIONSREPOSITORY_H


#include "CSP2SATException.h"

class CSP2SATBadAccessException : public CSP2SATException {
public:
    CSP2SATBadAccessException(int line, int pos, const string &badAccess) :
            CSP2SATException(
                    line,
                    pos,
                    "Invalid access: \"" + badAccess + "\" is not a variable or param"
            ) {}
};

class CSP2SATStringOnlyOutputException : public CSP2SATException {
public:
    CSP2SATStringOnlyOutputException(int line, int pos, const string &str) :
            CSP2SATException(
                    line,
                    pos,
                    "\"" + str + "\": String only allowed on output"
            ) {}
};

class CSP2SATNotExistsException : public CSP2SATException {
public:
    CSP2SATNotExistsException(int line, int pos, const string &badAccess) :
            CSP2SATException(
                    line,
                    pos,
                    "Invalid: \"" + badAccess + "\" don't exists"
            ) {}
};


class CSP2SATInvalidExpressionTypeException : public CSP2SATException {
public:
    CSP2SATInvalidExpressionTypeException(int line, int pos, string expr, string typeFound, string typeExpected) :
            CSP2SATException(
                    line,
                    pos,
                    "Invalid expression type \"" + expr + "\": found " + typeFound + " vs expected " + typeExpected
            ) {}
};


class CSP2SATParamAsConstraintException : public CSP2SATException {
public:
    CSP2SATParamAsConstraintException(int line, int pos, string expr) :
            CSP2SATException(
                    line,
                    pos,
                    "\"" + expr + "\": Params not allowed as constraints"
            ) {}
};

class CSP2SATAlreadyExistException : public CSP2SATException {
public:
    CSP2SATAlreadyExistException(int line, int pos, string expr) :
            CSP2SATException(
                    line,
                    pos,
                    "\"" + expr + "\" already exists"
            ) {}
};

class CSP2SATOutOfRangeException : public CSP2SATException {
public:
    CSP2SATOutOfRangeException(int line, int pos, string expr) :
            CSP2SATException(
                    line,
                    pos,
                    "\"" + expr + "\" access out of range"
            ) {}
};

class CSP2SATTypeNotMatchException : public CSP2SATException {
public:
    CSP2SATTypeNotMatchException(int line, int pos, string expr) :
            CSP2SATException(
                    line,
                    pos,
                    "Types not matching \"" + expr + "\""
            ) {}
};

class CSP2SATInvalidOperationException : public CSP2SATException {
public:
    CSP2SATInvalidOperationException(int line, int pos, string expr) :
            CSP2SATException(
                    line,
                    pos,
                    "Invalid operation \"" + expr + "\""
            ) {}
};


class CSP2SATInvalidFormulaException : public CSP2SATException {
public:
    CSP2SATInvalidFormulaException(int line, int pos, string formula, string message = "") :
            CSP2SATException(
                    line,
                    pos,
                    "Invalid formula \"" + formula + "\": " + message
            ) {}
};


#endif //CSP2SAT_CSP2SATEXCEPTIONSREPOSITORY_H
