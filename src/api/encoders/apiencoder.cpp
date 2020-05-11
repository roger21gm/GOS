#include "apiencoder.h"

APIEncoder::APIEncoder(Encoding * encoding) : Encoder(encoding){

}

void APIEncoder::initAssumptionOptimization(int lb, int ub){	
	workingFormula = EncodedFormula(enc->encode(lb,ub),lb,ub);

	lastLB = lb;
	lastUB = ub;
}

APIEncoder::~APIEncoder(){

}
