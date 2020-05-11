#include "optimizer.h"
#include <iostream>
#include "limits.h"

Optimizer::Optimizer() {
	beforeSatisfiabilityCall = NULL;
	beforeNativeOptimizationCall = NULL;
	afterSatisfiabilityCall = NULL;
	afterNativeOptimizationCall = NULL;
	onNewBoundsProved = NULL;
	onSATSolutionFound = NULL;
	onUNSATBoundsDetermined = NULL;
	onProvedOptimum = NULL;
	onProvedSAT = NULL;
	onProvedUNSAT = NULL;
}

Optimizer::~Optimizer() {

}

bool Optimizer::checkSAT(Encoder * e, int lb, int ub){

	if(beforeSatisfiabilityCall != NULL)
		beforeSatisfiabilityCall(lb, ub);

	bool satcheck = e->checkSAT(lb,ub);

	if(afterSatisfiabilityCall != NULL)
		afterSatisfiabilityCall(lb, ub,e);


	if(satcheck){
		int obj;
		if(onSATSolutionFound != NULL)
			onSATSolutionFound(lb,ub,obj);
		if(onProvedSAT != NULL)
			onProvedSAT();
	}
	else
		if(onProvedUNSAT != NULL)
			onProvedUNSAT();

	return satcheck;
}

int Optimizer::minimize(Encoder * e, int LB, int UB, bool useAssumptions, bool narrowBounds){
	std::cerr << "Bad configuration: unsupported functionality" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
}

int Optimizer::maximize(Encoder * e, int LB, int UB, bool useAssumptions, bool narrowBounds){
	std::cerr << "Bad configuration: unsupported functionality" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
}

void Optimizer::setBeforeSatisfiabilityCall(std::function<void(int lb, int ub)> callback_func){
	beforeSatisfiabilityCall=callback_func;
}

void Optimizer::setBeforeNativeOptimizationCall(std::function<void(int lb, int ub)> callback_func){
	beforeNativeOptimizationCall=callback_func;
}

void Optimizer::setAfterSatisfiabilityCall(std::function<void(int lb, int ub, Encoder * encoder)> callback_func){
	afterSatisfiabilityCall=callback_func;
}

void Optimizer::setAfterNativeOptimizationCall(std::function<void(int lb, int ub, Encoder * encoder)> callback_func){
	afterNativeOptimizationCall=callback_func;
}

void Optimizer::setOnNewBoundsProved(std::function<void(int lb, int ub)> callback_func){
	onNewBoundsProved=callback_func;
}

void Optimizer::setOnSATSolutionFound(std::function<void(int & lb, int & ub, int & obj_val)> callback_func){
	onSATSolutionFound=callback_func;
}

void Optimizer::setOnUNSATBoundsDetermined(std::function<void(int & lb, int & ub)> callback_func){
	onUNSATBoundsDetermined=callback_func;
}

void Optimizer::setOnProvedOptimum(std::function<void(int opt)> callback_func){
	onProvedOptimum=callback_func;
}

void Optimizer::setOnProvedSAT(std::function<void()> callback_func){
	onProvedSAT=callback_func;
}

void Optimizer::setOnProvedUNSAT(std::function<void()> callback_func){
	onProvedUNSAT=callback_func;
}
