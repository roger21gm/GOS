#include <iostream>
#include <string>

// antlr4 runtime
#include "antlr4-runtime.h"
#include "CSP2SATMainListener.h"

// generated lexer and parser
#include <CSP2SATLexer.h>
#include <CSP2SATParser.h>

// custom listener

using namespace std;
using namespace antlr4;
using namespace CSP2SAT;
using namespace tree;

void execute_expression(const std::string &expr) {
    ANTLRInputStream input(expr);
    CSP2SATLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSP2SATParser parser(&tokens);

    tree::ParseTree *tree = parser.init();
    CSP2SATMainListener listener;

    ParseTreeWalker *walker = new ParseTreeWalker();
    walker->walk(&listener, tree);
}

int main() {
    std::string prefix = ">>> ";

    // parse and interpet the expression readen from the standard input
    std::cout << prefix;
    std::string line;
    while( std::getline(std::cin,line) ) {
        execute_expression(line);
        std::cout << prefix;
    }

    return 0;
}