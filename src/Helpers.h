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
};


#endif //CSP2SAT_HELPERS_H
