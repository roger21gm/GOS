#include "encoder.h"
#include <iostream>


Encoder::Encoder(Encoding * encoding){
	this->enc = encoding;
	this->workingFormula = EncodedFormula();

	createModel = true;

	lastchecktime = -1;
	solverchecktime = -1;
	natoms = -1;
	nrestarts = -1;
	nsimplify = -1;
	nreduce = -1;
	ndecisions = -1;
	npropagations = -1;
	nconflicts = -1;
	ntheorypropagations = -1;
	ntheoryconflicts = -1;

}

Encoder::~Encoder(){
	if(workingFormula.f!=NULL)
		delete workingFormula.f;
}

int Encoder::getObjective() const{
	if(enc==NULL){
		std::cerr << "Tried to access the objective value of a non-solved formula" << std::endl;
		exit(SOLVING_ERROR);
	}

	return enc->getObjective();
}

bool Encoder::optimize(int lb, int ub){
	std::cerr << "The selected encoder does not support optimization" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
	return false;
}

bool Encoder::checkSATAssuming(int lb, int ub){
	std::cerr << "The selected encoder does not support checks with assumptions" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
	return false;
}

void Encoder::initAssumptionOptimization(int lb, int ub){
	std::cerr << "The selected encoder does not support checks with assumptions" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
}

void Encoder::narrowBounds(int lb, int ub){
	std::cerr << "The selected encoder does not support narrowing bounds" << std::endl;
	exit(UNSUPPORTEDFUNC_ERROR);
}

void Encoder::setProduceModels(bool b){
	this->createModel = b;
}

bool Encoder::produceModels() const{
	return createModel;
}

float Encoder::getCheckTime() const{
	return lastchecktime;
}

float Encoder::getSolverCheckTime() const{
	return solverchecktime;
}

int Encoder::getNBoolVars() const{
	return workingFormula.f->getNBoolVars();
}

int Encoder::getNIntVars() const{
	return workingFormula.f->getNIntVars();
}

int Encoder::getNAtoms() const{
	return natoms;
}

int Encoder::getNClauses() const{
	return workingFormula.f->getNClauses();
}

int Encoder::getNRestarts() const{
	return nrestarts;
}

int Encoder::getNSimplify() const{
	return nsimplify;
}

int Encoder::getNReduce() const{
	return nreduce;
}

int Encoder::getNDecisions() const{
	return ndecisions;
}

int Encoder::getNPropagations() const{
	return npropagations;
}

int Encoder::getNConflicts() const{
	return nconflicts;
}

int Encoder::getNTheoryPropagations() const{
	return ntheorypropagations;
}

int Encoder::getNTheoryConflicts() const{
	return ntheoryconflicts;
}
