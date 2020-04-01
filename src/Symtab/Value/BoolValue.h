//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_BOOLVALUE_H
#define CSP2SAT_BOOLVALUE_H


#include <string>
#include "Value.h"

class BoolValue : public Value {
public:
    string getRealValue() override {
        return "nullptr";
    }

};


#endif //CSP2SAT_BOOLVALUE_H
