#include <string>
#include <controllers/solvingarguments.h>
#include "CSP2SATCompiler.h"

using namespace std;

string readFile(string name){
    ifstream inFile;
    inFile.open(name); //open the input file
    stringstream inputStream;
    inputStream << inFile.rdbuf(); //read the file
    string inputStr = inputStream.str(); //str holds the content of the file
    return inputStr;
}


int main(int argc, char **argv) {

    Arguments<int> *pargs = new Arguments<int>(
            {
                    arguments::arg("modelfile", "Instance file path."),
                    arguments::arg("datafile", "Instance data file path."),
            },
            2, {}, "Solve CSP to SAT"
    );
    SolvingArguments * sargs = SolvingArguments::readArguments(argc,argv,pargs);

    string inputStr = readFile(pargs->getArgument(1));
    string modelStr = readFile(pargs->getArgument(0));

    CSP2SATCompiler * compiler = new CSP2SATCompiler(inputStr, modelStr, sargs);
    compiler->run();

    return 0;
}