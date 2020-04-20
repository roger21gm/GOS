//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_CSP2SATCOMPILER_H
#define CSP2SAT_CSP2SATCOMPILER_H

// antlr4 runtime
#include "antlr4-runtime.h"

// generated lexer and parser
#include <CSP2SATLexer.h>
#include <CSP2SATParser.h>
#include <JSONLexer.h>
#include <JSONParser.h>

#include <controllers/solvingarguments.h>

#include <utility>
#include <controllers/basiccontroller.h>
#include "Symtab/SymbolTable.h"


// custom listener
#include "Visitors/CSP2SATTypeVarDefinitionVisitor.h"
#include "Visitors/Input/CSP2SATInputJSONVisitor.h"
#include "Visitors/CSP2SATConstraintsVisitor.h"

// custom error
#include "Errors/CSP2SATErrorListener.h"
#include "CSP2SATEncoding.h"
#include "Visitors/Input/CSP2SATInputPredeclaredParamsVisitor.h"

using namespace antlr4;
using namespace CSP2SAT;
using namespace std;

class CSP2SATCompiler {
public:
    CSP2SATCompiler(string inStr, string modelStr, SolvingArguments *sargs) : inStr(std::move(inStr)), modelStr(std::move(modelStr)), sargs(sargs) {
        symbolTable = new SymbolTable();
        _f = new SMTFormula();
    }

    void runVisitor(CSP2SATBaseVisitor * visitor, string inStr){
        ANTLRInputStream input(inStr);
        CSP2SATLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        CSP2SATParser parser(&tokens);
        CSP2SATParser::Csp2satContext *tree = parser.csp2sat();
        visitor->visit(tree);
    }

    auto runInputVisitor(JSONBaseVisitor * visitor, string inStr){
        ANTLRInputStream input2(inStr);
        JSONLexer lexer2(&input2);
        CommonTokenStream tokens2(&lexer2);
        JSONParser parser2(&tokens2);
        JSONParser::JsonContext *tree2 = parser2.json();
        return visitor->visit(tree2);
    }

    void run(){

        CSP2SATInputPredeclaredParamsVisitor * inputPreJsonVisitor = new CSP2SATInputPredeclaredParamsVisitor();
        ParamJSON * readParams = runInputVisitor(inputPreJsonVisitor, inStr);


        CSP2SATTypeVarDefinitionVisitor * visitor = new CSP2SATTypeVarDefinitionVisitor(symbolTable, _f, readParams);
        runVisitor(visitor, modelStr);
//
//        CSP2SATInputJSONVisitor * inputJsonVisitor = new CSP2SATInputJSONVisitor(symbolTable);
//        runInputVisitor(inputJsonVisitor, inStr);
//
//        CSP2SATConstraintsVisitor * constraintsVisitor = new CSP2SATConstraintsVisitor(symbolTable, _f);
//        runVisitor(constraintsVisitor, modelStr);
//
//        CSP2SATEncoding * encoding = new CSP2SATEncoding(_f,symbolTable);
//        BasicController c(sargs, encoding,false, 0, 0);
//        c.run();
    }



    SMTFormula *_f;
private:
    string inStr;
    string modelStr;
    SymbolTable *symbolTable;
    SolvingArguments *sargs;
};


#endif //CSP2SAT_CSP2SATCOMPILER_H
