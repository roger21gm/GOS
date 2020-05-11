#include "glucoseapiencoder.h"
#include <iostream>

using namespace Glucose;

GlucoseAPIEncoder::GlucoseAPIEncoder(Encoding * enc) : APIEncoder(enc){

	this->lastVar = 0;
	this->lastClause = -1;

	s = new SimpSolver();
	s->use_simplification = false;
	s->use_elim = false;
	s->verbosity=0;
	s->showModel=false;
	s->vbyte = false;
	s->certifiedUNSAT=false;
	//s->setIncrementalMode();


}

GlucoseAPIEncoder::~GlucoseAPIEncoder(){
	delete s;
}

bool GlucoseAPIEncoder::checkSATAssuming(int lb, int ub){

	std::vector<literal> assumptions;
	enc->assumeBounds(workingFormula,lb,ub,assumptions);

	return assertAndCheck(lb,ub,&assumptions);
}

void GlucoseAPIEncoder::narrowBounds(int lb, int ub){
	enc->narrowBounds(workingFormula,lastLB,lastUB,lb,ub);
}

bool GlucoseAPIEncoder::checkSAT(int lb, int ub){
	if(workingFormula.f==NULL){
		workingFormula = EncodedFormula(enc->encode(lb, ub),lb,ub);
	}
	else{
		bool narrowed = enc->narrowBounds(workingFormula,lastLB, lastUB, lb, ub);
		if(!narrowed){
			delete workingFormula.f;
			this->lastVar = 0;
			this->lastClause = -1;
			workingFormula = EncodedFormula(enc->encode(lb, ub),lb,ub);

			//Reset glucose solver
			delete s;
			s = new SimpSolver();
			vars.clear();
		}
	}

	lastLB = lb;
	lastUB = ub;

	return assertAndCheck(lb,ub,NULL);
}


bool GlucoseAPIEncoder::assertAndCheck(int lb, int ub, std::vector<literal> * assumptions){

	//Add the new variables
	vars.resize(workingFormula.f->getNBoolVars()+1);

	for(int i = lastVar+1; i <= workingFormula.f->getNBoolVars(); i++)
		vars[i]=s->newVar();


	bool consistent = true;

	//Add the new clauses
	for(int i = lastClause+1; i < workingFormula.f->getNClauses(); i++){
		const clause & c = workingFormula.f->getClauses()[i];
		vec<Lit> cv;
		for(const literal & l : c.v)
			cv.push(getLiteral(l,vars));
		if(!s->addClause(cv)){
			consistent = false;
			break;
		}
		consistent = s->simplify();
	}

	lastVar = workingFormula.f->getNBoolVars();
	lastClause = workingFormula.f->getNClauses()-1;


	bool sat;
	if(!consistent){
		sat=false;
		lastchecktime=0;
	}
	else{
		clock_t begin_time = clock();

		//Make the satisfiability check
		int nassumptions = assumptions==NULL ? 0 : assumptions->size();
		vec<Lit> dummy(nassumptions);

		for(int i = 0; i < nassumptions; i++)
			dummy[i]=getLiteral((*assumptions)[i],vars);

		sat = s->solveLimited(dummy,false,true)==l_True;
		lastchecktime = float( clock() - begin_time ) /  CLOCKS_PER_SEC;

	}

	//Retrieve the model
	if(sat && produceModels()){
		std::vector<bool> bmodel(workingFormula.f->getNBoolVars()+1);
		std::vector<int> imodel;

		int ntrue=0;
		int nfalse=0;
		for(int i = 1; i <= workingFormula.f->getNBoolVars(); i++){
			bmodel[i]=s->model[i-1]==l_True;
			if(bmodel[i])ntrue++;
			else nfalse++;
		}
		enc->setModel(workingFormula,lb,ub,bmodel,imodel);
	}

	return sat;
}

Lit GlucoseAPIEncoder::getLiteral(const literal & l, const std::vector<Var> & vars){
	if(l.arith){
		std::cerr << "Error: Glucose cannot deal with arithmetic literals"<< std::endl;
		exit(BADCODIFICATION_ERROR);
	}
	else{
		if(l.v.id<=0 || l.v.id > workingFormula.f->getNBoolVars()){
			std::cerr << "Error: asserted undefined Boolean variable: " << l.v.id << std::endl;
			exit(UNDEFINEDVARIABLE_ERROR);
		}
		else
			return mkLit(vars[l.v.id],!l.sign);
	}
}
