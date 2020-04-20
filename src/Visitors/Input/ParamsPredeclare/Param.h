//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_PARAM_H
#define CSP2SAT_PARAM_H

#include <vector>
#include <string>
#include <map>
#include <regex>
#include <iostream>
#include "../../Utils.h"

using namespace std;

class Param {
public:
    Param(const string &name) : name(name) {}

    virtual bool isValuable() = 0;

public:
    string name;
};

class ParamValuable : public Param {
public:
    ParamValuable(const string &name) : Param(name) {}

    bool isValuable() override {
        return true;
    }

    virtual int getValue() = 0;
};

class ParamBool : public ParamValuable {
public:
    ParamBool(const string &name, bool val) : ParamValuable(name) {
        this->value = val;
    }
    int getValue() override {
        return value;
    }
    bool value;
};


class ParamInt : public ParamValuable {
public:
    ParamInt(const string &name, int val) : ParamValuable(name) {
        this->value = val;
    }
    int getValue() override {
        return value;
    }
    int value;
};

class ParamScoped : public Param {
public:
    ParamScoped(const string &name) : Param(name) {}

    bool isValuable() override {
        return false;
    }

    virtual void add(Param * a) = 0;
    virtual Param * get(string name) = 0;
};

class ParamArray : public ParamScoped {
public:
    ParamArray(const string &name) : ParamScoped(name) {
        elements = vector<Param*>();
    }

    void add(Param *a) override {
        elements.push_back(a);
    }

    Param *get(string name) override {
        return elements[stoi(name)];
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

    Param *get(string name) override {
        return elements[name];
    }

    map<string, Param*> elements;

    int resolve(string attrAccess) {
        vector<string> splitted = Utils::splitVarAccessNested(attrAccess);

        ParamScoped * currentScope = this;
        for(string attr : splitted){
            Param * currentParam = nullptr;
            if(attr.back() == ']'){
                currentParam = currentScope->get(attr.substr(0, attr.size()-1));
            }
            else {
                currentParam = currentScope->get(attr);
            }
            if(!currentParam) break;
            if(currentParam->isValuable())
                return ((ParamValuable*) currentParam)->getValue();

            currentScope = (ParamScoped*) currentParam;
        }
        return -1;
    }
};





#endif //CSP2SAT_PARAM_H
