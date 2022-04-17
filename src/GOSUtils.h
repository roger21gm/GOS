//
// Created by Roger Generoso Masós on 12/04/2020.
//

#ifndef CSP2SAT_GOSUTILS_H
#define CSP2SAT_GOSUTILS_H


// It is better to use namespaces than static class methods
// https://stackoverflow.com/questions/1434937/namespace-functions-versus-static-methods-on-a-class

#include <string.h>

using std::string;
using std::vector;

namespace GOS {
namespace Utils {

bool check_number(const string & str) {
    string num = str;
    if(num[0] == '-'){
        num.erase(0);
    }
    for (int i = 0; i < num.length(); i++)
        if (isdigit(num[i]) == 0)
            return false;
    return true;
}

vector<string> splitVarAccessNested(string a){
    vector<string> result;
    size_t pos = 0;
    size_t newpos;
    while(pos != string::npos) {
        newpos = a.find_first_of(".[", pos);
        if(newpos != string::npos){
            result.push_back(a.substr(pos, newpos-pos));
            if(pos != string::npos)
                pos = newpos + 1;
        }else {
            result.push_back(a.substr(pos));
            break;
        }
    }
    return result;
}

string toRawString(string const& in)
{
    char c;
    istringstream s(in);
    enum { CHARACTER, ESCAPE } state = CHARACTER;

    string result = "";
    while (s.get(c)) {
        switch (state) {
            case CHARACTER:
                if (c == '\\') {
                    state = ESCAPE;
                } else {
                    result += c;
                }
                break;

            case ESCAPE:
                switch (c) {
                    case 'n':
                        result += "\n";
                        break;
                    case 't':
                        result += "\t";
                        break;
                }
                state = CHARACTER;
                break;
        }
    }
    return result;
}

}
}


#endif //CSP2SAT_GOSUTILS_H
