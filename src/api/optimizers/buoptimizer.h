#ifndef BUOPTIMIZER_DEFINITION
#define BUOPTIMIZER_DEFINITION

#include "optimizer.h"


class BUOptimizer : public Optimizer{

public:

	BUOptimizer();

	~BUOptimizer();

	int maximize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	int minimize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

};

#endif
