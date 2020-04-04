//
// Created by Roger Generoso Masós on 28/03/2020.
//

#ifndef CSP2SAT_VALUE_H
#define CSP2SAT_VALUE_H

using namespace std;

class Value {
public:
    virtual int getRealValue() = 0;
    virtual void setRealValue(int val) = 0;
    virtual bool isBoolean() = 0;
};


#endif //CSP2SAT_VALUE_H
