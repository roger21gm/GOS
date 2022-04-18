//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_GOSEXCEPTION_H
#define CSP2SAT_GOSEXCEPTION_H

#include <exception>
#include <string>

namespace GOS {

class GOSException : public std::exception {
private:
    int line;
    int column;
    std::string message;

public:
    GOSException(int line, int pos, const std::string &message) : line(line), column(pos), message(message) {
        SymbolTable::errors = true;
    }

    std::string getErrorMessage(){
        std::string error =  std::string("ERROR on line ") + std::to_string(line) + ":" + std::to_string(column) + "\n\t" + message;
        return error;
    }
};

}

#endif //CSP2SAT_GOSEXCEPTION_H
