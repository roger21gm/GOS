//
// Created by Roger Generoso Masós on 01/04/2020.
//

#ifndef CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
#define CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H


#include "CSP2SATCustomBaseVisitor.h"

class CSP2SATConstraintsVisitor : public CSP2SATCustomBaseVisitor {

public:
    explicit CSP2SATConstraintsVisitor(SymbolTable *symbolTable) : CSP2SATCustomBaseVisitor(symbolTable) {}

    antlrcpp::Any visitList(CSP2SATParser::ListContext *ctx) override {
        int resultListSize = 1;

        map<string, vector<int>> namedRanges;
        map<string, int> indices;
        LocalScope * listLocalScope = new LocalScope(this->currentScope);

        auto * newScope = new LocalScope(this->currentScope);
        for (int i = 0; i < ctx->TK_IDENT().size() ; i++) {
            listLocalScope->define(new ConstantSymbol(ctx->TK_IDENT(i)->getText(), (Type*)SymbolTable::_integer));

            Value * minRange = visit(ctx->range(i)->min);
            Value * maxRange = visit(ctx->range(i)->max);
            int rangeDiff = maxRange->getRealValue() - minRange->getRealValue() + 1;
            resultListSize *= rangeDiff;

            vector<int> currRange;
            int currNum = minRange->getRealValue();
            for(int j=minRange->getRealValue(); j <= maxRange->getRealValue(); j++){
                currRange.push_back(currNum++);
            }

            namedRanges[ctx->TK_IDENT(i)->getText()] = currRange;
            indices[ctx->TK_IDENT(i)->getText()] = 0;
        }

        ArraySymbol * newList = Utils::createArrayParam("unique", this->currentScope, vector<int>{resultListSize}, SymbolTable::_integer);
        int index = 0;

        this->currentScope = listLocalScope;
        while(true) {
            auto itCustomAssignation = indices.begin();
            while(itCustomAssignation != indices.end()){
                IntValue * currAss = new IntValue(namedRanges[itCustomAssignation->first][indices[itCustomAssignation->first]]);
                ((AssignableSymbol*)listLocalScope->resolve(itCustomAssignation->first))->setValue(currAss);
                itCustomAssignation++;
            }

            if(ctx->condExpr){
                Value * condition = visit(ctx->condExpr);
                if(condition->getRealValue()){
                    Value * exprVal = visit(ctx->resExpr);
                    ((AssignableSymbol*)newList->resolve(to_string(index)))->setValue(exprVal);
                    index++;
                }
            }
            else {
                Value * exprVal = visit(ctx->resExpr);
                ((AssignableSymbol*)newList->resolve(to_string(index)))->setValue(exprVal);
                index++;
            }

            auto indicesRev = indices.rbegin();
            while(indicesRev != indices.rend() && indicesRev->second + 1 >= namedRanges[indicesRev->first].size()){
                indicesRev++;
            }

            if(indicesRev == indices.rend()){
                newList->setSize(index);
                break;
            }


            indices[indicesRev->first] += 1;

            auto indiceForward = indices.begin();
            while(indiceForward->first != indicesRev->first)
                indiceForward++;

            indiceForward++;

            while(indiceForward != indices.end()) {
                indices[indiceForward->first] = 0;
                indiceForward++;
            }
        }
        this->currentScope = listLocalScope->getEnclosingScope();


        map<string, Symbol*> a = newList->getScopeSymbols();
        auto it = a.begin();

        while(it != a.end()){
            cout << ((AssignableSymbol*)it->second)->getValue()->getRealValue() << endl;
            it++;
        }
        return 0;
    }


};


#endif //CSP2SAT_CSP2SATCONSTRAINTSVISITOR_H
