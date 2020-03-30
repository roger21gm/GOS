#include <iostream>
#include <string>

// antlr4 runtime
#include "antlr4-runtime.h"
#include "CSP2SATTypeVarDefinitionVisitor.h"

// generated lexer and parser
#include <CSP2SATLexer.h>
#include <CSP2SATParser.h>


// custom listener


using namespace std;
using namespace antlr4;
using namespace CSP2SAT;
using namespace tree;

int main() {

    SymbolTable * symbolTable = new SymbolTable();


    ANTLRInputStream input(
            ""
            "types:"
            "     Queens {"
            "         const int n1;"
            "     };"
            "vars:"
            "    const Queens nQueens;"
            "constraints:"
            "    nQueens.n1;"
    );

    CSP2SATLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSP2SATParser parser(&tokens);

    CSP2SATParser::Csp2satContext *tree = parser.csp2sat();

    CSP2SATTypeVarDefinitionVisitor * visitor = new CSP2SATTypeVarDefinitionVisitor(symbolTable);
    visitor->visit(tree);

    return 0;
}