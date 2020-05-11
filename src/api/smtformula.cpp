#include "smtformula.h"
#include "MDD/amopbmddbuilder.h"
#include "MDD/amopbbddbuilder.h"
#include "MDD/mdd.h"
#include "./util/util.h"
#include <limits.h>
#include <algorithm>
#include <math.h>


namespace smtapi{


std::map<AMOPBEncoding,PBEncoding> amopb_pb_rel = {
	{AMOPB_LIA,PB_LIA},
	{AMOPB_BDD,PB_BDD},
	{AMOPB_SWC,PB_SWC},
	{AMOPB_MTO,PB_MTO},
	{AMOPB_LMTO,PB_LMTO},
	{AMOPB_GT,PB_GT},
	{AMOPB_RGT,PB_RGT},
	{AMOPB_RGTnoR,PB_RGTnoR},
	{AMOPB_RGTnoPre,PB_RGTnoPre},
	{AMOPB_GPW,PB_GPW},
	{AMOPB_LPW,PB_LPW},
	{AMOPB_LPW2,PB_LPW2},
	{AMOPB_LPW3,PB_LPW3},
	{AMOPB_GBM,PB_GBM},
	{AMOPB_LBM,PB_LBM}
};

std::string SMTFormula::defaultauxboolvarpref = "b";
std::string SMTFormula::defaultauxintvarpref = "i";

SMTFormula::SMTFormula() {
	nBoolVars=0;
	nIntVars=0;
	nClauses=0;

	boolVarNames.push_back("");
	intVarNames.push_back("");
	declareVar.push_back(false);

	hasObjFunc = false;
	isMinimization = false;
	LB=INT_MIN;
	UB=INT_MAX;
	hassoftclauseswithvars = false;
    
    use_predef_lits = false;
    use_predef_order = false;
    
    auxboolvarpref=defaultauxboolvarpref;
    auxintvarpref=defaultauxintvarpref;
}

SMTFormula::~SMTFormula() {

}

FORMULA_TYPE SMTFormula::getType() const{
	if(nIntVars > 0){
		if(hasObjFunc){
			if(isMinimization)
				return OMTMINFORMULA;
			else
				return OMTMAXFORMULA;
		}
		else
			return SMTFORMULA;
	}
	else if(!softclauses.empty())
		return MAXSATFORMULA;
	else return SATFORMULA;
}
    
    void SMTFormula::setAuxBoolvarPref(const std::string & s){
    auxboolvarpref=s;
}
    
    void SMTFormula::setAuxIntvarPref(const std::string & s){
    auxintvarpref=s;
}
    
void SMTFormula::setDefaultAuxBoolvarPref(){
    auxboolvarpref=defaultauxboolvarpref;
}

void SMTFormula::setDefaultIntvarPref(){
    auxintvarpref=defaultauxintvarpref;
}
    
bool SMTFormula::usePredefDecs() const{
    return use_predef_lits;
}
    
bool SMTFormula::usePredefOrder() const{
    return use_predef_order;
}
    
void SMTFormula::setUsePredefDecs(const std::vector<literal> & lits, bool order){
    predef_lits = lits;
    use_predef_lits=true;
    use_predef_order=order;
}

void SMTFormula::getPredefDecs(std::vector<literal> & lits) const{
    lits = predef_lits;
}
    
bool SMTFormula::hasSoftClausesWithVars() const{
	return hassoftclauseswithvars;
}

int SMTFormula::getNBoolVars() const{
	return nBoolVars;
}

int SMTFormula::getNIntVars() const{
	return nIntVars;
}

int SMTFormula::getNClauses() const{
	return clauses.size();
}

int SMTFormula::getNSoftClauses() const{
	return softclauses.size();
}

const std::vector<clause> & SMTFormula::getClauses() const{
	return clauses;
}

const std::vector<clause> & SMTFormula::getSoftClauses() const{
	return softclauses;
}

const std::vector<int> & SMTFormula::getWeights() const{
	return weights;
}

const std::vector<intvar> & SMTFormula::getSoftClauseVars() const{
	return softclausevars;
}

int SMTFormula::getHardWeight() const{
	int sum = 2;
	for(int i : weights)
		sum+= i;
	return sum;
}

const std::vector<std::string> & SMTFormula::getBoolVarNames() const{
	return boolVarNames;
}

const std::vector<std::string> & SMTFormula::getIntVarNames() const{
	return intVarNames;
}

bool SMTFormula::isDeclareVar(int id) const{
	return declareVar[id];
}

const intsum &  SMTFormula::getObjFunc() const{
	return objFunc;
}

boolvar SMTFormula::trueVar(){
	if(truevar.id==0){
		truevar=newBoolVar();
		addClause(truevar);
	}
	return truevar;
}

boolvar SMTFormula::falseVar(){
	if(falsevar.id==0){
		falsevar=newBoolVar();
		addClause(!falsevar);
	}
	return falsevar;
}

boolvar SMTFormula::newBoolVar(){
	boolvar x;
	x.id=++nBoolVars;
	boolVarNames.push_back(auxboolvarpref+"__"+std::to_string(x.id));
	return x;
}

boolvar SMTFormula::newBoolVar(const std::string & s){
	boolvar x;
	x.id=++nBoolVars;
	mapBoolVars[s] = x;
	boolVarNames.push_back(s);
	return x;
}

boolvar SMTFormula::newBoolVar(const std::string & s, int i1){
	boolvar x;
	x.id=++nBoolVars;
	std::string s2 = ssubs(s,i1);
	mapBoolVars[s2] = x;
	boolVarNames.push_back(s2);
	return x;
}

boolvar SMTFormula::newBoolVar(const std::string & s, int i1, int i2){
	boolvar x;
	x.id=++nBoolVars;
	std::string s2 = ssubs(s,i1,i2);
	mapBoolVars[s2] = x;
	boolVarNames.push_back(s2);
	return x;
}

boolvar SMTFormula::newBoolVar(const std::string & s, int i1, int i2, int i3){
	boolvar x;
	x.id=++nBoolVars;
	std::string s2 = ssubs(s,i1,i2,i3);
	mapBoolVars[s2] = x;
	boolVarNames.push_back(s2);
	return x;
}

void SMTFormula::aliasBoolVar(const boolvar & x, const std::string & s){
	mapBoolVars[s] = x;
}

void SMTFormula::aliasBoolVar(const boolvar & x, const std::string & s, int i1){
	std::string s2 = ssubs(s,i1);
	mapBoolVars[s2] = x;
}

void SMTFormula::aliasBoolVar(const boolvar & x, const std::string & s, int i1, int i2){
	std::string s2 = ssubs(s,i1,i2);
	mapBoolVars[s2] = x;
}

void SMTFormula::aliasBoolVar(const boolvar & x, const std::string & s, int i1, int i2, int i3){
	std::string s2 = ssubs(s,i1,i2,i3);
	mapBoolVars[s2] = x;
}

intvar SMTFormula::newIntVar(bool declare){
	intvar x;
	x.id=++nIntVars;
	intVarNames.push_back(auxintvarpref+"__"+std::to_string(x.id));
	declareVar.push_back(declare);
	return x;
}

intvar SMTFormula::newIntVar(const std::string & s, bool declare){
	intvar x;
	x.id=++nIntVars;
	mapIntVars[s] = x;
	intVarNames.push_back(s);
	declareVar.push_back(declare);
	return x;
}

intvar SMTFormula::newIntVar(const std::string & s, int i1, bool declare){
	intvar x;
	x.id=++nIntVars;
	std::string s2 = ssubs(s,i1);
	mapIntVars[s2] = x;
	intVarNames.push_back(s2);
	declareVar.push_back(declare);
	return x;
}

intvar SMTFormula::newIntVar(const std::string & s, int i1, int i2, bool declare){
	intvar x;
	x.id=++nIntVars;
	std::string s2 = ssubs(s,i1,i2);
	mapIntVars[s2] = x;
	intVarNames.push_back(s2);
	declareVar.push_back(declare);
	return x;
}

intvar SMTFormula::newIntVar(const std::string & s, int i1, int i2, int i3, bool declare){
	intvar x;
	x.id=++nIntVars;
	std::string s2 = ssubs(s,i1,i2,i3);
	mapIntVars[s2] = x;
	intVarNames.push_back(s2);
	declareVar.push_back(declare);
	return x;
}



void SMTFormula::aliasIntVar(const intvar & x, const std::string & s){
	mapIntVars[s] = x;
}

void SMTFormula::aliasIntVar(const intvar & x, const std::string & s, int i1){
	std::string s2 = ssubs(s,i1);
	mapIntVars[s2] = x;
}

void SMTFormula::aliasIntVar(const intvar & x, const std::string & s, int i1, int i2){
	std::string s2 = ssubs(s,i1,i2);
	mapIntVars[s2] = x;
}

void SMTFormula::aliasIntVar(const intvar & x, const std::string & s, int i1, int i2, int i3){
	std::string s2 = ssubs(s,i1,i2,i3);
	mapIntVars[s2] = x;
}

boolvar SMTFormula::bvar(const std::string & s) const{
	return mapBoolVars.find(s)->second;
}

boolvar SMTFormula::bvar(const std::string & s, int i1) const{
	return mapBoolVars.find(ssubs(s,i1))->second;
}

boolvar SMTFormula::bvar(const std::string & s, int i1, int i2) const{
	return mapBoolVars.find(ssubs(s,i1,i2))->second;
}

boolvar SMTFormula::bvar(const std::string & s, int i1, int i2, int i3) const{
	return mapBoolVars.find(ssubs(s,i1,i2,i3))->second;
}

intvar SMTFormula::ivar(const std::string & s) const{
	return mapIntVars.find(s)->second;
}

intvar SMTFormula::ivar(const std::string & s, int i1) const{
	return mapIntVars.find(ssubs(s,i1))->second;
}

intvar SMTFormula::ivar(const std::string & s, int i1, int i2) const{
	return mapIntVars.find(ssubs(s,i1,i2))->second;
}

intvar SMTFormula::ivar(const std::string & s, int i1, int i2, int i3) const{
	return mapIntVars.find(ssubs(s,i1,i2,i3))->second;
}


std::string SMTFormula::ssubs(const std::string & s, int i1) const{
	char aux[50];
	sprintf(aux,"%s_%d",s.c_str(),i1);
	return aux;
}

std::string SMTFormula::ssubs(const std::string & s, int i1, int i2) const{
	char aux[50];
	sprintf(aux,"%s_%d_%d",s.c_str(),i1,i2);
	return aux;
}

std::string SMTFormula::ssubs(const std::string & s, int i1, int i2, int i3) const{
	char aux[50];
	sprintf(aux,"%s_%d_%d_%d",s.c_str(),i1,i2,i3);
	return aux;
}

void SMTFormula::minimize(const intsum & sum){
	hasObjFunc = true;
	isMinimization = true;
	objFunc = sum;
}

void SMTFormula::maximize(const intsum &sum){
	hasObjFunc = true;
	isMinimization = false;
	objFunc = sum;
}

void SMTFormula::setLowerBound(int lb){
	this->LB = lb;
}

void SMTFormula::setUpperBound(int ub){
	this->UB = ub;
}

int SMTFormula::getLowerBound(){
	return this->LB;
}

int SMTFormula::getUpperBound(){
	return this->UB;
}

int SMTFormula::getIValue(const intvar & var, const std::vector<int> & vals){
	return vals[var.id];
}

bool SMTFormula::getBValue(const boolvar & var, const std::vector<bool> & vals){
	return vals[var.id];
}

void SMTFormula::addEmptyClause(){
	clauses.push_back(clause());
}

void SMTFormula::addClause(const clause &c) {
	clauses.push_back(c);
}

void SMTFormula::addSoftClause(const clause &c, int weight) {
	softclauses.push_back(c);
	weights.push_back(weight);
	softclausevars.push_back(intvar());
}

void SMTFormula::addSoftClauseWithVar(const clause &c, int weight, const intvar & var) {
	softclauses.push_back(c);
	weights.push_back(weight);
	softclausevars.push_back(var);
	hassoftclauseswithvars = true;
}

void SMTFormula::addClauses(const std::vector<clause> &c) {
	clauses.insert(clauses.end(),c.begin(),c.end());
}

void SMTFormula::addALO(const std::vector<literal> & v) {
	addClause(v);
}

void SMTFormula::addAMO(const std::vector<literal> & x, AMOEncoding enc) {

	int n = x.size();
	if(n <= 1) //Constraint trivially satisfied
		return;

	switch(enc){
		//Quadratic endoding
		//No auxilliary variables required
		//O(n^2) clauses
		case AMO_QUAD:
			//Mutual exclusion between every pair of variables
			for (int i=0;i<n-1;i++)
				for (int j=i+1;j<n;j++)
					addClause(!x[i] | !x[j]);
			break;

		//Logarithmic endoding
		//O(log(n)) auxilliary variables
		//O(n log(n)) clauses
		case AMO_LOG:
		{
			//Number of bits necessary to represent 0..n-1 in binary
			int m = (int)ceil(log2(n));

			//'y' is the binary representation of the integer 'i' such that variable x[i] is true
			//if more than one variable x[i] is true, a conflict arise
			std::vector<boolvar> y(m);
			for(int j = 0; j < m; j++)
				y[j] = newBoolVar();

			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					if((i >> j) % 2 == 0) //If the j-th bit of the binary representation of 'i' is 0
						addClause(!x[i] | !y[j]); //The j-th bit of y has to be 0
					else
						addClause(!x[i] | y[j]); //The j-th bit of y has to be 1
		}
			break;

		//Ladder endoding
		//O(n) auxilliary variables
		//O(n) clauses
		case AMO_LADDER:
		{
			//'y' is an order encoding of the integer 'i' such that the variable x[i] which is true
			//if more than one variable x[i] is true, a conflict arise
			std::vector<boolvar> y(n-1);
			for(int i = 0; i < n-1; i++){
				y[i] = newBoolVar();
				//Order encoding of 'y'
				if(i > 0)
					addClause(!y[i] | y[i-1]);
			}

			for(int i = 0; i < n; i++){

				//Channeling between 'i' and 'y':  x[i] -> (y[i-1] /\ ¬y[i])
				if(i == 0){
					addClause(!x[i] | !y[i]);
					//addClause(x[i] | y[i]); //Needed in EO
				}
				else if(i == n-1){
					addClause(!x[i] | y[i-1]);
					//addClause(x[i] | !y[i-1]); //Needed in EO
				}
				else{
					addClause(!x[i] | y[i-1]);
					addClause(!x[i] | !y[i]);
					//addClause(!y[i-1] | y[i] | x[i]); //Needed in EO
				}
			}
		}
			break;

		//Heule endoding
		//O(n) auxilliary variables
		//O(n) clauses
		case AMO_HEULE:
		{
			if(n <= 3)
				addAMO(x,AMO_QUAD);
			else{
				//Recursively encode AMO(x1,x2,y) /\ AMO(x3,x4,...,xn,¬y)
				boolvar y = newBoolVar();
				std::vector<literal> v1(x.begin(),x.begin()+2);
				std::vector<literal> v2(x.begin()+2,x.end());
				v1.push_back(y);
				v2.push_back(!y);
				addAMO(v1,AMO_QUAD); //AMO(x1,x2,y)
				addAMO(v2,AMO_LADDER); //AMO(x3,x4,...,xn,¬y)
			}
		}
			break;


		//Commander encoding with k=3
		//O(n) auxilliary variables
		//O(n) clauses
		case AMO_COMMANDER:
		{
			if(n<6)
				addAMO(x,AMO_QUAD);
			else{
				int nsplits = n/3;
				if(n%3!=0) nsplits++;

				std::vector<literal> cmd_vars(nsplits);

				if(nsplits==2){
					cmd_vars[0] = newBoolVar();
					cmd_vars[1] = !cmd_vars[0];
				}
				else{
					for(int i= 0; i < nsplits; i++)
						cmd_vars[i] = newBoolVar();
					addEO(cmd_vars,AMO_COMMANDER);
				}

				for(int i = 0; i < nsplits; i++){
					std::vector<literal> v;
					for(int j = 3*i; j < 3*(i+1) && j < n; j++){
						v.push_back(x[j]);
						addClause(v[i] | !x[j]);
					}
					addAMO(v,AMO_QUAD);
				}
			}
		}
		default:
			std::cerr << "Wrong AMO encoding" << std::endl;
			exit(BADCODIFICATION_ERROR);
			break;
	}
}

void SMTFormula::addEO(const std::vector<literal> & v, AMOEncoding enc) {
	addALO(v);
	addAMO(v,enc);
}


void SMTFormula::addALK(const std::vector<literal> & v, int K){
	int n = v.size();
	if(K>n){ //Trivially false
		addEmptyClause();
		return;
	}
	else if(K<=0)//Trivially true
		return;
	else if(K==1){ //At least one constraint
		addALO(v);
	}
	else if(n==K)
		for(const literal &l : v)
			addClause(l);
	else{
		if(K > n/2){ //AMK encoding of the negated literals is smaller
			std::vector<literal> v2;
			for(const literal & l : v)
				v2.push_back(!l);
			addAMK(v2,n-K,CARD_SORTER);
		}
		else{
			std::vector<literal> sorted;
			addMCardinality(v,sorted,K,false,true);
			addClause(sorted[K-1]);
		}
	}
}

void SMTFormula::addAMK(const std::vector<literal> & v, int K, CardinalityEncoding enc){
	int n = v.size();
	if(K < 0){ //Trivially false
		addEmptyClause();
		return;
	}
	else if(K>=n){ //Trivially true
		return;
	}
	else if(K==0) //All must be false
		for(const literal &l : v)
			addClause(!l);
	else if(K==1){ //At most one constraint
		if(n >= 5)
			addAMO(v,AMO_LADDER);
		else
			addAMO(v,AMO_QUAD);
	}
	else{
		switch(enc){
			case CARD_TOTALIZER:
			{
				std::vector<literal> root(std::min(K+1,n));
				addTotalizer(v,root,K);
				if(root.size() > K)
					addClause(!root[K]);
			}
			break;

			case CARD_SORTER:
			default:
			{
				if(K > n/2){ //ALK encoding of the negated literals is smaller
					std::vector<literal> v2;
					for(const literal & l : v)
						v2.push_back(!l);
					addALK(v2,n-K);
				}
				else{
					std::vector<literal> sorted;
					addMCardinality(v,sorted,K+1,true,false);
					addClause(!sorted[K]);
				}
			}
			break;
		}
	}
}

void SMTFormula::addEK(const std::vector<literal> & v, int K){
	int n = v.size();
	if(K>n | K < 0){ //Triviavlly false
		addEmptyClause();
		return;
	}
	else if(K == n) //All must be true
		for(const literal &l : v)
			addClause(l);
	else if(K==0) //All must be false
		for(const literal &l : v)
			addClause(!l);
	else{
		if(K > n/2){ //EK encoding of the negated literals is smaller
			std::vector<literal> v2;
			for(const literal & l : v)
				v2.push_back(!l);
			addEK(v2,n-K);
		}
		else{
			std::vector<literal> sorted(n);
			addMCardinality(v,sorted,K+1,true,true);
			addClause(sorted[K-1]);
			addClause(!sorted[K]);
		}
	}
}

void SMTFormula::addPB(const std::vector<int> & Q, const std::vector<literal> & X, int K, PBEncoding encoding){

	if(X.size()!=Q.size())
	{
		std::cerr << "Tried to assert a PB with different number of coefficient and variable " << std::endl;
		exit(BADCODIFICATION_ERROR);
	}

	std::vector<int> Q2;
	std::vector<literal> X2;

	int maxsum = 0;

	for(int i = 0; i < X.size(); i++){
		if(Q[i]>K) //If coefficient greater than K, the variable cannot be true
			addClause(!X[i]);
		else if(Q[i]> 0){ //suppress coefficients == 0
			//If repeated coefficients, half-reify into single variable
			Q2.push_back(Q[i]);
			X2.push_back(X[i]);
			maxsum+=Q[i];
		}
		else if(Q[i]<0){
			std::cerr << "Error: Tried to assert a PB with a negative coefficient" << std::endl;
			exit(BADCODIFICATION_ERROR);
		}
	}

	//Trivial cases
	if(K < 0){
		addEmptyClause();
		return;
	}
	if(K==0){
		for(const literal & l : X2)
			addClause(!l);
		return;
	}
	if(K >= maxsum) //Also handles empty sums
		return;

	int N = X2.size();
	if(N==1) //We have enforced that no coefficient is greater than K
		return;


	std::vector<std::vector<int> > QQ;
	std::vector<std::vector<literal> > XX;
	switch(encoding){
		case PB_LIA:
		{
			addPBLIA(Q2,X2,K);
			break;
		}

		case PB_BDD:
		{
			util::sortCoefsDecreasing(Q2,X2);
			AMOPBMDDBuilder mb(Q2,X2,K);
			MDD * mdd = mb.getMDD();
			addClause(assertMDDLEQAbio(mdd));
		}
			break;

		case PB_SWC:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GSWC);
			break;

		case PB_GT:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GGT);
			break;

		case PB_RGT:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_RGGT);
			break;

		case PB_RGTnoR:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_RGGTnoR);
			break;

		case PB_RGTnoPre:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_RGGTnoPre);
			break;

		case PB_MTO:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GMTO);
			break;

		case PB_LMTO:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GLMTO);
			break;

		case PB_LPW:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GLPW);
			break;

		case PB_LPW2:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GLPW2);
			break;

		case PB_LPW3:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GLPW3);
			break;

		case PB_GPW:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GGPW);
			break;

		case PB_LBM:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GLBM);
			break;

		case PB_GBM:
			util::PBtoAMOPB(Q2,X2,QQ,XX);
			addAMOPB(QQ,XX,K,AMOPB_GGBM);
			break;

		default:
			std::cerr << "Wrong kind of PB encoding" << std::endl;
			exit(BADCODIFICATION_ERROR);
			break;
	}
}

void SMTFormula::addAMOPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, AMOPBEncoding encoding){

	std::map<AMOPBEncoding,PBEncoding>::iterator it = amopb_pb_rel.find(encoding);
	if(it != amopb_pb_rel.end()){
		std::vector<int> Q2;
		std::vector<literal> X2;
		util::AMOPBtoPB(Q,X,Q2,X2);
		addPB(Q2,X2,K,it->second);
		return;
	}


	if(X.size()!=Q.size())
	{
		std::cerr << "Tried to assert an AMO-PB with different number of coefficient groups and variable groups" << std::endl;
		exit(BADCODIFICATION_ERROR);
	}

	std::vector<std::vector<int> > Q2;
	std::vector<std::vector<literal> > X2;

	int maxsum = 0;

	for(int i = 0; i < X.size(); i++){
		if(X[i].size()!=Q[i].size()){
			std::cerr << "Error: Tried to assert an AMO-PB with different number of coefficients and variables in a group" << std::endl;
			exit(BADCODIFICATION_ERROR);
		}


		int max = 0;
		std::vector<int> q;
		std::vector<literal> x;

		if(encoding==AMOPB_RGGTnoPre){
			for(int j = 0; j < X[i].size(); j++){
				if(Q[i][j]>K) //If coefficient greater than K, the variable cannot be true
					addClause(!X[i][j]);
				else{
					x.push_back(X[i][j]);
					q.push_back(Q[i][j]);
					if(Q[i][j] > max)
						max = Q[i][j];
				}
			}
		}
		else
		{
			std::map<int,literal> terms;
			std::map<int,int> count;

			for(int j = 0; j < X[i].size(); j++){
				if(Q[i][j]>K) //If coefficient greater than K, the variable cannot be true
					addClause(!X[i][j]);
				else if(Q[i][j] > 0){
					//If repeated coefficients, half-reify into single variable
					if(count.find(Q[i][j]) == count.end()){
						count[Q[i][j]] = 1;
						terms[Q[i][j]] = X[i][j];
					}
					else{
						if(count[Q[i][j]]==1){
							boolvar v = newBoolVar();
							addClause(!terms[Q[i][j]] | v);
							terms[Q[i][j]] = v;
						}
						addClause(!X[i][j] | terms[Q[i][j]]);
						count[Q[i][j]] += 1;
					}
				}
				else if(Q[i][j]<0){
					std::cerr << "Error: Tried to assert an AMO-PB with a negative coefficient" << std::endl;
					exit(BADCODIFICATION_ERROR);
				}
			}

			for(const std::pair<int,literal> & term : terms){
				q.push_back(term.first);
				x.push_back(term.second);
				if(term.first > max)
					max = term.first;
			}
		}
		if(!q.empty()){
			Q2.push_back(q);
			X2.push_back(x);
		}
		maxsum+=max;
	}

	//Trivial cases
	if(K < 0){
		addEmptyClause();
		return;
	}
	if(K==0){
		for(const std::vector<literal> & v : X2)
			for(const literal & l : v)
				addClause(!l);
		return;
	}
	if(K >= maxsum) //Also handles empty sums
		return;

	int N = X2.size();
	if(N==1) //We have enforced that no AMO group contains a coefficient greater than K
		return;


	switch(encoding){
		case AMOPB_AMOMDD:
		{
			util::sortCoefsDecreasing(Q2,X2);

			AMOPBMDDBuilder mb(Q2,X2,K);
			MDD * mdd = mb.getMDD();
			addClause(assertMDDLEQAbio(mdd));
		}
			break;

		case AMOPB_IMPCHAIN :
		{
			util::sortCoefsDecreasing(Q2,X2);

			std::vector<std::vector<literal> > Y2;
			for(int i = 0; i < X2.size();i++){
				Y2.push_back(std::vector<literal>(X2[i].size()));
				for(int j = 0; j < X2[i].size(); j++)
					Y2[i][j] = newBoolVar();
				util::sortCoefsIncreasing(Q2[i],X2[i]);
				for(int j = 0; j < X2[i].size(); j++){
					addClause(!X2[i][j]|Y2[i][j]);
					if(j < X2[i].size()-1){
						addClause(!X2[i][j] | !Y2[i][j+1]);
						addClause(!Y2[i][j+1] | Y2[i][j]);
					}
				}

			}

			AMOPBMDDBuilder mb(Q2,Y2,K);
			MDD * mdd = mb.getMDD();
			addClause(assertMDDLEQAbio(mdd));
		}
			break;

		case AMOPB_AMOBDD:
		{
			util::sortCoefsDecreasing(Q2,X2);

			AMOPBBDDBuilder mb(Q2,X2,K);
			MDD * mdd = mb.getMDD();
			addClause(assertMDDLEQAbio(mdd));
		}
			break;

		case AMOPB_GSWC:
			addAMOPBSWC(Q2,X2,K);
			break;

		case AMOPB_SORTER:
			addAMOPBSorter(Q2,X2,K);
			break;

		case AMOPB_GGT:
			addAMOPBGeneralizedTotalizer(Q2,X2,K);
			break;

		case AMOPB_RGGT:
		case AMOPB_RGGTnoPre:
			addAMOPBReducedGeneralizedGeneralizedTotalizer(Q2,X2,K,true);
			break;

		case AMOPB_RGGTnoR:
			addAMOPBReducedGeneralizedGeneralizedTotalizer(Q2,X2,K,false);
			break;

		case AMOPB_GMTO:
			addAMOPBModuloTotalizer(Q2,X2,K);
			break;


		case AMOPB_GLMTO:
			addAMOPBLocalModuloTotalizer(Q2,X2,K);
			break;

		case AMOPB_GGBM:
			addAMOPBGlobalPolynomialWatchdog(Q2,X2,K,true);
			break;

		case AMOPB_GLBM:
			addAMOPBLocalPolynomialWatchdog(Q2,X2,K,true);
			break;

		case AMOPB_GLPW:
			addAMOPBLocalPolynomialWatchdog(Q2,X2,K,false);
			break;

		case AMOPB_GLPW2:
			addAMOPBLocalPolynomialWatchdog2(Q2,X2,K);
			break;

		case AMOPB_GLPW3:
			addAMOPBLocalPolynomialWatchdog3(Q2,X2,K);
			break;

		case AMOPB_GGPW:
			addAMOPBGlobalPolynomialWatchdog(Q2,X2,K,false);
			break;

		default://PB encoding
			std::cerr << "Wrong kind of AMOPB encoding" << std::endl;
			exit(SOLVING_ERROR);
			break;
	}
}


void SMTFormula::addPBGEQ(const std::vector<int> & Q, const std::vector<literal> & X, int K, PBEncoding encoding){

	std::vector<literal> X2;
	int K2=0;

	for(int i = 0; i < Q.size(); i++){
		X2[i]=!X[i];
		K2+=Q[i];
	}
	K2 -= K;

	addPB(Q,X2,K,encoding);
}


void SMTFormula::addAMOPBGEQ(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, AMOPBEncoding encoding){

	std::vector<std::vector<int> > Q2(Q.size());
	std::vector<std::vector<literal> > X2(X.size());
	int K2=-K;

	for(int i = 0; i < Q.size(); i++){
		if(Q[i].size()==1){
			X2[i].push_back(!X[i][0]);
			Q2[i].push_back(Q[i][0]);
			K2+=Q[i][0];
		}
		else{
			boolvar aux = newBoolVar();
			int maxq = *max_element(Q[i].begin(),Q[i].end());
			std::vector<literal> c;
			c.push_back(aux);
			X2[i].push_back(aux);
			Q2[i].push_back(maxq);
			K2+=maxq;
			for(int j = 0; j < Q[i].size(); j++){
				int q = maxq-Q[i][j];
				addClause(!aux | !X[i][j]);
				c.push_back(X[i][j]);
				if(q > 0){
					Q2[i].push_back(q);
					X2[i].push_back(X[i][j]);
				}
			}
			addClause(c);
		}
	}

	addAMOPB(Q2,X2,K2,encoding);
}




literal SMTFormula::assertMDDLEQAbio(MDD * mdd) {
	std::vector<literal> asserted(mdd->getId()+1);
	boolvar undef;
	undef.id=-1;

	for(int i = 0; i <= mdd->getId(); i++)
		asserted[i] = undef; 
	return assertMDDLEQAbio(mdd,asserted);
}

literal SMTFormula::assertMDDLEQAbio(MDD * mdd, std::vector<literal> & asserted) {
	if(mdd->isTrueMDD())
		return trueVar();
	else if(mdd->isFalseMDD())
		return falseVar();

	literal v=asserted[mdd->getId()];
	if(v.v.id==-1){
		v = newBoolVar();
		asserted[mdd->getId()]=v;

		literal velse = assertMDDLEQAbio(mdd->getElseChild(),asserted);
		addClause(velse | !v);

		for(int i = 0; i < mdd->getNSelectors();i++){
			std::pair<literal,MDD *> p = mdd->getSelectorAndChild(i);
			if(p.second != mdd->getElseChild())
			{
				literal vi = assertMDDLEQAbio(p.second,asserted);
				addClause(vi | !p.first | !v);
			}
		}
	}

	return v;
}

void SMTFormula::addPBLIA(const std::vector<int> & Q, const std::vector<literal> & X, int K){

	int N = X.size();

	intsum s;


	//If the literal is a boolean variable or its negation, reuse integer variable if already defined
	//Otherwise, define new integer variable
	for(int i = 0; i < N; i++){
		intvar  ix;

		bool reused = false;
		int litid;

		if(!X[i].arith){
			litid = X[i].v.id;
			if(!X[i].sign)
				litid = -litid;

			std::map<int,intvar>::iterator it = mapLiteralToInt.find(litid);
			if(it != mapLiteralToInt.end()){
				//If equivalent 0/1 variable exists for literal, retrieve it
				ix = it->second;
				reused = true;
			}
		}
		if(!reused)
		{
			//Auxilliary intvar never created. Create and define it
			ix = newIntVar();
			addClause(ix >= 0);
			addClause(ix <= 1);
			addClause(!X[i] |  ix == 1);
			addClause( X[i] | ix == 0);

			if(!X[i].arith)
				mapLiteralToInt[litid] = ix;
		}
		s += Q[i]*ix;
	}

	addClause(s <= K);
}

void SMTFormula::addAMOPBSWC(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){

	int N = X.size();

	std::vector<literal> Sin, Sout(K);

	for(int i = 0; i < N; i++){
		Sin = Sout;

		if(i < N-1)
			for(int j = 0; j < K; j++)
				Sout[j] = newBoolVar();

		if(i < N-1 && i > 0)
			for(int j = 0; j < K; j++)
				addClause(!Sin[j] | Sout[j]);

		for(int j = 0; j < X[i].size(); j++){
			int q = Q[i][j];
			if(i < N-1)
				for(int k = 0; k < q; k++)
					addClause(!X[i][j] | Sout[k]);
			if(i>0 && i < N-1)
				for(int k = 0; k < K-q; k++)
					addClause(!Sin[k] | !X[i][j] | Sout[k+q]);
			if(i>0 && q > 0)
				addClause(!Sin[K-q] | !X[i][j]);
		}
	}
}

void SMTFormula::addAMOPBSorter(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){

	int n = Q.size();

	if(K==0){
		for(const std::vector<literal> & v : X)
			for(const literal & l : v)
				addClause(!l);
		return;
	}

	int maxsum = 0;
	for(int i = 0; i < n; i++)
		maxsum+= *(max_element(Q[i].begin(),Q[i].end()));

	if(maxsum <= K)
		return;

	std::vector<std::vector<literal> > orders;
	for(int i = 0; i < n; i++){
		int maxq = *(max_element(Q[i].begin(),Q[i].end()));
		if(maxq > 0){
			std::vector<literal> order;
			addOrderEncoding(maxq,order);
			for(int j = 0; j < Q[i].size(); j++)
				if(Q[i][j]>0)
					addClause(!X[i][j] | order[Q[i][j]-1]);
			orders.push_back(order);
		}
	}

	while(orders.size()>1){
		sort(orders.begin(), orders.end(),
          [](const std::vector<literal>& a, const std::vector<literal>& b) {
					return a.size() < b.size();
				}
		);
		std::vector<literal> result;
		addSimplifiedMerge(orders[0],orders[1],result,K+1,true,false);
		orders.push_back(result);
		orders.erase(orders.begin());
		orders.erase(orders.begin());
	}

	addClause(!orders[0][K]);
}


inline int lchild(int i){
	return 2*i+1;
}

inline int rchild(int i){
	return 2*i+2;
}

inline int parent(int i){
	return (i-1)/2;
}

void SMTFormula::addAMOPBGeneralizedTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){

	int n = X.size();

	std::vector<int> * tree = new std::vector<int>[2*n-1];
	std::vector<literal> * treevars = new std::vector<literal> [2*n-1];
	std::map<int,literal> * treevarsmap = new std::map<int,literal> [n-1];

	//Fill tree nodes with coefficients
	for(int i = 0; i < n; i++){
		int idx = n-1+i;
		tree[idx].clear();
		treevars[idx].clear();
		std::map<int,int> count;
		std::map<int,literal> lit;
		for(int j = 0; j < Q[i].size(); j++){

			int q = Q[i][j];
			if(q!=0){
				if(count.find(q) == count.end()){
					count[q] = 1;
					lit[q] = X[i][j];
				}
				else{
					if(count[q]==1){
						boolvar v = newBoolVar();
						addClause(!lit[q] | v);
						lit[q] = v;
					}
					addClause(!X[i][j] | lit[q]);
					count[q] = count[q]+1;
				}
			}
		}
		for(const std::pair<int,literal> & p : lit){
			tree[idx].push_back(p.first);
			treevars[idx].push_back(p.second);
		}
		tree[idx].push_back(0);
	}

	for(int i = n-2; i >= 0; i--){
		tree[i].clear();
		for(int j = 0; j < tree[lchild(i)].size(); j++){
			for(int k = 0; k < tree[rchild(i)].size(); k++){
				int x = std::min(tree[lchild(i)][j]+tree[rchild(i)][k],K+1);
				util::insertSortedIfNotExists(tree[i],x);
			}
		}
	}

	//Simplify the root
	if(tree[0][0] <= K)
		return;

	tree[0].resize(2);
	tree[0][1]=0;

	//Encode the tree
	for(int i = n-2; i >= 0; i--){
		for(int j = 0; j < tree[i].size()-1; j++){
			boolvar v = newBoolVar();
			treevars[i].push_back(v);
			treevarsmap[i][tree[i][j]] = v;
		}
		int l = lchild(i);
		int r = rchild(i);

		for(int j = 0; j < tree[l].size(); j++){
			for(int k = 0; k < tree[r].size(); k++){
				int x = std::min(tree[l][j]+tree[r][k],K+1);
				if(treevarsmap[i].find(x) != treevarsmap[i].end()){
					if(j<tree[l].size()-1 || k < tree[r].size()-1){
						if(j == tree[l].size()-1)
							addClause(!treevars[r][k] | treevarsmap[i][x]);
						else if(k == tree[r].size()-1)
							addClause(!treevars[l][j] | treevarsmap[i][x]);
						else
							addClause(!treevars[l][j] | !treevars[r][k] | treevarsmap[i][x]);
					}
				}
			}
		}
	}


	//Negate that the sum is greater than K
	if(!tree[0].empty())
		addClause(!treevars[0][0]);

	delete [] tree;
	delete [] treevars;
	delete [] treevarsmap;
}



void SMTFormula::addAMOPBModuloTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){

	//Compute vector of moduli
	std::vector<int> moduli;
	baseSelectionMTO(Q,K,moduli);

	//Fill tree with variables and add clauses
	std::vector<std::map<int,literal> >  D(moduli.size()+1);
	nLevelsMTO(Q,X,0,Q.size(),moduli,D);

	//Ensure sum(Q*X <= k)
	comtMTO(K,moduli,D,NULL);
}

void SMTFormula::addAMOPBLocalModuloTotalizer(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){

	//Compute vector of moduli
	std::vector<int> moduli;
	baseSelectionMTO(Q,K,moduli);

	//Create the tree formula for each group
	std::map<std::pair<int,int>, std::vector<std::map<int,literal> > > constructed;
	for(int i = 0; i < Q.size(); i++){
		//Fill tree with variables and add clauses for new nodes
		std::vector<std::map<int,literal> >  D(moduli.size()+1);
		localnLevelsMTO(Q,X,0,Q.size(),moduli,D,constructed,i);
		
		for(int j = 0; j < Q[i].size(); j++){
			//Ensure sum(Q\{Q[i]} * X\{X[i]} <= K - Q[i][j])
			literal l = X[i][j];
			comtMTO(K-Q[i][j],moduli,D,&l);
		}
	}
}


void SMTFormula::baseSelectionMTO(const std::vector<std::vector<int> > & Q, int K, std::vector<int> & moduli){
	moduli.clear();
	std::list<int> q;
	for(const std::vector<int> & v : Q)
		q.insert(q.begin(),v.begin(),v.end());

	int k = K;
	while(k>1){
		int bestCandidate=-1;
		int bestCandidateVotes=0;

		for(int candidate = k; candidate >= 2; candidate--){
			int candidateVotes = 0;
			for(int x : q){
				if(x!=0 && x%candidate == 0){
					candidateVotes++;
					if(candidateVotes>bestCandidateVotes){
						bestCandidate = candidate;
						bestCandidateVotes=INT_MAX;
					}
				}
			}
			if(bestCandidate==candidate)
				bestCandidateVotes=candidateVotes;
		}

		//For inner nodes in case of very large K w.r.t. coefficient values
		if(bestCandidate==-1)
			bestCandidate=2;

		for(int & x : q)
			x/=bestCandidate;

		moduli.push_back(bestCandidate);
		k/=bestCandidate;	
	}

}


void SMTFormula::nLevelsMTO(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int lIndex, int partSize, 
	const std::vector<int> & moduli, std::vector<std::map<int,literal> > & D){
	int n = moduli.size(); //Number of modulo
	int m = partSize; //Number of variables

	//Base case, leaf
	if(m==1){
		int modProd = 1;
		for(int mo : moduli)
			modProd*=mo;

		std::vector<int> w = Q[lIndex];
		for(int i = n; i >= 0; i--){
			D[i][0]=trueVar();

			std::map<int,bool> varWithCoefCreated;

			for(int j = 0; j < w.size(); j++){
				int wmod = w[j]/modProd;

				if(wmod!=0){
					if(D[i].find(wmod) == D[i].end()){
						D[i][wmod] = X[lIndex][j]; //Initialize with the original variable itself
						varWithCoefCreated[wmod]=false;
					}
					else{
						if(!varWithCoefCreated[wmod]){ //Replace original variable by a half-reified aux variable
							boolvar v = newBoolVar();
							addClause(!D[i][wmod] | v);
							D[i][wmod] = v;
							varWithCoefCreated[wmod]=true;
						}
						addClause(!X[lIndex][j] | D[i][wmod]);
					}
				}
			}

			if(i > 0){
				for(int j = 0; j < w.size(); j++)
					w[j] %= modProd;
				modProd/=moduli[i-1];
			}
		}
	}

	//Recursive case, branch in the binary tree
	else{
		std::vector<std::map<int,literal> >  Dleft(n+1);
		std::vector<std::map<int,literal> >  Dright(n+1);

		int lSize = m/2;
		int rSize = m - m/2;
		nLevelsMTO(Q,X,lIndex, lSize, moduli,  Dleft);
		nLevelsMTO(Q,X,lIndex+lSize, rSize, moduli, Dright);



		std::vector<literal> c(n);

		
		bool thisLevelHasCarry = false;
		bool prevLevelHasCarry;
		for(int h = 0; h < n; h++){
			prevLevelHasCarry = thisLevelHasCarry;
			thisLevelHasCarry = false;
			D[h][0] = trueVar();
			c[h] = newBoolVar();

			std::map<int,literal>::iterator i, j;

			for(i = Dleft[h].begin(); i != Dleft[h].end(); i++){
				for(j = Dright[h].begin(); j != Dright[h].end(); j++){
					int wi = i->first;
					literal xi = i->second;


					int wj = j->first;
					literal xj = j->second;

					int sum = wi + wj; 


					clause base; //Children in a LHS of a implication, unless 0 that are ommitted
					if(wi>0)
						base |= !xi;
					if(wj>0)
						base |= !xj;

					if(sum>0){ //Clauses for sum==0 trivially satisfied
						//Clauses for lowest and intermediate digits
						if(sum<moduli[h])
							addClause(base | MTOVar(D[h],sum) | c[h]);
						else{
							thisLevelHasCarry=true;
							addClause(base | c[h]);
							if(sum > moduli[h] && sum%moduli[h]>0)
								addClause(base | MTOVar(D[h],sum%moduli[h]));
						}
					}
					

					//Clauses only for intermediate digits
					if(h>0 && prevLevelHasCarry){ //If previous level never has carry, clauses trivially satisfied
						sum++; //Last carry added, sum will not be 0
						if(sum < moduli[h])
							addClause(base | !c[h-1] | MTOVar(D[h],sum) | c[h]);
						else {
							thisLevelHasCarry=true;
							addClause(base | !c[h-1] | c[h]);
							if(sum > moduli[h] && sum%moduli[h]>0)
								addClause(base | !c[h-1] | MTOVar(D[h],sum%moduli[h]));
						}
					}
				}
			}		
			if(!thisLevelHasCarry)
				addClause(!c[h]);
		}

		prevLevelHasCarry = thisLevelHasCarry;

		//Clauses of the uppermost digits
		D[n][0] = trueVar();
		std::map<int,literal>::iterator i, j;
		for(i = Dleft[n].begin(); i != Dleft[n].end(); i++){
			for(j = Dright[n].begin(); j != Dright[n].end(); j++){
				int wi = i->first;
				literal xi = i->second;

				int wj = j->first;
				literal xj = j->second;

				int sum = wi + wj; 

				clause base; //Children in a LHS of a implication, unless 0 that are ommitted
				if(wi>0)
					base |= !xi;
				if(wj>0)
					base |= !xj;

				if(sum!=0)
					addClause(base | MTOVar(D[n],sum));
				
				if(prevLevelHasCarry)
					addClause(base | !c[n-1] | MTOVar(D[n],sum+1));
			}
		}
	}

}

/*
	Pre: 
		- Q is not empty
		- Q and X have the same size
		- Q[i] and X[i] are not empty and have the same size, for all i in 0..Q.size()-1
		- Q[i] contains no repeated values, for all i in 0..Q.size()-1
		- lIndex >= 0
		- partSize >=1
		- lIndex + partSize < Q.size()
		-  0 <= ommittedLeaf < Q.size() or ommittedLeaf==-1
	Post:
		- builds and encodes the n-Level modulo totalizer root node of the subtree with leaves between Q[lIndex] and Q[lIndex+partSize-1]
		- if ommittedLeaf==-1, builds the full tree
			-otherwise, ommits the indicated leaf (used in local encoding)
*/
void SMTFormula::localnLevelsMTO(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int lIndex, int partSize, 
	const std::vector<int> & moduli, std::vector<std::map<int,literal> >  & D, 
	std::map<std::pair<int,int>, std::vector<std::map<int,literal> > > & constructed, int ommittedLeaf){
	int n = moduli.size(); //Number of modulo
	int m = partSize; //Number of variables

	//In local encoding (ommittedLeaf!=-1), if already constructed, retrieve and return
	//A tree containing an ommitted leaf is never reused
	if(ommittedLeaf!=-1 && (ommittedLeaf< lIndex || ommittedLeaf >= lIndex+ partSize)){
		std::pair<int,int> p(lIndex,partSize);
		std::map<std::pair<int,int>, std::vector<std::map<int,literal> > >::iterator it = constructed.find(p);
		if(it != constructed.end()){
			D = it->second;
			return;
		}
	}

	//Base case, leaf. If pre is satisfied, an ommitted leaf should never reach this point
	if(m==1){
		int modProd = 1;
		for(int mo : moduli)
			modProd*=mo;

		std::vector<int> w = Q[lIndex];
		for(int i = n; i >= 0; i--){
			D[i][0]=trueVar();

			std::map<int,bool> varWithCoefCreated;

			for(int j = 0; j < w.size(); j++){
				int wmod = w[j]/modProd;

				if(wmod!=0){
					if(D[i].find(wmod) == D[i].end()){
						D[i][wmod] = X[lIndex][j]; //Initialize with the original variable itself
						varWithCoefCreated[wmod]=false;
					}
					else{
						if(!varWithCoefCreated[wmod]){ //Replace original variable by a half-reified aux variable
							boolvar v = newBoolVar();
							addClause(!D[i][wmod] | v);
							D[i][wmod] = v;
							varWithCoefCreated[wmod]=true;
						}
						addClause(!X[lIndex][j] | D[i][wmod]);
					}
				}
			}

			if(i > 0){
				for(int j = 0; j < w.size(); j++)
					w[j] %= modProd;
				modProd/=moduli[i-1];
			}
		}
	}

	//Recursive case, branch in the binary tree
	else{
		int lSize = m/2;
		int rSize = m - m/2;
		int rlIndex = lIndex+lSize;

		//If left child not present, return right child
		if(lSize==1 && ommittedLeaf==lIndex){
			localnLevelsMTO(Q,X,rlIndex, rSize, moduli, D,constructed,ommittedLeaf);
			return;
		}
		//If right child not present, return left child
		else if(rSize==1 && ommittedLeaf==rlIndex){
			localnLevelsMTO(Q,X,lIndex, lSize, moduli, D,constructed,ommittedLeaf);
			return;
		}

		std::vector<std::map<int,literal> >  Dleft(n+1);
		std::vector<std::map<int,literal> >  Dright(n+1);

		localnLevelsMTO(Q,X,lIndex, lSize, moduli,  Dleft,constructed,ommittedLeaf);
		localnLevelsMTO(Q,X,rlIndex, rSize, moduli, Dright,constructed,ommittedLeaf);

		std::vector<literal> c(n);
		
		bool thisLevelHasCarry = false;
		bool prevLevelHasCarry;
		for(int h = 0; h < n; h++){
			prevLevelHasCarry = thisLevelHasCarry;
			thisLevelHasCarry = false;
			D[h][0] = trueVar();
			c[h] = newBoolVar();

			std::map<int,literal>::iterator i, j;

			for(i = Dleft[h].begin(); i != Dleft[h].end(); i++){
				for(j = Dright[h].begin(); j != Dright[h].end(); j++){
					int wi = i->first;
					literal xi = i->second;


					int wj = j->first;
					literal xj = j->second;

					int sum = wi + wj; 


					clause base; //Children in a LHS of a implication, unless 0 that are ommitted
					if(wi>0)
						base |= !xi;
					if(wj>0)
						base |= !xj;

					if(sum>0){ //Clauses for sum==0 trivially satisfied
						//Clauses for lowest and intermediate digits
						if(sum<moduli[h])
							addClause(base | MTOVar(D[h],sum) | c[h]);
						else{
							thisLevelHasCarry=true;
							addClause(base | c[h]);
							if(sum > moduli[h] && sum%moduli[h]>0)
								addClause(base | MTOVar(D[h],sum%moduli[h]));
						}
					}
					

					//Clauses only for intermediate digits
					if(h>0 && prevLevelHasCarry){ //If previous level never has carry, clauses trivially satisfied
						sum++; //Last carry added, sum will not be 0
						if(sum < moduli[h])
							addClause(base | !c[h-1] | MTOVar(D[h],sum) | c[h]);
						else {
							thisLevelHasCarry=true;
							addClause(base | !c[h-1] | c[h]);
							if(sum > moduli[h] && sum%moduli[h]>0)
								addClause(base | !c[h-1] | MTOVar(D[h],sum%moduli[h]));
						}
					}
				}
			}		
			if(!thisLevelHasCarry)
				addClause(!c[h]);
		}

		prevLevelHasCarry = thisLevelHasCarry;

		//Clauses of the uppermost digits
		D[n][0] = trueVar();
		std::map<int,literal>::iterator i, j;
		for(i = Dleft[n].begin(); i != Dleft[n].end(); i++){
			for(j = Dright[n].begin(); j != Dright[n].end(); j++){
				int wi = i->first;
				literal xi = i->second;

				int wj = j->first;
				literal xj = j->second;

				int sum = wi + wj; 

				clause base; //Children in a LHS of a implication, unless 0 that are ommitted
				if(wi>0)
					base |= !xi;
				if(wj>0)
					base |= !xj;

				if(sum!=0)
					addClause(base | MTOVar(D[n],sum));
				
				if(prevLevelHasCarry)
					addClause(base | !c[n-1] | MTOVar(D[n],sum+1));
			}
		}
	}

	//In local encoding and does not contain ommitted leaf, store subtree
	if(ommittedLeaf!=-1 && (ommittedLeaf< lIndex || ommittedLeaf >= lIndex+ partSize)){
		std::pair<int,int> p(lIndex,partSize);
		constructed[p] = D;
	}

}

literal SMTFormula::MTOVar(std::map<int,literal> & m, int w){
	if(m.find(w)==m.end()){
		boolvar x = newBoolVar();
		m[w]=x;
		return x;
	}
	else
		return m[w];
}


void SMTFormula::comtMTO(int K, const std::vector<int> & moduli, const std::vector<std::map<int,literal> > & D,  literal * localLit){

	int n = moduli.size();
	std::vector<int> k(n+1);
	int modProd = 1;
	for(int lambda : moduli)
		modProd*=lambda;

	for(int i = n; i >=0; i--){
		k[i] = K / modProd;
		K%=modProd;
		if(i>0)
			modProd/=moduli[i-1];
	}


	clause c;
	if(localLit != NULL)
		c=!(*localLit);

	for(int i = n; i >= 0; i--){
		if(i<n && k[i+1]!=0){
			std::map<int,literal>::const_iterator it = D[i+1].find(k[i+1]);
			if(it==D[i+1].end())
				break; //If not possible to be equal in this level, no need to look at the folowing levels
			else
				c|= !it->second;
		}
		for(const std::pair<int,literal> & p : D[i])
			if(p.first > k[i])
				addClause(c | !p.second);
	}
}






void SMTFormula::addAMOPBLocalPolynomialWatchdog3(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K)
{
	int n = Q.size();

	K+=1;

	//Maximum of each AMO group
	std::vector<int> max_coefs(Q.size(),0);
	//Total maximum
	int max = 0;
	//Sum of maximum coefficients
	int sum_max_coefs = 0;

	for(int i = 0; i < Q.size(); i++){
		for(int j = 0; j < Q[i].size(); j++){
			if(Q[i][j] > max)
				max = Q[i][j];
			if(Q[i][j] > max_coefs[i])
				max_coefs[i] =Q[i][j];
		}
		sum_max_coefs+=max_coefs[i];
	}


	int p = (int)floor(log2(max));
	int p2 = 1<<p; // 2^p

	std::vector<literal> * B = new std::vector<literal>[p+1]; //Buckets

	std::vector<std::pair<int,std::set<int> > > *  B_inputs = new std::vector<std::pair<int,std::set<int> > > [p+1]; //Bucket inputs

	int ** indexesInBuckets = new int * [p+1];//Store which index in each bucket occupies each group
	for(int i = 0; i < p+1; i++){
		indexesInBuckets[i] = new int[Q.size()];
		for(int j = 0; j < Q.size(); j++)
			indexesInBuckets[i][j] = -1;
	}

	std::map<std::set<int>, literal> * constructedYs = new std::map<std::set<int>, literal>[Q.size()];

	//Construct the inputs of the buckets reusing the Y variables already constructed
	for(int k = 0; k <= p; k++){
		for(int i = 0; i < n; i++){

			std::set<int> inputs;
			for(int j = 0; j < Q[i].size(); j++)
				if(util::nthBit(Q[i][j],k))
					inputs.insert(j);

			if(!inputs.empty()){
				literal y;
				if(inputs.size()==1) //If just one input variable in the group, no need to create a new variable
					y = X[i][*(inputs.begin())];
				else{
					
					std::map<std::set<int>, literal>::iterator it = constructedYs[i].find(inputs);
					if(it==constructedYs[i].end()){ //If not constructed before, add half reifications and store
						y = newBoolVar();
						for(int j : inputs)
							addClause(!X[i][j] | y);
						constructedYs[i][inputs] = y;
					}
					else //If already constructed, retrieve
						y= it->second;
				}
				indexesInBuckets[k][i]=B[k].size();
				B[k].push_back(y);
				B_inputs[k].push_back(std::pair<int,std::set<int> >(i,inputs));
			}
		}
	}


	std::map<std::set<std::pair<int,int> >, std::vector<literal> > constructedTotalizers;
	std::map<std::set<std::pair<int,int> >, std::vector<literal> > * constructedMergers = new std::map<std::set<std::pair<int,int> >, std::vector<literal> >[p]; //Bucket 0 does not have a merger, hence size is not p+1.


	//Construct circuits for each group. 
	for(int i = 0; i < Q.size(); i++){
		
		//Complete de circuit with the particlar mergers for each variable 'x_'j' or each variable in group 'i'
		for(int j = 0; j < Q[i].size(); j++){

			//Compute the new normalized K, and T
			int Kj = K - Q[i][j];


			//If the sum of the coefficients of the remaining AMO groups is <= K - Q[i][j],
				// no need to encode any constraintfor this group
			if(sum_max_coefs - max_coefs[i] < Kj)
				continue;

			int m = Kj / p2;
			if(Kj%p2 != 0)
				m++;
			int T = m*p2 - Kj;

			std::set<std::pair<int,int> > usedLits;
			std::vector<literal> S, Shalf;
			//For each bucket
			for(int k = 0; k <= p; k++){

				//Update input literals util now
				for(const std::pair<int,std::set<int> > & p : B_inputs[k]){
					if(p.first != i){
						for(int l : p.second)
							usedLits.insert(std::pair<int,int>(p.first,l));
					}
				}

				std::vector<literal> U;
				if(!B[k].empty()){
					int ommittedLeaf = indexesInBuckets[k][i];
					if(!(B[k].size()==1 && ommittedLeaf!=-1))
						addTotalizer(B[k],B_inputs[k],U,0,B[k].size(),ommittedLeaf,constructedTotalizers);
				}

				if(k==0){
					S=U;
				}
				else{

					//Get the output of the left merger
					int Tkm1 = T&(1<<(k-1));
					int firstBit;
					if(Tkm1){//If the bit of T in the previous bucket is 1, shift
						firstBit=0;
						Shalf.resize((S.size()+1)/2);
						usedLits.insert(std::pair<int,int>(-1,Tkm1)); //If a 1 was considered to get Shalf, this must be added
					}
					else{
						firstBit = 1;
						Shalf.resize(S.size()/2);
					}

					for(int l = firstBit; l < S.size(); l+=2)
						Shalf[l/2]=S[l];


					//Build or reuse the merger
					std::map<std::set<std::pair<int,int> >, std::vector<literal> >::iterator it;
					it = constructedMergers[k-1].find(usedLits);
					if(it == constructedMergers[k-1].end()){
						S.clear();
						addQuadraticMerge(U,Shalf,S);
						constructedMergers[k-1][usedLits]=S;
					}
					else{
						S = it->second;
					}
				}
			}

			//Add the clause forbidding X[i][j] to be true if sum exceeded
			//The last bit never shifts
			addClause(!X[i][j] | !S[m-1]);
		}
	}


	delete [] B;
	delete [] B_inputs;

	for(int i = 0; i < p+1; i++)
		delete []indexesInBuckets[i];
	
	delete [] indexesInBuckets;
	delete [] constructedYs;
	delete [] constructedMergers;
}






void SMTFormula::addAMOPBLocalPolynomialWatchdog2(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K)
{
	int n = Q.size();

	//Maximum of each AMO group
	std::vector<int> max_coefs(Q.size(),0);
	//Total maximum
	int max = 0;
	//Sum of maximum coefficients
	int sum_max_coefs = 0;

	for(int i = 0; i < Q.size(); i++){
		for(int j = 0; j < Q[i].size(); j++){
			if(Q[i][j] > max)
				max = Q[i][j];
			if(Q[i][j] > max_coefs[i])
				max_coefs[i] =Q[i][j];
		}
		sum_max_coefs+=max_coefs[i];
	}

	int p = (int)floor(log2(max));


	std::vector<std::vector<literal> > B(p+1); //Buckets
	std::vector<std::vector<std::pair<int,std::set<int> > > > B_inputs(p+1); //Bucket inputs
	std::vector<std::vector<int> > indexesInBuckets(p+1,std::vector<int>(Q.size(),-1)); //Store which index in each bucket occupies each group

	std::vector<std::map<std::set<int>, literal> > constructedYs(Q.size());

	//Construct the inputs of the buckets reusing the Y variables already constructed
	for(int k = 0; k <= p; k++){
		for(int i = 0; i < n; i++){

			std::set<int> inputs;
			for(int j = 0; j < Q[i].size(); j++)
				if(util::nthBit(Q[i][j],k))
					inputs.insert(j);

			if(!inputs.empty()){
				literal y;
				if(inputs.size()==1) //If just one input variable in the group, no need to create a new variable
					y = X[i][*(inputs.begin())];
				else{
					
					std::map<std::set<int>, literal>::iterator it = constructedYs[i].find(inputs);
					if(it==constructedYs[i].end()){ //If not constructed before, add half reifications and store
						y = newBoolVar();
						for(int j : inputs)
							addClause(!X[i][j] | y);
						constructedYs[i][inputs] = y;
					}
					else //If already constructed, retrieve
						y= it->second;
				}
				indexesInBuckets[k][i]=B[k].size();
				B[k].push_back(y);
				B_inputs[k].push_back(std::pair<int,std::set<int> >(i,inputs));
			}
		}
	}


	std::map<std::set<std::pair<int,int> >,  std::vector<literal> > constructedTotalizers;

	//Construct circuit for each group. The group 'i' is properly removed in the i-th group
	for(int i = 0; i < Q.size(); i++){
		std::vector<literal> S, Shalf;
		std::vector<literal> remainder(p);

		for(int k = 0; k <= p; k++){
			

			S.clear();
			std::vector<literal> U;
			if(!B[k].empty()){
				int ommittedLeaf = indexesInBuckets[k][i];
				if(!(B[k].size()==1 && ommittedLeaf!=-1))
					addTotalizer(B[k],B_inputs[k],U,0,B[k].size(),ommittedLeaf,constructedTotalizers);
			}

			if(k==0)
				S=U;
			else{
				addQuadraticMerge(U,Shalf,S);
			}

			if(k<p){
				remainder[k] = newBoolVar();
				for(int bit = 0; bit < S.size(); bit+=2){
					if(bit+1 < S.size())
						addClause(!S[bit] | S[bit+1]  | remainder[k]);
					else
						addClause(!S[bit] | remainder[k]);
				}
			}

			Shalf.resize(S.size()/2);
			for(int l = 1; l < S.size(); l+=2)
				Shalf[l/2]=S[l];
		}
		//Add the clauses for each variable in group 'i'
		for(int j = 0; j < Q[i].size(); j++){
			int K2 = K - Q[i][j]; //Obtain the K when X[i][j] is true

			//If the sum of the coefficients of the remaining AMO groups is <= K - Q[i][j],
			// no need to encode any constraintfor this group
			if(sum_max_coefs - max_coefs[i] <= K2)
				continue;
			
			//obtain binary representation of K2 and enforce that if the sum is greater or equal than K2, then X[i][j] must be false
			int p2 = (1<<p); //2^p
			if(S.size() > K2/p2)
				addClause(!S[K2/p2] | !X[i][j]);

			clause c;
			if(K2/p2 > 0) 
				c|= !S[K2/p2 -1]; //TODO: vigilar amb aquest -1
			K2%=p2;
			p2/=2;
			for(int k = p-1; k >= 0; k--){
				if(K2 / p2==0)
					addClause(c | !remainder[k] | !X[i][j]);
				else
					c|= !remainder[k];
				K2%=p2;
				p2/=2;
			}
		}		
	}
}


literal SMTFormula::addPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter){
	int n = Q.size();

	//This encoding is for < K instead of <= K
	K+=1;

	int max = 0;
	for(const std::vector<int> & q : Q)
		for(int qi : q)
			if(qi > max)
				max = qi;

	int p = (int)floor(log2(max));
	int p2 = (int) exp2(p);
	int m = K / p2;
	if(K%p2 != 0)
		m++;
	int T = (m*p2) - K;

	std::vector<std::vector<literal> > B(p+1); //Buckets

	for(int k = 0; k <= p; k++){
		for(int i = 0; i < n; i++){
			bool used = false;
			bool created = false;
			literal vk;
			for(int j = 0; j < Q[i].size(); j++){
				if(util::nthBit(Q[i][j],k)){
					if(!used){
						vk = X[i][j];
						used = true;
					}
					else{
						if(!created){
							boolvar aux = newBoolVar();
							addClause(!vk | aux);
							vk = aux;
							created=true;
						}
						addClause(!X[i][j] | vk);
					}
				}
			}
			if(used) {
				B[k].push_back(vk);
			}
		}
	}

	std::vector<literal> S, Shalf;
	for(int i = 0; i <= p; i++){
		S.clear();
		std::vector<literal> U;
		if(useSorter)
			addSorting(B[i],U,true,false);
		else
			addTotalizer(B[i],U);
		if(i==0)
			S=U;
		else{
			if(useSorter)
				addMerge(U,Shalf,S,true,false);
			else
				addQuadraticMerge(U,Shalf,S);
		}
		if(util::nthBit(T,i))
			S.insert(S.begin(),trueVar());

		Shalf.resize(S.size()/2);
		for(int i = 1; i < S.size(); i+=2)
			Shalf[i/2]=S[i];
	}
	return S[m-1];
}



void SMTFormula::addAMOPBGlobalPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter){
	if(K==0){
		for(const std::vector<literal> & v : X)
			for(const literal & l : v)
				addClause(!l);
		return;
	}
	else if(K < 0){
		addEmptyClause();
		return;
	}
	int n = Q.size();

	int maxsum = 0;
	for(int i = 0; i < n; i++)
		maxsum+= *(max_element(Q[i].begin(),Q[i].end()));

	if(maxsum <= K)
		return;

	if(n==1){
		clause c;
		for(int i = 0; i < Q[0].size(); i++)
			if(Q[0][i] >= K)
				c |= X[0][i];
		addClause(c);
		return;
	}

	addClause(!addPolynomialWatchdog(Q,X,K,useSorter));
}

void SMTFormula::addAMOPBLocalPolynomialWatchdog(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K, bool useSorter){
	if(K==0){
		for(const std::vector<literal> & v : X)
			for(const literal & l : v)
				addClause(!l);
		return;
	}
	else if(K < 0){
		addEmptyClause();
		return;
	}
	int n = Q.size();

	int maxsum = 0;
	for(int i = 0; i < n; i++)
		maxsum+= *(max_element(Q[i].begin(),Q[i].end()));

	if(maxsum <= K)
		return;

	if(n==1){
		clause c;
		for(int i = 0; i < Q[0].size(); i++)
			if(Q[0][i] >= K)
				c |= X[0][i];
		addClause(c);
		return;
	}

	for(int i = 0; i < n; i++){
		std::vector<std::vector<int> > Q2 = Q;
		std::vector<std::vector<literal> > X2 = X;
		Q2[i]=Q2[Q2.size()-1];
		Q2.resize(Q2.size()-1);
		X2[i]=X2[X2.size()-1];
		X2.resize(X2.size()-1);
		for(int j = 0; j < Q[i].size(); j++){
			std::map<int,literal> watchdog;
			if(watchdog.find(Q[i][j]) == watchdog.end())
				watchdog[Q[i][j]] = addPolynomialWatchdog(Q2,X2,K-Q[i][j],useSorter);
			addClause(!watchdog[Q[i][j]] | !X[i][j]);
		}
	}
}



void SMTFormula::addAMOPBReducedGeneralizedGeneralizedTotalizer(std::vector<std::vector<int> >  Q, std::vector<std::vector<literal> > X, int K, bool reduce){
    //  Badly co-sort Q and X.
    for(int i=0; i<Q.size(); i++) {
        //  Cosort Q[i] and X[i] by insertion sort. 
        for(int j=1; j<Q[i].size(); j++) {
            for(int k=j-1; k>=0; k--) {
                if(Q[i][k+1]<Q[i][k]) {
                    //  Swap
                    int tmpq=Q[i][k];
                    Q[i][k] = Q[i][k+1];
                    Q[i][k+1] = tmpq;
                    
                    literal tmpx=X[i][k];
                    X[i][k]= X[i][k+1];
                    X[i][k+1]= tmpx;
                }
            }
        }
    }
    
    RGGTNode * tree = new RGGTNode[2*X.size()-1];
    bool repeatReduce=true;
    int tree_size, n;

    while(repeatReduce) {
        repeatReduce=false;
        n = X.size();
        tree_size = n;

        //  Leaf nodes on the left (indexes 0 to n-1) 
        
        //  Fill leaf nodes with values
        //  Literals left empty for now. 

         //  Create intermediate node with greatest proportional reduction in values compared to the product of the two children.
        std::vector<RGGTNode*> todo(n);  // copy tree into todo.


        for(int i = 0; i < n; i++) {
        	tree[i] = RGGTNode();           
            tree[i].values.push_back(0);
            todo[i] = tree + i;
            for(int j = 0; j < Q[i].size(); j++) {
                if(Q[i][j]!=0 && (j==0 || Q[i][j]!=Q[i][j-1])) {
                    //  Non-zero coeff and different to previous coeff.
                    tree[i].values.push_back(Q[i][j]);
                }
            }
        }
        
        
        std::map<std::pair<RGGTNode *,RGGTNode *>, double> cached_rat;
        bool first_pass = true;
        while(todo.size()>1) {
            //Compute new ratios
            for(int i=0; i<todo.size()-1; i++) {
            	//If first, time, compute all the ratios
            	if(first_pass){
	                for(int j=i+1; j<todo.size(); j++) {
	                    std::vector<int> testvals;
	                    mergeValues(todo[i]->values, todo[j]->values, testvals, K);
	                    double rat=((double)testvals.size())/(todo[i]->values.size()*todo[j]->values.size());
	                    cached_rat[std::pair<RGGTNode *,RGGTNode *>(todo[i], todo[j])] = rat;
	                }
	            }
	            //Otherwise, there is only need to compute the ratio w.r.t. the newly inserted node
	            else{
	            	int j = todo.size()-1;
	            	std::vector<int> testvals;
	                mergeValues(todo[i]->values, todo[j]->values, testvals, K);
	                double rat=((double)testvals.size())/(todo[i]->values.size()*todo[j]->values.size());
	                cached_rat[std::pair<RGGTNode *,RGGTNode *>(todo[i], todo[j])] = rat;
	            }
            }
            first_pass=false;

            //Find pair of nodes with the best ratio
            int i1=-1;
            int i2=-1;
            double bestRatio=std::numeric_limits<double>::max();
            for(int i=0; i<todo.size()-1; i++) {
	            for(int j=i+1; j<todo.size(); j++) {
	            	double rat = cached_rat[std::pair<RGGTNode *,RGGTNode *>(todo[i], todo[j])];
	                if(rat<bestRatio) {
	                    i1=i;
	                    i2=j;
	                    bestRatio=rat;
	                }
	            }
            }

       
                        

            tree[tree_size]=(RGGTNode(todo[i1],todo[i2]));
            tree_size++;
            RGGTNode * n3 = tree + tree_size-1;
            todo[i1]->parent=n3;
            todo[i2]->parent=n3;
            
            mergeValues(todo[i1]->values, todo[i2]->values, n3->values, K);  // Populate n3.values
           
            todo.erase(todo.begin()+i2);
            todo.erase(todo.begin()+i1);
            todo.push_back(n3);
        }
        
        //  Now tree has values, but intervals and literals are empty
        //  except bottom layer which has literals populated. 
        
        //  Start to populate intervals from the root. 
        
        RGGTNode * root= tree + tree_size - 1;
        
        //  Check the tree is not trivial here...
        
        
        long lb=root->values[0];
        long ub=root->values[root->values.size()-1];
        if(ub==K+1) {
            ub=root->values[root->values.size()-2];
        }
        root->intervals.push_back(std::pair<int,int>(lb, ub));
        if(root->values[root->values.size()-1]==K+1) {
            root->intervals.push_back(std::pair<int,int>(K+1, K+1));
        }
        
        // Go down the tree from root to leaves, creating the interval sets.
        // Parent must be processed before its children.
        
        for(int i=tree_size-2; i>=0; i--) {
            tree[i].makeIntervals(K, reduce);
        }
        
        // Check for trivial leaf nodes 
        // This could be much more interesting. Leaf nodes that have non-singleton
        // intervals could be have coefficients changed to turn the interval into a 
        // single value. 
        
        for(int i=n-1; i>=0; i--) {
            if(tree[i].intervals.size()==1) {
                //  Single interval. Remove the AMO group.
                //  This definitely helps -- reduces number of internal tree nodes. 
                Q.erase(Q.begin()+i);
                X.erase(X.begin()+i);
                repeatReduce=true;
            }
            //  I suspect the following may not help except by
            //  changing the heuristic order of combining nodes. 
            else if(tree[i].intervals.size()<tree[i].values.size()) {
                std::vector<std::pair<int,int> > intervals=tree[i].intervals;
                int intervalidx=0;
                
                for(int qidx=0; qidx<Q[i].size(); qidx++) {
                    int value=Q[i][qidx];
                    std::pair<int,int> interval=intervals[intervalidx];
                    while(value>interval.second) {
                        intervalidx++;
                        interval=intervals[intervalidx];
                    }

                    //assert value>=interval.lower && value<=interval.upper;
                    if(value!=interval.first) {
                        if(interval.first==0) {
                            //  Indistinguishable from 0 -- bin the term. 
                            Q[i].erase(Q[i].begin()+qidx);
                            X[i].erase(X[i].begin()+qidx);
                            qidx--;
                        }
                        else {
                            Q[i][qidx] = interval.first;  //  Heuristic -- push indistinguishable values down to be the same value.
                        }
                    }
                }
                
                repeatReduce=true;
            }
        }
        
        //if(repeatReduce) System.out.println("Restarting");
    }  // End of while loop.
    
    //  Encode the tree.
    //  SAT variables correspond to intervals (>= lower bound ofinterval).
    



    for(int i=n; i<tree_size; i++) {
        //assert tree[i].intervals[0].lower==0;
        tree[i].literals.push_back(trueVar());
        
        //  Skip the first interval. 
        for(int j=1; j<tree[i].intervals.size(); j++) {
            boolvar v = newBoolVar();
            tree[i].literals.push_back(v);
        }
    }
    
    //  Fill in literals for the leaf nodes.
    for(int i=0; i<n; i++) {
        RGGTNode * l= tree + i;
        
        for(int j=0; j<l->intervals.size(); j++) {
            if(l->intervals[j].first==0) {
                l->literals.push_back(trueVar());
            }
            else {
                //  Find all coeffs that fall within the l->intervals[j]

                
                int count=0;
                literal last;
                
                for(int k=0; k<Q[i].size(); k++) {
                    if(Q[i][k]>=l->intervals[j].first && Q[i][k]<=l->intervals[j].second) {
                        count++;
                        last=X[i][k];
                    }
                }
                
                if(count>1) {
                    boolvar aux=newBoolVar();
                    l->literals.push_back(aux);
                    
                    for(int k=0; k<Q[i].size(); k++) {
                        if(Q[i][k]>=l->intervals[j].first && Q[i][k]<=l->intervals[j].second) {
                            addClause(!X[i][k] | aux);
                        }
                    }
                }
                else {
                    //assert count==1;
                    l->literals.push_back(last);
                }
            }
        }
        //assert l.literals.size()==l.intervals.size();
    }
    
    for(int i=n; i<tree_size; i++) {
        RGGTNode * l=tree[i].left;
        RGGTNode * r=tree[i].right;
        
        for(int j=0; j<l->intervals.size(); j++) {
            for(int k = 0; k < r->intervals.size(); k++) {
                // Calculate the value from the lower bounds of the two intervals. 
                int x = std::min(l->intervals[j].first+r->intervals[k].first,K+1);
                
                //  Find the interval that x belongs to in the parent.
                std::vector<std::pair<int,int> > & parint=tree[i].intervals;
                for(int parintidx=0; parintidx<parint.size(); parintidx++) {
                    if(x>=parint[parintidx].first && x<=parint[parintidx].second) {
                        addClause(!l->literals[j] | !r->literals[k] |  tree[i].literals[parintidx]);
                        break;
                    }
                }
            }
        }
    }
    
    // Assert that the sum is <=K
    int i=tree_size-1;
    //assert tree.get(i).intervals.get(tree.get(i).intervals.size()-1).lower==K+1;
    addClause(!tree[i].literals[tree[i].literals.size()-1]);
    delete [] tree;
}

void SMTFormula::mergeValues(const std::vector<int> & n1, const std::vector<int> & n2, std::vector<int> & n3, int K) {
	std::set<int> s;
	for(int j=0; j < n1.size(); j++)
		for(int k = 0; k < n2.size(); k++) 
			s.insert(std::min(n1[j]+n2[k], K+1));
	n3.clear();
	n3.insert(n3.begin(),s.begin(),s.end());
}



void SMTFormula::addOrderEncoding(int x, std::vector<literal> & lits){

	lits.resize(x);
	lits[0]=newBoolVar();
	for(int i = 1; i < x; i++){
		lits[i] = newBoolVar();
		addClause(!lits[i] | lits[i-1]);
	}
}



void SMTFormula::addTwoComparator(const literal &x1, const literal &x2, literal &y1, literal &y2, bool leqclauses, bool geqclauses){
	y1 = newBoolVar();
	y2 = newBoolVar();

	if(leqclauses){
		addClause(!x1 | y1);
		addClause(!x2 | y1);
		addClause(!x1 | ! x2 | y2);
	}

	if(geqclauses){
		addClause(x1 | !y2);
		addClause(x2 | !y2);
		addClause(x1 | x2 | !y1);
	}
}

void SMTFormula::addQuadraticMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y){
	if(x1.empty())
		y = x2;
	else if(x2.empty())
		y = x1;
	else{
		y.resize(x1.size() + x2.size());
		for(int i = 0; i < x1.size() + x2.size(); i++)
			y[i] = newBoolVar();
		for(int i = 0; i < x1.size(); i++){
			addClause(!x1[i] | y[i]);
			for(int j = 0; j < x2.size(); j++)
				addClause(!x1[i] | !x2[j] | y[i+j+1]);
		}
		for(int i = 0; i < x2.size(); i++)
			addClause(!x2[i] | y[i]);
	}
}

void SMTFormula::addMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y, bool leqclauses, bool geqclauses){
	int a = x1.size();
	int b = x2.size();

	if(a==0 && b==0){
		y.clear();
		return;
	}

	y.resize(a+b);

	if(a==1 && b==1)
		addTwoComparator(x1[0],x2[0],y[0],y[1],leqclauses,geqclauses);
	else if(a == 0)
		y = x2;
	else if(b == 0)
		y = x1;
	else{
		std::vector<literal> x1even, x1odd, x2even, x2odd;
		for(int i = 0; i < a-1; i+=2){
				x1even.push_back(x1[i]);
				x1odd.push_back(x1[i+1]);
		}
		if(a%2==1)
			x1even.push_back(x1[a-1]);

		for(int i = 0; i < b-1; i+=2){
				x2even.push_back(x2[i]);
				x2odd.push_back(x2[i+1]);
		}
		if(b%2==1)
			x2even.push_back(x2[b-1]);

		std::vector<literal> zeven;
		std::vector<literal> zodd;

		addMerge(x1even, x2even, zeven,leqclauses,geqclauses);
		addMerge(x1odd, x2odd,zodd,leqclauses,geqclauses);

		std::vector<literal> z(a+b);
		if(a%2==0){
			if(b%2==0){
				for(int i = 0; i < (a+b)/2; i++)
					z[2*i] = zeven[i];

				for(int i = 0; i < (a+b)/2; i++)
					z[2*i + 1] = zodd[i];

				y[0] = z[0];
				y[a+b-1] = z[a+b-1];
				for(int i = 1; i < a+b-2; i+=2)
					addTwoComparator(z[i],z[i+1],y[i],y[i+1],leqclauses,geqclauses);

			}else{
				for(int i = 0; i < (a+b)/2 + 1; i++)
					z[2*i] = zeven[i];

				for(int i = 0; i < (a+b)/2; i++)
					z[2*i + 1] = zodd[i];

				y[0] = z[0];
				for(int i = 1; i < a+b-1; i+=2)
					addTwoComparator(z[i],z[i+1],y[i],y[i+1],leqclauses,geqclauses);

			}
		}
		else{ //a%2==1
			if(b%2==0)
				addMerge(x2,x1,y,leqclauses,geqclauses);
			else{
				for(int i = 0; i < (a+1)/2; i++)
					z[2*i] = zeven[i];
				for(int i = 0; i < (b+1)/2; i++)
					z[a + 2*i] = zeven[(a+1)/2 + i];

				for(int i = 0; i < a/2; i++)
					z[2*i+1] = zodd[i];
				for(int i = 0; i < b/2; i++)
					z[a + 2*i+1] = zodd[a/2 + i];

				y[0] = z[0];
				y[a+b-1] = z[a+b-1];
				for(int i = 1; i < a+b-2; i+=2)
					addTwoComparator(z[i],z[i+1],y[i],y[i+1],leqclauses,geqclauses);

			}
		}
	}
}


void SMTFormula::addSimplifiedMerge(const std::vector<literal> &x1, const std::vector<literal> &x2, std::vector<literal> &y, int c, bool leqclauses, bool geqclauses){
	int a = x1.size();
	int b = x2.size();

	if(a==0 && b==0){
		y.clear();
		return;
	}

	if(c==0){
		y.clear();
		return;
	}


	if(a==1 && b==1 && c==1){
		y.resize(c);
		y[0] = newBoolVar();
		if(leqclauses){
			addClause(!x1[0] | y[0]);
			addClause(!x2[0] | y[0]);
		}
		if(geqclauses)
			addClause(x1[0] | x2[0] | !y[0]);
	}
	else if(a > c)
		addSimplifiedMerge(std::vector<literal>(x1.begin(),x1.begin()+c),x2,y,c,leqclauses,geqclauses);
	else if(b > c)
		addSimplifiedMerge(x1,std::vector<literal>(x2.begin(),x2.begin()+c),y,c,leqclauses,geqclauses);
	else if(a+b<=c)
		addMerge(x1,x2,y,leqclauses,geqclauses);
	else{
		y.resize(c);
		std::vector<literal> x1even, x1odd, x2even, x2odd;
		for(int i = 0; i < a-1; i+=2){
				x1even.push_back(x1[i]);
				x1odd.push_back(x1[i+1]);
		}
		if(a%2==1)
			x1even.push_back(x1[a-1]);

		for(int i = 0; i < b-1; i+=2){
				x2even.push_back(x2[i]);
				x2odd.push_back(x2[i+1]);
		}
		if(b%2==1)
			x2even.push_back(x2[b-1]);

		std::vector<literal> zeven;
		std::vector<literal> zodd;
		std::vector<literal> z;

		if(c%2==0){
			addSimplifiedMerge(x1even, x2even, zeven, c/2 + 1,leqclauses,geqclauses);
			addSimplifiedMerge(x1odd, x2odd, zodd, c/2,leqclauses,geqclauses);

			z.resize(c+1);
			for(int i = 0; i < c/2; i++){
				z[2*i] = zeven[i];
				z[2*i +1] = zodd[i];
			}
			z[c] = zeven[c/2];

			y[0] = z[0];
			for(int i = 1; i < c-2; i+=2)
				addTwoComparator(z[i],z[i+1],y[i],y[i+1],leqclauses,geqclauses);
			y[c-1]=newBoolVar();
			if(leqclauses){
				addClause(!z[c-1] | y[c-1]);
				addClause(!z[c] | y[c-1]);
			}
			if(geqclauses)
				addClause(z[c-1] | z[c] | !y[c-1]);

		}
		else{ //c%2==1
			addSimplifiedMerge(x1even, x2even, zeven, (c+1)/2,leqclauses,geqclauses);
			addSimplifiedMerge(x1odd, x2odd, zodd, (c-1)/2,leqclauses,geqclauses);

			z.resize(c);
			for(int i = 0; i < (c-1)/2; i++){
				z[2*i] = zeven[i];
				z[2*i +1] = zodd[i];
			}
			z[c-1] = zeven[(c-1)/2];

			y[0] = z[0];
			for(int i = 1; i < c-1; i+=2)
				addTwoComparator(z[i],z[i+1],y[i],y[i+1],leqclauses,geqclauses);
		}
	}
}

//Pre:: ommitted node is never alone in x
void SMTFormula::addTotalizer(const std::vector<literal> &x, const std::vector<std::pair<int,std::set<int> > > &inputBits, std::vector<literal> &y, int lIndex, 
	int partSize, int ommittedLeaf,
	std::map<std::set<std::pair<int,int> >,  std::vector<literal> > & constructed){

	y.clear();

	//Base case, leaf. Ommitted leaf should never reach a partSize==1
	if(partSize==1)
		y.push_back(x[lIndex]);

	//Recursive case, branch in the binary tree
	else{
		//In local encoding (ommittedLeaf!=-1), if already constructed, retrieve and return
		//A tree containing an ommitted leaf is never reused
		std::set<std::pair<int,int> > input;
		for(int i = lIndex; i < lIndex+partSize; i++){
			int group = inputBits[i].first;
			if(i!=ommittedLeaf)
				for(int j : inputBits[i].second)
					input.insert(std::pair<int,int>(group,j));
		}

		std::map<std::set<std::pair<int,int> >, std::vector<literal> >::iterator it = constructed.find(input);
		if(it != constructed.end()){
			y = it->second;
			return;
		}

		int lSize = partSize/2;
		int rSize = partSize - partSize/2;
		int rlIndex = lIndex+lSize;

		//If left child not present, return right child
		if(lSize==1 && ommittedLeaf==lIndex){
			addTotalizer(x, inputBits, y, rlIndex, rSize,ommittedLeaf, constructed);
			return;
		}
		//If right child not present, return left child
		else if(rSize==1 && ommittedLeaf==rlIndex){
			addTotalizer(x, inputBits, y, lIndex, lSize,ommittedLeaf, constructed);
			return;
		}

		std::vector<literal>  yleft;
		std::vector<literal>  yright;

		addTotalizer(x, inputBits, yleft, lIndex, lSize,ommittedLeaf, constructed);
		addTotalizer(x, inputBits, yright, rlIndex, rSize,ommittedLeaf, constructed);

		if(lIndex <= ommittedLeaf && ommittedLeaf < lIndex+lSize)
			lSize--;
		else if(rlIndex <= ommittedLeaf && ommittedLeaf < rlIndex+rSize)
			rSize--;
			
		y.resize(lSize + rSize);
		for(int j = 0; j < lSize + rSize; j++)
			y[j] = newBoolVar();

		for(int j = 0; j < lSize; j++){
			addClause(!yleft[j] | y[j]);
			for(int k = 0; k < rSize; k++)
				addClause(!yleft[j] | !yright[k] | y[j+k+1]);
		}
		for(int k = 0; k < rSize; k++)
			addClause(!yright[k] | y[k]);

		//Store totalizer
		constructed[input] = y;
	}
}

void SMTFormula::addTotalizer(const std::vector<literal> &x, std::vector<literal> &y){

	int n = x.size();

	if(n==0){
		y.clear();
		return;
	}
	if(n==1){
		y = x;
		return;
	}

	std::vector<literal> * tree = new std::vector<literal> [2*n-1];

	//Fill tree nodes with coefficients
	for(int i = 0; i < n; i++){
		int idx = n-1+i;
		tree[idx].resize(1);
		tree[idx][0] = x[i];
	}

	for(int i = n-2; i >= 0; i--){
		int ls = tree[lchild(i)].size();
		int rs = tree[rchild(i)].size();
		tree[i].resize(ls + rs);
		for(int j = 0; j < ls + rs; j++)
			tree[i][j] = newBoolVar();

		for(int j = 0; j < ls; j++){
			addClause(!tree[lchild(i)][j] | tree[i][j]);
			for(int k = 0; k < rs; k++)
				addClause(!tree[lchild(i)][j] | !tree[rchild(i)][k] | tree[i][j+k+1]);
		}
		for(int k = 0; k < rs; k++)
			addClause(!tree[rchild(i)][k] | tree[i][k]);
	}

	y = tree[0];

	delete [] tree;
}

void SMTFormula::addTotalizer(const std::vector<literal> &x, std::vector<literal> &y, int K){

	int n = x.size();

	if(n==0){
		y.clear();
		return;
	}
	if(n==1){
		y = x;
		return;
	}

	std::vector<literal> * tree = new std::vector<literal> [2*n-1];

	//Fill tree nodes with coefficients
	for(int i = 0; i < n; i++){
		int idx = n-1+i;
		tree[idx].resize(1);
		tree[idx][0] = x[i];
	}

	for(int i = n-2; i >= 0; i--){
		int ls = tree[lchild(i)].size();
		int rs = tree[rchild(i)].size();
		tree[i].resize(std::min(K+1,ls + rs));
		for(int j = 0; j < std::min(K+1,ls + rs); j++)
			tree[i][j] = newBoolVar();

		for(int j = 0; j < ls; j++){
			addClause(!tree[lchild(i)][j] | tree[i][j]);
			for(int k = 0; k < rs; k++)
				addClause(!tree[lchild(i)][j] | !tree[rchild(i)][k] | tree[i][std::min(K,j+k+1)]);
		}
		for(int k = 0; k < rs; k++)
			addClause(!tree[rchild(i)][k] | tree[i][k]);
	}

	y = tree[0];

	delete [] tree;
}

void SMTFormula::addSorting(const std::vector<literal> &x, std::vector<literal> &y, bool leqclauses, bool geqclauses){
	//Codifies a mergesort
	int n = x.size();

	if(n==0){
		y.clear();
		return;
	}

	if(n==1)
		y=x;
	else if(n==2){
		y.resize(2);
		addTwoComparator(x[0],x[1],y[0],y[1],leqclauses,geqclauses);
	}
	else{
		std::vector<literal> z1,z2;

		std::vector<literal> x1 = std::vector<literal>(x.begin(), x.begin() + n/2);
		std::vector<literal> x2 = std::vector<literal>(x.begin() + n/2, x.end());

		addSorting(x1,z1,leqclauses,geqclauses);
		addSorting(x2,z2,leqclauses,geqclauses);
		addMerge(z1,z2,y,leqclauses,geqclauses);
	}
}


void SMTFormula::addMCardinality(const std::vector<literal> &x, std::vector<literal> &y, int m, bool leqclauses, bool geqclauses){
	//Codifies a mergesort
	int n = x.size();
	

	if(m==0){
		y.clear();
		return;
	}

	if(n<=m){
		addSorting(x,y,leqclauses,geqclauses);
		return;
	}

	std::vector<literal> z1,z2;

	std::vector<literal> x1 = std::vector<literal>(x.begin(), x.begin() + n/2);
	std::vector<literal> x2 = std::vector<literal>(x.begin() + n/2, x.end());

	addMCardinality(x1,z1,std::min(n/2,m),leqclauses,geqclauses);
	addMCardinality(x2,z2,std::min(n-(n/2),m),leqclauses,geqclauses);
	addSimplifiedMerge(z1,z2,y,m,leqclauses,geqclauses);
}


RGGTNode::RGGTNode()
{
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}


RGGTNode::RGGTNode(RGGTNode * left, RGGTNode * right)
{
	this->left = left;
	this->right = right;
	this->parent = NULL;
}

RGGTNode::~RGGTNode()
{

}


void RGGTNode::makeIntervals(int K, bool reduce)
{
	if(reduce) {
        // Assumes parent already has a set of intervals. 
        // Uses values of the sibling. 
        
        //  Singleton interval to start with.
        intervals.push_back(std::pair<int,int>(values[0], values[0]));
        
        //  Iterate through values, checking each one 
        for(int i=0; i<values.size()-1; i++) {
            int lower=values[i];
            int upper=values[i+1];
            
            bool split=false;
            
            const std::vector<int> & siblingvals=(parent->left==this ? parent->right->values : parent->left->values); 
            for(int j=0; j<siblingvals.size(); j++) {
                int sibval=siblingvals[j];
                
                // For this sibling value, does the difference between lower and upper shift
                // to a different interval in the parent?
                
                int seekval=sibval+lower;
                
                // Lazy loop for now -- should be binary search.
                std::pair<int,int> parentInterval;
                const std::vector<std::pair<int,int> > & parints=parent->intervals;
                for(int k=0; k<parints.size(); k++) {
                    if(parints[k].first<=seekval && parints[k].second>=seekval) {
                        parentInterval=parints[k];
                        break;
                    }
                    if(parints[k].first==K+1) {
                        //assert seekval>=K+1;
                        parentInterval=parints[k];
                        break;
                    }
                }
                
                int val2=sibval+upper;
                if(seekval<=K && (val2<parentInterval.first || val2>parentInterval.second)) {
                    split=true;
                    break;
                }
            }
            
            if(split) {
                // Start a new interval with upper. 
                intervals.push_back(std::pair<int,int>(upper, upper));
            }
            else {
                // Join upper onto the last interval.
                intervals[intervals.size()-1].second=upper;
            }
        }
    }
    else {
        // Don't do reduction -- one interval for each value. 
        for(int i=0; i<values.size(); i++) {
            intervals.push_back(std::pair<int,int>(values[i], values[i]));
        }
    }
}

}

