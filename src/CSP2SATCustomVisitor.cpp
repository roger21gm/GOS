
#include <support/Any.h>
#include "CSP2SATCustomVisitor.h"
#include "Symtab/Symbol/VariableSymbol.h"
#include "Symtab/Symbol/ConstantSymbol.h"
#include "Symtab/Symbol/StructSymbol.h"
#include <typeinfo>
#include <string>

using namespace std;


antlrcpp::Any CSP2SATCustomVisitor::visitExpr(CSP2SATParser::ExprContext *ctx) {
    if (ctx->TK_INTERROGANT()) {
        return 0;
    } else {
        return visit(ctx->expr_6());
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_6(CSP2SATParser::Expr_6Context *ctx) {
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

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_5(CSP2SATParser::Expr_5Context *ctx) {
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

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_4(CSP2SATParser::Expr_4Context *ctx) {
    if (ctx->op) {
        if (ctx->TK_OP_ARIT_SUM(0))
            return visit(ctx->expr_3(0)).as<int>() + visit(ctx->expr_3(1)).as<int>();
        else
            return visit(ctx->expr_3(0)).as<int>() - visit(ctx->expr_3(1)).as<int>();
    } else {
        return visit(ctx->expr_3(0));
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_3(CSP2SATParser::Expr_3Context *ctx) {
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

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_2(CSP2SATParser::Expr_2Context *ctx) {
    if (ctx->op) {
        return 0;
    } else {
        return visit(ctx->expr_base());
    }
}

antlrcpp::Any CSP2SATCustomVisitor::visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) {
    if (ctx->valueBaseType()) {
        if (ctx->valueBaseType()->TK_BOOLEAN_VALUE())
            return ctx->valueBaseType()->TK_BOOLEAN_VALUE()->getText() == "true";
        else
            return stoi(ctx->valueBaseType()->TK_INT_VALUE()->getText());
    } else if (ctx->TK_LPAREN())
        return visit(ctx->expr());
    else if (ctx->TK_IDENT())
        //TODO return value && type?
        return currentScope->resolve(ctx->TK_IDENT()->getText());
    else {

    }
    return ctx->getText();
}

antlrcpp::Any CSP2SATCustomVisitor::visitVarDefinition(CSP2SATParser::VarDefinitionContext *ctx) {
    VariableSymbol *newVar;
    newVar = new VariableSymbol(
            ctx->name->getText(),
            (Type *) (currentScope->resolve(ctx->type->getText()))
    );
    cout << "var  " << newVar->getName() << "  " <<  currentScope->resolve(ctx->type->getText())->getName() << endl;
    currentScope->define(newVar);
    return CSP2SATBaseVisitor::visitVarDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitConstDefinition(CSP2SATParser::ConstDefinitionContext *ctx) {

    Type *type = (Type*)currentScope->resolve(ctx->type->getText());

    ConstantSymbol *newConst;
    if(type->getTypeIndex() == SymbolTable::tInt || type->getTypeIndex() == SymbolTable::tBool){
        newConst = new ConstantSymbol(
                ctx->name->getText(),
                (BuiltInTypeSymbol*)currentScope->resolve(ctx->type->getText())
        );
    }
    else{
        newConst = new ConstantSymbol(
                ctx->name->getText(),
                (StructSymbol*)currentScope->resolve(ctx->type->getText())
        );
    }


    currentScope->define(newConst);
    if(currentScope->getScopeName() == st.gloabls->getScopeName()){
        cout << "1. const  " << newConst->getName() << "  " <<  currentScope->resolve(ctx->type->getText())->getName() << endl;
        cout << "2. " << newConst->type->getName() << endl;

    }

    return CSP2SATBaseVisitor::visitConstDefinition(ctx);
}

antlrcpp::Any CSP2SATCustomVisitor::visitTypeDefinition(CSP2SATParser::TypeDefinitionContext *ctx) {
    StructSymbol *newType;
    newType = new StructSymbol(ctx->name->getText(), currentScope);
    currentScope->define(newType);

    currentScope = newType;
    CSP2SATBaseVisitor::visitTypeDefinition(ctx);
    currentScope = currentScope->getEnclosingScope();

    return nullptr;
}

antlrcpp::Any CSP2SATCustomVisitor::visitCsp2sat(CSP2SATParser::Csp2satContext *ctx) {
    CSP2SATBaseVisitor::visitCsp2sat(ctx);
    return nullptr;
}

