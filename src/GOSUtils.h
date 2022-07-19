//
// Created by Roger Generoso Masós on 12/04/2020.
//

#ifndef CSP2SAT_GOSUTILS_H
#define CSP2SAT_GOSUTILS_H

// It is better to use namespaces than static class methods
// https://stackoverflow.com/questions/1434937/namespace-functions-versus-static-methods-on-a-class

#include <string>
#include <sstream> // std::istringstream
#include <fstream>
#include <vector>
#include <memory>

namespace GOS {
namespace Utils {

std::string readFile(const std::string& name) {
    std::ifstream inFile;
    inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inFile.open(name); //open the input file
    std::stringstream inputStream;
    inputStream << inFile.rdbuf(); //read the file
    std::string inputStr = inputStream.str(); //str holds the content of the file
    return inputStr;
}

bool check_number(const std::string & str) {
    std::string num = str;
    if(num[0] == '-'){
        num.erase(0);
    }
    for (int i = 0; i < num.length(); i++)
        if (isdigit(num[i]) == 0)
            return false;
    return true;
}

std::vector<std::string> splitVarAccessNested(std::string a){
    std::vector<std::string> result;
    size_t pos = 0;
    size_t newpos;
    while(pos != std::string::npos) {
        newpos = a.find_first_of(".[", pos);
        if(newpos != std::string::npos){
            result.push_back(a.substr(pos, newpos-pos));
            if(pos != std::string::npos)
                pos = newpos + 1;
        }else {
            result.push_back(a.substr(pos));
            break;
        }
    }
    return result;
}

std::string toRawString(std::string const& in)
{
    char c;
    std::istringstream s(in);
    enum { CHARACTER, ESCAPE } state = CHARACTER;

    std::string result = "";
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

template<class T, class U>
std::shared_ptr<T> as(U param) {
    return std::dynamic_pointer_cast<T>(param);
}

template<class T, class U>
bool is(U param) {
    return std::dynamic_pointer_cast<T>(param) != nullptr;
}

std::vector<std::string> string_split(std::string s, const char delimiter)
{
    size_t start=0;
    size_t end=s.find_first_of(delimiter);

    std::vector<std::string> output;

    while (end <= std::string::npos)
    {
        output.emplace_back(s.substr(start, end-start));

        if (end == std::string::npos)
            break;

        start=end+1;
        end = s.find_first_of(delimiter, start);
    }

    return output;
}

std::vector<std::string> string_split2(std::string s, const char delimiter)
{
    std::vector<std::string> res = {""};
    for(char c : s) {
        if(c == delimiter)
            res.emplace_back("");
        else res.back() += c;
    }

    return res;
}

}
}


#endif //CSP2SAT_GOSUTILS_H
