#include "buoptimizer.h"
#include "../util/errors.h"
#include <iostream>


BUOptimizer::BUOptimizer() : Optimizer(){

}

int BUOptimizer::maximize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds) {

	bool satcheck = true;
	bool issat = false;
	int obj_val;
	int lastlb=lb;

	while(satcheck && ub >= lb){

		if(beforeSatisfiabilityCall)
			beforeSatisfiabilityCall(lb, ub);

		satcheck = e->checkSAT(lb,ub);

		if(afterSatisfiabilityCall)
			afterSatisfiabilityCall(lb, ub,e);

		if(!issat)
			issat = satcheck;

		if(satcheck){
			if(e->produceModels() && e->getObjective()!=INT_MIN){
				obj_val = e->getObjective();
				if(onNewBoundsProved)
					onNewBoundsProved(obj_val,ub);
				if(onSATSolutionFound)
					onSATSolutionFound(lb,ub,obj_val);
			}
			else{
				obj_val = lb;
				if(onNewBoundsProved)
					onNewBoundsProved(obj_val,ub);
			}

			lastlb = obj_val;
			lb=obj_val+1;
		}
		else{
			if(onNewBoundsProved)
				onNewBoundsProved(lastlb,lb-1);
			if(onUNSATBoundsDetermined)
				onUNSATBoundsDetermined(lb,ub);
		}
	}

	if(issat){
		if(onProvedOptimum)
			onProvedOptimum(lastlb);
		return lb-1;
	}
	else{
		if(onProvedUNSAT)
			onProvedUNSAT();
		return INT_MIN;
	}
}

int BUOptimizer::minimize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds)
{

	bool satcheck = false;
	int obj_val;
	int checkub=lb;

	if(useAssumptions)
		e->initAssumptionOptimization(lb,ub);

	while(!satcheck && checkub <= ub){
		if(beforeSatisfiabilityCall)
			beforeSatisfiabilityCall(checkub, checkub);

			satcheck = useAssumptions ?
					e->checkSATAssuming(checkub,checkub):
					e->checkSAT(checkub,checkub);

		if(afterSatisfiabilityCall)
			afterSatisfiabilityCall(checkub, checkub,e);

		if(satcheck){
			if(onNewBoundsProved)
				onNewBoundsProved(checkub,checkub);
			if(onSATSolutionFound)
				onSATSolutionFound(checkub,checkub,checkub);
		}
		else{
			if(narrowBounds && useAssumptions)
				e->narrowBounds(checkub+1,ub);
			if(onNewBoundsProved)
				onNewBoundsProved(checkub+1,ub);
			if(onUNSATBoundsDetermined)
				onUNSATBoundsDetermined(checkub,checkub);
			checkub++;
		}
	}
	if(satcheck){
		if(onProvedOptimum)
			onProvedOptimum(satcheck);
		return checkub;
	}
	else{
		if(onProvedUNSAT)
			onProvedUNSAT();
		return INT_MIN;
	}
}



BUOptimizer::~BUOptimizer() {

}
