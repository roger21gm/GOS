//
// Created by Roger Generoso Masós on 19/03/2020.
//

#ifndef CSP2SAT_STRUCTSYMBOL_H
#define CSP2SAT_STRUCTSYMBOL_H


class StructSymbol : public Scope, public Type {

private:
    map<string, Symbol*> fields;
    Scope * enclosingScope = nullptr;

public:

    StructSymbol(const string& name, Type * type, Scope * enclosingScope) : Type(SymtbolTable::tCustom, name) {
        this->enclosingScope = enclosingScope;
    }

    StructSymbol(const string& name, Scope * enclosingScope) : Type(SymtbolTable::tCustom, name) {
        this->enclosingScope = enclosingScope;
    }

    string getScopeName() override {
        return this->name;
    }

    Scope *getEnclosingScope() override {
        return this->enclosingScope;
    }

    void define(Symbol *sym) override {
        sym->scope = this;
        fields.insert(pair<string, Symbol*>(sym->getName(), sym));
    }

    Symbol *resolve(const string& name) override {
        if ( fields.find(name) != fields.end() )
            return fields.find(name)->second;
        if ( enclosingScope != nullptr )
            return enclosingScope->resolve(name);
        return nullptr;
    }
};


#endif //CSP2SAT_STRUCTSYMBOL_H
