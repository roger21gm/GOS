#include "singlecheck.h"
#include "limits.h"
#include <iostream>


SingleCheck::SingleCheck() : Optimizer(){

}

int SingleCheck::minimize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds){
	return checkSAT(e,lb,ub) ? 1 : INT_MIN;
}

int SingleCheck::maximize(Encoder * e, int lb, int ub, bool useAssumptions, bool narrowBounds){
	return checkSAT(e,lb,ub) ? 1 : INT_MIN;
}

SingleCheck::~SingleCheck() {
}
