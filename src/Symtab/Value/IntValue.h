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

    int getRealValue() override {
        return realIntValue;
    }

    void setRealValue(int realVal) override {
        this->realIntValue = realVal;
    }

    bool isBoolean() override {
        return false;
    }

private:
    int realIntValue;
};


#endif //CSP2SAT_INTVALUE_H
