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

    ifstream inFile;
    inFile.open("../input/i0.json"); //open the input file
    stringstream inputStream;
    inputStream << inFile.rdbuf(); //read the file
    string inputStr = inputStream.str(); //str holds the content of the file


    ifstream modelFile;
    modelFile.open("../input/test0.sat"); //open the input file
    stringstream modelStream;
    modelStream << modelFile.rdbuf(); //read the file
    string modelStr = modelStream.str(); //str holds the content of the file


    ANTLRInputStream input(modelStr);

    CSP2SATLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSP2SATParser parser(&tokens);
    CSP2SATParser::Csp2satContext *tree = parser.csp2sat();
    CSP2SATTypeVarDefinitionVisitor * visitor = new CSP2SATTypeVarDefinitionVisitor(symbolTable);
    visitor->visit(tree);


    ANTLRInputStream input2(inputStr);

    JSONLexer lexer2(&input2);
    CommonTokenStream tokens2(&lexer2);
    JSONParser parser2(&tokens2);
    JSONParser::JsonContext *tree2 = parser2.json();
    CSP2SATInputJSONVisitor * visitor2 = new CSP2SATInputJSONVisitor(symbolTable);
    visitor2->visit(tree2);


    StructSymbol * queens = (StructSymbol*)symbolTable->gloabls->resolve("nQueens");
    StructSymbol * queensQ = ((StructSymbol*) queens->resolve("queens"));
    AssignableSymbol * queensN1 = ((AssignableSymbol*) queensQ->resolve("n1"));
    AssignableSymbol * queensN2 = ((AssignableSymbol*) queensQ->resolve("n2"));


    cout << queensN1->getValue()->getRealValue() << endl;
    cout << queensN2->getValue()->getRealValue() << endl;


    return 0;
}