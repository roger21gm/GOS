#ifndef FILEENCODER_DEFINITION
#define FILEENCODER_DEFINITION


#include <stdlib.h>
#include "encoder.h"
#include "encoding.h"
#include <cstring>

using namespace smtapi;

/*
 * Virtual class from which all file encoders inherit
 */
class FileEncoder : public Encoder {

private:
	std::string tmpfilename;
	bool defaulttmpdir;

protected:
	std::string getTMPFileName() const;

public:

	//Default constructor
	FileEncoder(Encoding * encoding);

	//Destructor
	virtual ~FileEncoder();

	virtual void createFile(std::ostream & os, SMTFormula * f) const = 0;

	void setTmpFileName(const std::string & filename);



};

#endif

