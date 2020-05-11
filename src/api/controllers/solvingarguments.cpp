#include "solvingarguments.h"
#include <encoders/glucoseapiencoder.h>
#include <encoders/minisatapiencoder.h>
#include "../optimizers/uboptimizer.h"
#include "../optimizers/buoptimizer.h"
#include "../optimizers/singlecheck.h"
#include "../optimizers/dicooptimizer.h"
#include "../optimizers/nativeoptimizer.h"
#include "../encoders/dimacsfileencoder.h"
#include "../encoders/smtlib2fileencoder.h"
#include "smtformula.h"

#ifdef USEYICES
#include "../solvers/yices2apiencoder.h"
#endif

#ifdef USEGLUCOSE
#include "glucoseapiencoder.h"
#endif


#ifdef USEMINISAT
#include "minisatapiencoder.h"
#endif

#define VERSION "1.0"

using namespace util;
using namespace smtapi;

std::map<std::string,AMOEncoding> SolvingArguments::amoencodings = {
	{"quad",AMO_QUAD},
	{"log",AMO_LOG},
	{"ladder",AMO_LADDER},
	{"heule",AMO_HEULE},
	{"commander",AMO_COMMANDER}
};

std::map<std::string,CardinalityEncoding> SolvingArguments::cardinalityencodings = {
	{"sorter",CARD_SORTER},
	{"totalizer",CARD_TOTALIZER}
};

std::map<std::string,PBEncoding> SolvingArguments::pbencodings = {
	{"lia",PB_LIA},
	{"bdd",PB_BDD},
	{"swc",PB_SWC},
	{"gt",PB_GT},
	{"rgt",PB_RGT},
	{"rgtnor",PB_RGTnoR},
	{"rgtnopre",PB_RGTnoPre},
	{"mto",PB_MTO},
	{"lmto",PB_LMTO},
	{"gpw",PB_GPW},
	{"lpw",PB_LPW},
	{"lpw2",PB_LPW2},
	{"lpw3",PB_LPW3},
	{"gbm",PB_GBM},
	{"lbm",PB_LBM}
};

 std::map<std::string,AMOPBEncoding> SolvingArguments::amopbencodings = {
 	{"lia",AMOPB_LIA},
	{"bdd",AMOPB_BDD},
	{"swc",AMOPB_SWC},
	{"gt",AMOPB_GT},
	{"rgt",AMOPB_RGT},
	{"rgtnor",AMOPB_RGGTnoR},
	{"rgtnopre",AMOPB_RGGTnoPre},
	{"mto",AMOPB_MTO},
	{"lmto",AMOPB_LMTO},
	{"gpw",AMOPB_GPW},
	{"lpw",AMOPB_LPW},
	{"lpw2",AMOPB_LPW2},
	{"lpw3",AMOPB_LPW3},
	{"gbm",AMOPB_GBM},
	{"lbm",AMOPB_LBM},
	{"amomdd",AMOPB_AMOMDD},
	{"ic",AMOPB_IMPCHAIN},
	{"amobdd",AMOPB_AMOBDD},
	{"gswc",AMOPB_GSWC},
	{"sorter",AMOPB_SORTER},
	{"ggt",AMOPB_GGT},
	{"rggt",AMOPB_RGGT},
	{"rggtnor",AMOPB_RGGTnoR},
	{"rggtnopre",AMOPB_RGGTnoPre},
	{"gmto",AMOPB_GMTO},
	{"glmto",AMOPB_GLMTO},
	{"ggpw",AMOPB_GGPW},
	{"glpw",AMOPB_GLPW},
	{"glpw2",AMOPB_GLPW2},
	{"glpw3",AMOPB_GLPW3},
	{"ggbm",AMOPB_GGBM},
	{"glbm",AMOPB_GLBM}
};

SolvingArguments::SolvingArguments() : Arguments<SolvingArg>(

	//No solving arguments requred
	{},
	0,

	//Program solving options
	{arguments::sop("s","solver",SOLVER,"yices",
	{"yices","lingeling","openwbo","glucose","optimathsat","minisat"},
	"Solver to use. API only available with yices and glucose. For SMT encodings, only yices. For MaxSAT encodings, only openwbo. For SAT: glucose, minisat. Default: yices."),

	arguments::bop("e","output-encoding",OUTPUT_ENCODING,false,
	"If 1, the instance will not be solved but the encoding will be output in stdout. If the encoding does not contain a native optimization functionality, the encoding will correspond to the decision version of the problem with the given/computed bounds. Default: 0."),

	arguments::sop("f","file-format",FILE_FORMAT,"smtlib2",
	{"smtlib2","dimacs"},
	"Format to be used to output the encodings (if -E=1). Options: dimacs, smtlib2. For SMT encodings, smlib2 is required. Default: smtlib2."),

	arguments::sop("o","optimizer",OPTIMIZER,"ub",
	{"check","ub","bu","dico","native"},
	"Optimization procedure to use. Check (no optimization), ub (ub to bottom), bu (bottom to up), dico (dicotomic), native (objective function included in the formulation, to be solved with a native optimization approach, e.g. MaxSAT or Optimization Modulo Theories). Default: ub."),

	arguments::iop("r","random-seed",RANDOM_SEED,-1,
	"Random seed of the SAT/SMT solver. Default: default seed of the used solver."),

	arguments::sop("p","file-prefix",FILE_PREFIX,"aux",
	"Prefix of the file name of auxilliary files. This parameter is intended to avoid concurrency issues in multiple executions on a same file system. Default: aux."),

	arguments::bop("a","api",USE_API,true,
	"If 1, use the SAT/SMT solver API. If 0,call the solver as an independent procedure through instance files. Only available with yices and glucose. Default: 1."),

	arguments::bop("","use-assumptions",USE_ASSUMPTIONS,true,
	"If 1, use checks with assumptions in optimization procedures when applicable. Default: 1."),

	arguments::bop("","narrow-bounds",NARROW_BOUNDS,true,
	"If 1, when using optimization with assumptions, the new proved bounds will be asserted. Default: 1."),

	arguments::iop("l","lower-bound",LOWER_BOUND,INT_MIN,
	"Lower bound to be used when solving the instance. Default: problem specific lower bound."),

	arguments::iop("u","upper-bound",UPPER_BOUND,INT_MIN,
	"Upper bound to be used when solving the instance. Default: problem specific upper bound."),

	arguments::bop("m","output-models",PRODUCE_MODELS,true,
	"If 1, models will be retrieved after each satisfiability/optimality call, and the SMTLIB2 file will contain a query of the model (in case -E=1). Required for optimization. Default: 1."),

	/*arguments::bop("","idl",USE_IDL_SOVER,false,
	"Use specific IDL theory solver. Default: 0."),
	*/

	arguments::bop("","print-optimal",PRINT_OPTIMAL_SOLUTION,true,
	"If 1, the optimal solution will be printed. If --print-nonoptimal=1, then --print-optimal=1 regardless the given value. Default: 1."),

	arguments::bop("","print-nonoptimal",PRINT_NOOPTIMAL_SOLUTIONS,true,
	"If 1, all the solutions found during the search for the optimal will be printed. Default: 1."),

	arguments::bop("","print-checks",PRINT_CHECKS,true,
	"If 1, all the lower/upper bounds found during the search will be printed. Default: 1."),

	arguments::bop("","print-stats",PRINT_CHECKS_STATISTICS,true,
	"If 1, the solving statistics in the computation of each lower/upper bound will be printed. Default: 1."),
        
    arguments::iop("","trace-sat",TRACE_SAT,0,
    "If 1 and using Minisat, it will be printed the trace of the execution, excluding propagations. If 2, also print conflict analysis. If 3, propagations also printed. Default: 0."),
        
        
    arguments::bop("","enable-restarts",ENABLE_RESTARTS,1,
    "Restarts enable iff set to 1 (only Minisat). Default: 1."),
        
    arguments::iop("","phase-saving",PHASE_SAVING,2,
        "Minisat phase-saving. (0=none, 1=limited, 2=full). Default: 2."),
        

	arguments::sop("","amo",AMO_ENCODING,"quad",
	{"quad","log","ladder","heule","commander"},
	"Encoding for AMO constraints. Default: quad."),

	arguments::sop("","card",CARDINALITY_ENCODING,"sorter",
	{"sorter","totalizer"},
	"Encoding for AMO constraints. Default: sorter."),


	arguments::sop("","pb",PB_ENCODING,"bdd", 
	util::extract_keys(pbencodings),
	"Encoding for PB constraints. Default: bdd."),

	arguments::sop("","amopb",AMOPB_ENCODING,"amomdd",
	util::extract_keys(amopbencodings),
	"Encoding for AMOPB constraints. Default: amomdd.")
	},
	""
	)
{

}


SolvingArguments::~SolvingArguments() {

}


void SolvingArguments::printVersion() const{
	std::cout << "Program version: " << VERSION << std::endl;
}

void SolvingArguments::checkSolvingArguments(){
	if(getBoolOption(PRINT_NOOPTIMAL_SOLUTIONS))
		setOption(PRINT_OPTIMAL_SOLUTION,true);
}

Optimizer * SolvingArguments::getOptimizer(){
	Optimizer * o;
	std::string so = getStringOption(OPTIMIZER);
	if(so == "ub") o = new UBOptimizer();
	else if(so == "bu") o = new BUOptimizer();
	else if(so == "dico") o = new DicoOptimizer();
	else if(so == "check") o = new SingleCheck();
	else if(so == "native") o = new NativeOptimizer();

	return o;
}

Encoder * SolvingArguments::getEncoder(Encoding * enc){
	Encoder * e = NULL;
	if(getBoolOption(USE_API)){
		std::string solver = getStringOption(SOLVER);
		if(solver=="yices"){
		#ifndef USEYICES
			std::cerr << "Error: this binary has been compiled without support for yices. " << std::endl;
			exit(UNSUPPORTEDFUNC_ERROR);
		#else
			Yices2APIEncoder * e2 = new Yices2APIEncoder(enc);
			if(getIntOption(RANDOM_SEED) != -1)
				e2->setRandomSeed(getIntOption(RANDOM_SEED));
			e = e2;
			e->setProduceModels(getBoolOption(PRODUCE_MODELS));
		#endif
		}
		else if(solver=="glucose"){
			e = new GlucoseAPIEncoder(enc);
		}
		else if(solver=="minisat"){
			e = new MinisatAPIEncoder(enc,getIntOption(TRACE_SAT),getBoolOption(ENABLE_RESTARTS),getIntOption(PHASE_SAVING));
		}
		else{
			std::cerr << "API interaction not supported for solver " << solver << std::endl;
			exit(BADARGUMENTS_ERROR);
		}
	}
	else
		e = getFileEncoder(enc);
	return e;
}

FileEncoder * SolvingArguments::getFileEncoder(Encoding * enc){
	FileEncoder * fe = NULL;
	std::string fileformat = getStringOption(FILE_FORMAT);
	std::string solver = getStringOption(SOLVER);
	std::string fileprefix = getStringOption(FILE_PREFIX);
	if(fileformat=="dimacs"){
		fe = new DimacsFileEncoder(enc,solver);
		fe->setTmpFileName(fileprefix +".dimacs");
	}
	else if(fileformat=="smtlib2"){
		fe = new SMTLIB2FileEncoder(enc,solver);
		fe->setTmpFileName(fileprefix +".smt2");
	}
	else{
		std::cerr << "Unsupported file format " << fileformat << std::endl;
		exit(BADARGUMENTS_ERROR);
	}
	fe->setProduceModels(getBoolOption(PRODUCE_MODELS));
	return fe;
}


AMOEncoding SolvingArguments::getAMOEncoding(){
	return amoencodings[getStringOption(AMO_ENCODING)];
}

CardinalityEncoding SolvingArguments::getCardinalityEncoding(){
	return cardinalityencodings[getStringOption(CARDINALITY_ENCODING)];
}

PBEncoding SolvingArguments::getPBEncoding(){
	return pbencodings[getStringOption(PB_ENCODING)];
}

AMOPBEncoding SolvingArguments::getAMOPBEncoding(){
	return amopbencodings[getStringOption(AMOPB_ENCODING)];
}
