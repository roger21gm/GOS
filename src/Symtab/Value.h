//
// Created by Roger Generoso Masós on 28/03/2020.
//

#ifndef CSP2SAT_VALUE_H
#define CSP2SAT_VALUE_H

#include <memory>

namespace GOS {

class Value {
public:
    virtual int getRealValue() = 0;
    virtual void setRealValue(int val) = 0;
    virtual bool isBoolean() = 0;
};
typedef std::shared_ptr<Value> ValueRef;

class BoolValue;
typedef std::shared_ptr<BoolValue> BoolValueRef;
class BoolValue : public Value {
public:
    static BoolValueRef Create(bool value = true) {
        return std::shared_ptr<BoolValue>(new BoolValue(value));
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

protected:
    BoolValue(bool value = true){
        this->val = value;
    }

private:
    bool val;
};

class IntValue;
typedef std::shared_ptr<IntValue> IntValueRef;
class IntValue : public Value {
public:
    static IntValueRef Create(int intVal) {
        return std::shared_ptr<IntValue>(new IntValue(intVal));
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

protected:
    explicit IntValue(int intVal) {
        this->realIntValue = intVal;
    }

private:
    int realIntValue;
};


}

#endif //CSP2SAT_VALUE_H
