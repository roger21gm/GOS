#ifndef ENCODING_DEFINITION
#define ENCODING_DEFINITION

#include "smtformula.h"
#include "limits.h"
#include <iostream>


using namespace smtapi;


struct EncodedFormula{
	SMTFormula * f;
	int LB;
	int UB;

	EncodedFormula(){
		this->f = NULL;
		this->LB = 0;
		this->UB = 0;
	}

	EncodedFormula(SMTFormula *f, int LB, int UB){
		this->f = f;
		this->LB = LB;
		this->UB = UB;
	}
};

class Encoding {

protected:

public:
	Encoding();
	virtual ~Encoding();

	virtual SMTFormula * encode(int LB = INT_MIN, int UB = INT_MAX) = 0;

	virtual bool narrowBounds(const EncodedFormula & ef, int lastLB, int lastUB, int lb, int ub);
	virtual void assumeBounds(const EncodedFormula & ef, int LB, int UB, std::vector<literal> & assumptions);
	virtual void setModel(const EncodedFormula & ef, int lb, int ub, const std::vector<bool> & bmodel, const std::vector<int> & imodel);

	virtual int getObjective() const;

	virtual bool printSolution(std::ostream & os) const;
};

#endif

