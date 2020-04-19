//
// Created by Roger Generoso Masós on 19/04/2020.
//

#ifndef CSP2SAT_CSP2SATEXCEPTION_H
#define CSP2SAT_CSP2SATEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class CSP2SATException : public exception {
private:
    int line;
    int column;
    string message;

public:
    CSP2SATException(int line, int pos, const string &message) : line(line), column(pos), message(message) {}

    string getErrorMessage(){
        string error =  string("ERROR on line ") + to_string(line) + ":" + to_string(column) + "\n\t" + message;
        return error;
    }
};


#endif //CSP2SAT_CSP2SATEXCEPTION_H
