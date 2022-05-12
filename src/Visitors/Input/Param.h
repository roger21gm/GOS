//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_PARAM_H
#define CSP2SAT_PARAM_H

#include <regex>
#include <iostream>
#include <memory>
#include "../../Errors/GOSException.h"
#include "../../Errors/GOSInputExceptionsRepository.h"
#include <string>
#include <vector>
#include <map>

namespace GOS {

class Param {
public:
    Param(const std::string &name) : name(name) {}
    virtual ~Param() {};

    virtual bool isValuable() = 0;

public:
    std::string name;
};
typedef std::shared_ptr<Param> ParamRef;

class ParamValuable : public Param {
public:
    ParamValuable(const std::string &name) : Param(name) {}
    virtual ~ParamValuable() {};

    bool isValuable() override {
        return true;
    }

    virtual int getValue() = 0;
};
typedef std::shared_ptr<ParamValuable> ParamValuableRef;

class ParamBool;
typedef std::shared_ptr<ParamBool> ParamBoolRef;
class ParamBool : public ParamValuable {
public:
    static ParamBoolRef Create(const std::string &name, bool val) {
        return std::shared_ptr<ParamBool>(new ParamBool(name, val));
    }
    int getValue() override {
        return value;
    }
    bool value; // TODO should be protected/private

protected:
    ParamBool(const std::string &name, bool val) : ParamValuable(name) {
        this->value = val;
    }
};

class ParamInt;
typedef std::shared_ptr<ParamInt> ParamIntRef;
class ParamInt : public ParamValuable {
public:
    static ParamIntRef Create(const std::string &name, int val) {
        return std::shared_ptr<ParamInt>(new ParamInt(name, val));
    }
    int getValue() override {
        return value;
    }
    int value; // TODO should be protected/private

protected:
    ParamInt(const std::string &name, int val) : ParamValuable(name) {
        this->value = val;
    }
};

class ParamScoped : public Param {
public:
    ParamScoped(const std::string &name) : Param(name) {}
    virtual ~ParamScoped() {};
    
    bool isValuable() override {
        return false;
    }

    virtual void add(ParamRef a) = 0;
    virtual ParamRef get(std::string name) = 0;
};
typedef std::shared_ptr<ParamScoped> ParamScopedRef;

class ParamArray;
typedef std::shared_ptr<ParamArray> ParamArrayRef;
class ParamArray : public ParamScoped {
public:
    static ParamArrayRef Create(const std::string &name) {
        return std::shared_ptr<ParamArray>(new ParamArray(name));
    }

    void add(ParamRef a) override {
        elements.push_back(a);
    }

    ParamRef get(std::string name) override {
        int index = stoi(name);
        if(index < elements.size()){
            return elements[index];
        }
        return nullptr;
    }

    std::vector<ParamRef> elements; // TODO should be protected/private

protected:
    ParamArray(const std::string &name) : ParamScoped(name) {
        elements = std::vector<ParamRef>();
    }
};

class ParamJSON;
typedef std::shared_ptr<ParamJSON> ParamJSONRef;
class ParamJSON : public ParamScoped, public std::enable_shared_from_this<ParamJSON> {
public:
    static ParamJSONRef Create(const std::string &name) {
        return std::shared_ptr<ParamJSON>(new ParamJSON(name));
    }

    void add(ParamRef a) override {
        elements[a->name] = a;
    }

    ParamRef get(std::string name) override {
        if(elements.find(name) != elements.end())
            return elements[name];
        return nullptr;
    }

    std::map<std::string, ParamRef> elements;

    int resolve(std::string attrAccess) {
        std::vector<std::string> splitted = Utils::splitVarAccessNested(attrAccess);

        std::string currAccess = "";

        bool first = true;

        ParamScopedRef currentScope = shared_from_this();
        for(std::string attr : splitted){
            ParamRef currentParam;
            if(attr.back() == ']'){
                currentParam = currentScope->get(attr.substr(0, attr.size()-1));
                currAccess += "[" + attr.substr(0, attr.size()-1) + "]";
            }
            else {
                currentParam = currentScope->get(attr);
                currAccess += (first ? "" : ".") + attr;
            }

            if(currentParam == nullptr) {
                throw CSP2SATInputNotFoundValue(currAccess);
            };

            if(currentParam->isValuable())
                return std::dynamic_pointer_cast<ParamValuable>(currentParam)->getValue();

            currentScope = std::dynamic_pointer_cast<ParamScoped>(currentParam);
            first = false;
        }
        return -1;
    }
protected:
    ParamJSON(const std::string &name) : ParamScoped(name) {
        elements = std::map<std::string, ParamRef>();
    }
};

}

#endif //CSP2SAT_PARAM_H
