#ifndef EVENTHANDLER_DEFINITION
#define EVENTHANDLER_DEFINITION

#include "../encoders/encoder.h"


class EventHandler{

public:

	EventHandler(){};

	virtual ~EventHandler(){};


	virtual void beforeSatisfiabilityCall(int lb, int ub){};

	virtual void beforeNativeOptimizationCall(int lb, int ub){};

	virtual void afterSatisfiabilityCall(int lb, int ub, Encoder * encoder){};

	virtual void afterNativeOptimizationCall(int lb, int ub, Encoder * encoder){};

	virtual void onNewBoundsProved(int lb, int ub){};

	virtual void onSATSolutionFound(int & lb, int & ub, int & obj_val){};

	virtual void onUNSATBoundsDetermined(int & lb, int & ub){};

	virtual void onProvedOptimum(int opt){};

	virtual void onProvedSAT(){};

	virtual void onProvedUNSAT(){};

};

#endif


