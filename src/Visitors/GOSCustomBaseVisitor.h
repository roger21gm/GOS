//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_GOSCUSTOMBASEVISITOR_H
#define CSP2SAT_GOSCUSTOMBASEVISITOR_H

#include <BUPBaseVisitor.h>
#include "../Visitors/VisitorsUtils.h"
#include "../Errors/GOSException.h"
#include "../Errors/GOSExceptionsRepository.h"
#include "../Symtab/Scope.h"
#include "../Symtab/Symbol/Symbol.h"
#include "../Symtab/Symbol/StringSymbol.h"
#include "../Symtab/SymbolTable.h"
#include "../Symtab/Value.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <exception>
#include <utility>

namespace GOS {

class GOSCustomBaseVisitor : public BUPBaseVisitor {

protected:
    bool accessingNotLeafVariable = false;
    SymbolTable *st;
    SMTFormula *_f;
    ScopeRef currentScope;
    ScopeRef currentLocalScope = nullptr;

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
            std::cerr << e.getErrorMessage() << std::endl;
        }
        catch (std::exception & e) {
            std::cerr << e.what() << std::endl;
        }
        return nullptr;
    }


    virtual antlrcpp::Any visitEntityDefinitionBlock(BUPParser::EntityDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    virtual antlrcpp::Any visitViewpointBlock(BUPParser::ViewpointBlockContext *ctx) override {
        return nullptr;
    }

    virtual antlrcpp::Any visitPredDefBlock(BUPParser::PredDefBlockContext *ctx) override {
        return nullptr;
    }

    virtual antlrcpp::Any visitOutputBlock(BUPParser::OutputBlockContext *ctx) override {
        return nullptr;
    }

    virtual antlrcpp::Any visitConstraintDefinitionBlock(BUPParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }



    antlrcpp::Any visitExpr(BUPParser::ExprContext *ctx) override {
        try {
            ValueRef condition = visit(ctx->condition);
            if (ctx->TK_INTERROGANT()) {
                if (condition->getRealValue())
                    return visit(ctx->op1);
                else
                    return visit(ctx->op2);
            }
            else return condition;
        } catch (GOSException &e) {
            throw;
        }
    }

    antlrcpp::Any visitExprListAgg(BUPParser::ExprListAggContext *ctx) override {
        ArraySymbolRef list = visit(ctx->list());
        ValueRef result = nullptr;

        if(list->getElementsType()->getTypeIndex() == SymbolTable::tInt){
            std::vector<SymbolRef> elements = list->getSymbolVector();

            if(ctx->opAggregateExpr()->getText() == "sum"){
                int sum = 0;
                for(auto & element : elements)
                    sum += Utils::as<AssignableSymbol>(element)->getValue()->getRealValue();
                result = IntValue::Create(sum);
            }
            else if(ctx->opAggregateExpr()->getText() == "max"){
                int max = INT_MIN;
                for(auto & element : elements){
                    if(Utils::as<AssignableSymbol>(element)->getValue()->getRealValue() > max){
                        max = Utils::as<AssignableSymbol>(element)->getValue()->getRealValue();
                    }
                }
                result = IntValue::Create(max);
            }
            else if(ctx->opAggregateExpr()->getText() == "min"){
                int min = INT_MAX;
                for(auto & element : elements){
                    if(Utils::as<AssignableSymbol>(element)->getValue()->getRealValue() < min){
                        min = Utils::as<AssignableSymbol>(element)->getValue()->getRealValue();
                    }
                }
                result = IntValue::Create(min);
            }
            else { //Length
                result = IntValue::Create(elements.size());
            }
        }
        else if(ctx->opAggregateExpr()->getText() == "sizeof") {
            const int size = list->getSymbolVector().size();
            result = IntValue::Create(size);
        }
        else{
            throw CSP2SATInvalidExpressionTypeException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine()
                },
                ctx->getText(),
                "list<" + VisitorsUtils::getTypeName(list->getElementsType()->getTypeIndex()) + ">",
                VisitorsUtils::getTypeName(SymbolTable::tInt)
            );
        }

        return result;
    }

    antlrcpp::Any visitExprAnd(BUPParser::ExprAndContext *ctx) override {
        ValueRef result = visit(ctx->exprOr(0));
        if (ctx->exprOr().size() > 1) {
            ValueRef res = BoolValue::Create(true);
            for (int i = 0; i < ctx->exprOr().size(); i++) {
                ValueRef currValue = visit(ctx->exprOr(i));
                res->setRealValue(res->getRealValue() && currValue->getRealValue());
            }
            return res;
        }
        return result;
    }

    antlrcpp::Any visitExprOr(BUPParser::ExprOrContext *ctx) override {
        ValueRef result = visit(ctx->exprEq(0));
        if (ctx->exprEq().size() > 1) {
            ValueRef res = BoolValue::Create(false);
            for (int i = 0; i < ctx->exprEq().size(); i++) {
                ValueRef currValue = visit(ctx->exprEq(i));
                if (currValue->isBoolean())
                    res->setRealValue(res->getRealValue() || currValue->getRealValue());
                else {
                    throw CSP2SATInvalidExpressionTypeException(
                        {
                            st->parsedFiles.front()->getPath(),
                            ctx->exprEq(i)->getStart()->getLine(),
                            ctx->exprEq(i)->getStart()->getCharPositionInLine()
                        },
                        ctx->getText(),
                        VisitorsUtils::getTypeName(SymbolTable::tInt),
                        VisitorsUtils::getTypeName(SymbolTable::tBool)
                    );
                }
            }
            return res;
        }
        return result;
    }

    antlrcpp::Any visitExprEq(BUPParser::ExprEqContext *ctx) override {
        ValueRef lVal = visit(ctx->exprRel(0));
        if (ctx->exprRel().size() > 1) {
            for (int i = 1; i < ctx->exprRel().size(); i++) {
                ValueRef rVal = visit(ctx->exprRel(i));
                if (lVal->isBoolean() == rVal->isBoolean()) {
                    ValueRef res = BoolValue::Create();
                    if (ctx->opEquality(0)->getText() == "==")
                        res->setRealValue(lVal->getRealValue() == rVal->getRealValue());
                    else
                        res->setRealValue(lVal->getRealValue() != rVal->getRealValue());
                    lVal = res;
                } else {
                    throw CSP2SATTypeNotMatchException(
                        {
                            st->parsedFiles.front()->getPath(),
                            ctx->opEquality(0)->start->getLine(),
                            ctx->opEquality(0)->start->getCharPositionInLine()
                        },
                        ctx->getText()
                    );
                }

            }

        }
        return lVal;
    }

    antlrcpp::Any visitExprRel(BUPParser::ExprRelContext *ctx) override {
        ValueRef lVal = visit(ctx->exprSumDiff(0));
        if (ctx->exprSumDiff().size() == 2) {
            ValueRef rVal = visit(ctx->exprSumDiff(1));

            if (lVal->isBoolean()) {
                throw CSP2SATInvalidExpressionTypeException(
                    {
                        st->parsedFiles.front()->getPath(),
                        ctx->exprSumDiff(0)->start->getLine(),
                        ctx->exprSumDiff(0)->start->getCharPositionInLine()
                    },
                    ctx->exprSumDiff(0)->getText(),
                    VisitorsUtils::getTypeName(SymbolTable::tBool),
                    VisitorsUtils::getTypeName(SymbolTable::tInt)
                );
            }
            if (rVal->isBoolean()) {
                throw CSP2SATInvalidExpressionTypeException(
                    {
                        st->parsedFiles.front()->getPath(),
                        ctx->exprSumDiff(1)->start->getLine(),
                        ctx->exprSumDiff(1)->start->getCharPositionInLine()
                    },
                    ctx->exprSumDiff(1)->getText(),
                    VisitorsUtils::getTypeName(SymbolTable::tBool),
                    VisitorsUtils::getTypeName(SymbolTable::tInt)
                );
            };

            ValueRef res = BoolValue::Create();
            if (ctx->opRelational(0)->getText() == "<")
                res->setRealValue(lVal->getRealValue() < rVal->getRealValue());
            else if (ctx->opRelational(0)->getText() == ">")
                res->setRealValue(lVal->getRealValue() > rVal->getRealValue());
            else if (ctx->opRelational(0)->getText() == "<=")
                res->setRealValue(lVal->getRealValue() <= rVal->getRealValue());
            else
                res->setRealValue(lVal->getRealValue() >= rVal->getRealValue());
            return res;

        } else if (ctx->exprSumDiff().size() > 2) {
            throw CSP2SATInvalidOperationException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine()
                },
                ctx->getText()
            );
        }
        return lVal;
    }

    antlrcpp::Any visitExprSumDiff(BUPParser::ExprSumDiffContext *ctx) override {
        ValueRef result = visit(ctx->exprMulDivMod(0));
        if (ctx->exprMulDivMod().size() > 1) {
            ValueRef res = IntValue::Create(result->getRealValue());
            for (int i = 0; i < ctx->opSumDiff().size(); i++) {
                ValueRef currValue = visit(ctx->exprMulDivMod(i + 1));
                if (!currValue->isBoolean()) {
                    if (ctx->opSumDiff(i)->getText() == "+")
                        res->setRealValue(res->getRealValue() + currValue->getRealValue());
                    else
                        res->setRealValue(res->getRealValue() - currValue->getRealValue());
                } else {
                    throw CSP2SATInvalidExpressionTypeException(
                        {
                            st->parsedFiles.front()->getPath(),
                            ctx->exprMulDivMod(1)->start->getLine(),
                            ctx->exprMulDivMod(1)->start->getCharPositionInLine()
                        },
                        ctx->exprMulDivMod(1)->getText(),
                        VisitorsUtils::getTypeName(SymbolTable::tBool),
                        VisitorsUtils::getTypeName(SymbolTable::tInt)
                    );
                }

            }
            return res;
        }
        return result;
    }

    antlrcpp::Any visitExprMulDivMod(BUPParser::ExprMulDivModContext *ctx) override {
        ValueRef result = visit(ctx->exprNot(0));
        if (ctx->exprNot().size() > 1) {
            ValueRef res = IntValue::Create(result->getRealValue());
            for (int i = 0; i < ctx->opMulDivMod().size(); i++) {
                ValueRef currValue = visit(ctx->exprNot(i + 1));
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
            return res;
        }
        return result;
    }

    antlrcpp::Any visitExprNot(BUPParser::ExprNotContext *ctx) override {
        ValueRef result = visit(ctx->expr_base()); // TODO safe cast?
        if (ctx->op) {
            if (result->isBoolean()) {
                result = BoolValue::Create(!result->getRealValue());
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                    {
                        st->parsedFiles.front()->getPath(),
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine()
                    },
                    ctx->getText(),
                    VisitorsUtils::getTypeName(SymbolTable::tInt),
                    VisitorsUtils::getTypeName(SymbolTable::tBool)
                );
            }
        }
        return result;
    }

    antlrcpp::Any visitExpr_base(BUPParser::Expr_baseContext *ctx) override {
        if (ctx->expr()) {
            return visit(ctx->expr());
        } else if (ctx->varAccess()) {
            SymbolRef value = visit(ctx->varAccess());
            if (value->isAssignable()) {
                return Utils::as<AssignableSymbol>(value)->getValue();
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                    {
                        st->parsedFiles.front()->getPath(),
                        ctx->getStart()->getLine(),
                        ctx->getStart()->getCharPositionInLine()
                    },
                    ctx->getText(),
                    VisitorsUtils::getTypeName(value->getType()->getTypeIndex()),
                    VisitorsUtils::getTypeName(SymbolTable::tInt)
                );
            }
        }
        return BUPBaseVisitor::visitExpr_base(ctx);
    }


    antlrcpp::Any visitVarAccessObjectOrArray(BUPParser::VarAccessObjectOrArrayContext *ctx) override {
        if (ctx->attr) {
            return this->currentScope->resolve(ctx->attr->getText());
        } else if (ctx->index) {
            ScopeRef prev = this->currentScope;
            this->currentScope = this->currentLocalScope;
            ValueRef index = visit(ctx->index);
            this->currentScope = prev;
            return this->currentScope->resolve(std::to_string(index->getRealValue()));
        }
        return nullptr;
    }


    antlrcpp::Any visitVarAccess(BUPParser::VarAccessContext *ctx) override {
        std::string a = ctx->TK_IDENT()->getText();
        std::string b = ctx->getText();
        SymbolRef var = this->currentScope->resolve(ctx->TK_IDENT()->getText());

        if (var == nullptr) {
            throw CSP2SATNotExistsException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine()
                },
                ctx->getText()
            );
        }

        if (!ctx->varAccessObjectOrArray().empty()) {
            for (int i = 0; i < ctx->varAccessObjectOrArray().size(); i++) {
                auto nestedScope = ctx->varAccessObjectOrArray(i);
                std::string nest = nestedScope->getText();
                if (var != nullptr && var->isScoped()) {
                    this->currentLocalScope = this->currentScope;
                    if (!nestedScope->underscore) {
                        this->currentScope = Utils::as<ScopedSymbol>(var);
                        var = visit(nestedScope);
                    } else {
                        ScopedSymbolRef result = Utils::as<ScopedSymbol>(var);
                        for (int j = i + 1; j < ctx->varAccessObjectOrArray().size(); j++) {
                            if (ctx->varAccessObjectOrArray(j)->underscore) {
                                throw CSP2SATInvalidExpressionTypeException(
                                    {
                                        st->parsedFiles.front()->getPath(),
                                        ctx->start->getLine(),
                                        ctx->start->getCharPositionInLine()
                                    },
                                    ctx->getText(),
                                    "matrix",
                                    "list"
                                );
                            }
                            ArraySymbolRef aux = ArraySymbol::Create(
                                    "aux",
                                    result,
                                    Utils::as<ArraySymbol>(result)->getElementsType()
                            );
                            for (auto currDimElem : Utils::as<ScopedSymbol>(result)->getScopeSymbols()) {
                                if (currDimElem.second->getType()->getTypeIndex() == SymbolTable::tArray) {
                                    this->currentScope = Utils::as<ScopedSymbol>(currDimElem.second);
                                    SymbolRef currDimSymElem = visit(ctx->varAccessObjectOrArray(j));
                                    aux->add(currDimSymElem);
                                } else {
                                    throw CSP2SATBadAccessException(
                                        {
                                            st->parsedFiles.front()->getPath(),
                                            ctx->start->getLine(),
                                            ctx->start->getCharPositionInLine()
                                        },
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
                        {
                            st->parsedFiles.front()->getPath(),
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine()
                        },
                        ctx->getText()
                    );
                }
            }
        }

        if (var == nullptr || (!this->accessingNotLeafVariable && var->isScoped())) {
            throw CSP2SATBadAccessException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine()
                },
                ctx->getText()
            );
        }
        return var;
    }


    antlrcpp::Any visitValueBaseType(BUPParser::ValueBaseTypeContext *ctx) override {
        ValueRef result;
        if (ctx->integer) {
            result = IntValue::Create(stoi(ctx->integer->getText()));
        } else {
            result = BoolValue::Create(ctx->boolean->getText() == "true");
        }
        return result;
    }

    antlrcpp::Any visitRangList(BUPParser::RangListContext *ctx) override {
        ValueRef minRange = visit(ctx->min);
        ValueRef maxRange = visit(ctx->max);

        int minValue = minRange->getRealValue();
        int maxValue = maxRange->getRealValue();

        if (minValue <= maxValue) {
            ArraySymbolRef result = ArraySymbol::Create(
                    "auxRangList",
                    this->currentScope,
                    SymbolTable::_integer
            );
            for (int i = 0; i <= (maxValue - minValue); i++) {
                AssignableSymbolRef newValue = AssignableSymbol::Create(std::to_string(i), SymbolTable::_integer);
                newValue->setValue(IntValue::Create(minValue + i));
                result->add(newValue);
            }
            return result;
        } else {
            throw GOSException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                },
                "Range must be ascendant"
            );
        }
    }

    antlrcpp::Any visitAuxiliarListAssignation(BUPParser::AuxiliarListAssignationContext *ctx) override {
        ArraySymbolRef arrayDefined = visit(ctx->list());
        return std::pair<std::string, ArraySymbolRef>(ctx->TK_IDENT()->getText(), arrayDefined);
    }



    antlrcpp::Any visitComprehensionList(BUPParser::ComprehensionListContext *ctx) override {
        LocalScopeRef listLocalScope = LocalScope::Create(this->currentScope);
        std::vector<std::map<std::string, SymbolRef>> possibleAssignations = getAllCombinations(ctx->auxiliarListAssignation());
        ArraySymbolRef newList = nullptr;

        this->currentScope = listLocalScope;
        for (const auto &assignation: possibleAssignations) {
            for (const auto &auxVarAssign : assignation)
                listLocalScope->assign(auxVarAssign.first, auxVarAssign.second);

            bool condition = true;
            if (ctx->condExpr) {
                ValueRef cond = visit(ctx->condExpr);
                if (!cond->isBoolean()) {
                    throw CSP2SATInvalidExpressionTypeException(
                        {
                            st->parsedFiles.front()->getPath(),
                            ctx->condExpr->start->getLine(),
                            ctx->condExpr->start->getCharPositionInLine()
                        },
                        ctx->condExpr->getText(),
                        VisitorsUtils::getTypeName(SymbolTable::tInt),
                        VisitorsUtils::getTypeName(SymbolTable::tBool)
                    );
                }
                condition = cond->getRealValue() == 1;
            }

            SymbolRef exprRes;

            if (ctx->listResultExpr()->varAcc) {
                this->accessingNotLeafVariable = true;
                exprRes = visit(ctx->listResultExpr());
                this->accessingNotLeafVariable = false;
            }
            else if (ctx->listResultExpr()->resExpr) {
                ValueRef val = visit(ctx->listResultExpr()->resExpr);
                AssignableSymbolRef valueResult = AssignableSymbol::Create(
                        std::to_string(rand()),
                        val->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer
                );
                valueResult->setValue(val);
                exprRes = valueResult;
            }
            else if (ctx->listResultExpr()->string()){
                std::string currStr = visit(ctx->listResultExpr()->string());
                exprRes = StringSymbol::Create(currStr);
            }
            else {
                formulaReturnRef formula = visit(ctx->listResultExpr()->constraint_expression());
                exprRes = formula;
            }

            if (newList == nullptr)
                newList = ArraySymbol::Create(
                        "comprehensionListAux",
                        listLocalScope,
                        exprRes->getType()
                );

            if(condition)
                newList->add(exprRes);
        }
        this->currentScope = listLocalScope->getEnclosingScope();
        return newList;
    }

    antlrcpp::Any visitVarAccessList(BUPParser::VarAccessListContext *ctx) override {
        SymbolRef array = nullptr;
        this->accessingNotLeafVariable = true;
        array = visit(ctx->varAccess());
        this->accessingNotLeafVariable = false;

        if (array && array->getType() && array->getType()->getTypeIndex() == SymbolTable::tArray) {
            return Utils::as<ArraySymbol>(array);
        } else {
            throw CSP2SATInvalidExpressionTypeException(
                {
                    st->parsedFiles.front()->getPath(),
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine()
                },
                ctx->getText(),
                VisitorsUtils::getTypeName(array->getType()->getTypeIndex()),
                "array"
            );
        }
    }

    antlrcpp::Any visitExplicitList(BUPParser::ExplicitListContext *ctx) override {
        ArraySymbolRef resultList = nullptr;

        for (auto currVal : ctx->listResultExpr()) {
            SymbolRef curr = nullptr;
            if (currVal->varAcc) {
                curr = visit(currVal);
            } else if (currVal->resExpr) {
                ValueRef exprVal = visit(currVal->resExpr);
                curr = AssignableSymbol::Create(std::to_string(rand()),
                                            exprVal->isBoolean() ? SymbolTable::_boolean : SymbolTable::_integer);
                Utils::as<AssignableSymbol>(curr)->setValue(exprVal);
            } else if (currVal->string()) {
                std::string currStr = visit(currVal->string());
                curr = StringSymbol::Create(currStr);
            } else {
                formulaReturnRef a =  visit(currVal->constraint_expression());
                curr = a;
            }

            if (resultList == nullptr) {
                resultList = ArraySymbol::Create(
                        std::to_string(rand()),
                        this->currentScope,
                        curr->getType()
                );
            }

            if (curr->getType()->getTypeIndex() == resultList->getElementsType()->getTypeIndex()) {
                resultList->add(curr);
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                    {
                        st->parsedFiles.front()->getPath(),
                        currVal->start->getLine(),
                        currVal->start->getCharPositionInLine()
                    },
                    currVal->getText(),
                    VisitorsUtils::getTypeName(curr->getType()->getTypeIndex()),
                    VisitorsUtils::getTypeName(resultList->getElementsType()->getTypeIndex())
                );
            }
        }
        return resultList;
    }

protected:
    std::vector<std::map<std::string, SymbolRef>> 
    getAllCombinations(std::vector<GOS::BUPParser::AuxiliarListAssignationContext *> aux)
    {
        std::vector<std::map<std::string, SymbolRef>> combinations = std::vector<std::map<std::string, SymbolRef>>();
        LocalScopeRef combScope = LocalScope::Create(this->currentScope);
        getAllCombinations(0, aux, combinations, combScope);
        return combinations;
    }

    void 
    getAllCombinations(
        int idx, 
        std::vector<GOS::BUPParser::AuxiliarListAssignationContext *> aux, 
        std::vector<std::map<std::string, SymbolRef>> & combinations, 
        LocalScopeRef combinationsScope)
    {
        if (idx == aux.size()) {
            combinations.push_back(combinationsScope->getScopeSymbols());
            return;
        }
        this->currentScope = combinationsScope;
        std::pair<std::string, ArraySymbolRef> currArr = visit(aux[idx]);
        for (int i = 0; i < currArr.second->getSize(); i++) {
            combinationsScope->define(currArr.first, currArr.second->resolve(std::to_string(i)));
            getAllCombinations(idx + 1, aux, combinations, combinationsScope);
        }
        this->currentScope = combinationsScope->getEnclosingScope();
    }
};

}

#endif //CSP2SAT_GOSCUSTOMBASEVISITOR_H
