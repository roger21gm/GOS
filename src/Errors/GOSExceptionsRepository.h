//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_GOSEXCEPTIONSREPOSITORY_H
#define CSP2SAT_GOSEXCEPTIONSREPOSITORY_H

#include "GOSException.h"
#include <string>
#include <vector>

namespace GOS {

class CSP2SATBadAccessException : public GOSException {
public:
    CSP2SATBadAccessException(ExceptionLocation location, const std::string &badAccess) :
            GOSException(
                    location,
                    "Invalid access: \"" + badAccess + "\" is not a variable or param"
            ) {}
};

class CSP2SATStringOnlyOutputException : public GOSException {
public:
    CSP2SATStringOnlyOutputException(ExceptionLocation location, const std::string &str) :
            GOSException(
                    location,
                    "\"" + str + "\": String only allowed on output"
            ) {}
};

class CSP2SATNotExistsException : public GOSException {
public:
    CSP2SATNotExistsException(ExceptionLocation location, const std::string &badAccess) :
            GOSException(
                    location,
                    "Invalid: \"" + badAccess + "\" doesn't exist"
            ) {}
};

class CSP2SATArrayBoundsException : public GOSException {
public:
    CSP2SATArrayBoundsException(ExceptionLocation location, bool shouldBeBounded) :
        GOSException(
                location,
                shouldBeBounded ? "Invalid array definition: Bounded arrays as predicate parameters are not allowed"
                                : "Invalid array definition: Unbounded dimensions in array definitions are not allowed."
        ) {}
};

class CSP2SATPredNotExistsException : public GOSException {
public:
    CSP2SATPredNotExistsException(ExceptionLocation location, const std::string& signature,
                                  const std::vector<std::pair<std::string, ExceptionLocation>>& candidates) :
            GOSException(
                    location,
                    errorMessage(signature, candidates)
            ) {}

private:
    static std::string errorMessage(const std::string& signature,
                                    const std::vector<std::pair<std::string, ExceptionLocation>>& candidates){
        std::string message = "Predicate with signature \"" + signature + "\" is undefined. ";
        message += (candidates.size() > 1 ? "Candidates are" : "Candidate is") ;
        message += ":\n";
        for (auto c : candidates) {
            std::string modifiedLocStr = c.second.toString().erase(0,1);
            modifiedLocStr.pop_back();
            message += "\t" + c.first + "\t" + "Defined i" + modifiedLocStr + "\n";
        }
        return message;
    }
};



class CSP2SATInvalidExpressionTypeException : public GOSException {
public:
    CSP2SATInvalidExpressionTypeException(ExceptionLocation location, std::string expr, std::string typeFound, std::string typeExpected) :
            GOSException(
                    location,
                    "Invalid expression type \"" + expr + "\": found " + typeFound + " vs expected " + typeExpected
            ) {}
};


class CSP2SATParamAsConstraintException : public GOSException {
public:
    CSP2SATParamAsConstraintException(ExceptionLocation location, std::string expr) :
            GOSException(
                    location,
                    "\"" + expr + "\": Params not allowed as constraints"
            ) {}
};

class CSP2SATAlreadyExistException : public GOSException {
public:
    CSP2SATAlreadyExistException(ExceptionLocation location, std::string expr) :
            GOSException(
                    location,
                    "\"" + expr + "\" already exists"
            ) {}
};

class CSP2SATOutOfRangeException : public GOSException {
public:
    CSP2SATOutOfRangeException(ExceptionLocation location, std::string expr) :
            GOSException(
                    location,
                    "\"" + expr + "\" access out of range"
            ) {}
};

class CSP2SATTypeNotMatchException : public GOSException {
public:
    CSP2SATTypeNotMatchException(ExceptionLocation location, std::string expr) :
            GOSException(
                    location,
                    "Types not matching \"" + expr + "\""
            ) {}
};

class CSP2SATInvalidOperationException : public GOSException {
public:
    CSP2SATInvalidOperationException(ExceptionLocation location, std::string expr) :
            GOSException(
                    location,
                    "Invalid operation \"" + expr + "\""
            ) {}
};


class CSP2SATInvalidFormulaException : public GOSException {
public:
    CSP2SATInvalidFormulaException(ExceptionLocation location, std::string formula, std::string message = "") :
            GOSException(
                    location,
                    "Invalid formula \"" + formula + "\": " + message
            ) {}
};

}

#endif //CSP2SAT_GOSEXCEPTIONSREPOSITORY_H
