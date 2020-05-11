#ifndef SINGLECHECK_DEFINITION
#define SINGLECHECK_DEFINITION


#include "optimizer.h"


class SingleCheck : public Optimizer{

public:
	SingleCheck();

	~SingleCheck();

	int minimize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	int maximize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

};

#endif

