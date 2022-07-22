//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_GOSEXCEPTION_H
#define CSP2SAT_GOSEXCEPTION_H

#include <exception>
#include <string>
#include "../Symtab/SymbolTable.h"

namespace GOS {

struct ExceptionLocation {
    std::filesystem::path file;
    size_t line;
    size_t pos;
    static std::filesystem::path rootPath;

    std::string toString() const {
        if(rootPath.empty())
            throw std::invalid_argument("Root path not defined");
        const std::filesystem::path filePath = relative(file,rootPath) / file.filename();
        return "In file \"" + filePath.string() + "\" (" + std::to_string(line) + ":" + std::to_string(pos) + "):";
    }
};
std::filesystem::path ExceptionLocation::rootPath = "";

class GOSException : public std::exception {
private:
    ExceptionLocation _location;
    std::string _message;

public:
    GOSException(ExceptionLocation location, const std::string &message) : _location(location), _message(message) {
        SymbolTable::errors = true;
    }

    std::string getErrorMessage(){
        std::string error = _location.toString() + " ERROR: " + _message;
        return error;
    }
};

}

#endif //CSP2SAT_GOSEXCEPTION_H
