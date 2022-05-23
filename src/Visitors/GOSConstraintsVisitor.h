//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_GOSCONSTRAINTSVISITOR_H
#define CSP2SAT_GOSCONSTRAINTSVISITOR_H

#include "../Symtab/Symbol/formulaReturn.h"
#include "../Symtab/Symbol/Valued/VariableSymbol.h"
#include "../Symtab/Symbol/Scoped/ArraySymbol.h"
#include "../GOSUtils.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

namespace GOS {

class GOSConstraintsVisitor : public GOSCustomBaseVisitor {
public:
    explicit GOSConstraintsVisitor(SymbolTable *symbolTable, SMTFormula *f) : GOSCustomBaseVisitor(symbolTable,
                                                                                                   f) {}


    antlrcpp::Any visitEntityDefinitionBlock(BUPParser::EntityDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitViewpointBlock(BUPParser::ViewpointBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitOutputBlock(BUPParser::OutputBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitConstraintDefinitionBlock(BUPParser::ConstraintDefinitionBlockContext *ctx) override {
        for (auto constraint : ctx->constraintDefinition()) {
            try {
                visit(constraint);
            }
            catch (GOSException &e) {
                std::cerr << e.getErrorMessage() << std::endl;
            }
        }
        return nullptr;
    }

    antlrcpp::Any
    visitLocalConstraintDefinitionBlock(BUPParser::LocalConstraintDefinitionBlockContext *ctx) override {
        try {
            for (auto constraint : ctx->constraintDefinition()) {
                visit(constraint);
            }
        }
        catch (GOSException &e) {
            throw e;
        }
        return nullptr;
    }


    antlrcpp::Any visitConstraintDefinition(BUPParser::ConstraintDefinitionContext *ctx) override {

        try {
            BUPBaseVisitor::visitConstraintDefinition(ctx);
        }
        catch (GOSException &e) {
            throw e;
        }
        return nullptr;
    }


    antlrcpp::Any visitConstraint(BUPParser::ConstraintContext *ctx) override {
        if (ctx->constraint_expression()) {
            formulaReturnRef result = visit(ctx->constraint_expression());
            for (clause clause : result->clauses)
                this->_f->addClause(clause);
        } else visit(ctx->constraint_aggreggate_op());
        return nullptr;

    }

    antlrcpp::Any visitConstraint_base(BUPParser::Constraint_baseContext *ctx) override {
        formulaReturnRef clause = formulaReturn::Create();
        if (ctx->varAccess()) {
            SymbolRef valSym = visit(ctx->varAccess());
            if (valSym != nullptr && valSym->getType() != nullptr && valSym->getType()->getTypeIndex() == SymbolTable::tVarBool) {
                clause->addClause(Utils::as<VariableSymbol>(valSym)->getVar());
            } else {
                throw CSP2SATParamAsConstraintException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText()
                );
            }
        } else if (ctx->TK_BOOLEAN_VALUE()) {
            if (ctx->TK_BOOLEAN_VALUE()->getText() == "true")
                clause->addClause(this->_f->trueVar());
            else
                clause->addClause(this->_f->falseVar());
        } else {
            formulaReturnRef innerParenClauses = visit(ctx->constraint_expression());
            clause->addClauses(innerParenClauses->clauses);
        }
        return clause;
    }

    antlrcpp::Any visitConstraint_literal(BUPParser::Constraint_literalContext *ctx) override {
        formulaReturnRef clauses = visit(ctx->constraint_base());
        if (ctx->TK_CONSTRAINT_NOT()) {
            formulaReturnRef result = formulaReturn::Create();

            if (clauses->clauses.size() == 1) {
                for (auto literal : clauses->clauses.front().v) {
                    result->addClause(!literal);
                }
            } else {
                clause clauResult;
                for (clause currClause : clauses->clauses) {
                    if (currClause.v.size() == 1)
                        clauResult |= !currClause.v.front();
                    else {
                        throw CSP2SATInvalidFormulaException(
                                ctx->start->getLine(),
                                ctx->start->getCharPositionInLine(),
                                ctx->getText(),
                                "You can only negate literals or AND lists"
                        );
                    }
                }
                result->addClause(clauResult);
            }
            clauses = result;
        }
        return clauses;
    }

    antlrcpp::Any visitCAndExpression(BUPParser::CAndExpressionContext *ctx) override {
        formulaReturnRef newClauses = formulaReturn::Create();
        for (int i = 0; i < ctx->constraint_and_2().size(); i++) {
            formulaReturnRef currClauses = visit(ctx->constraint_and_2(i));
            newClauses->addClauses(currClauses->clauses);
        }
        return newClauses;
    }

    antlrcpp::Any visitCAndList(BUPParser::CAndListContext *ctx) override {
        ArraySymbolRef list = visit(ctx->list());
        formulaReturnRef newClauses = formulaReturn::Create();
        std::string a = ctx->getText();
        if (list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool
            || list->getElementsType()->getTypeIndex() == SymbolTable::tFormula) {
            std::map<std::string, SymbolRef> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                if (it->second->getType()->getTypeIndex() == SymbolTable::tVarBool)
                    newClauses->addClause(Utils::as<VariableSymbol>(it->second)->getVar());
                else {
                    newClauses->addClauses(Utils::as<formulaReturn>(it->second)->clauses);
                }
                it++;
            }
        } else {
            throw CSP2SATInvalidFormulaException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    "Invalid Constraint AND"
            );
        }
        return newClauses;
    }


    antlrcpp::Any visitCOrExpression(BUPParser::COrExpressionContext *ctx) override {
        formulaReturnRef result = visit(ctx->constraint_or_2(0));


        if (ctx->constraint_or_2().size() > 1) {
            std::vector<formulaReturnRef> andClauses;
            formulaReturnRef newClauses = formulaReturn::Create();
            clause orClause;
            for (int i = 0; i < ctx->constraint_or_2().size(); i++) {
                formulaReturnRef currClauses = visit(ctx->constraint_or_2(i));
                if (currClauses->clauses.size() == 1)
                    orClause |= currClauses->clauses.front();
                else
                    andClauses.push_back(currClauses);
            }

            if (andClauses.size() == 0)
                newClauses->addClause(orClause);
            else if (andClauses.size() == 1) {
                for (auto andClause : andClauses.front()->clauses) {
                    if (andClause.v.size() == 1)
                        newClauses->addClause(orClause | andClause);
                    else {
                        throw CSP2SATInvalidFormulaException(
                                ctx->start->getLine(),
                                ctx->start->getCharPositionInLine(),
                                ctx->getText(),
                                "AND_CLAUSULES | AND_LITERALS not allowed"
                        );
                    }
                }
            } else {
                throw CSP2SATInvalidFormulaException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText(),
                        "AND_CLAUSULES | AND_LITERALS not allowed"
                );
            }


            result = newClauses;
        }

        return result;
    }

    antlrcpp::Any visitCOrList(BUPParser::COrListContext *ctx) override {
        ArraySymbolRef list = visit(ctx->list());
        clause orClause;
        if (list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool
            || list->getElementsType()->getTypeIndex() == SymbolTable::tFormula
                ) {
            std::map<std::string, SymbolRef> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                if (it->second->getType()->getTypeIndex() == SymbolTable::tVarBool)
                    orClause |= Utils::as<VariableSymbol>(it->second)->getVar();
                else {
                    for (auto clause : Utils::as<formulaReturn>(it->second)->clauses) {
                        orClause |= clause;
                    }
                }
                it++;
            }
        } else {
            throw CSP2SATInvalidFormulaException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    "Constraint OR list elements must be propositional formulas"
            );
        }

        formulaReturnRef newClauses = formulaReturn::Create();
        newClauses->addClause(orClause);

        return newClauses;
    }


    antlrcpp::Any visitConstraint_implication(BUPParser::Constraint_implicationContext *ctx) override {
        formulaReturnRef result = visit(ctx->constraint_or(0));

        if (ctx->constraint_or().size() > 1) {
            formulaReturnRef leftExpr = result;

            for (int i = 1; i < ctx->constraint_or().size(); ++i) {
                formulaReturnRef rightExpr = visit(ctx->constraint_or(i));
                if (ctx->implication_operator(i - 1)->getText() == "<-") {
                    formulaReturnRef aux = rightExpr;
                    rightExpr = leftExpr;
                    leftExpr = aux;
                }
                clause result;
                if (rightExpr->clauses.size() == 1) {
                    result = rightExpr->clauses.front();
                    for (clause currLeft : leftExpr->clauses) {
                        if (currLeft.v.size() == 1) {
                            result |= !currLeft.v.front();
                        } else {
                            throw CSP2SATInvalidFormulaException(
                                    ctx->start->getLine(),
                                    ctx->start->getCharPositionInLine(),
                                    ctx->getText(),
                                    "Only allowed AND_LITERALS => OR_LITERALS"
                            );
                        }
                    }
                    leftExpr = formulaReturn::Create(result);
                } else if (leftExpr->clauses.size() == 1 && leftExpr->clauses.front().v.size() == 1) {
                    formulaReturnRef res = formulaReturn::Create();
                    for (auto andLiteral : rightExpr->clauses) {
                        if (andLiteral.v.size() == 1) {
                            res->addClause(andLiteral | !leftExpr->clauses.front().v.front());
                        } else
                            throw CSP2SATInvalidFormulaException(
                                    ctx->start->getLine(),
                                    ctx->start->getCharPositionInLine(),
                                    ctx->getText(),
                                    "Only allowed AND_LITERALS => OR_LITERALS"
                            );
                    }
                    leftExpr = res;
                } else {
                    throw CSP2SATInvalidFormulaException(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText(),
                            "Only allowed AND_LITERALS => OR_LITERALS"
                    );
                }
            }
            result = leftExpr;
        }
        return result;
    }

    antlrcpp::Any
    visitConstraint_double_implication(BUPParser::Constraint_double_implicationContext *ctx) override {
        formulaReturnRef res = visit(ctx->constraint_implication(0));

        if (ctx->constraint_implication().size() == 2) {
            formulaReturnRef lExp = res;
            formulaReturnRef rExp = visit(ctx->constraint_implication(1));


            if (!(lExp->clauses.size() == 1 && lExp->clauses.front().v.size() == 1)) {
                formulaReturnRef aux = rExp;
                rExp = lExp;
                lExp = aux;
            }

            if (lExp->clauses.size() == 1 && lExp->clauses.front().v.size() == 1) {
                literal lLit = lExp->clauses.front().v.front();
                formulaReturnRef result = formulaReturn::Create();

                if (rExp->clauses.size() == 1) { // OR left side
                    for (auto currLit : rExp->clauses.front().v) {
                        clause newClause = !currLit | lLit;
                        result->addClause(newClause);
                    }
                    result->addClause(!lLit | rExp->clauses.front());
                } else { // AND left side
                    clause aux = lLit;
                    for (auto unitClause : rExp->clauses) {
                        clause newClause = !lLit | unitClause.v.front();
                        aux |= !unitClause.v.front();
                        result->addClause(newClause);
                    }
                    result->addClause(aux);
                }

                res = result;
            } else {
                throw CSP2SATInvalidFormulaException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText(),
                        "Only allowed LITERAL <=> OR_LITERALS and LITERAL <=> AND_LITERALS"
                );
            }
        } else if (ctx->constraint_implication().size() != 1) {
            throw CSP2SATInvalidFormulaException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    "Only allowed LITERAL <=> OR_LITERALS and LITERAL <=> AND_LITERALS"
            );
        }

        return res;
    }

    antlrcpp::Any visitForall(BUPParser::ForallContext *ctx) override {
        LocalScopeRef forallLocalScope = LocalScope::Create(this->currentScope);
        std::vector<std::map<std::string, SymbolRef>> possibleAssignations = getAllCombinations(ctx->auxiliarListAssignation());

        this->currentScope = forallLocalScope;
        for (const auto &assignation: possibleAssignations) {
            for (const auto &auxVarAssign : assignation)
                forallLocalScope->assign(auxVarAssign.first, auxVarAssign.second);
            visit(ctx->localConstraintDefinitionBlock());
        }

        this->currentScope = forallLocalScope->getEnclosingScope();

        return nullptr;
    }

    antlrcpp::Any visitIfThenElse(BUPParser::IfThenElseContext *ctx) override {
        for (int i = 0; i < ctx->expr().size(); ++i) {
            ValueRef condVal = visit(ctx->expr(i));
            if (condVal->isBoolean()) {
                if (condVal->getRealValue() == 1) {
                    visit(ctx->localConstraintDefinitionBlock(i));
                    return nullptr;
                }
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->expr(i)->start->getLine(),
                        ctx->expr(i)->start->getCharPositionInLine(),
                        ctx->expr(i)->getText(),
                        VisitorsUtils::getTypeName(SymbolTable::tInt),
                        VisitorsUtils::getTypeName(SymbolTable::tBool)
                );
            }
        }
        if (ctx->TK_ELSE())
            visit(ctx->localConstraintDefinitionBlock().back());
        return nullptr;
    }

    antlrcpp::Any visitConstraint_aggreggate_op(BUPParser::Constraint_aggreggate_opContext *ctx) override {
        ValueRef k = nullptr;
        if (ctx->param) {
            k = visit(ctx->param);
        }
        ArraySymbolRef list = visit(ctx->list());

        try {
            std::vector<literal> literalList = VisitorsUtils::getLiteralVectorFromVariableArraySymbol(list);
            if (k != nullptr) {
                if (ctx->aggregate_op()->getText() == "EK") {
                    this->_f->addEK(literalList, k->getRealValue());
                } else if (ctx->aggregate_op()->getText() == "ALK") {
                    this->_f->addALK(literalList, k->getRealValue());
                } else if (ctx->aggregate_op()->getText() == "AMK") {
                    this->_f->addAMK(literalList, k->getRealValue());
                } else {
                    throw CSP2SATBadCardinalityConstraint(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText()
                    );
                }
            } else {
                if (ctx->aggregate_op()->getText() == "EO") {
                    this->_f->addEO(literalList);
                } else if (ctx->aggregate_op()->getText() == "ALO") {
                    this->_f->addALO(literalList);
                } else if (ctx->aggregate_op()->getText() == "AMO") {
                    this->_f->addAMO(literalList);
                } else {
                    throw CSP2SATBadCardinalityConstraint(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText()
                    );
                }
            }

            return nullptr;
        }
        catch (GOSException &e) {
            throw GOSException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->list()->getText() + " must be a list of literals"
            );
        }
    }
};

}

#endif //CSP2SAT_GOSCONSTRAINTSVISITOR_H
