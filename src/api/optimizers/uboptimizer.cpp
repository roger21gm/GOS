#include "uboptimizer.h"
#include <iostream>


UBOptimizer::UBOptimizer() : Optimizer(){

}

int UBOptimizer::maximize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds)
{
	
	bool satcheck = false;
	int obj_val;
	int checklb=ub;

	if(useAssumptions)
		e->initAssumptionOptimization(lb,ub);

	while(!satcheck && checklb >= lb){
		if(beforeSatisfiabilityCall)
			beforeSatisfiabilityCall(checklb, ub);

		satcheck = useAssumptions ?
					e->checkSATAssuming(checklb,ub):
					e->checkSAT(checklb,ub);

		if(afterSatisfiabilityCall)
			afterSatisfiabilityCall(checklb, ub,e);

		if(satcheck){
			if(onNewBoundsProved) onNewBoundsProved(checklb,ub);
			if(onSATSolutionFound) onSATSolutionFound(checklb,ub,checklb);
		}
		else{
			ub = checklb;
			if(narrowBounds && useAssumptions)
				e->narrowBounds(lb,ub-1);
			if(onNewBoundsProved) onNewBoundsProved(lb,ub);
			if(onUNSATBoundsDetermined) onUNSATBoundsDetermined(checklb,ub);

			checklb--;
		}
	}
	if(satcheck){
		if(onProvedOptimum) onProvedOptimum(satcheck);
		return checklb;
	}
	else{
		if(onProvedUNSAT) onProvedUNSAT();
		return INT_MIN;
	}
}


int UBOptimizer::minimize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds)
{

	bool satcheck = true;
	bool issat = false;
	int obj_val;
	int lastub=ub;



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
				if(onNewBoundsProved) onNewBoundsProved(lb,obj_val);
				if(onSATSolutionFound) onSATSolutionFound(lb,ub,obj_val);
			}
			else{
				obj_val = ub;
				if(onNewBoundsProved) onNewBoundsProved(lb,obj_val);
			}

			lastub = obj_val;
			ub=obj_val-1;
		}
		else{
			if(onNewBoundsProved && issat) onNewBoundsProved(ub+1,lastub);
			if(onUNSATBoundsDetermined) onUNSATBoundsDetermined(lb,ub);
		}
	}

	if(issat){
		if(onProvedOptimum) onProvedOptimum(lastub);
		return ub+1;
	}
	else{
		if(onProvedUNSAT) onProvedUNSAT();
		return INT_MIN;
	}
}

UBOptimizer::~UBOptimizer() {

}
