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
        if(ctx->cLit){
            ValueSymbol * val = visit(ctx->cLit);
            SymbolTable::_f->addClause(((VariableSymbol*) val)->getVar());
        }
        else {
            CSP2SATBaseVisitor::visitConstraint(ctx);
        }
        return nullptr;
    }

    antlrcpp::Any visitCOrExpression(CSP2SATParser::COrExpressionContext *ctx) override {
        ValueSymbol * firstValue = visit(ctx->constraint_literal(0));
        VariableSymbol * firstLiteral = (VariableSymbol*) firstValue;
        clause orClause = firstLiteral->getVar();

        for(int i=1; i < ctx->constraint_literal().size(); i++){
            ValueSymbol * currValue = visit(ctx->constraint_literal(i));
            VariableSymbol * currLiteral = (VariableSymbol*) currValue;
            orClause |= currLiteral->getVar();
        }
        SymbolTable::_f->addClause(orClause);
        return nullptr;
    }

    antlrcpp::Any visitCOrList(CSP2SATParser::COrListContext *ctx) override {
        ArraySymbol * list = visit(ctx->list());
        clause orClause;

        if(list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool){
            map<string, Symbol *> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                orClause |= ((VariableSymbol *) it->second)->getVar();
                it++;
            }
            SymbolTable::_f->addClause(orClause);
        }
        else {
            cerr << "Constraint OR list elements must be literals" << endl;
            throw;
        }



        return nullptr;
    }

    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override {
        ValueSymbol * valSym = visit(ctx->varAccess());
        if(!valSym->isAssignable()){
            VariableSymbol * var = (VariableSymbol*) valSym;
            if(ctx->TK_CONSTRAINT_NOT())
                return (ValueSymbol*) new VariableSymbol("!" + var->name, !(var->getVar()));
            return valSym;
        }
        else {
            cerr << ctx->getText() << ": constraints only can be variables" << endl;
            throw;
        }

    }


    antlrcpp::Any visitRangeForall(CSP2SATParser::RangeForallContext *ctx) override {
        auto *forallLocalScope = new LocalScope(this->currentScope);

        map<string, pair<int, int>> ranges;
        this->currentScope = forallLocalScope;
        for (int i = 0; i < ctx->range().size(); i++) {
            this->currentScope->define(new AssignableSymbol(ctx->range(i)->TK_IDENT()->getText(), SymbolTable::_integer));
            pair<string, pair<int, int>> currRange = visit(ctx->range(i));
            ranges.insert(currRange);
        }

        vector<map<string, int>> possibleAssignations = Utils::getAllRangeCombinations(ranges);
        for(map<string,int> currAssignation : possibleAssignations) {
            auto itCurrAssignation = currAssignation.begin();
            while (itCurrAssignation != currAssignation.end()) {
                IntValue *currAss = new IntValue(itCurrAssignation->second);
                ((AssignableSymbol *) this->currentScope->resolve(itCurrAssignation->first))->setValue(currAss);
                itCurrAssignation++;
            }
            CSP2SATBaseVisitor::visitRangeForall(ctx);
        }
        this->currentScope = forallLocalScope->getEnclosingScope();
        return nullptr;
    }


};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
