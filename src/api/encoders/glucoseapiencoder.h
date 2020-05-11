#ifndef GLUCOSEAPIENCODER_DEFINITION
#define GLUCOSEAPIENCODER_DEFINITION

#include <solvers/glucose/simp/SimpSolver.h>
#include <solvers/glucose/core/SolverTypes.h>
#include "apiencoder.h"


using namespace smtapi;
using namespace Glucose;


/*
 * This class asserts an SMT formula to the Yices2 API.
 */
class GlucoseAPIEncoder : public APIEncoder {

private:

	Glucose::SimpSolver * s;

	std::vector<Glucose::Var> vars;

	int lastVar;
	int lastClause;

	Glucose::Lit getLiteral(const literal & l, const std::vector<Glucose::Var> & boolvars);
	bool assertAndCheck(int lb, int ub, std::vector<literal> * assumptions);

public:
	//Default constructor
	GlucoseAPIEncoder(Encoding * enc);

	//Destructor
	~GlucoseAPIEncoder();

	bool checkSAT(int lb, int ub);
	bool checkSATAssuming(int lb, int ub);
	void narrowBounds(int lb, int ub);

};

#endif

