//
// Created by Roger Generoso Masós on 24/04/2020.
//

#ifndef CSP2SAT_CSP2SATOUTPUTVISITOR_H
#define CSP2SAT_CSP2SATOUTPUTVISITOR_H


#include "../CSP2SATCustomBaseVisitor.h"

class CSP2SATOutputVisitor : public CSP2SATCustomBaseVisitor {

public:
    CSP2SATOutputVisitor(SymbolTable *symbolTable, SMTFormula *f) : CSP2SATCustomBaseVisitor(symbolTable, f) {}

    antlrcpp::Any visitCsp2sat(CSP2SATParser::Csp2satContext *ctx) override {
        if(ctx->outputBlock()){
            CSP2SATBaseVisitor::visitCsp2sat(ctx);
            return true;
        }
        return false;
    }


    antlrcpp::Any visitEntityDefinitionBlock(CSP2SATParser::EntityDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitViewpointBlock(CSP2SATParser::ViewpointBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitConstraintDefinitionBlock(CSP2SATParser::ConstraintDefinitionBlockContext *ctx) override {
        return nullptr;
    }

    antlrcpp::Any visitOutputBlock(CSP2SATParser::OutputBlockContext *ctx) override {
        for(auto str : ctx->string()) {
            try{
                string out = visit(str);
                cout << out << endl;
            }
            catch (CSP2SATException & e) {
                cerr << e.getErrorMessage() << endl;
                return nullptr;
            }
        }
        return nullptr;
    }

    antlrcpp::Any visitString(CSP2SATParser::StringContext *ctx) override {
        string result = "";
        if(ctx->TK_STRING()){
            string iniText = ctx->TK_STRING()->getText();
            iniText.erase(std::remove(iniText.begin(),iniText.end(),'\"'),iniText.end());
            result = Helpers::toRawString(iniText);

        }
        else if(ctx->stringTernary()){
            string ternaryResult = visit(ctx->stringTernary());
            result = ternaryResult;
        }
        else if(ctx->list()){
            ArraySymbol * str = visit(ctx->list());
            if(str->getElementsType()->getTypeIndex() == SymbolTable::tString){
                for(auto currStr : str->getSymbolVector())
                    result += currStr->getName();
            }
            else {
                throw CSP2SATStringOnlyOutputException(
                    ctx->list()->start->getLine(),
                    ctx->list()->start->getCharPositionInLine(),
                    ctx->list()->getText()
                );
            }
        }
        else if(ctx->concatString()){
            string lString = visit(ctx->string());
            string rString = visit(ctx->concatString()->string());
            result = lString + rString;

            auto currentConcat = ctx->concatString()->concatString();
            while(currentConcat){
                string current = visit(currentConcat->string());
                result += current;
                currentConcat = currentConcat->concatString();
            }
        }
        else if(ctx->expr()){
            Value * val = visit(ctx->expr());
            result = to_string(val->getRealValue());
        }
        else if(ctx->varAccess()){
            accessingNotLeafVariable = true;
            Symbol * var = visit(ctx->varAccess());
            accessingNotLeafVariable = false;
            if(!var->isScoped()){
                if(var->isAssignable())
                    result = to_string(((AssignableSymbol*)var)->getValue()->getRealValue());
                else
                    result = ((VariableSymbol*)var)->getModelValue() ? "true" : "false";
            }
            else {
                ArraySymbol * arrayAccess = (ArraySymbol*)var;
                result += "[";
                for(auto elem : arrayAccess->getSymbolVector()){
                    if(elem->isAssignable())
                        result += to_string(((AssignableSymbol*)elem)->getValue()->getRealValue());
                    else
                        result += ((VariableSymbol*)elem)->getModelValue() ? "true" : "false";

                    if(elem != arrayAccess->getSymbolVector().back())
                        result += ", ";
                }
                result += "]";
            }

        }
        else if(ctx->TK_LPAREN()){
            string innerParen = visit(ctx->string());
            result = innerParen;
        }
        return (string) result;
    }

    antlrcpp::Any visitStringTernary(CSP2SATParser::StringTernaryContext *ctx) override {
        Value * cond = visit(ctx->condition);

        if(cond->getRealValue())
            return visit(ctx->op1);
        else
            return visit(ctx->op2);
    }

    antlrcpp::Any visitExpr_base(CSP2SATParser::Expr_baseContext *ctx) override {
        if (ctx->expr()) {
            return visit(ctx->expr());
        } else if (ctx->varAccess()) {
            Symbol *value = visit(ctx->varAccess());
            if (value->isAssignable()) {
                return (Value *) ((AssignableSymbol *) value)->getValue();
            } else {
                bool a = ((VariableSymbol*) value)->getModelValue();
                Value * modelValue = new BoolValue(a);
                return (Value *) modelValue;
            }
        }
        return CSP2SATBaseVisitor::visitExpr_base(ctx);
    }
};



#endif //CSP2SAT_CSP2SATOUTPUTVISITOR_H
