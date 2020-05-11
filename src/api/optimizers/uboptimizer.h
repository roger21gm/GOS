#ifndef UBOPTIMIZER_DEFINITION
#define UBOPTIMIZER_DEFINITION


#include "optimizer.h"


class UBOptimizer : public Optimizer{

public:

	UBOptimizer();

	~UBOptimizer();

	int minimize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	int maximize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

};

#endif
