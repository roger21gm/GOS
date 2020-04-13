//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
#define CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H

#include <CSP2SATLexer.h>
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Symbol/Scoped/ArraySymbol.h"
#include "Utils.h"
#include "CSP2SATBaseVisitor.h"
#include "../Symtab/Value/IntValue.h"
#include "../Symtab/Value/BoolValue.h"
#include "../Symtab/Scope/LocalScope.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATCustomBaseVisitor : public CSP2SATBaseVisitor {

protected:
    SymbolTable *st;
    Scope *currentScope;

public:

    explicit CSP2SATCustomBaseVisitor(SymbolTable *symbolTable) {
        this->st = symbolTable;
        this->currentScope = this->st->gloabls;
    }

    antlrcpp::Any visitExprTernary(CSP2SATParser::ExprTernaryContext *ctx) override {
        Value *condition = visit(ctx->condition);
        if (condition->getRealValue())
            return visit(ctx->op1);
        else
            return visit(ctx->op2);
    }

    antlrcpp::Any visitExprAnd(CSP2SATParser::ExprAndContext *ctx) override {
        Value *result = visit(ctx->exprOr(0));
        if (ctx->exprOr().size() > 1) {
            BoolValue *res = new BoolValue(true);
            for (int i = 0; i < ctx->exprOr().size(); i++) {
                Value *currValue = visit(ctx->exprOr(i));
                res->setRealValue(res->getRealValue() && currValue->getRealValue());
            }
            return (Value *) res;
        }
        return result;
    }

    antlrcpp::Any visitExprOr(CSP2SATParser::ExprOrContext *ctx) override {
        Value *result = visit(ctx->exprEq(0));
        if (ctx->exprEq().size() > 1) {
            BoolValue *res = new BoolValue(false);
            for (int i = 0; i < ctx->exprEq().size(); i++) {
                Value *currValue = visit(ctx->exprEq(i));
                if (currValue->isBoolean())
                    res->setRealValue(res->getRealValue() || currValue->getRealValue());
                else {
                    cerr << ctx->exprEq(i)->getText() << " is not a boolean value" << endl;
                    throw;
                }
            }
            return (Value *) res;
        }
        return result;
    }

    antlrcpp::Any visitExprEq(CSP2SATParser::ExprEqContext *ctx) override {
        Value *lVal = visit(ctx->exprRel(0));
        if (ctx->exprRel().size() == 2) {
            Value *rVal = visit(ctx->exprRel(1));
            if (lVal->isBoolean() == rVal->isBoolean()) {
                BoolValue *res = new BoolValue();
                if (ctx->opEquality(0)->getText() == "==")
                    res->setRealValue(lVal->getRealValue() == rVal->getRealValue());
                else
                    res->setRealValue(lVal->getRealValue() != rVal->getRealValue());
                return (Value *) res;
            } else {
                cerr << "Equality operation types don't match" << endl;
                throw;
            }
        } else if (ctx->exprRel().size() > 2) {
            cerr << "Invalid equality operation int vs bool" << endl;
            throw;
        }
        return lVal;
    }

    antlrcpp::Any visitExprRel(CSP2SATParser::ExprRelContext *ctx) override {
        Value *lVal = visit(ctx->exprSumDiff(0));
        if (ctx->exprSumDiff().size() == 2) {
            Value *rVal = visit(ctx->exprSumDiff(1));
            if (lVal->isBoolean() == rVal->isBoolean()) {
                BoolValue *res = new BoolValue();
                if (ctx->opRelational(0)->getText() == "<")
                    res->setRealValue(lVal->getRealValue() < rVal->getRealValue());
                else if (ctx->opRelational(0)->getText() == ">")
                    res->setRealValue(lVal->getRealValue() > rVal->getRealValue());
                else if (ctx->opRelational(0)->getText() == "<=")
                    res->setRealValue(lVal->getRealValue() <= rVal->getRealValue());
                else
                    res->setRealValue(lVal->getRealValue() >= rVal->getRealValue());
                return (Value *) res;
            } else {
                cerr << "Relational operation types don't match" << endl;
                throw;
            }
        } else if (ctx->exprSumDiff().size() > 2) {
            cerr << "Invalid relational operation int vs bool" << endl;
            throw;
        }
        return lVal;
    }

    antlrcpp::Any visitExprSumDiff(CSP2SATParser::ExprSumDiffContext *ctx) override {
        Value *result = visit(ctx->exprMulDivMod(0));
        if (ctx->exprMulDivMod().size() > 1) {
            IntValue *res = new IntValue(result->getRealValue());
            for (int i = 0; i < ctx->opSumDiff().size(); i++) {
                Value *currValue = visit(ctx->exprMulDivMod(i + 1));
                if (!currValue->isBoolean()) {
                    if (ctx->opSumDiff(i)->getText() == "+")
                        res->setRealValue(res->getRealValue() + currValue->getRealValue());
                    else
                        res->setRealValue(res->getRealValue() - currValue->getRealValue());
                } else {
                    cerr << ctx->exprMulDivMod(i + 1)->getText() << " is not an int value" << endl;
                    throw;
                }

            }
            return (Value *) res;
        }
        return result;
    }

    antlrcpp::Any visitExprMulDivMod(CSP2SATParser::ExprMulDivModContext *ctx) override {
        Value *result = visit(ctx->exprNot(0));
        if (ctx->exprNot().size() > 1) {
            IntValue *res = new IntValue(result->getRealValue());
            for (int i = 0; i < ctx->opMulDivMod().size(); i++) {
                Value *currValue = visit(ctx->exprNot(i + 1));
                if (!currValue->isBoolean()) {
                    if (ctx->opMulDivMod(i)->getText() == "*")
                        res->setRealValue(res->getRealValue() * currValue->getRealValue());
                    else if (ctx->opMulDivMod(i)->getText() == "/")
                        res->setRealValue(res->getRealValue() / currValue->getRealValue());
                    else
                        res->setRealValue(res->getRealValue() % currValue->getRealValue());
                } else {

                }
            }
            return (Value *) res;
        }
        return result;
    }

    antlrcpp::Any visitExprNot(CSP2SATParser::ExprNotContext *ctx) override {
        Value *result = visit(ctx->expr_base());
        if (ctx->op) {
            if (result->isBoolean()) {
                return (Value *) new BoolValue(!result->getRealValue());
            } else {
                cerr << ctx->getText() << ": can't negate a non-boolean value" << endl;
                throw;
            }
        }
        return result;
    }

    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override {
        if (ctx->expr()) {
            return visit(ctx->expr());
        } else if (ctx->varAccess()) {
            ValueSymbol *value = visit(ctx->varAccess());
            if (value->isAssignable()) {
                return (Value *) ((AssignableSymbol *) value)->getValue();
            }
            else {
                cerr << "Not allowed arithmetic expressions with variables: " << ctx->getText() << endl;
                throw;
            }
        }
        return CSP2SATBaseVisitor::visitExpr_base(ctx);
    }

    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        Scope *iniScope = this->currentScope;
        string a = ctx->id->getText();
        Symbol *var = this->currentScope->resolve(ctx->id->getText());
        if (!ctx->varAccessObjectOrArray().empty()) {
            ValueSymbol *val = nullptr;
            ScopedSymbol *nestedScope = (ScopedSymbol *) var;
            if (nestedScope->getTypeIndex() == SymbolTable::tArray ||
                nestedScope->getTypeIndex() == SymbolTable::tCustom) {
                this->currentScope = nestedScope;
                ScopedSymbol *prevScope = nestedScope;
                for (int i = 0; i < ctx->varAccessObjectOrArray().size(); i++) {
                    auto nestedElem = ctx->varAccessObjectOrArray()[i];
                    string nestedElementToFind;
                    if (nestedElem->index) {
                        this->currentScope = iniScope;
                        nestedElementToFind = to_string(((Value *) visit(nestedElem->index))->getRealValue());
                        this->currentScope = prevScope;
                    } else {
                        nestedElementToFind = nestedElem->attr->getText();
                    }

                    if (i == ctx->varAccessObjectOrArray().size() - 1) {
                        Symbol *valueSymbol = this->currentScope->resolve(nestedElementToFind);
                        if (valueSymbol->isAssignable() ||
                            (valueSymbol->type && valueSymbol->type->getTypeIndex() == SymbolTable::tVarBool)) {
                            val = (ValueSymbol *) valueSymbol;
                        } else throw runtime_error(ctx->getText() + " is not a variable/param");
                    } else {
                        if (prevScope->getTypeIndex() == SymbolTable::tArray ||
                            prevScope->getTypeIndex() == SymbolTable::tCustom) {
                            prevScope = (ScopedSymbol *) this->currentScope->resolve(nestedElementToFind);
                            this->currentScope = prevScope;
                        } else {
                            cerr << "BAD ACCESS: " << ctx->getText() << endl;
                            throw;
                        }
                    }
                }
                this->currentScope = iniScope;
                return val;
            } else {
                cerr << "BAD ACCESS: " << ctx->getText() << endl;
                throw;
            }
        } else if (var->type->getTypeIndex() != SymbolTable::tCustom &&
                   var->type->getTypeIndex() != SymbolTable::tArray) {
            AssignableSymbol *a = (AssignableSymbol *) var;
            return (ValueSymbol *) a;
        } else {
            cerr << "BAD ACCESS: " << ctx->getText() << endl;
            throw;
        }
    }

    antlrcpp::Any visitValueBaseType(CSP2SATParser::ValueBaseTypeContext *ctx) override {
        if (ctx->integer) {
            return (Value *) new IntValue(stoi(ctx->integer->getText()));
        } else {
            return (Value *) new BoolValue(ctx->boolean->getText() == "true");
        }
    }

    antlrcpp::Any visitRange(CSP2SATParser::RangeContext *ctx) override {
        Value *minRange = visit(ctx->min);
        Value *maxRange = visit(ctx->max);
        pair<int,int> range(minRange->getRealValue(), maxRange->getRealValue());
        pair<string, pair<int, int>> result (ctx->TK_IDENT()->getText(), range);
        return result;
    }

    antlrcpp::Any visitList(CSP2SATParser::ListContext *ctx) override {

        auto *listLocalScope = new LocalScope(this->currentScope);

        map<string, pair<int, int>> ranges;
        this->currentScope = listLocalScope;
        for (int i = 0; i < ctx->range().size(); i++) {
            this->currentScope->define(new AssignableSymbol(ctx->range(i)->TK_IDENT()->getText(), SymbolTable::_integer));
            pair<string, pair<int, int>> currRange = visit(ctx->range(i));
            ranges.insert(currRange);
        }

        vector<map<string, int>> possibleAssignations = Utils::getAllRangeCombinations(ranges);
        ArraySymbol *newList = nullptr;

        int index = 0;
        for(map<string,int> currAssignation : possibleAssignations) {
            auto itCurrAssignation = currAssignation.begin();
            while (itCurrAssignation != currAssignation.end()) {
                IntValue *currAss = new IntValue(itCurrAssignation->second);
                ((AssignableSymbol *) listLocalScope->resolve(itCurrAssignation->first))->setValue(currAss);
                itCurrAssignation++;
            }

            bool condition = true;
            if (ctx->condExpr) {
                Value *conditionVal = visit(ctx->condExpr);
                condition = conditionVal->getRealValue();
            }

            if (condition) {
                if (ctx->varAcc) {
                    ValueSymbol *valueSymbol = visit(ctx->varAcc->varAccess());
                    if (valueSymbol->isAssignable()) {
                        if (newList == nullptr)
                            newList = Utils::defineNewArray(
                                        "aux",
                                        listLocalScope,
                                        vector<int>{(int)possibleAssignations.size()},
                                        SymbolTable::_integer
                                    );

                        ((AssignableSymbol *) newList->resolve(to_string(index)))->setValue(
                                ((AssignableSymbol *) valueSymbol)->getValue());
                    } else {
                        if (newList == nullptr)
                            newList = new ArraySymbol(
                                    "aux",
                                    listLocalScope,
                                    SymbolTable::_varbool,
                                    possibleAssignations.size()
                            );
                        ValueSymbol * litSymbol = visit(ctx->varAcc);
                        newList->define((VariableSymbol *) litSymbol);
                    }
                    index++;
                } else {
                    if (newList == nullptr)
                        newList = Utils::defineNewArray(
                                    "aux",
                                    listLocalScope,
                                    vector<int>{(int)possibleAssignations.size()},
                                    SymbolTable::_integer
                                );

                    Value *exprVal = visit(ctx->resExpr);
                    ((AssignableSymbol *) newList->resolve(to_string(index)))->setValue(exprVal);
                    index++;
                }
            }
        }
        this->currentScope = listLocalScope->getEnclosingScope();

        map<string, Symbol *> a = newList->getScopeSymbols();
        auto it = a.begin();

        while (it != a.end()) {
            if (it->second->isAssignable())
                cout << ((AssignableSymbol *) it->second)->getValue()->getRealValue() << endl;
            else
                cout << ((VariableSymbol *) it->second)->getVar().v.id << "->" << ((VariableSymbol *) it->second)->getVar().sign << endl;
            it++;
        }
        return newList;
    }

};


#endif //CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
