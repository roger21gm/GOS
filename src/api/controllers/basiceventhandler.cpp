#include "basiceventhandler.h"
#include "errors.h"

BasicEventHandler::BasicEventHandler(Encoding * encoding, SolvingArguments * sargs) : EventHandler(){
	this->encoding = encoding;
	this->sargs = sargs;
}

BasicEventHandler::~BasicEventHandler(){

}

void BasicEventHandler::afterSatisfiabilityCall(int lb, int ub, Encoder * encoder){
	if(sargs->getBoolOption(PRINT_CHECKS_STATISTICS)){
		std::cout << "c stats ";

		//Bounds and time
		std::cout << lb << ";";
		std::cout << ub << ";";
		std::cout << encoder->getCheckTime() << ";";
		std::cout << encoder->getSolverCheckTime() << ";";

		//Formula sizes
		std::cout << encoder->getNBoolVars() << ";";
		std::cout << encoder->getNClauses() << ";";

		//Solving statistics
		std::cout << encoder->getNRestarts() << ";";
		std::cout << encoder->getNSimplify() << ";";
		std::cout << encoder->getNReduce() << ";";
		std::cout << encoder->getNDecisions() << ";";
		std::cout << encoder->getNPropagations() << ";";
		std::cout << encoder->getNConflicts() << ";";
		std::cout << encoder->getNTheoryPropagations() << ";";
		std::cout << encoder->getNTheoryConflicts() << ";";

		std::cout << std::endl;
	}
}

void BasicEventHandler::afterNativeOptimizationCall(int lb, int ub, Encoder * encoder){
	afterSatisfiabilityCall(lb,ub,encoder);
}

void BasicEventHandler::onNewBoundsProved(int lb, int ub){
	if(sargs->getBoolOption(PRINT_CHECKS))
		std::cout << "c lb/ub " << lb << " " << ub << std::endl;
}

void BasicEventHandler::onSATSolutionFound(int & lb, int & ub, int & obj_val){
	if(sargs->getBoolOption(PRODUCE_MODELS) && sargs->getBoolOption(PRINT_NOOPTIMAL_SOLUTIONS)){
		std::cout << "v ";
		if(!encoding->printSolution(std::cout))
			std::cout << " [Solution printing not implemented]";
		std::cout << std::endl;
	}
}


void BasicEventHandler::onProvedOptimum(int opt){
	if(sargs->getBoolOption(PRODUCE_MODELS) && sargs->getBoolOption(PRINT_NOOPTIMAL_SOLUTIONS) && !sargs->getBoolOption(PRINT_OPTIMAL_SOLUTION)){
		std::cout << "v ";
		if(!encoding->printSolution(std::cout))
			std::cout << " [Solution printing not implemented]";
		std::cout << std::endl;
	}
	std::cout << "s OPTIMUM FOUND" << std::endl;
	std::cout << "o " << encoding->getObjective() << std::endl;
}

void BasicEventHandler::onProvedSAT(){
	std::cout << "s SATISFIABLE" << std::endl;
}

void BasicEventHandler::onProvedUNSAT(){
	std::cout << "s UNSATISFIABLE" << std::endl;
}


