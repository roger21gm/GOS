//
// Created by Roger Generoso Masós on 11/03/2020.
//

#ifndef CSP2SAT_CSP2SATCUSTOMVISITOR_H
#define CSP2SAT_CSP2SATCUSTOMVISITOR_H

#include "CSP2SATBaseVisitor.h"
#include "Symtab/SymtbolTable.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATCustomVisitor: public CSP2SATBaseVisitor {

private:
    SymtbolTable st;
    Scope *currentScope = st.gloabls;

public:

    antlrcpp::Any visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) override;

    antlrcpp::Any visitConstDefinition(CSP2SATParser::ConstDefinitionContext *ctx) override;

    antlrcpp::Any visitExpr(CSP2SATParser::ExprContext *ctx) override;

    antlrcpp::Any visitExpr_6(CSP2SATParser::Expr_6Context *ctx) override;

    antlrcpp::Any visitExpr_5(CSP2SATParser::Expr_5Context *ctx) override;

    antlrcpp::Any visitExpr_4(CSP2SATParser::Expr_4Context *ctx) override;

    antlrcpp::Any visitExpr_3(CSP2SATParser::Expr_3Context *ctx) override;

    antlrcpp::Any visitExpr_2(CSP2SATParser::Expr_2Context *ctx) override;

    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override;

    antlrcpp::Any visitTypeDefinition(CSP2SATParser::TypeDefinitionContext *ctx) override;

    antlrcpp::Any visitCsp2sat(CSP2SATParser::Csp2satContext *ctx) override;


};


#endif //CSP2SAT_CSP2SATCUSTOMVISITOR_H
