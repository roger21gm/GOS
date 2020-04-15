#include <iostream>
#include <string>

// antlr4 runtime
#include "antlr4-runtime.h"

// generated lexer and parser
#include <CSP2SATLexer.h>
#include <CSP2SATParser.h>
#include <JSONLexer.h>


// custom listener
#include "Visitors/CSP2SATTypeVarDefinitionVisitor.h"
#include "Visitors/Input/CSP2SATInputJSONVisitor.h"
#include "Visitors/CSP2SATConstraintsVisitor.h"

// custom error
#include "Errors/CSP2SATErrorListener.h"

using namespace std;
using namespace antlr4;
using namespace CSP2SAT;
using namespace tree;


void showAllDefinedVariables(Scope * currentScope, const string& prefix = ""){
    map<string, Symbol*> currentScopeSymbols = currentScope->getScopeSymbols();

    for(pair<string, Symbol *> sym : currentScopeSymbols){
        if(sym.second->type){
            if(sym.second->type->getTypeIndex() == SymbolTable::tCustom || sym.second->type->getTypeIndex() == SymbolTable::tArray)
                if(!isdigit(sym.first[0]))
                    showAllDefinedVariables( (ScopedSymbol*) sym.second, prefix + "." + sym.first );
                else
                    showAllDefinedVariables( (ScopedSymbol*) sym.second, isdigit(sym.first[0]) ? prefix + "[" + sym.first + "]" : prefix + sym.first);
            else{
                string output = sym.second->type->getTypeIndex() != SymbolTable::tVarBool ?  "param -> " : "var -> ";
                if(!prefix.empty() && prefix[0] == '.')
                    output += prefix.substr(1, prefix.length()-1);
                else
                    output += prefix;

                if(isdigit(sym.first[0])){
                    output += "[" + sym.first + "]";
                }
                else {
                    output += "." + sym.first ;
                }

                if(sym.second->type->getTypeIndex() != SymbolTable::tVarBool){
                    Value * val = ((AssignableSymbol*)sym.second)->getValue();
                    cout << output  << " -> " << (val ? to_string(val->getRealValue()) : "_") << endl;
                }
                else {
                    cout << output  << endl;
                }

            }
        }
        else {
            cout << "defined type -> " << prefix +  sym.first << endl;
        }
    }
}

int main() {

    SymbolTable * symbolTable = new SymbolTable();

    ifstream inFile;
    inFile.open("../input/i4_1.json"); //open the input file
    stringstream inputStream;
    inputStream << inFile.rdbuf(); //read the file
    string inputStr = inputStream.str(); //str holds the content of the file


    ifstream modelFile;
    modelFile.open("../input/test4_1.sat"); //open the input file
    stringstream modelStream;
    modelStream << modelFile.rdbuf(); //read the file
    string modelStr = modelStream.str(); //str holds the content of the file

    ANTLRInputStream input(modelStr);
    CSP2SATLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CSP2SATParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(new CSP2SATErrorListener());
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


    ANTLRInputStream input3(modelStr);
    CSP2SATLexer lexer3(&input3);
    CommonTokenStream tokens3(&lexer3);
    CSP2SATParser parser3(&tokens3);
    CSP2SATParser::Csp2satContext *tree3 = parser3.csp2sat();
    CSP2SATConstraintsVisitor * visitor3 = new CSP2SATConstraintsVisitor(symbolTable);
    visitor3->visit(tree3);

    SMTFormula * a = SymbolTable::_f;


    //showAllDefinedVariables(symbolTable->gloabls);

    cout << a->getNBoolVars() << endl;

    return 0;
}