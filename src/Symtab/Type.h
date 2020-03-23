//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_TYPE_H
#define CSP2SAT_TYPE_H

#include <string>

using namespace std;

class Type {
public:
    virtual string getName() = 0;
    virtual int getTypeIndex() = 0;
};


#endif //CSP2SAT_TYPE_H
