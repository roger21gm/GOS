#include "dicooptimizer.h"
#include <iostream>


DicoOptimizer::DicoOptimizer() : Optimizer(){

}

int DicoOptimizer::minimize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds) {

	bool satcheck = true;
	bool issat = false;
	bool satverified = false;
	int firstub = ub;
	int obj_val;
	int lastval=ub;

	int checkbound;

	if(useAssumptions)
		e->initAssumptionOptimization(lb,ub);

	while(ub > lb | !satverified){
		checkbound = (ub + lb)/2;
		if(beforeSatisfiabilityCall)
			beforeSatisfiabilityCall(lb, checkbound);

		satcheck = useAssumptions ?
					e->checkSATAssuming(lb,checkbound):
					e->checkSAT(lb,checkbound);

		if(afterSatisfiabilityCall)
			afterSatisfiabilityCall(lb, checkbound,e);

		if(!issat)
			issat = satcheck;

		if(satcheck){
			satverified = true;
			if(narrowBounds && useAssumptions)
				e->narrowBounds(lb,checkbound);

			if(e->produceModels() && e->getObjective()!=INT_MIN){
				obj_val = e->getObjective();
				if(onNewBoundsProved) onNewBoundsProved(lb,obj_val);
				if(onSATSolutionFound) onSATSolutionFound(lb,checkbound,obj_val);
			}
			else{
				obj_val = checkbound;
				if(onNewBoundsProved)
					onNewBoundsProved(lb,obj_val);
			}

			lastval = obj_val;
			ub = obj_val;
		}
		else{
			if(lb == firstub)
				satverified = true;

			if(narrowBounds && useAssumptions)
				e->narrowBounds(checkbound+1,ub);

			if(onNewBoundsProved) onNewBoundsProved(checkbound+1,ub);
			if(onUNSATBoundsDetermined) onUNSATBoundsDetermined(lb,checkbound);

			lb = checkbound+1;
		}
	}

	if(issat){
		if(onProvedOptimum)
			onProvedOptimum(lastval);
		return lastval;
	}
	else{
		if(onProvedUNSAT)
			onProvedUNSAT();
		return INT_MIN;
	}
}


int DicoOptimizer::maximize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds) {

	bool satcheck = true;
	bool issat = false;
	bool satverified = false;
	int firstlb = lb;
	int obj_val;
	int lastval=lb;

	int checkbound;

	if(useAssumptions)
		e->initAssumptionOptimization(lb,ub);

	while(ub > lb | !satverified){
		checkbound = (ub + lb + 1)/2;
		if(beforeSatisfiabilityCall)
			beforeSatisfiabilityCall(checkbound,ub);

		satcheck = useAssumptions ?
					e->checkSATAssuming(checkbound,ub):
					e->checkSAT(checkbound,ub);

		if(afterSatisfiabilityCall)
			afterSatisfiabilityCall(checkbound,ub,e);

		if(!issat)
			issat = satcheck;

		if(satcheck){
			satverified = true;
			if(narrowBounds && useAssumptions)
				e->narrowBounds(checkbound,ub);

			if(e->produceModels() && e->getObjective()!=INT_MIN){
				obj_val = e->getObjective();
				if(onNewBoundsProved)
					onNewBoundsProved(obj_val,ub);
				if(onSATSolutionFound)
					onSATSolutionFound(checkbound,ub,obj_val);
			}
			else{
				obj_val = checkbound;
				if(onNewBoundsProved)
					onNewBoundsProved(obj_val,ub);
			}
			lastval = obj_val;
			lb = obj_val;
		}
		else{
			if(ub == firstlb)
				satverified = true;

			if(narrowBounds && useAssumptions)
				e->narrowBounds(lb,checkbound-1);

			if(onNewBoundsProved)
				onNewBoundsProved(lb,checkbound-1);
			if(onUNSATBoundsDetermined)
				onUNSATBoundsDetermined(checkbound,ub);
			ub = checkbound-1;
		}
	}

	if(issat){
		if(onProvedOptimum)
			onProvedOptimum(lastval);
		return lastval;
	}
	else{
		if(onProvedUNSAT)
			onProvedUNSAT();
		return INT_MIN;
	}
}



DicoOptimizer::~DicoOptimizer() {

}
