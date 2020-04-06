//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_BOOLVALUE_H
#define CSP2SAT_BOOLVALUE_H


#include <string>
#include "Value.h"

class BoolValue : public Value {
private:
    bool val;

public:
    BoolValue() {
        val = true;
    }

    BoolValue(bool value){
        this->val = value;
    }

    BoolValue(int value){
        this->val = value == 1;
    }

    int getRealValue() override {
        return this->val ? 1 : 0;
    }

    void setRealValue(int value) override {
        this->val = value == 1;
    }

    bool isBoolean() override {
        return true;
    }
};


#endif //CSP2SAT_BOOLVALUE_H
