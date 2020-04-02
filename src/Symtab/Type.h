//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_TYPE_H
#define CSP2SAT_TYPE_H

#include <string>
#include <utility>
#include "Symbol/Symbol.h"

using namespace std;


class Type : public Symbol {
public:
    Type(int typeIndex, string name) : Symbol(std::move(name)){
        this->typeIndex = typeIndex;
    }

    int getTypeIndex() {
        return this->typeIndex;
    }

    bool isAssignable() override {
        return false;
    }


private:
    int typeIndex;

};

#endif //CSP2SAT_TYPE_H
