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
#include "../Errors/CSP2SATExceptionsRepository.h"

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

    antlrcpp::Any visitExprTop(CSP2SATParser::ExprTopContext *ctx) override {
        try {
            return CSP2SATBaseVisitor::visitExprTop(ctx);
        } catch (CSP2SATException &e) {
            cerr << e.getErrorMessage() << endl;
            return nullptr;
        }
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
                    throw CSP2SATInvalidExpressionTypeException(
                            ctx->exprEq(i)->getStart()->getLine(),
                            ctx->exprEq(i)->getStart()->getCharPositionInLine(),
                            ctx->getText(),
                            Utils::getTypeName(SymbolTable::tInt),
                            Utils::getTypeName(SymbolTable::tBool)
                    );
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
                throw CSP2SATTypeNotMatchException(
                        ctx->opEquality(0)->start->getLine(),
                        ctx->opEquality(0)->start->getCharPositionInLine(),
                        ctx->getText()
                );
            }
        } else if (ctx->exprRel().size() > 2) {
            throw CSP2SATInvalidOperationException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
        }
        return lVal;
    }

    antlrcpp::Any visitExprRel(CSP2SATParser::ExprRelContext *ctx) override {
        Value *lVal = visit(ctx->exprSumDiff(0));
        if (ctx->exprSumDiff().size() == 2) {
            Value *rVal = visit(ctx->exprSumDiff(1));

            if (lVal->isBoolean()) {
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->exprSumDiff(0)->start->getLine(),
                        ctx->exprSumDiff(0)->start->getCharPositionInLine(),
                        ctx->exprSumDiff(0)->getText(),
                        Utils::getTypeName(SymbolTable::tBool),
                        Utils::getTypeName(SymbolTable::tInt)
                );
            }
            if (rVal->isBoolean()) {
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->exprSumDiff(1)->start->getLine(),
                        ctx->exprSumDiff(1)->start->getCharPositionInLine(),
                        ctx->exprSumDiff(1)->getText(),
                        Utils::getTypeName(SymbolTable::tBool),
                        Utils::getTypeName(SymbolTable::tInt)
                );
            };

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

        } else if (ctx->exprSumDiff().size() > 2) {
            throw CSP2SATInvalidOperationException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
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
                    throw CSP2SATInvalidExpressionTypeException(
                            ctx->exprMulDivMod(1)->start->getLine(),
                            ctx->exprMulDivMod(1)->start->getCharPositionInLine(),
                            ctx->exprMulDivMod(1)->getText(),
                            Utils::getTypeName(SymbolTable::tBool),
                            Utils::getTypeName(SymbolTable::tInt)
                    );
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
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText(),
                        Utils::getTypeName(SymbolTable::tInt),
                        Utils::getTypeName(SymbolTable::tBool)
                );
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
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->getStart()->getLine(),
                        ctx->getStart()->getCharPositionInLine(),
                        ctx->getText(),
                        Utils::getTypeName(SymbolTable::tInt),
                        Utils::getTypeName(value->type->getTypeIndex())
                );
            }
        }
        return CSP2SATBaseVisitor::visitExpr_base(ctx);
    }


    antlrcpp::Any visitVarAccessObjectOrArray(CSP2SATParser::VarAccessObjectOrArrayContext *ctx) override {
        if (ctx->attr) {
            return (Symbol *) this->currentScope->resolve(ctx->attr->getText());
        } else if (ctx->index) {
            Scope *prev = this->currentScope;
            this->currentScope = this->currentLocalScope;
            Value *index = visit(ctx->index);
            this->currentScope = prev;

            Symbol *res = this->currentScope->resolve(to_string(index->getRealValue()));

            return (Symbol *) this->currentScope->resolve(to_string(index->getRealValue()));
        }
        return nullptr;
    }


    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        string a = ctx->getText();
        Symbol *var = this->currentScope->resolve(ctx->TK_IDENT()->getText());

        if (!var) {
            throw CSP2SATNotExistsException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
        }

        if (!ctx->varAccessObjectOrArray().empty()) {
            for (int i = 0; i < ctx->varAccessObjectOrArray().size(); i++) {
                auto nestedScope = ctx->varAccessObjectOrArray(i);
                string nest = nestedScope->getText();
                if (var->isScoped()) {
                    this->currentLocalScope = this->currentScope;
                    if (!nestedScope->underscore) {
                        this->currentScope = (ScopedSymbol *) var;
                        var = visit(nestedScope);
                    } else {
                        ScopedSymbol *result = (ScopedSymbol *) var;
                        for (int j = i + 1; j < ctx->varAccessObjectOrArray().size(); j++) {
                            if (ctx->varAccessObjectOrArray(j)->underscore) {
                                throw CSP2SATInvalidExpressionTypeException(
                                        ctx->start->getLine(),
                                        ctx->start->getCharPositionInLine(),
                                        ctx->getText(),
                                        "matrix",
                                        "list"
                                );
                            }
                            ArraySymbol *aux = new ArraySymbol(
                                    "aux",
                                    result,
                                    ((ArraySymbol *) result)->getElementsType()
                            );
                            for (auto currDimElem : ((ScopedSymbol *) result)->getScopeSymbols()) {
                                if (currDimElem.second->type->getTypeIndex() == SymbolTable::tArray) {
                                    this->currentScope = (ScopedSymbol *) currDimElem.second;
                                    Symbol *currDimSymElem = visit(ctx->varAccessObjectOrArray(j));
                                    aux->add(currDimSymElem);
                                } else {
                                    throw CSP2SATBadAccessException(
                                            ctx->start->getLine(),
                                            ctx->start->getCharPositionInLine(),
                                            ctx->getText()
                                    );
                                }
                            }
                            result = aux;
                        }
                        var = result;
                        this->currentScope = this->currentLocalScope;
                        break;
                    }
                    this->currentScope = this->currentLocalScope;
                } else {
                    throw CSP2SATBadAccessException(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText()
                    );
                }
            }
        }
        if (!this->accessingNotLeafVariable && var->isScoped()) {
            throw CSP2SATBadAccessException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
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

    antlrcpp::Any visitListResultExpr(CSP2SATParser::ListResultExprContext *ctx) override {
        Symbol * result = nullptr;
        if(ctx->varAcc && ctx->varAcc->constraint_base()->varAccess()){
            result = visit(ctx->varAcc->constraint_base()->varAccess());
            if(ctx->varAcc->TK_CONSTRAINT_NOT()){
                if(result->type->getTypeIndex() == SymbolTable::tVarBool){
                    result = new VariableSymbol("!" + result->name, !((VariableSymbol*)result)->getVar());
                }
            }
        }
        else {
            throw;
        }
        return result;
    }

    antlrcpp::Any visitRangList(CSP2SATParser::RangListContext *ctx) override {

        Value *minRange = visit(ctx->min);
        Value *maxRange = visit(ctx->max);

        int minValue = minRange->getRealValue();
        int maxValue = maxRange->getRealValue();

        if (minValue < maxValue) {
            ArraySymbol *result = new ArraySymbol(
                    "auxRangList",
                    this->currentScope,
                    SymbolTable::_integer
            );
            for (int i = 0; i < (maxValue - minValue); ++i) {
                AssignableSymbol *newValue = new AssignableSymbol(to_string(i), SymbolTable::_integer);
                newValue->setValue(new IntValue(minValue + i));
                result->add(newValue);
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
                if (ctx->listResultExpr()->varAcc) {
                    this->accessingNotLeafVariable = true;
                    exprRes = visit(ctx->listResultExpr());
                    this->accessingNotLeafVariable = false;
                } else {
                    Value *val = visit(ctx->listResultExpr()->resExpr);
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

    antlrcpp::Any visitExplicitList(CSP2SATParser::ExplicitListContext *ctx) override {
        ArraySymbol *resultList = nullptr;

        for (auto currVal : ctx->listResultExpr()) {
            Symbol *curr = nullptr;
            if (currVal->varAcc) {
                curr = visit(currVal);
            } else {
                Value *exprVal = visit(currVal->resExpr);
                curr = new AssignableSymbol(to_string(rand()),
                                            exprVal->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer);
                ((AssignableSymbol *) curr)->setValue(exprVal);
            }

            if (resultList == nullptr) {
                resultList = new ArraySymbol(
                        to_string(rand()),
                        this->currentScope,
                        curr->type
                );
            }

            if (curr->type->getTypeIndex() == resultList->getElementsType()->getTypeIndex()) {
                resultList->add(curr);
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                        currVal->start->getLine(),
                        currVal->start->getCharPositionInLine(),
                        currVal->getText(),
                        Utils::getTypeName(curr->type->getTypeIndex()),
                        Utils::getTypeName(resultList->getElementsType()->getTypeIndex())
                );
            }
        }

        return resultList;
    }

};


#endif //CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
