#ifndef APIENCODER_DEFINITION
#define APIENCODER_DEFINITION

#include "encoding.h"
#include "encoder.h"



/*
 * Virtual class from which all API encoders inherit
 */
class APIEncoder : public Encoder {

public:

	//Default constructor
	APIEncoder(Encoding * encoding);

	void initAssumptionOptimization(int lb, int ub);

	//Destructor
	virtual ~APIEncoder();


};

#endif

