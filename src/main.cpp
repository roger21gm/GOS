#include <string>
#include "api/controllers/solvingarguments.h"
#include "GOSCompiler.h"

using namespace std;
using namespace GOS;

string readFile(string name) {
    ifstream inFile;
    inFile.open(name); //open the input file
    stringstream inputStream;
    inputStream << inFile.rdbuf(); //read the file
    string inputStr = inputStream.str(); //str holds the content of the file
    return inputStr;
}


enum ProgramArg {
    SHOWFORMULA
};

int main(int argc, char **argv) {

    Arguments<ProgramArg> *pargs = new Arguments<ProgramArg>(
            {
                    arguments::arg("modelfile", "Instance file path."),
                    arguments::arg("datafile", "Input params file path."),
            },
            2,
            {
                    arguments::bop("pf", "print-formula", SHOWFORMULA, false, "Print CNF formula"),
            },
            "Solve CSP to SAT"
    );


    SolvingArguments *sargs = SolvingArguments::readArguments(argc, argv, pargs);

    bool showFormula = pargs->getBoolOption(SHOWFORMULA);

    SolvingArg solver = sargs->getOptionRef("-s");
    sargs->setOption(solver, (string) "minisat");

    SolvingArg optimize = sargs->getOptionRef("-o");
    sargs->setOption(optimize, (string) "check");

    if (showFormula) {
        SolvingArg print = sargs->getOptionRef("-e");
        sargs->setOption(print, true);
        SolvingArg format = sargs->getOptionRef("-f");
        sargs->setOption(format, (string) "dimacs");
    }

    string inputStr = readFile(pargs->getArgument(1));
    string modelStr = readFile(pargs->getArgument(0));

    GOSCompiler *compiler = new GOSCompiler(inputStr, modelStr, sargs);
    compiler->run();

    delete pargs, sargs, compiler;

    return 0;
}