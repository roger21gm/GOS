#include <iostream>
#include <string>

// antlr4 runtime
#include "antlr4-runtime.h"
#include "Visitors/CSP2SATTypeVarDefinitionVisitor.h"
#include "Visitors/Input/CSP2SATInputJSONVisitor.h"

// generated lexer and parser
#include <CSP2SATLexer.h>
#include <CSP2SATParser.h>
#include <JSONLexer.h>


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


    ANTLRInputStream input2(
            "{"
            "     \"nQueens\": {"
            "           \"n1\": 150"
            "      }"
            "}"
    );

    JSONLexer lexer2(&input2);
    CommonTokenStream tokens2(&lexer2);
    JSONParser parser2(&tokens2);
    JSONParser::JsonContext *tree2 = parser2.json();
    CSP2SATInputJSONVisitor * visitor2 = new CSP2SATInputJSONVisitor(symbolTable);
    visitor2->visit(tree2);

    return 0;
}