//
// Created by Roger Generoso Masós on 29/03/2020.
//

#ifndef CSP2SAT_STRUCTVALUE_H
#define CSP2SAT_STRUCTVALUE_H


#include <string>
#include "Value.h"
#include <map>

class StructValue : public Value {
public:
    string getRealValue() override {
        return nullptr;
    }

    bool isBaseType() override {
        return false;
    }

    void addField(const string& name, Value * val) {
        fields[name] = val;
    }

    Value * getField(const string& name) {
        return fields[name];
    }

private:
    map<string, Value*> fields;
};


#endif //CSP2SAT_STRUCTVALUE_H
