#include "encoding.h"
#include "util/errors.h"
#include <iostream>

Encoding::Encoding(){

}

Encoding::~Encoding(){

}

void Encoding::setModel(const EncodedFormula & ef, int lb, int ub, const std::vector<bool> & bmodel, const std::vector<int> & imodel){

}

int Encoding::getObjective() const{
	return INT_MIN;
}

void Encoding::assumeBounds(const EncodedFormula & ef, int LB, int UB, std::vector<literal> & assumptions){
	std::cerr << "Error: tried to solve using assumptions, but the selected encoding does not implement checks with assumptions." << std::endl;
	exit(SOLVING_ERROR);
}

bool Encoding::narrowBounds(const EncodedFormula & ef, int lastLB, int lastUB, int lb, int ub){
	return false;
}

bool Encoding::printSolution(std::ostream & os) const{
	return false;
}


