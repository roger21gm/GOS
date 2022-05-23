//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_TYPE_H
#define CSP2SAT_TYPE_H

#include <string>
#include <utility>
#include <memory>
#include "Symbol/Symbol.h"

namespace GOS {

class Type;
typedef std::shared_ptr<Type> TypeRef;
class Type : public Symbol {
public:
    static TypeRef Create(int typeIndex, std::string name) {
        return TypeRef(new Type(typeIndex, name));
    }

    int getTypeIndex() {
        return this->typeIndex;
    }

    bool isAssignable() override {
        return false;
    }

protected:
    Type(int typeIndex, std::string name) : Symbol(std::move(name)){
        this->typeIndex = typeIndex;
    }

private:
    int typeIndex;
};

}

#endif //CSP2SAT_TYPE_H
