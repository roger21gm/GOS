#ifndef BASICEVENTHANDLER_DEFINITION
#define BASICEVENTHANDLER_DEFINITION

#include "eventhandler.h"
#include "../encoders/encoder.h"
#include "solvingarguments.h"

class BasicEventHandler : public EventHandler{

protected:

	Encoding * encoding;
	SolvingArguments * sargs;

public:

	BasicEventHandler(Encoding * encoding, SolvingArguments * sargs);

	~BasicEventHandler();

	void afterSatisfiabilityCall(int lb, int ub, Encoder * encoder);

	void afterNativeOptimizationCall(int lb, int ub, Encoder * encoder);

	void onNewBoundsProved(int lb, int ub);

	void onSATSolutionFound(int & lb, int & ub, int & obj_val);

	void onProvedOptimum(int opt);

	void onProvedSAT();

	void onProvedUNSAT();


};

#endif
