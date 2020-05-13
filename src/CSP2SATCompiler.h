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
#include "Visitors/CSP2SATConstraintsVisitor.h"

// custom error
#include "Errors/CSP2SATErrorListener.h"
#include "CSP2SATEncoding.h"
#include "Visitors/Input/CSP2SATJSONInputVisitor.h"
#include "Visitors/Output/CSP2SATOutputVisitor.h"

using namespace antlr4;
using namespace CSP2SAT;
using namespace std;

class CSP2SATCompiler {
public:
    CSP2SATCompiler(string inStr, string modelStr, SolvingArguments *sargs) : inStr(std::move(inStr)), modelStr(std::move(modelStr)), sargs(sargs) {
        symbolTable = new SymbolTable();
        _f = new SMTFormula();
    }

    auto runVisitor(CSP2SATBaseVisitor * visitor, string inStr){
        ANTLRInputStream input(inStr);
        CSP2SATLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        CSP2SATParser parser(&tokens);
        CSP2SATParser::Csp2satContext *tree = parser.csp2sat();
        return visitor->visit(tree);
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

        CSP2SATJSONInputVisitor * inputPreJsonVisitor = new CSP2SATJSONInputVisitor();
        ParamJSON * readParams = runInputVisitor(inputPreJsonVisitor, inStr);

        CSP2SATTypeVarDefinitionVisitor * visitor = new CSP2SATTypeVarDefinitionVisitor(symbolTable, _f, readParams);
        runVisitor(visitor, modelStr);

        if(!symbolTable->errors){
            CSP2SATConstraintsVisitor * constraintsVisitor = new CSP2SATConstraintsVisitor(symbolTable, _f);
            runVisitor(constraintsVisitor, modelStr);

            if(!symbolTable->errors){
                CSP2SATEncoding * encoding = new CSP2SATEncoding(_f,symbolTable);
                BasicController c(sargs, encoding,false, 0, 0);
                c.run();

                if(encoding->isSat()){
                    CSP2SATOutputVisitor * outputVisitor = new CSP2SATOutputVisitor(symbolTable, _f);
                    bool customOutput = runVisitor(outputVisitor, modelStr);
                    if(!customOutput)
                        encoding->printModelSolution(cout);
                }
            }
            else {
                cerr << endl <<  "Execution stopped due to errors in constraint definition" << endl;
            }
        }
        else {
            cerr << "Execution stopped due to errors in input" << endl;
        }
    }

private:
    SMTFormula *_f;
    string inStr;
    string modelStr;
    SymbolTable *symbolTable;
    SolvingArguments *sargs;

};


#endif //CSP2SAT_CSP2SATCOMPILER_H
