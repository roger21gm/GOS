#ifndef MINISATAPIENCODER_DEFINITION
#define MINISATAPIENCODER_DEFINITION

#include "apiencoder.h"
#include <solvers/minisat/core/Solver.h>
#include <solvers/minisat/core/SolverTypes.h>
#include <solvers/minisat/mtl/Vec.h>

using namespace smtapi;

/*
 * This class asserts an SMT formula to the Yices2 API.
 */
class MinisatAPIEncoder : public APIEncoder {

private:

	Minisat::Solver * s;

	std::vector<Minisat::Var> vars;
    
    int trace_sat;
    bool restarts_enabled;
    int phase_saving;

	int lastVar;
	int lastClause;

	Minisat::Lit getLiteral(const literal & l, const std::vector<Minisat::Var> & boolvars);
	bool assertAndCheck(int lb, int ub, std::vector<literal> * assumptions);

public:
	//Default constructor
	MinisatAPIEncoder(Encoding * enc, int trace_sat, bool restarts_enabled, int phase_saving);

	//Destructor
	~MinisatAPIEncoder();

	bool checkSAT(int lb, int ub);
	bool checkSATAssuming(int lb, int ub);
	void narrowBounds(int lb, int ub);

};

#endif

