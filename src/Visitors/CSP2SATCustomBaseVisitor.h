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
    bool accessingNotLeafVariable = false;
    SymbolTable *st;
    Scope *currentScope;
    Scope *currentLocalScope = nullptr;

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
            Symbol *value = visit(ctx->varAccess());
            if (value->isAssignable()) {
                return (Value *) ((AssignableSymbol *) value)->getValue();
            } else {
                cerr << "Not allowed arithmetic expressions with variables: " << ctx->getText() << endl;
                throw;
            }
        }
        return CSP2SATBaseVisitor::visitExpr_base(ctx);
    }


    antlrcpp::Any visitVarAccessObjectOrArray(CSP2SATParser::VarAccessObjectOrArrayContext *ctx) override {
        if (ctx->attr) {
            return (Symbol *) this->currentScope->resolve(ctx->attr->getText());
        } else if (ctx->index) {
            Scope * prev = this->currentScope;
            this->currentScope = this->currentLocalScope;
            Value *index = visit(ctx->index);
            this->currentScope = prev;

            return (Symbol *) this->currentScope->resolve(to_string(index->getRealValue()));
        }
        return nullptr;
    }


    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        string a = ctx->getText();
        Symbol *var = this->currentScope->resolve(ctx->TK_IDENT()->getText());

        if(!var){
            cerr << ctx->getText() << " don't exist" << endl;
            throw;
        }

        if (!ctx->varAccessObjectOrArray().empty()) {
            for (auto nestedScope : ctx->varAccessObjectOrArray()) {
                string nest = nestedScope->getText();
                if (var->isScoped()) {
                    this->currentLocalScope = this->currentScope;
                    this->currentScope = (ScopedSymbol *) var;
                    var = visit(nestedScope);
                    this->currentScope = this->currentLocalScope;
                } else {
                    cerr << "BAD ACCESS: " << ctx->TK_IDENT()->getText() << endl;
                    throw;
                }
            }
        }
        if (!this->accessingNotLeafVariable && var->isScoped()) {
            cerr << "BAD ACCESS: " << ctx->getText() << endl;
            throw;
        }
        return var;
    }

    antlrcpp::Any visitValueBaseType(CSP2SATParser::ValueBaseTypeContext *ctx) override {
        if (ctx->integer) {
            return (Value *) new IntValue(stoi(ctx->integer->getText()));
        } else {
            return (Value *) new BoolValue(ctx->boolean->getText() == "true");
        }
    }

    antlrcpp::Any visitRangList(CSP2SATParser::RangListContext *ctx) override {

        Value *minRange = visit(ctx->min);
        Value *maxRange = visit(ctx->max);

        int minValue = minRange->getRealValue();
        int maxValue = maxRange->getRealValue();

        if (minValue < maxValue) {
            ArraySymbol *result = Utils::defineNewArray(
                    "auxRangList",
                    this->currentScope,
                    vector<int>{maxValue - minValue},
                    SymbolTable::_boolean
            );
            for (int i = 0; i < (maxValue - minValue); ++i) {
                ((AssignableSymbol *) result->resolve(to_string(i)))->setValue(new IntValue(minValue + i));
            }
            return result;
        } else {
            cerr << "It must be an incremental range" << endl;
            throw;
        }
    }

    antlrcpp::Any visitAuxiliarListAssignation(CSP2SATParser::AuxiliarListAssignationContext *ctx) override {
        ArraySymbol *arrayDefined = visit(ctx->list());
        return pair<string, ArraySymbol *>(ctx->TK_IDENT()->getText(), arrayDefined);
    }


    antlrcpp::Any visitComprehensionList(CSP2SATParser::ComprehensionListContext *ctx) override {
        auto *listLocalScope = new LocalScope(this->currentScope);
        map<string, ArraySymbol *> ranges;
        this->currentScope = listLocalScope;
        for (int i = 0; i < ctx->auxiliarListAssignation().size(); i++) {
            pair<string, ArraySymbol *> currAuxVar = visit(ctx->auxiliarListAssignation(i));
            ranges.insert(currAuxVar);
        }

        vector<map<string, Symbol *>> possibleAssignations = Utils::getAllCombinations(ranges);
        ArraySymbol *newList = nullptr;

        for (const auto &assignation: possibleAssignations) {
            for (const auto &auxVarAssign : assignation)
                listLocalScope->assign(auxVarAssign.first, auxVarAssign.second);

            bool condition = true;
            if (ctx->condExpr) {
                Value *cond = visit(ctx->condExpr);
                condition = cond->getRealValue();
            }

            if (condition) {
                Symbol *exprRes;
                if (ctx->varAcc) {
                    this->accessingNotLeafVariable = true;
                    exprRes = visit(ctx->varAcc);
                    this->accessingNotLeafVariable = false;
                } else {
                    Value *val = visit(ctx->resExpr);
                    auto *valueResult = new AssignableSymbol(
                            to_string(rand()),
                            val->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer
                    );
                    valueResult->setValue(val);
                    exprRes = valueResult;
                }


                if (newList == nullptr)
                    newList = new ArraySymbol(
                            "comprehensionListAux",
                            listLocalScope,
                            exprRes->type
                    );
                newList->add(exprRes);
            }
        }


        map<string, Symbol *> a = newList->getScopeSymbols();

        for (auto curr : a) {
            if (curr.second->isAssignable())
                cout << ((AssignableSymbol *) curr.second)->getValue()->getRealValue() << endl;
            else if (curr.second->type->getTypeIndex() == SymbolTable::tVarBool)
                cout << ((VariableSymbol *) curr.second)->getVar().v.id << "->"
                     << ((VariableSymbol *) curr.second)->getVar().sign << endl;
            else
                cout << ctx->getText() << " " << curr.first << endl;
        }

        this->currentScope = listLocalScope->getEnclosingScope();


        return newList;
    }

    antlrcpp::Any visitVarAccessList(CSP2SATParser::VarAccessListContext *ctx) override {
        Symbol *array = nullptr;
        this->accessingNotLeafVariable = true;
        array = visit(ctx->varAccess());
        this->accessingNotLeafVariable = false;

        if (array && array->type && array->type->getTypeIndex() == SymbolTable::tArray) {
            return (ArraySymbol *) array;
        } else {
            cerr << ctx->getText() << " is not an array" << endl;
            throw;
        }
    }

};


#endif //CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
