//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_ARRAYVALUE_H
#define CSP2SAT_ARRAYVALUE_H


#include <string>
#include "Value.h"

class ArrayValue : public Value {

public:
    string getRealValue() override {
        return "nullptr";
    }

    bool isBaseType() override {
        return false;
    }
};


#endif //CSP2SAT_ARRAYVALUE_H
