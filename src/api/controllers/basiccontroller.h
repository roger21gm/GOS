#ifndef BASICCONTROLLER_DEFINITION
#define BASICCONTROLLER_DEFINITION


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
#include "smtformula.h"
#include "solvingarguments.h"


class BasicController {
 protected:
	int LB;
	int UB;
	Encoding * encoding;
    bool minimize;
    SolvingArguments * sargs;

public:
	BasicController(SolvingArguments * sargs, Encoding * enc, bool minimize, int lb, int ub);
	virtual ~BasicController();

	static void afterSatisfiabilityCall(int lb, int ub, Encoder * encoder);
	static void afterNativeOptimizationCall(int lb, int ub, Encoder * encoder);
	static void onNewBoundsProved(int lb, int ub);
	static void onSATSolutionFound(int & lb, int & ub, int & obj_val, Encoding * encoding);
	static void onProvedOptimum(int opt);
	static void onProvedSAT();
	static void onProvedUNSAT();

	virtual void run();
};

#endif

