//
// Created by Roger Generoso Masós on 24/04/2020.
//

#ifndef CSP2SAT_CSP2SATOUTPUTVISITOR_H
#define CSP2SAT_CSP2SATOUTPUTVISITOR_H


#include "../CSP2SATCustomBaseVisitor.h"

class CSP2SATOutputVisitor : public CSP2SATCustomBaseVisitor {

public:
    CSP2SATOutputVisitor(SymbolTable *symbolTable, SMTFormula *f) : CSP2SATCustomBaseVisitor(symbolTable, f) {}


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
        return CSP2SATBaseVisitor::visitOutputBlock(ctx);
    }


//    antlrcpp::Any visitOutputBlock(CSP2SATParser::OutputBlockContext *ctx) override {
//        if(ctx->string()){
//            string result = visit(ctx->string());
//            cout << result << endl;
//        }
//        return nullptr;
//    }

    antlrcpp::Any visitString(CSP2SATParser::StringContext *ctx) override {
        string str = ctx->TK_STRING()->getText();
        str.erase(std::remove(str.begin(),str.end(),'\"'),str.end());
        return str;
    }

    antlrcpp::Any visitString_agg(CSP2SATParser::String_aggContext *ctx) override {
        for(auto currStr : ctx->string()){
            string currentString = visit(currStr);
            cout << currentString;
        }
        cout << endl;
        return nullptr;
    }



};



#endif //CSP2SAT_CSP2SATOUTPUTVISITOR_H
