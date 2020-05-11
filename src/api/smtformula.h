#ifndef SMTFORMULA_DEFINITION
#define SMTFORMULA_DEFINITION

#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <stdlib.h>
#include "MDD/mdd.h"
#include "smtapi.h"
#include "MDD/mddbuilder.h"


namespace smtapi{

/*
 * This class is meant to manage the creation and assertion of
 * a CNF SMT formula.
 * It only handles the theory of LIA.
 * Variables are identified by a name and up to 3 subindices.
 * It also provides unnamed variables, which will usually be auxilliary variables
 * which are going to be used only once.
 * It is a pure virtual class which delegates to child classes
 * the assertion of formulas, either to solver APIs or to standard files.
 * It implements SAT encodings of many common constraints:
 * 	- at-most-one
 * 	- at-least-one
 * 	- exactly-one
 * 	- cardinality constraint
 * 	- pseudo-Boolean constraint
 * 	- at-most-one pseudo-Boolean constraint
 */

enum FORMULA_TYPE{
	SATFORMULA,
	MAXSATFORMULA,
	SMTFORMULA,
	OMTMINFORMULA,
	OMTMAXFORMULA
};

enum AMOEncoding {
	AMO_QUAD,
	AMO_LOG,
	AMO_LADDER,
	AMO_HEULE,
	AMO_COMMANDER, //Draft, not tested
};

enum CardinalityEncoding {
	CARD_SORTER,
	CARD_TOTALIZER
};

enum PBEncoding {
	PB_LIA,
	PB_BDD,
	PB_SWC,
	PB_GT,
	PB_RGT,
	PB_RGTnoR,
	PB_RGTnoPre,
	PB_MTO,
	PB_LMTO,
	PB_GPW,
	PB_LPW,
	PB_LPW2,
	PB_LPW3,
	PB_GBM,
	PB_LBM
};

enum AMOPBEncoding {
	AMOPB_LIA,
	AMOPB_BDD,
	AMOPB_SWC,
	AMOPB_GT,
	AMOPB_RGT,
	AMOPB_RGTnoR,
	AMOPB_RGTnoPre,
	AMOPB_MTO,
	AMOPB_LMTO,
	AMOPB_GPW,
	AMOPB_LPW,
	AMOPB_LPW2,
	AMOPB_LPW3,
	AMOPB_GBM,
	AMOPB_LBM,
	AMOPB_AMOMDD,
	AMOPB_IMPCHAIN,
	AMOPB_AMOBDD,
	AMOPB_GSWC,
	AMOPB_SORTER,
	AMOPB_GGT,
	AMOPB_RGGT,
	AMOPB_RGGTnoR, //Do not reduce
	AMOPB_RGGTnoPre, //Do not pre-process equal coefficients in AMO
	AMOPB_GMTO,
	AMOPB_GLMTO,
	AMOPB_GGPW,
	AMOPB_GLPW,
	AMOPB_GLPW2,
	AMOPB_GLPW3,
	AMOPB_GGBM,
	AMOPB_GLBM
};

extern std::map<AMOPBEncoding,PBEncoding> amopb_pb_rel;


struct RGGTNode{
	RGGTNode * left;
	RGGTNode *right;
	RGGTNode *parent;

	std::vector<int> values;
	std::vector<std::pair<int,int> > intervals;
	std::vector<literal> literals;

	RGGTNode();
	RGGTNode(RGGTNode * left, RGGTNode * right);
	
	~RGGTNode();

	void makeIntervals(int K, bool reduce);
};

class SMTFormula {

private:

	/*
	 * Boolean/Int variables are identified in the ranges [1,nBoolVars] and
	 * [1,nIntVars] respectively. Any variable with an identifier out of this
	 * range will cause a panic exit in time of solver API/file formula assertion,
	 * with error code UNDEFINEDVARIABLE_ERROR.
	 */
	int nBoolVars; //Number of Boolean variables
	int nIntVars; //Number of Int variables

	int nClauses;//Number of clauses
	std::vector<clause> clauses; //Vector of clauses
	std::vector<clause> softclauses; //Vector of soft clauses. If non-empty, is a partial MaxSat problem
	std::vector<int> weights; //Vector of weights of the soft clauses.
	std::vector<intvar> softclausevars; //Vector of soft clauses.

	std::map<std::string,boolvar> mapBoolVars; //Map of Boolean variables identified by name
	std::map<std::string,intvar> mapIntVars; //Map of Int variables identified by name

	std::vector<std::string> boolVarNames; //Name of Boolvars indexed by id. Position 0 is "".
	std::vector<std::string> intVarNames; //Name of Intvars indexed by id. Position 0 is "".
	std::vector<bool> declareVar; //True iff if the i-th int var is a variable has to be declared (i.e. is not a soft clause var)
    
    static std::string defaultauxboolvarpref; //Default prefix for auxilliary bool variables names
    static std::string defaultauxintvarpref; //Default prefix for auxilliary int variables names
    std::string auxboolvarpref; //Prefix for auxilliary bool variables names
    std::string auxintvarpref; //Prefix for auxilliary int variables names

    std::map<int,intvar> mapLiteralToInt; //Mapping from boolvarId to equivalent 0/1 integer variables
    
    bool use_predef_lits;
    bool use_predef_order;
    std::vector<literal> predef_lits;

	boolvar falsevar; //Singleton trivially false variable
	boolvar truevar; //Single trivially true variable

	intsum objFunc; //Objective function in case it is OMT
	bool hasObjFunc; //True iff an objective function has been defined
	bool hassoftclauseswithvars; //True if some soft clause has an associated variable
	bool isMinimization; //True if is an OMT minimization problem
	int LB; //Lower bound for the objective function
	int UB; //Upper bound for the objective function


	void addOrderEncoding(int x, std::vector<literal> & lits);

	//Adds the codification of Sorter [x1,x2] -> [y1,y2]
	void addTwoComparator(const literal &x1, const literal &x2, literal &y1, literal &y2, bool leqclauses, bool geqclauses);

	//Adds the codification of "y is the result of merging x1,x2". Used in cardinality constraint
	void addSimplifiedMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y, int c, bool leqclauses, bool geqclauses);

	void addQuadraticMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y);

	void addTotalizer(const std::vector<literal> &x, std::vector<literal> &y);

	void addTotalizer(const std::vector<literal> &x, const std::vector<std::pair<int,std::set<int> > > &inputBits, std::vector<literal> &y, int lIndex, 
	int partSize, int ommittedLeaf,
	std::map<std::set<std::pair<int,int> >,  std::vector<literal> > & constructed);

	void addTotalizer(const std::vector<literal> &x, std::vector<literal> &y, int k);

	literal assertMDDLEQAbio(MDD * mdd);

	literal assertMDDLEQAbio(MDD * mdd, std::vector<literal> & asserted);

	literal assertMDDGTAbio(MDD * mdd);

	literal assertMDDGTAbio(MDD * mdd, std::vector<literal> & asserted, std::vector<literal> & elses);

	void addPBLIA(const std::vector<int> & Q, const std::vector<literal> & X, int K);

	void addAMOPBSWC(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBSorter(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBGeneralizedTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBReducedGeneralizedGeneralizedTotalizer(std::vector<std::vector<int> >  Q, std::vector<std::vector<literal> > X, int K, bool reduce);
	void mergeValues(const std::vector<int> & n1, const std::vector<int> & n2, std::vector<int> & n3, int K);


	void nLevelsMTO(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int lIndex, int partSize, 
	const std::vector<int> & moduli, std::vector<std::map<int,literal> > & D);

	void localnLevelsMTO(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int lIndex, int partSize, 
	const std::vector<int> & moduli, std::vector<std::map<int,literal> > & D, 
	std::map<std::pair<int,int>, std::vector<std::map<int,literal> > > & constructed, int ommittedLeaf);

	literal MTOVar(std::map<int,literal> & m, int w);

	void comtMTO(int K, const std::vector<int> & moduli, const std::vector<std::map<int,literal> > & D, literal * localLit);

	void baseSelectionMTO(const std::vector<std::vector<int> > & Q, int K, std::vector<int> & moduli);

	void baseSelectionMTO2(const std::vector<std::vector<int> > & Q, int K, std::vector<int> & moduli);

	void addAMOPBModuloTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBLocalModuloTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);


	literal addPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter);

	void addAMOPBLocalPolynomialWatchdog3(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBLocalPolynomialWatchdog2(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

	void addAMOPBLocalPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter);

	void addAMOPBGlobalPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter);


	std::string ssubs(const std::string & var, int i1) const;
	std::string ssubs(const std::string & var, int i1, int i2) const;
	std::string ssubs(const std::string & var, int i1, int i2, int i3) const;


public:
	//Default constructor
	SMTFormula();

	//Destructor
	~SMTFormula();

	//Return the type of the formula based on its content
	FORMULA_TYPE getType() const;

	bool hasSoftClausesWithVars() const;

	int getNBoolVars() const;

	int getNIntVars() const;

	int getNClauses() const;

	int getNSoftClauses() const;

	const std::vector<clause> & getClauses() const;

	const std::vector<clause> & getSoftClauses() const;

	const std::vector<int> & getWeights() const;

	const std::vector<intvar> & getSoftClauseVars() const;

	int getHardWeight() const;

	const std::vector<std::string> & getBoolVarNames() const;

	const std::vector<std::string> & getIntVarNames() const;
    
    void setAuxBoolvarPref(const std::string & s);
    
    void setAuxIntvarPref(const std::string & s);
    
    void setDefaultAuxBoolvarPref();
    
    void setDefaultIntvarPref();

    bool usePredefDecs() const;
    
    bool usePredefOrder() const;
    
    void setUsePredefDecs(const std::vector<literal> & lits, bool order);
    
    void getPredefDecs(std::vector<literal> & lits) const;
    
	bool isDeclareVar(int id) const;

	const intsum & getObjFunc() const;

	//Get the trivially false variable
	boolvar falseVar();

	//Get the trivially true variable
	boolvar trueVar();


	//The name of a variable cannot contain the character "_"


	//Get a new unnamed Boolean variable
	boolvar newBoolVar();
	//Get a new named Boolean variable, with up to 3 subindices in the name
	boolvar newBoolVar(const std::string & var);
	boolvar newBoolVar(const std::string & var, int i1);
	boolvar newBoolVar(const std::string & var, int i1, int i2);
	boolvar newBoolVar(const std::string & var, int i1, int i2, int i3);

	//Set an alias for a boolvar
	void aliasBoolVar(const boolvar & x, const std::string & var);
	void aliasBoolVar(const boolvar & x, const std::string & var, int i1);
	void aliasBoolVar(const boolvar & x, const std::string & var, int i1, int i2);
	void aliasBoolVar(const boolvar & x, const std::string & var, int i1, int i2, int i3);

	//Get a new unnamed Int variable
	intvar newIntVar(bool declare=true);
	//Get a new named Int variable, with up to 3 subindices in the name
	intvar newIntVar(const std::string & var, bool declare=true);
	intvar newIntVar(const std::string & var, int i1, bool declare=true);
	intvar newIntVar(const std::string & var, int i1, int i2, bool declare=true);
	intvar newIntVar(const std::string & var, int i1, int i2, int i3, bool declare=true);

	//Set an alias for an intvar
	void aliasIntVar(const intvar & x, const std::string & var);
	void aliasIntVar(const intvar & x, const std::string & var, int i1);
	void aliasIntVar(const intvar & x, const std::string & var, int i1, int i2);
	void aliasIntVar(const intvar & x, const std::string & var, int i1, int i2, int i3);

	//Get named Boolean variable by name and subindices
	boolvar bvar(const std::string & var) const;
	boolvar bvar(const std::string & var, int i1) const;
	boolvar bvar(const std::string & var, int i1, int i2) const;
	boolvar bvar(const std::string & var, int i1, int i2, int i3) const;

	//Get named Int variable by name and subindices
	intvar ivar(const std::string & var) const;
	intvar ivar(const std::string & var, int i1) const;
	intvar ivar(const std::string & var, int i1, int i2) const;
	intvar ivar(const std::string & var, int i1, int i2, int i3) const;

	void minimize(const intsum & sum);
	void maximize(const intsum & sum);
	void setLowerBound(int LB);
	void setUpperBound(int UB);
	int getLowerBound();
	int getUpperBound();

	static int getIValue(const intvar & var, const std::vector<int> & vals);
	static bool getBValue(const boolvar & var, const std::vector<bool> & vals);

	//Add the empty clause to the formula
	void addEmptyClause();

	//Add clause 'c' to the formula
	void addClause(const clause &c);

	//Add soft clause 'c' to the formula
	void addSoftClause(const clause &c, int weight = 1);

	//Add soft clause 'c' to the formula
	void addSoftClauseWithVar(const clause &c, int weight, const intvar & var);

	//All all the clauses in 'v' to the formula
	void addClauses(const std::vector<clause> &c);

	//Adds at-least-one constraint on the literals in 'v'
	void addALO(const std::vector<literal> & v);

	//Adds at-most-one constraint on the literals in 'v'
	void addAMO(const std::vector<literal> & v, AMOEncoding enc = AMO_QUAD);

	//Adds exactly-one constraint on the literals in 'v'
	void addEO(const std::vector<literal> & v, AMOEncoding enc = AMO_QUAD);

	//Adds at-least-K constraint on the literals in 'v'
	void addALK(const std::vector<literal> & v, int K);

	//Adds at-most-K constraint on the literals in 'v'
	void addAMK(const std::vector<literal> & v, int K, CardinalityEncoding enc = CARD_SORTER);

	//Adds exactly-K constraint on the literals in 'v'
	void addEK(const std::vector<literal> & v, int K);

	//Adds PB constraint Q*X <= K
	void addPB(const std::vector<int> & Q, const std::vector<literal> & X, int K, PBEncoding = PB_BDD);

	//Adds PB constraint Q*X >= K
	void addPBGEQ(const std::vector<int> & Q, const std::vector<literal> & X, int K, PBEncoding = PB_BDD);

	//Adds AMO-PB constraint Q*X <= K
	void addAMOPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, AMOPBEncoding encoding = AMOPB_AMOMDD);

	//Adds AMO-PB constraint Q*X >= K
	void addAMOPBGEQ(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, AMOPBEncoding encoding = AMOPB_AMOMDD);

	//Adds the codification of "y is the x list sorted  decreasingly". Used in cardinality constraint
	void addSorting(const std::vector<literal> &x, std::vector<literal> &y, bool leqclauses, bool geqclauses);

	//Adds the codification of "y contains the first m bits of the x list sorted decreasingly". Used in cardinality constraint
	//If the length of x is smaller than m, the length of y is the same as the length of x
	void addMCardinality(const std::vector<literal> &x, std::vector<literal> &y, int m, bool leqclauses, bool geqclauses);


	//Adds the codification of "y is the result of merging x1,x2". Used in cardinality constraint
	void addMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y, bool leqclauses, bool geqclauses);
};

}

#endif

