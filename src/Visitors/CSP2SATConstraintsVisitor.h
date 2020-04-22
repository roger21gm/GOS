//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


struct clausesReturn {
    clausesReturn() {}

    clausesReturn(clause claus) {
        clauses.push_back(claus);
    }

    void addClause(clause claus) {
        clauses.push_back(claus);
    }

    void addClauses(vector<clause> claus) {
        for (clause curr : claus)
            clauses.push_back(curr);
    }

    vector<clause> clauses;
};

class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {
private:
    bool inForall = false;

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable, SMTFormula *f) : CSP2SATCustomBaseVisitor(symbolTable,
                                                                                                           f) {}


    antlrcpp::Any visitConstraintDefinition(CSP2SATParser::ConstraintDefinitionContext *ctx) override {
        if(ctx->forall()){
            inForall = true;
            visit(ctx->forall());
            inForall = false;
        }
        else {
            try {
                CSP2SATBaseVisitor::visitConstraintDefinition(ctx);
            }
            catch (CSP2SATException & e) {
                if(inForall) throw;
                cerr << e.getErrorMessage() << endl;
            }
        }
        return nullptr;
    }


    antlrcpp::Any visitConstraint(CSP2SATParser::ConstraintContext *ctx) override {
        if (ctx->constraint_expression()) {
            clausesReturn *result = visit(ctx->constraint_expression());
            for (clause clause : result->clauses)
                this->_f->addClause(clause);
        } else visit(ctx->constraint_aggreggate_op());
        return nullptr;

    }

    antlrcpp::Any visitConstraint_base(CSP2SATParser::Constraint_baseContext *ctx) override {
        clausesReturn *clause = new clausesReturn();
        if (ctx->varAccess()) {
            Symbol *valSym = visit(ctx->varAccess());
            if (valSym != nullptr && valSym->type && valSym->type->getTypeIndex() == SymbolTable::tVarBool) {
                clause->addClause(((VariableSymbol *) valSym)->getVar());
            } else {
                throw CSP2SATInvalidExpressionTypeException(
                        ctx->start->getLine(),
                        ctx->start->getCharPositionInLine(),
                        ctx->getText(),
                        valSym != nullptr ? Utils::getTypeName(valSym->type->getTypeIndex()) : "undefined",
                        Utils::getTypeName(SymbolTable::tVarBool)
                );
            }
        } else if (ctx->TK_BOOLEAN_VALUE()) {
            if (ctx->TK_BOOLEAN_VALUE()->getText() == "true")
                clause->addClause(this->_f->trueVar());
            else
                clause->addClause(this->_f->falseVar());
        } else {
            clausesReturn *innerParenClauses = visit(ctx->constraint_expression());
            clause->addClauses(innerParenClauses->clauses);
        }
        return clause;
    }

    antlrcpp::Any visitConstraint_literal(CSP2SATParser::Constraint_literalContext *ctx) override {
        clausesReturn *clauses = visit(ctx->constraint_base());
        if (ctx->TK_CONSTRAINT_NOT()) {
            clause result;
            for (clause currClause : clauses->clauses) {
                if (currClause.v.size() == 1)
                    result |= !currClause.v.front();
                else {
                    throw CSP2SATInvalidFormulaException(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText(),
                            "You can only negate literals or AND lists"
                    );
                }
            }
            clauses = new clausesReturn(result);
        }
        return clauses;
    }

    antlrcpp::Any visitCAndExpression(CSP2SATParser::CAndExpressionContext *ctx) override {
        clausesReturn *newClauses = new clausesReturn();
        for (int i = 0; i < ctx->constraint_literal().size(); i++) {
            clausesReturn *currClauses = visit(ctx->constraint_literal(i));
            newClauses->addClauses(currClauses->clauses);
        }
        return newClauses;
    }

    antlrcpp::Any visitCAndList(CSP2SATParser::CAndListContext *ctx) override {
        ArraySymbol *list = visit(ctx->list());
        clausesReturn *newClauses = new clausesReturn();
        if (list->getElementsType()->getTypeIndex() == SymbolTable::tVarBool) {
            map<string, Symbol *> a = list->getScopeSymbols();
            auto it = a.begin();
            while (it != a.end()) {
                newClauses->addClause(((VariableSymbol *) it->second)->getVar());
                it++;
            }
        } else {
            throw CSP2SATInvalidFormulaException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    "Constraint AND list elements must be literals"
            );
        }
        return newClauses;
    }


    antlrcpp::Any visitCOrExpression(CSP2SATParser::COrExpressionContext *ctx) override {
        clausesReturn *result = visit(ctx->constraint_and(0));

        if (ctx->constraint_and().size() > 1) {
            clausesReturn *newClauses = new clausesReturn();
            clause orClause;
            for (int i = 0; i < ctx->constraint_and().size(); i++) {
                clausesReturn *currClauses = visit(ctx->constraint_and(i));
                for (clause curr : currClauses->clauses) {
                    orClause |= curr;
                }
            }
            newClauses->addClause(orClause);
            result = newClauses;
        }

        return result;
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
            throw CSP2SATInvalidFormulaException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->getText(),
                    "Constraint OR list elements must be literals"
            );
        }

        clausesReturn *newClauses = new clausesReturn();
        newClauses->addClause(orClause);

        return newClauses;
    }


    antlrcpp::Any visitConstraint_implication(CSP2SATParser::Constraint_implicationContext *ctx) override {
        clausesReturn *result = visit(ctx->constraint_or(0));

        if (ctx->constraint_or().size() > 1) {
            clausesReturn *leftExpr = result;

            for (int i = 1; i < ctx->constraint_or().size(); ++i) {
                clausesReturn *rightExpr = visit(ctx->constraint_or(i));
                if (ctx->implication_operator(i - 1)->getText() == "<-") {
                    clausesReturn *aux = rightExpr;
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
                } else {
                    throw CSP2SATInvalidFormulaException(
                            ctx->start->getLine(),
                            ctx->start->getCharPositionInLine(),
                            ctx->getText(),
                            "Only allowed AND_LITERALS => OR_LITERALS"
                    );
                }
                leftExpr = new clausesReturn(result);
            }
            result = leftExpr;
        }
        return result;
    }

    antlrcpp::Any
    visitConstraint_double_implication(CSP2SATParser::Constraint_double_implicationContext *ctx) override {
        clausesReturn *res = visit(ctx->constraint_implication(0));

        if (ctx->constraint_implication().size() == 2) {
            clausesReturn *lExp = res;
            clausesReturn *rExp = visit(ctx->constraint_implication(1));


            if (!(lExp->clauses.size() == 1 && lExp->clauses.front().v.size() == 1)) {
                clausesReturn *aux = rExp;
                rExp = lExp;
                lExp = aux;
            }

            if (lExp->clauses.size() == 1 && lExp->clauses.front().v.size() == 1) {

                literal lLit = lExp->clauses.front().v.front();

                clausesReturn *result = new clausesReturn();

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

            try {
                visit(ctx->localConstraintDefinitionBlock());
            }
            catch (CSP2SATException &e) {
                cerr << e.getErrorMessage() << endl;
                return nullptr;
            }
        }
        this->currentScope = forallLocalScope->getEnclosingScope();


        return nullptr;
    }

    antlrcpp::Any visitIfThenElse(CSP2SATParser::IfThenElseContext *ctx) override {
        for (int i = 0; i < ctx->expr().size(); ++i) {
            Value *condVal = visit(ctx->expr(i));
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
                        Utils::getTypeName(SymbolTable::tInt),
                        Utils::getTypeName(SymbolTable::tBool)
                );
            }
        }
        if (ctx->TK_ELSE())
            visit(ctx->localConstraintDefinitionBlock().back());
        return nullptr;
    }

    antlrcpp::Any visitConstraint_aggreggate_op(CSP2SATParser::Constraint_aggreggate_opContext *ctx) override {
        Value *k = visit(ctx->param);
        ArraySymbol *list = visit(ctx->list());

        try {
            vector<literal> literalList = Utils::getLiteralVectorFromVariableArraySymbol(list);
            if (ctx->aggregate_op()->getText() == "EK") {
                this->_f->addEK(literalList, k->getRealValue());
            } else if (ctx->aggregate_op()->getText() == "ALK") {
                this->_f->addALK(literalList, k->getRealValue());
            } else {
                this->_f->addAMK(literalList, k->getRealValue());
            }
            return nullptr;
        }
        catch (CSP2SATException &e) {
            throw CSP2SATInvalidExpressionTypeException(
                    ctx->start->getLine(),
                    ctx->start->getCharPositionInLine(),
                    ctx->list()->getText(),
                    "list<int>",
                    "list<literal>"
            );
        }


    }
};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
