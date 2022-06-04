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
#include <iostream>
#include <string>

namespace GOS {

class GOSCompiler {
private:
    bool synError = false;
public:
    GOSCompiler(std::string inStr, std::string modelStr, SolvingArguments *sargs) : inStr(std::move(inStr)), modelStr(std::move(modelStr)), sargs(sargs) {
        symbolTable = new SymbolTable();
        _f = new SMTFormula();
    }

    auto runVisitor(BUPBaseVisitor& visitor, std::string inStr, bool showSintaxErrors = true){
        antlr4::ANTLRInputStream input(inStr);
        BUPLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        BUPParser parser(&tokens);
        if(!showSintaxErrors)
            parser.removeErrorListeners();
        BUPParser::Csp2satContext *tree = parser.csp2sat();
        if(parser.getNumberOfSyntaxErrors() > 0)
            synError = true;
        return visitor.visit(tree);
    }

    ParamJSONRef runInputVisitor(JSONBaseVisitor& visitor, std::string inStr){
        antlr4::ANTLRInputStream input2(inStr);
        JSONLexer lexer2(&input2);
        antlr4::CommonTokenStream tokens2(&lexer2);
        JSONParser parser2(&tokens2);
        JSONParser::JsonContext *tree2 = parser2.json();
        return visitor.visit(tree2);
    }

    void run(){
        GOSJSONInputVisitor inputPreJsonVisitor;
        ParamJSONRef readParams = runInputVisitor(inputPreJsonVisitor, inStr);

        GOSTypeVarDefinitionVisitor visitor(symbolTable, _f, readParams);
        runVisitor(visitor, modelStr);

        if(!symbolTable->errors){
            GOSConstraintsVisitor constraintsVisitor(symbolTable, _f);
            runVisitor(constraintsVisitor, modelStr, false);

            if(!synError){
                if(!symbolTable->errors){
                    GOSEncoding encoding(_f, symbolTable);
                    BasicController c(sargs, &encoding, false, 0, 0);
                    c.run();

                    if(encoding.isSat()){
                        CSP2SATOutputVisitor outputVisitor(symbolTable, _f);
                        bool customOutput = runVisitor(outputVisitor, modelStr, false);
                        if(!customOutput)
                            encoding.printModelSolution(std::cout);
                    }
                }
                else {
                    std::cerr << std::endl <<  "Execution stopped due to errors in constraint definition" << std::endl;
                }
            }
            else{
                std::cerr << "Execution stopped" << std::endl;
            }
        }
        else {
            std::cerr << "Execution stopped due to errors in input" << std::endl;
        }
    }

private:
    SMTFormula *_f;
    std::string inStr;
    std::string modelStr;
    SymbolTable *symbolTable;
    SolvingArguments *sargs;

};

}

#endif //CSP2SAT_CSP2SATCOMPILER_H
