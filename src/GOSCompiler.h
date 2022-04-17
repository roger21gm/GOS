//
// Created by Roger Generoso Masós on 20/04/2020.
//

#ifndef CSP2SAT_CSP2SATCOMPILER_H
#define CSP2SAT_CSP2SATCOMPILER_H

// antlr4 runtime
#include "antlr4-runtime.h"

// generated lexer and parser
#include <BUPLexer.h>
#include <BUPParser.h>
#include <JSONLexer.h>
#include <JSONParser.h>

#include <controllers/solvingarguments.h>

#include <utility>
#include <controllers/basiccontroller.h>
#include "Symtab/SymbolTable.h"

// custom listener
#include "Visitors/GOSTypeVarDefinitionVisitor.h"
#include "Visitors/GOSConstraintsVisitor.h"

// custom error
#include "Errors/GOSErrorListener.h"
#include "GOSEncoding.h"
#include "Visitors/Input/GOSJSONInputVisitor.h"
#include "Visitors/Output/GOSOutputVisitor.h"

// std
#include <string>
#include <vector>

using namespace antlr4; // TODO correct?
using std::string; // TODO correct?
using std::vector;

namespace GOS {

class GOSCompiler {
private:
    bool synError = false;
public:
    GOSCompiler(string inStr, string modelStr, SolvingArguments *sargs) : inStr(std::move(inStr)), modelStr(std::move(modelStr)), sargs(sargs) {
        symbolTable = new SymbolTable();
        _f = new SMTFormula();
    }

    auto runVisitor(BUPBaseVisitor * visitor, string inStr, bool showSintaxErrors = true){
        ANTLRInputStream input(inStr);
        BUPLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        BUPParser parser(&tokens);
        if(!showSintaxErrors)
            parser.removeErrorListeners();
        BUPParser::Csp2satContext *tree = parser.csp2sat();
        if(parser.getNumberOfSyntaxErrors() > 0)
            synError = true;
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

        GOSJSONInputVisitor * inputPreJsonVisitor = new GOSJSONInputVisitor();
        ParamJSON * readParams = runInputVisitor(inputPreJsonVisitor, inStr);

        GOSTypeVarDefinitionVisitor * visitor = new GOSTypeVarDefinitionVisitor(symbolTable, _f, readParams);
        runVisitor(visitor, modelStr);

        if(!symbolTable->errors){
            GOSConstraintsVisitor * constraintsVisitor = new GOSConstraintsVisitor(symbolTable, _f);
            runVisitor(constraintsVisitor, modelStr, false);

            if(!synError){
                if(!symbolTable->errors){
                    GOSEncoding * encoding = new GOSEncoding(_f, symbolTable);
                    BasicController c(sargs, encoding,false, 0, 0);
                    c.run();

                    if(encoding->isSat()){
                        CSP2SATOutputVisitor * outputVisitor = new CSP2SATOutputVisitor(symbolTable, _f);
                        bool customOutput = runVisitor(outputVisitor, modelStr, false);
                        if(!customOutput)
                            encoding->printModelSolution(cout);
                    }
                }
                else {
                    cerr << endl <<  "Execution stopped due to errors in constraint definition" << endl;
                }
            }
            else{
                cerr << "Execution stopped" << endl;
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

}

#endif //CSP2SAT_CSP2SATCOMPILER_H
