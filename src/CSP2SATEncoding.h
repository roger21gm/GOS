//
// Created by Roger Generoso Masós on 16/04/2020.
//

#ifndef CSP2SAT_CSP2SATENCODING_H
#define CSP2SAT_CSP2SATENCODING_H


#include <encoding.h>

class CSP2SATEncoding : public Encoding {
public:
    SMTFormula *encode(int LB, int UB) override {
        return nullptr;
    }
};


#endif //CSP2SAT_CSP2SATENCODING_H
