//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"
#include "smtformula.h"


struct clausesReturn {
    clausesReturn(){}
    void addClause (clause claus) {
        clauses.push_back(claus);
    }
    vector<clause> clauses;
};

class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}

    antlrcpp::Any visitConstraint(CSP2SATParser::ConstraintContext *ctx) override {
        if (ctx->cLit) {
            Symbol *val = visit(ctx->cLit);
            if(!val->isAssignable()){
                cout << "added unitary constraint " << ctx->getText() << " -> " << ((VariableSymbol *) val)->getVar().v.id << endl;
                VariableSymbol * currVar = (VariableSymbol *) val;
                clause newClause = currVar->getVar();
                SymbolTable::_f->addClause(newClause);
            }
            else {
                cerr << "Unitary clause " << ctx->getText() << " must be a variable" << endl;
                throw;
            }
        }
        else if (ctx->constraint_aggreggate_op()) {
            visit(ctx->constraint_aggreggate_op());
        }
        else {
            clausesReturn * clauses = CSP2SATBaseVisitor::visitConstraint(ctx);
            for(clause clause : clauses->clauses){
                SymbolTable::_f->addClause(clause);
            }
        }
        return nullptr;
    }

    antlrcpp::Any visitCAndExpression(CSP2SATParser::CAndExpressionContext *ctx) override {
        clausesReturn * newClauses = new clausesReturn();

        for (int i = 0; i < ctx->constraint_literal().size(); i++) {
            Symbol *currValue = visit(ctx->constraint_literal(i));
            VariableSymbol *currLiteral = (VariableSymbol *) currValue;
            newClauses->addClause(currLiteral->getVar());
        }
        cout << "added AND list constraint " << ctx->getText() << endl;

        return newClauses;
    }

    antlrcpp::Any visitCAndList(CSP2SATParser::CAndListContext *ctx) override {
        ArraySymbol *list = visit(ctx->list());
        clausesReturn * newClauses = new clausesReturn();

        if (list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool) {
            map<string, Symbol *> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                newClauses->addClause(((VariableSymbol *) it->second)->getVar());
                it++;
            }
        } else {
            cerr << "Constraint OR list elements must be literals" << endl;
            throw;
        }

        return newClauses;
    }



    antlrcpp::Any visitCOrExpression(CSP2SATParser::COrExpressionContext *ctx) override {
        Symbol *firstValue = visit(ctx->constraint_literal(0));
        VariableSymbol *firstLiteral = (VariableSymbol *) firstValue;
        clause orClause =  firstLiteral->getVar();

        for (int i = 1; i < ctx->constraint_literal().size(); i++) {
            Symbol *currValue = visit(ctx->constraint_literal(i));
            VariableSymbol *currLiteral = (VariableSymbol *) currValue;
            orClause |= currLiteral->getVar();
        }
        cout << "added or list constraint " << ctx->getText() << endl;

        clausesReturn * newClauses = new clausesReturn();
        newClauses->addClause(orClause);

        return newClauses;
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
        } else {
            cerr << "Constraint OR list elements must be literals" << endl;
            throw;
        }

        clausesReturn * newClauses = new clausesReturn();
        newClauses->addClause(orClause);

        return newClauses;
    }



    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override {
        Symbol *valSym = visit(ctx->varAccess());
        if (!valSym->isAssignable()) {
            VariableSymbol *var = (VariableSymbol*) valSym;
            if (ctx->TK_CONSTRAINT_NOT())
                valSym = (Symbol*) new VariableSymbol("!" + var->name, !(var->getVar()));
        }
        return valSym;
    }

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

    antlrcpp::Any visitForall(CSP2SATParser::ForallContext *ctx) override {
        auto *forallLocalScope = new LocalScope(this->currentScope);

        map<string, ArraySymbol *> ranges;
        this->currentScope = forallLocalScope;
        for (int i = 0; i < ctx->auxiliarListAssignation().size(); i++) {
            pair<string, ArraySymbol *> currAuxVar = visit(ctx->auxiliarListAssignation(i));
            ranges.insert(currAuxVar);
        }

        vector<map<string, Symbol *>> possibleAssignations = Utils::getAllCombinations(ranges);
        for (const auto &assignation: possibleAssignations) {
            for (const auto &auxVarAssign : assignation)
                forallLocalScope->assign(auxVarAssign.first, auxVarAssign.second);
            visit(ctx->localConstraintDefinitionBlock());
        }
        this->currentScope = forallLocalScope->getEnclosingScope();
        return nullptr;
    }

    antlrcpp::Any visitIfThenElse(CSP2SATParser::IfThenElseContext *ctx) override {
        for (int i = 0; i < ctx->expr().size(); ++i) {
            Value * condVal = visit(ctx->expr(i));
            if(condVal->isBoolean()){
                if(condVal->getRealValue() == 1){
                    visit(ctx->localConstraintDefinitionBlock(i));
                    return nullptr;
                }
            }
            else{
                cerr << "Conditions of conditionals must be boolean expressions" << endl;
                throw;
            }
        }
        if(ctx->TK_ELSE())
            visit(ctx->localConstraintDefinitionBlock().back());
        return nullptr;
    }



};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
