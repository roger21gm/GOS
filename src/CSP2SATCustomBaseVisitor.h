//
// Created by Roger Generoso Masós on 30/03/2020.
//

#ifndef CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
#define CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H

#include "Symtab/SymbolTable.h"
#include "CSP2SATBaseVisitor.h"

using namespace CSP2SAT;
using namespace std;

class CSP2SATCustomBaseVisitor: public CSP2SATBaseVisitor {

protected:
    SymbolTable st;
    Scope *currentScope = st.gloabls;


public:
    antlrcpp::Any visitExpr(CSP2SATParser::ExprContext *ctx) override {
        if (ctx->TK_INTERROGANT()) {
            return 0;
        } else {
            return visit(ctx->expr_6());
        }
    }

    antlrcpp::Any visitExpr_6(CSP2SATParser::Expr_6Context *ctx) override {
        if (ctx->op) {
            if (ctx->TK_OP_LOGIC_AND(0))
                return visit(ctx->expr_5(0)).as<bool>() && visit(ctx->expr_5(1)).as<bool>();
            else if (ctx->TK_OP_LOGIC_OR_PIPE(0))
                return visit(ctx->expr_5(0)).as<bool>() || visit(ctx->expr_5(1)).as<bool>();
        } else {
            return visit(ctx->expr_5(0));
        }
        return visitExpr_6(ctx);
    }

    antlrcpp::Any visitExpr_5(CSP2SATParser::Expr_5Context *ctx) override {
        if (ctx->op) {
            if (ctx->TK_OP_REL_LT(0))
                return visit(ctx->expr_4(0)).as<bool>() < visit(ctx->expr_4(1)).as<bool>();
            else if (ctx->TK_OP_REL_GT(0))
                return visit(ctx->expr_4(0)).as<bool>() > visit(ctx->expr_4(1)).as<bool>();
            else if (ctx->TK_OP_REL_GE(0))
                return visit(ctx->expr_4(0)).as<bool>() >= visit(ctx->expr_4(1)).as<bool>();
            else if (ctx->TK_OP_REL_LE(0))
                return visit(ctx->expr_4(0)).as<bool>() <= visit(ctx->expr_4(1)).as<bool>();
            else if (ctx->TK_OP_REL_EQ(0))
                return visit(ctx->expr_4(0)).as<bool>() == visit(ctx->expr_4(1)).as<bool>();
            else if (ctx->TK_OP_REL_NEQ(0))
                return visit(ctx->expr_4(0)).as<bool>() != visit(ctx->expr_4(1)).as<bool>();
        } else {
            return visit(ctx->expr_4(0));
        }
        return visitExpr_5(ctx);
    }

    antlrcpp::Any visitExpr_4(CSP2SATParser::Expr_4Context *ctx) override {
        if (ctx->op) {
            if (ctx->TK_OP_ARIT_SUM(0))
                return visit(ctx->expr_3(0)).as<int>() + visit(ctx->expr_3(1)).as<int>();
            else
                return visit(ctx->expr_3(0)).as<int>() - visit(ctx->expr_3(1)).as<int>();
        } else {
            return visit(ctx->expr_3(0));
        }
    }

    antlrcpp::Any visitExpr_3(CSP2SATParser::Expr_3Context *ctx) override {
        if (ctx->op) {
            if (ctx->TK_OP_ARIT_MULT(0))
                return visit(ctx->expr_2(0)).as<int>() * visit(ctx->expr_2(1)).as<int>();
            else if (ctx->TK_OP_ARIT_DIV(0))
                return visit(ctx->expr_2(0)).as<int>() / visit(ctx->expr_2(1)).as<int>();
            else
                return visit(ctx->expr_2(0)).as<int>() % visit(ctx->expr_2(1)).as<int>();
        } else {
            return visit(ctx->expr_2(0));
        }
    }

    antlrcpp::Any visitExpr_2(CSP2SATParser::Expr_2Context *ctx) override {
        if (ctx->op) {
            return 0;
        } else {
            return visit(ctx->expr_base());
        }
    }

    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override {
        if (ctx->valueBaseType()) {
            if (ctx->valueBaseType()->TK_BOOLEAN_VALUE())
                return ctx->valueBaseType()->TK_BOOLEAN_VALUE()->getText() == "true";
            else
                return stoi(ctx->valueBaseType()->TK_INT_VALUE()->getText());
        } else if (ctx->TK_LPAREN())
            return visit(ctx->expr());
        else if (ctx->varAccess())
            return visit(ctx->varAccess());
        else {

        }
        return ctx->getText();
    }

    antlrcpp::Any visitVarAccess(CSP2SATParser::VarAccessContext *ctx) override {
        Symbol * curr = currentScope->resolve(ctx->id->getText());
        switch (curr->type->getTypeIndex()){
            case SymbolTable::tCustom: {
                cout << "és struct" << endl;
                StructSymbol *ss = (StructSymbol *) curr->type;
                cout << ss->resolve(ctx->attr[0].getText())->getName() << endl;
                cout << ss->resolve(ctx->attr[0].getText())->type->getName() << endl;
                break;
            }
            case SymbolTable::tArray: {
                cout << "és array" << endl;
                break;
            }
            default: {
                cout << "és int or bool" << endl;
                break;
            }
        }
        return CSP2SATBaseVisitor::visitVarAccess(ctx);
    }
};


#endif //CSP2SAT_CSP2SATCUSTOMBASEVISITOR_H
