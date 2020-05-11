#ifndef ENCODER_DEFINITION
#define ENCODER_DEFINITION

#include "encoding.h"


class Encoder {


protected:
	bool createModel;

	Encoding * enc;

	EncodedFormula workingFormula;
	int lastLB;
	int lastUB;


	//Statistics
	float lastchecktime;
	float solverchecktime;
	int natoms;
	int nrestarts;
	int nsimplify;
	int nreduce;
	int ndecisions;
	int npropagations;
	int nconflicts;
	int ntheorypropagations;
	int ntheoryconflicts;

public:

	//Default constructor
	Encoder(Encoding * encoding);

	//Destructor
	virtual ~Encoder();

	virtual bool checkSAT(int lb, int ub) = 0;

	virtual bool checkSATAssuming(int lb, int ub);

	virtual void narrowBounds(int lb, int ub);

	virtual void initAssumptionOptimization(int lb, int ub);

	virtual bool optimize(int lb, int ub);

	virtual int getObjective() const;

	void setProduceModels(bool b);
	bool produceModels() const;


	//Statistics
	float getCheckTime() const;
	float getSolverCheckTime() const;
	int getNBoolVars() const;
	int getNIntVars() const;
	int getNAtoms() const;
	int getNClauses() const;
	int getNRestarts() const;
	int getNSimplify() const;
	int getNReduce() const;
	int getNDecisions() const;
	int getNPropagations() const;
	int getNConflicts() const;
	int getNTheoryPropagations() const;
	int getNTheoryConflicts() const;


};

#endif

