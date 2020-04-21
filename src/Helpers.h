//
// Created by Roger Generoso Masós on 12/04/2020.
//

#ifndef CSP2SAT_HELPERS_H
#define CSP2SAT_HELPERS_H


class Helpers {

public:
    static bool check_number(string str) {
        for (int i = 0; i < str.length(); i++)
            if (isdigit(str[i]) == false)
                return false;
        return true;
    }

    static vector<string> splitVarAccessNested(string a){
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
};


#endif //CSP2SAT_HELPERS_H
