#ifndef OPTIMIZER_DEFINITION
#define OPTIMIZER_DEFINITION

#include "../encoders/encoder.h"
#include<functional>

class Optimizer{

protected :

	std::function<void(int lb, int ub)> beforeSatisfiabilityCall;
	std::function<void(int lb, int ub)> beforeNativeOptimizationCall;
	std::function<void(int lb, int ub, Encoder * encoder)> afterSatisfiabilityCall;
	std::function<void(int lb, int ub, Encoder * encoder)> afterNativeOptimizationCall;
	std::function<void(int lb, int ub)> onNewBoundsProved;
	std::function<void(int & lb, int & ub, int & obj_val)> onSATSolutionFound;
	std::function<void(int & lb, int & ub)> onUNSATBoundsDetermined;
	std::function<void(int opt)> onProvedOptimum;
	std::function<void()> onProvedSAT;
	std::function<void()> onProvedUNSAT;

public:

	Optimizer();

	virtual ~Optimizer();

	virtual bool checkSAT(Encoder * e, int LB, int UB);

	virtual int minimize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	virtual int maximize(Encoder * e, int LB, int UB, bool useAssumptions=false, bool narrowBounds=false);

	void setBeforeSatisfiabilityCall(std::function<void(int lb, int ub)> callback_func);
	void setBeforeNativeOptimizationCall(std::function<void(int lb, int ub)> callback_func);
	void setAfterSatisfiabilityCall(std::function<void(int lb, int ub, Encoder * encoder)> callback_func);
	void setAfterNativeOptimizationCall(std::function<void(int lb, int ub, Encoder * encoder)> callback_func);
	void setOnNewBoundsProved(std::function<void(int lb, int ub)> callback_func);
	void setOnSATSolutionFound(std::function<void(int & lb, int & ub, int & obj_val)> callback_func);
	void setOnUNSATBoundsDetermined(std::function<void(int & lb, int & ub)> callback_func);
	void setOnProvedOptimum(std::function<void(int opt)> callback_func);
	void setOnProvedSAT(std::function<void()> callback_func);
	void setOnProvedUNSAT(std::function<void()> callback_func);


};

#endif

