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
    BoolValue(bool value){
        this->val = value;
    }

    int getRealValue() override {
        return this->val ? 1 : 0;
    }
};


#endif //CSP2SAT_BOOLVALUE_H
