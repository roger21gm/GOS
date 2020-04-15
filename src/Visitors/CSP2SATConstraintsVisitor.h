//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"
#include "smtformula.h"


class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}


    antlrcpp::Any visitConstraint(CSP2SATParser::ConstraintContext *ctx) override {
        if (ctx->cLit) {
            VariableSymbol *val = visit(ctx->cLit);
            SymbolTable::_f->addClause(((VariableSymbol *) val)->getVar());
        } else {
            CSP2SATBaseVisitor::visitConstraint(ctx);
        }
        return nullptr;
    }

    antlrcpp::Any visitCOrExpression(CSP2SATParser::COrExpressionContext *ctx) override {
        ValueSymbol *firstValue = visit(ctx->constraint_literal(0));
        VariableSymbol *firstLiteral = (VariableSymbol *) firstValue;
        clause orClause = firstLiteral->getVar();

        for (int i = 1; i < ctx->constraint_literal().size(); i++) {
            ValueSymbol *currValue = visit(ctx->constraint_literal(i));
            VariableSymbol *currLiteral = (VariableSymbol *) currValue;
            orClause |= currLiteral->getVar();
        }
        SymbolTable::_f->addClause(orClause);
        return nullptr;
    }

    antlrcpp::Any visitCOrList(CSP2SATParser::COrListContext *ctx) override {
        ArraySymbol *list = visit(ctx->list());
        clause orClause;

        if (list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool) {
            map<string, Symbol *> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                orClause |= ((VariableSymbol *) it->second)->getVar();
                it++;
            }
            SymbolTable::_f->addClause(orClause);
        } else {
            cerr << "Constraint OR list elements must be literals" << endl;
            throw;
        }


        return nullptr;
    }

    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override {
        Symbol *valSym = visit(ctx->varAccess());
        if (!valSym->isAssignable()) {
            VariableSymbol *var = (VariableSymbol*) valSym;
            if (ctx->TK_CONSTRAINT_NOT())
                valSym = new VariableSymbol("!" + var->name, !(var->getVar()));
        }
        return valSym;
    }

    antlrcpp::Any visitArrayForall(CSP2SATParser::ArrayForallContext *ctx) override {

        auto *forallLocalScope = new LocalScope(this->currentScope);
        this->currentScope = forallLocalScope;
        Symbol *array = (ArraySymbol *) visit(ctx->list());

        if (array && array->type && array->type->getTypeIndex() == SymbolTable::tArray) {
            ArraySymbol *arraySymbol = (ArraySymbol *) array;
            for (auto currAssignation : arraySymbol->getScopeSymbols()) {
                ((LocalScope *) this->currentScope)->assign(ctx->auxName->getText(), currAssignation.second);
                this->accessingNotLeafVariable = true;
                CSP2SATBaseVisitor::visitArrayForall(ctx);
                this->accessingNotLeafVariable = false;
            }
        } else {
            cerr << ctx->getText() << " is not an array" << endl;
            throw;
        }
        this->currentScope = forallLocalScope->getEnclosingScope();
        return nullptr;
    }


//    antlrcpp::Any visitRangeForall(CSP2SATParser::RangeForallContext *ctx) override {
//        auto *forallLocalScope = new LocalScope(this->currentScope);
//
//        map<string, pair<int, int>> ranges;
//        this->currentScope = forallLocalScope;
//        for (int i = 0; i < ctx->range().size(); i++) {
//            this->currentScope->define(
//                    new AssignableSymbol(ctx->range(i)->TK_IDENT()->getText(), SymbolTable::_integer));
//            pair<string, pair<int, int>> currRange = visit(ctx->range(i));
//            ranges.insert(currRange);
//        }
//
//        vector<map<string, int>> possibleAssignations = Utils::getAllRangeCombinations(ranges);
//        for (map<string, int> currAssignation : possibleAssignations) {
//            auto itCurrAssignation = currAssignation.begin();
//            while (itCurrAssignation != currAssignation.end()) {
//                IntValue *currAss = new IntValue(itCurrAssignation->second);
//                ((AssignableSymbol *) this->currentScope->resolve(itCurrAssignation->first))->setValue(currAss);
//                itCurrAssignation++;
//            }
//            CSP2SATBaseVisitor::visitRangeForall(ctx);
//        }
//        this->currentScope = forallLocalScope->getEnclosingScope();
//        return nullptr;
//    }

    antlrcpp::Any visitConstraint_aggreggate_op(CSP2SATParser::Constraint_aggreggate_opContext *ctx) override {
        ArraySymbol *variableArray = visit(ctx->list());
        if (variableArray->getElementsType()->getTypeIndex() == SymbolTable::tVarBool) {
            Value *param = visit(ctx->param);
            if (ctx->aggregate_op()->getText() == "EK")
                SymbolTable::_f->addEK(Utils::getLiteralVectorFromVariableArraySymbol(variableArray),
                                       param->getRealValue());

            else if (ctx->aggregate_op()->getText() == "ALK")
                SymbolTable::_f->addALK(Utils::getLiteralVectorFromVariableArraySymbol(variableArray),
                                        param->getRealValue());

            else if (ctx->aggregate_op()->getText() == "AMK")
                SymbolTable::_f->addAMK(Utils::getLiteralVectorFromVariableArraySymbol(variableArray),
                                        param->getRealValue());

        } else {
            cerr << "Aggregate opperator " << ctx->aggregate_op()->getText() << " only allow variable list" << endl;
            throw;
        }
        return nullptr;
    }


};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
