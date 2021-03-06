//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_GOSCUSTOMBASEVISITOR_H
#define CSP2SAT_GOSCUSTOMBASEVISITOR_H

#include <BUPBaseVisitor.h>
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Value/Value.h"
#include "../Symtab/Value/BoolValue.h"
#include "../Symtab/Value/IntValue.h"
#include "../Visitors/Utils.h"
#include "../Errors/GOSException.h"
#include "../Errors/GOSExceptionsRepository.h"
#include "../Symtab/Scope/LocalScope.h"
#include "../Symtab/Symbol/StringSymbol.h"
#include "../Symtab/Symbol/formulaReturn.h"


using namespace GOS;
using namespace std;

class GOSCustomBaseVisitor : public BUPBaseVisitor {

protected:
    bool accessingNotLeafVariable = false;
    SymbolTable *st;
    SMTFormula *_f;
    Scope *currentScope;
    Scope *currentLocalScope = nullptr;

public:

    explicit GOSCustomBaseVisitor(SymbolTable *symbolTable, SMTFormula *f) {
        this->st = symbolTable;
        this->_f = f;
        this->currentScope = this->st->gloabls;
    }

    antlrcpp::Any visitCsp2sat(BUPParser::Csp2satContext *ctx) override {
        try{
            return BUPBaseVisitor::visitCsp2sat(ctx);
        }
        catch (GOSException & e) {
            cerr << e.getErrorMessage() << endl;
        }
        catch (exception & e) {
            cerr << e.what() << endl;
        }
        return nullptr;
    }


    antlrcpp::Any visitExprTop(BUPParser::ExprTopContext *ctx) override {
        try {
            return BUPBaseVisitor::visitExprTop(ctx);
        } catch (GOSException &e) {
            throw;
        }
    }

    antlrcpp::Any visitExprTernary(BUPParser::ExprTernaryContext *ctx) override {
        Value *condition = visit(ctx->condition);
        if (condition->getRealValue())
            return visit(ctx->op1);
        else
            return visit(ctx->op2);
    }

    antlrcpp::Any visitExprListAggregateOp(BUPParser::ExprListAggregateOpContext *ctx) override {
        ArraySymbol * list = visit(ctx->list());
        Value * result = nullptr;

        if(list->getElementsType()->getTypeIndex() == SymbolTable::tInt){

            vector<Symbol*> elements = list->getSymbolVector();

            if(ctx->opAggregateExpr()->getText() == "sum"){
                int sum = 0;
                for(auto & element : elements)
                    sum += ((AssignableSymbol*)element)->getValue()->getRealValue();
                result = new IntValue(sum);
            }
            else if(ctx->opAggregateExpr()->getText() == "max"){
                int max = INT_MIN;
                for(auto & element : elements){
                    if(((AssignableSymbol*)element)->getValue()->getRealValue() > max){
                        max = ((AssignableSymbol*)element)->getValue()->getRealValue();
                    }
                }
                result = new IntValue(max);
            }
            else if(ctx->opAggregateExpr()->getText() == "min"){
                int min = INT_MAX;
                for(auto & element : elements){
                    if(((AssignableSymbol*)element)->getValue()->getRealValue() < min){
                        min = ((AssignableSymbol*)element)->getValue()->getRealValue();
                    }
                }
                result = new IntValue(min);
            }
            else { //Length
                result = new IntValue(elements.size());
            }
        }
        else{
            throw CSP2SATInvalidExpressionTypeException(
                        ctx->start->getStartIndex(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText(),
                        "list<" + Utils::getTypeName(list->getElementsType()->getTypeIndex()) + ">",
                        Utils::getTypeName(SymbolTable::tInt)
                    );
        }

        return result;
    }

    antlrcpp::Any visitExprAnd(BUPParser::ExprAndContext *ctx) override {
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

    antlrcpp::Any visitExprOr(BUPParser::ExprOrContext *ctx) override {
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

    antlrcpp::Any visitExprEq(BUPParser::ExprEqContext *ctx) override {
        Value *lVal = visit(ctx->exprRel(0));
        if (ctx->exprRel().size() > 1) {
            for (int i = 1; i < ctx->exprRel().size(); i++) {
                Value *rVal = visit(ctx->exprRel(i));
                if (lVal->isBoolean() == rVal->isBoolean()) {
                    BoolValue *res = new BoolValue();
                    if (ctx->opEquality(0)->getText() == "==")
                        res->setRealValue(lVal->getRealValue() == rVal->getRealValue());
                    else
                        res->setRealValue(lVal->getRealValue() != rVal->getRealValue());
                    lVal = res;
                } else {
                    throw CSP2SATTypeNotMatchException(
                            ctx->opEquality(0)->start->getLine(),
                            ctx->opEquality(0)->start->getCharPositionInLine(),
                            ctx->getText()
                    );
                }

            }

        }
        return lVal;
    }

    antlrcpp::Any visitExprRel(BUPParser::ExprRelContext *ctx) override {
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

    antlrcpp::Any visitExprSumDiff(BUPParser::ExprSumDiffContext *ctx) override {
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

    antlrcpp::Any visitExprMulDivMod(BUPParser::ExprMulDivModContext *ctx) override {
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

    antlrcpp::Any visitExprNot(BUPParser::ExprNotContext *ctx) override {
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

    antlrcpp::Any visitExpr_base(BUPParser::Expr_baseContext *ctx) override {
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
                        Utils::getTypeName(value->type->getTypeIndex()),
                        Utils::getTypeName(SymbolTable::tInt)
                );
            }
        }
        return BUPBaseVisitor::visitExpr_base(ctx);
    }


    antlrcpp::Any visitVarAccessObjectOrArray(BUPParser::VarAccessObjectOrArrayContext *ctx) override {
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


    antlrcpp::Any visitVarAccess(BUPParser::VarAccessContext *ctx) override {
        string a = ctx->TK_IDENT()->getText();
        string b = ctx->getText();
        Symbol *var = this->currentScope->resolve(ctx->TK_IDENT()->getText());

        if (var == nullptr) {
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
                if (var != nullptr && var->isScoped()) {
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



        if (var == nullptr || (!this->accessingNotLeafVariable && var->isScoped())) {
            throw CSP2SATBadAccessException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText()
            );
        }
        return var;
    }


    antlrcpp::Any visitValueBaseType(BUPParser::ValueBaseTypeContext *ctx) override {
        if (ctx->integer) {
            return (Value *) new IntValue(stoi(ctx->integer->getText()));
        } else {
            return (Value *) new BoolValue(ctx->boolean->getText() == "true");
        }
    }

    antlrcpp::Any visitRangList(BUPParser::RangListContext *ctx) override {

        Value *minRange = visit(ctx->min);
        Value *maxRange = visit(ctx->max);

        int minValue = minRange->getRealValue();
        int maxValue = maxRange->getRealValue();

        if (minValue <= maxValue) {
            ArraySymbol *result = new ArraySymbol(
                    "auxRangList",
                    this->currentScope,
                    SymbolTable::_integer
            );
            for (int i = 0; i <= (maxValue - minValue); i++) {
                AssignableSymbol *newValue = new AssignableSymbol(to_string(i), SymbolTable::_integer);
                newValue->setValue(new IntValue(minValue + i));
                result->add(newValue);
            }
            return result;
        } else {
            throw GOSException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    "Range must be ascendant"
            );
        }
    }

    antlrcpp::Any visitAuxiliarListAssignation(BUPParser::AuxiliarListAssignationContext *ctx) override {
        ArraySymbol *arrayDefined = visit(ctx->list());
        return pair<string, ArraySymbol *>(ctx->TK_IDENT()->getText(), arrayDefined);
    }



    antlrcpp::Any visitComprehensionList(BUPParser::ComprehensionListContext *ctx) override {
        auto *listLocalScope = new LocalScope(this->currentScope);
        vector<map<string, Symbol *>> possibleAssignations = getAllCombinations(ctx->auxiliarListAssignation());
        ArraySymbol *newList = nullptr;

        this->currentScope = listLocalScope;
        for (const auto &assignation: possibleAssignations) {
            for (const auto &auxVarAssign : assignation)
                listLocalScope->assign(auxVarAssign.first, auxVarAssign.second);

            bool condition = true;
            if (ctx->condExpr) {
                Value *cond = visit(ctx->condExpr);
                if (!cond->isBoolean()) {
                    throw CSP2SATInvalidExpressionTypeException(
                            ctx->condExpr->start->getLine(),
                            ctx->condExpr->start->getCharPositionInLine(),
                            ctx->condExpr->getText(),
                            Utils::getTypeName(SymbolTable::tInt),
                            Utils::getTypeName(SymbolTable::tBool)
                    );
                }
                condition = cond->getRealValue() == 1;
            }

            Symbol *exprRes;

            if (ctx->listResultExpr()->varAcc) {
                this->accessingNotLeafVariable = true;
                exprRes = visit(ctx->listResultExpr());
                this->accessingNotLeafVariable = false;
            }
            else if (ctx->listResultExpr()->resExpr) {
                Value *val = visit(ctx->listResultExpr()->resExpr);
                auto *valueResult = new AssignableSymbol(
                        to_string(rand()),
                        val->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer
                );
                valueResult->setValue(val);
                exprRes = valueResult;
            }
            else if (ctx->listResultExpr()->string()){
                string currStr = visit(ctx->listResultExpr()->string());
                exprRes = new StringSymbol(currStr);
            }
            else {
                formulaReturn * formula = visit(ctx->listResultExpr()->constraint_expression());
                exprRes = (Symbol*) formula;
            }

            if (newList == nullptr)
                newList = new ArraySymbol(
                        "comprehensionListAux",
                        listLocalScope,
                        exprRes->type
                );

            if(condition)
                newList->add(exprRes);
        }
        this->currentScope = listLocalScope->getEnclosingScope();
        return newList;
    }

    antlrcpp::Any visitVarAccessList(BUPParser::VarAccessListContext *ctx) override {
        Symbol *array = nullptr;
        this->accessingNotLeafVariable = true;
        array = visit(ctx->varAccess());
        this->accessingNotLeafVariable = false;

        if (array && array->type && array->type->getTypeIndex() == SymbolTable::tArray) {
            return (ArraySymbol *) array;
        } else {
            throw CSP2SATInvalidExpressionTypeException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    Utils::getTypeName(array->type->getTypeIndex()),
                    "array"
            );
        }
    }

    antlrcpp::Any visitExplicitList(BUPParser::ExplicitListContext *ctx) override {
        ArraySymbol *resultList = nullptr;

        for (auto currVal : ctx->listResultExpr()) {
            Symbol *curr = nullptr;
            if (currVal->varAcc) {
                curr = visit(currVal);
            } else if (currVal->resExpr) {
                Value *exprVal = visit(currVal->resExpr);
                curr = new AssignableSymbol(to_string(rand()),
                                            exprVal->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer);
                ((AssignableSymbol *) curr)->setValue(exprVal);
            } else if (currVal->string()) {
                string currStr = visit(currVal->string());
                curr = new StringSymbol(currStr);
            } else {
                formulaReturn * a =  visit(currVal->constraint_expression());
                curr = (Symbol*) a;
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

protected:
    vector<map<string, Symbol *>> getAllCombinations(vector<GOS::BUPParser::AuxiliarListAssignationContext *> aux){
        vector<map<string, Symbol *>> combinations = vector<map<string, Symbol *>>();
        LocalScope * combScope = new LocalScope(this->currentScope);
        getAllCombinations(0, aux, combinations, combScope);
        return combinations;
    }

    void getAllCombinations(int idx, vector<GOS::BUPParser::AuxiliarListAssignationContext *> aux, vector<map<string, Symbol *>> & combinations, LocalScope * combinationsScope) {
        if (idx == aux.size()) {
            combinations.push_back(combinationsScope->getScopeSymbols());
            return;
        }
        this->currentScope = combinationsScope;
        pair<string, ArraySymbol *> currArr = visit(aux[idx]);
        for (int i = 0; i < currArr.second->getSize(); i++) {
            combinationsScope->define(currArr.first, currArr.second->resolve(to_string(i)));
            getAllCombinations(idx + 1, aux, combinations, combinationsScope);
        }
        this->currentScope = combinationsScope->getEnclosingScope();
    }
};


#endif //CSP2SAT_GOSCUSTOMBASEVISITOR_H
