#include "nativeoptimizer.h"
#include <iostream>


NativeOptimizer::NativeOptimizer() : Optimizer(){

}

int NativeOptimizer::minimize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds){

	if(beforeNativeOptimizationCall)
			beforeNativeOptimizationCall(lb, ub);

	bool issat = e->optimize(lb,ub);

	if(afterNativeOptimizationCall)
			afterNativeOptimizationCall(lb, ub,e);

	if(issat){
		int obj = e->getObjective();
		if(obj==INT_MIN){
			smtapierrors::fatalError(
				"The encoding must implement getObjective() to retrieve optimal solutions from native optimization"
				,SOLVING_ERROR
			);
		}
		if(onNewBoundsProved) onNewBoundsProved(obj,obj);
		if(onSATSolutionFound) onSATSolutionFound(lb,ub,obj);
		if(onProvedOptimum) onProvedOptimum(obj);
		return obj;
	}
	else{
		if(onUNSATBoundsDetermined) onUNSATBoundsDetermined(lb,ub);
		if(onProvedUNSAT) onProvedUNSAT();

		return INT_MIN;
	}
}

int NativeOptimizer::maximize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds){

	if(beforeNativeOptimizationCall)
			beforeNativeOptimizationCall(lb, ub);

	bool issat = e->optimize(lb,ub);

	if(afterNativeOptimizationCall)
			afterNativeOptimizationCall(lb, ub,e);

	if(issat){
		int obj = e->getObjective();
		if(obj==INT_MIN){
			smtapierrors::fatalError(
				"The encoding must implement getObjective() to retrieve optimal solutions from native optimization"
				,SOLVING_ERROR
			);
		}
		if(onNewBoundsProved) onNewBoundsProved(obj,obj);
		if(onSATSolutionFound) onSATSolutionFound(lb,ub,obj);
		if(onProvedOptimum) onProvedOptimum(obj);

		return obj;
	}
	else{
		if(onUNSATBoundsDetermined) onUNSATBoundsDetermined(lb,ub);
		if(onProvedUNSAT) onProvedUNSAT();
		
		return INT_MIN;
	}
}

NativeOptimizer::~NativeOptimizer() {
}
