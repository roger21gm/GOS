//
// Created by Roger Generoso Masós on 28/03/2020.
//

#ifndef CSP2SAT_VALUE_H
#define CSP2SAT_VALUE_H

using namespace std;

class Value {
public:
    Value() = default;

    virtual string getRealValue() = 0;
    virtual bool isBaseType() = 0;
};


#endif //CSP2SAT_VALUE_H
