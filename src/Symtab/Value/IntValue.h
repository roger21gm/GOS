//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_INTVALUE_H
#define CSP2SAT_INTVALUE_H


#include <string>
#include "Value.h"

class IntValue : public Value {

public:
    explicit IntValue(int intVal) {
        this->realIntValue = intVal;
    }

    string getRealValue() override {
        return to_string(realIntValue);
    }

private:
    int realIntValue;
};


#endif //CSP2SAT_INTVALUE_H
