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

using namespace antlr4;
using namespace CSP2SAT;
using namespace std;

class CSP2SATCompiler {
public:
    CSP2SATCompiler(string inStr, string modelStr, SolvingArguments *sargs) : inStr(std::move(inStr)), modelStr(std::move(modelStr)), sargs(sargs) {
        symbolTable = new SymbolTable();
        _f = new SMTFormula();
    }

    void run(){
        ANTLRInputStream input(modelStr);
        CSP2SATLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        CSP2SATParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(new CSP2SATErrorListener());
        CSP2SATParser::Csp2satContext *tree = parser.csp2sat();
        CSP2SATTypeVarDefinitionVisitor * visitor = new CSP2SATTypeVarDefinitionVisitor(symbolTable, _f);
        visitor->visit(tree);

        ANTLRInputStream input2(inStr);
        JSONLexer lexer2(&input2);
        CommonTokenStream tokens2(&lexer2);
        JSONParser parser2(&tokens2);
        JSONParser::JsonContext *tree2 = parser2.json();
        CSP2SATInputJSONVisitor * visitor2 = new CSP2SATInputJSONVisitor(symbolTable);
        visitor2->visit(tree2);


        ANTLRInputStream input3(modelStr);
        CSP2SATLexer lexer3(&input3);
        CommonTokenStream tokens3(&lexer3);
        CSP2SATParser parser3(&tokens3);
        CSP2SATParser::Csp2satContext *tree3 = parser3.csp2sat();
        CSP2SATConstraintsVisitor * visitor3 = new CSP2SATConstraintsVisitor(symbolTable, _f);
        visitor3->visit(tree3);

        CSP2SATEncoding * encoding = new CSP2SATEncoding(_f,symbolTable);
        BasicController c(sargs, encoding,false, 0, 0);
        c.run();
    }



    SMTFormula *_f;
private:
    string inStr;
    string modelStr;
    SymbolTable *symbolTable;
    SolvingArguments *sargs;
};


#endif //CSP2SAT_CSP2SATCOMPILER_H
