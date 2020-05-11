#ifndef SOLVINGARGUMENTS_DEFINITION
#define SOLVINGARGUMENTS_DEFINITION


#include <vector>
#include <set>
#include <string>
#include <map>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "../encoders/encoder.h"
#include "../encoders/fileencoder.h"
#include "encoding.h"
#include "../optimizers/optimizer.h"
#include "smtformula.h"
#include "arguments.h"
#include "util/util.h"

#define programversion "1.0"

using namespace smtapi;
using namespace util;
using namespace arguments;


enum SolvingArg {
	OUTPUT_ENCODING,
	FILE_FORMAT,
	PRODUCE_MODELS,
	SOLVER,
	OPTIMIZER,
	RANDOM_SEED,
	FILE_PREFIX,
	USE_API,
	USE_ASSUMPTIONS,
	NARROW_BOUNDS,
	USE_IDL_SOVER,
	PRINT_NOOPTIMAL_SOLUTIONS,
	PRINT_OPTIMAL_SOLUTION,
	PRINT_CHECKS,
	PRINT_CHECKS_STATISTICS,
	LOWER_BOUND,
	UPPER_BOUND,

	AMO_ENCODING,
	CARDINALITY_ENCODING,
	PB_ENCODING,
	AMOPB_ENCODING,
    
    TRACE_SAT,
    ENABLE_RESTARTS,
    PHASE_SAVING
};


class SolvingArguments : public Arguments<SolvingArg>{


private:

	SolvingArguments();

	static std::map<std::string,AMOEncoding> amoencodings;
	static std::map<std::string,CardinalityEncoding> cardinalityencodings;
	static std::map<std::string,PBEncoding> pbencodings;
	static std::map<std::string,AMOPBEncoding> amopbencodings;


public:

	virtual ~SolvingArguments();

	template<class OptionT>
	static SolvingArguments * readArguments(int argc, char ** argv, Arguments<OptionT> * pargs);

	void checkSolvingArguments();

	void printVersion() const;
	void printHelp() const;
	void printSolvingOptions() const;
	template<class OptionT>
	void printHelp(Arguments<OptionT> * pargs) const;


	Encoder * getEncoder(Encoding * enc);
	FileEncoder * getFileEncoder(Encoding * enc);
	Optimizer * getOptimizer();


	AMOEncoding getAMOEncoding();
	CardinalityEncoding getCardinalityEncoding();
	PBEncoding getPBEncoding();
	AMOPBEncoding getAMOPBEncoding();


};

template<class OptionT>
SolvingArguments * SolvingArguments::readArguments(int argc, char ** argv, Arguments<OptionT> * pargs){

	SolvingArguments * sargs = new SolvingArguments();
	sargs->addArgument(argv[0]);

	for(int i = 1; i < argc; i++){

		//If it is an argument
		if(strncmp(argv[i], "-", 1)!=0)
			pargs->addArgument(argv[i]);

		//If it is an OPTION
		else{
			std::string argval = argv[i];

			if(argval=="-h" || argval=="--help"){
				sargs->printHelp(pargs);
				exit(0);
			}

			if(argval=="-v" || argval=="--version"){
				sargs->printVersion();
				exit(0);
			}

			std::string arg = argval;
			int delpos = argval.find("=");
			if(delpos==argval.size()-1)
				arg = argval.substr(0,delpos);
			if(delpos==std::string::npos || delpos==argval.size()-1){
				std::cerr << "Missing value for argument " << arg << std::endl;
				exit(BADARGUMENTS_ERROR);
			}

			arg = argval.substr(0,delpos);
			std::string val = argval.substr(delpos+1,argval.size());

			bool knownarg=false;

			if(sargs->hasOption(arg)){
				knownarg = true;
				SolvingArg sarg = sargs->getOptionRef(arg);
				switch(sargs->getOptionType(sarg)){

					case INT_TYPE:
						if(!isInteger(val)){
							std::cerr << arg << " must be an integer value, received: " << val << std::endl;
							exit(BADARGUMENTS_ERROR);
						}
						sargs->setOption(sarg,stoi(val));
						break;

					case BOOL_TYPE:
						if(!boolstring(val)){
							std::cerr << arg << " must be either 0 or 1, received: " << val << std::endl;
							exit(BADARGUMENTS_ERROR);
						}
						sargs->setOption(sarg,val == "1");
						break;

					case STRING_TYPE:
						sargs->setOption(sarg,val);
						break;

					default:
						std::cerr << "Undefined type for option " << arg << std::endl;
						exit(BADARGUMENTS_ERROR);
						break;
				}
			}
			if(pargs->hasOption(arg)){
				knownarg = true;
				OptionT parg = pargs->getOptionRef(arg);
				switch(pargs->getOptionType(parg)){
					case INT_TYPE:
						if(!isInteger(val)){
							std::cerr << arg << " must be an integer value, received: " << val << std::endl;
							exit(BADARGUMENTS_ERROR);
						}
						pargs->setOption(parg,stoi(val));
						break;

					case BOOL_TYPE:
						if(!boolstring(val)){
							std::cerr << arg << " must be either 0 or 1, received: " << val << std::endl;
							exit(BADARGUMENTS_ERROR);
						}
						pargs->setOption(parg,val == "1");
						break;

					case STRING_TYPE:
						pargs->setOption(parg,val);
						break;

					default:
						std::cerr << "Undefined type for option " << arg << std::endl;
						exit(BADARGUMENTS_ERROR);
						break;
				}
			}

			if(!knownarg){
				std::cerr << "Undefined option " << arg << std::endl;
				exit(BADARGUMENTS_ERROR);
			}
		}
	}

	sargs->checkSolvingArguments();

	if(pargs->getNArguments() > pargs->getAllowedArguments()){
		std::cerr << "Extra arguments:";
		for(int i = pargs->getAllowedArguments(); i < pargs->getNArguments(); i++)
			std::cerr << " " << pargs->getArgument(i);

		std::cerr << std::endl << std::endl;
		std::cerr << "Run \"" << argv[0] << " -h\" for help" << std::endl;
		exit(BADARGUMENTS_ERROR);
	}
	else if(pargs->getNArguments() < pargs->getMinimumArguments()){
		std::cerr << "Missing arguments" << std::endl << std::endl;
		std::cerr << "Run \"" << argv[0] << " -h\" for help" << std::endl;
		exit(BADARGUMENTS_ERROR);
	}

	return sargs;
}

template<class OptionT>
void SolvingArguments::printHelp(Arguments<OptionT> * pargs) const{
	printVersion();
	std::cout << std::endl;

	std::cout << "SYNOPSIS:" << std::endl << std::endl;

	std::cout << "    " << getArgument(0) << " [OPTIONS]";

	for(int i = 0; i < pargs->getMinimumArguments(); i++)
		std::cout << " " << pargs->getArgumentName(i);

	for(int i = pargs->getMinimumArguments()+1; i < pargs->getAllowedArguments(); i++){
		std::cout << " [" << pargs->getArgumentName(i) << "]";
	}

	std::cout << std::endl << std::endl;

	if(pargs->getDescription() != ""){
		std::cout << "DESCRIPTION:" << std::endl << std::endl;
		std::cout << "  " << pargs->getDescription();
		std::cout << std::endl << std::endl;
	}

	if(pargs->getAllowedArguments() > 0){
		std::cout << "ARGUMENTS:" << std::endl << std::endl;
		for(int i = 0; i < pargs->getAllowedArguments(); i++){
			printf("  %s: %s\n\n", pargs->getArgumentName(i).c_str(), pargs->getArgumentDesc(i).c_str());
		}

		std::cout << std::endl;
	}

	std::cout << "OPTIONS:" << std::endl << std::endl;
	std::cout << "Generic program information" << std::endl << std::endl;
	printf("  -%-6s --%s","h","help\n");
	std::cout << "            Print help page." << std::endl << std::endl;
	printf("  -%-6s --%s","v","version\n");
	std::cout << "            Print program version." << std::endl << std::endl;

	if(pargs->getNOptions() > 0){
		std::cout << "Program specific" << std::endl << std::endl;
		pargs->printOptions();
	}

	std::cout << "Solving" << std::endl << std::endl;
	printOptions();
}


#endif

