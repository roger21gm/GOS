//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_PARAM_H
#define CSP2SAT_PARAM_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Param {
public:
    Param(const string &name) : name(name) {}

public:
    string name;
};

class ParamScoped : public Param {
public:
    ParamScoped(const string &name) : Param(name) {}

    virtual void add(Param * a) = 0;
};

class ParamArray : public ParamScoped {
public:
    ParamArray(const string &name) : ParamScoped(name) {
        elements = vector<Param*>();
    }

    void add(Param *a) override {
        elements.push_back(a);
    }

    vector<Param*> elements;
};

class ParamJSON : public ParamScoped {
public:
    ParamJSON(const string &name) : ParamScoped(name) {
        elements = map<string, Param*>();
    }

    void add(Param *a) override {
        elements[a->name] = a;
    }

    map<string, Param*> elements;
};

class ParamBool : public Param {
public:
    ParamBool(const string &name, bool val) : Param(name) {
        this->value = val;
    }
    bool value;
};


class ParamInt : public Param {
public:
    ParamInt(const string &name, int val) : Param(name) {
        this->value = val;
    }
    int value;
};


#endif //CSP2SAT_PARAM_H
