//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_GOSEXCEPTION_H
#define CSP2SAT_GOSEXCEPTION_H

#include <exception>
#include <string>

namespace GOS {

class GOSException : public exception {
private:
    int line;
    int column;
    string message;

public:
    GOSException(int line, int pos, const string &message) : line(line), column(pos), message(message) {
        SymbolTable::errors = true;
    }

    string getErrorMessage(){
        string error =  string("ERROR on line ") + to_string(line) + ":" + to_string(column) + "\n\t" + message;
        return error;
    }
};

}

#endif //CSP2SAT_GOSEXCEPTION_H
