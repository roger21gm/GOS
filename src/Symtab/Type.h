//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_TYPE_H
#define CSP2SAT_TYPE_H

#include <string>

using namespace std;

class Type {
public:
    Type(int typeIndex) : typeIndex(typeIndex) {
        cout << typeIndex << endl;
    }

    virtual string getName() = 0;

    int getTypeIndex() {
        return this->typeIndex;
    }

private:
    int typeIndex;

};

#endif //CSP2SAT_TYPE_H
