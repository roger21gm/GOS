#include "basiccontroller.h"
#include <limits.h>
#include "../encoders/dimacsfileencoder.h"
#include "../encoders/smtlib2fileencoder.h"
#include "basiceventhandler.h"
#include "util/errors.h"

#ifdef USEYICES
#include "yices2apiencoder.h"
#endif


BasicController::BasicController(SolvingArguments * sargs, Encoding * enc, bool minimize, int lb, int ub){

	this->sargs = sargs;
	this->encoding = enc;
	this->minimize = minimize;
	this->LB = sargs->getIntOption(LOWER_BOUND);
	this->UB = sargs->getIntOption(UPPER_BOUND);
	if(this->LB==INT_MIN)
		this->LB = lb;
	if(this->UB==INT_MIN)
		this->UB = ub;
}

BasicController::~BasicController() {

}

void BasicController::run() {
	if(sargs->getBoolOption(OUTPUT_ENCODING)){
		FileEncoder * e = sargs->getFileEncoder(encoding);
		SMTFormula * f = encoding->encode(LB,UB);
		e->createFile(std::cout,f);
		delete e;
		delete f;
	}
	else{
		Optimizer * opti = sargs->getOptimizer();
		if(sargs->getBoolOption(PRINT_CHECKS_STATISTICS)){
			opti->setAfterSatisfiabilityCall([=](int lb, int ub, Encoder * encoder){this->afterSatisfiabilityCall(lb,ub,encoder);});
			opti->setAfterNativeOptimizationCall([=](int lb, int ub, Encoder * encoder){this->afterNativeOptimizationCall(lb,ub,encoder);});
		}

		if(sargs->getBoolOption(PRINT_CHECKS))
			opti->setOnNewBoundsProved([=](int lb, int ub){this->onNewBoundsProved(lb,ub);});
		
		if(sargs->getBoolOption(PRODUCE_MODELS) && sargs->getBoolOption(PRINT_NOOPTIMAL_SOLUTIONS))
			opti->setOnSATSolutionFound([=](int & lb, int & ub, int & obj_val){this->onSATSolutionFound(lb,ub,obj_val,this->encoding);});
		
		opti->setOnProvedOptimum([=](int opt){this->onProvedOptimum(opt);});
		opti->setOnProvedSAT([=](){this->onProvedSAT();});
		opti->setOnProvedUNSAT([=](){this->onProvedUNSAT();});

		Encoder * e = sargs->getEncoder(encoding);
		if(minimize)
			opti->minimize(e, LB,UB,sargs->getBoolOption(USE_ASSUMPTIONS),sargs->getBoolOption(NARROW_BOUNDS));
		else
			opti->maximize(e, LB, UB,sargs->getBoolOption(USE_ASSUMPTIONS),sargs->getBoolOption(NARROW_BOUNDS));
		delete opti;
		delete e;
	}
}



void BasicController::afterSatisfiabilityCall(int lb, int ub, Encoder * encoder){
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

void BasicController::afterNativeOptimizationCall(int lb, int ub, Encoder * encoder){
	afterSatisfiabilityCall(lb,ub,encoder);
}

void BasicController::onNewBoundsProved(int lb, int ub){
	std::cout << "c lb/ub " << lb << " " << ub << std::endl;
}

void BasicController::onSATSolutionFound(int & lb, int & ub, int & obj_val, Encoding * encoding){
	std::cout << "v ";
	if(!encoding->printSolution(std::cout))
		std::cout << " [Solution printing not implemented]";
	std::cout << std::endl;
}

void BasicController::onProvedOptimum(int opt){
	std::cout << "s OPTIMUM FOUND" << std::endl;
	std::cout << "o " << opt << std::endl;
}

void BasicController::onProvedSAT(){
	std::cout << "s SATISFIABLE" << std::endl << std::endl;
}

void BasicController::onProvedUNSAT(){
	std::cout << "s UNSATISFIABLE" << std::endl;
}
