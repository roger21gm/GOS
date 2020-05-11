#ifndef NATIVEOPTIMIZER_DEFINITION
#define NATIVEOPTIMIZER_DEFINITION

#include "optimizer.h"


class NativeOptimizer : public Optimizer{

public:
	NativeOptimizer();

	~NativeOptimizer();

	int minimize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	int maximize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

};

#endif

