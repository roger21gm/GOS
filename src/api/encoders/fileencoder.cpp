#include "fileencoder.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include "../util/errors.h"
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib>



FileEncoder::FileEncoder(Encoding * encoding) : Encoder(encoding){
	tmpfilename = "aux.txt";
	defaulttmpdir = true;
}

FileEncoder::~FileEncoder(){

}

std::string FileEncoder::getTMPFileName() const{
	std::string s;
	if(defaulttmpdir){
#ifdef TMPFILESPATH
		DIR* dir = opendir(TMPFILESPATH);
		if (dir)
			closedir(dir);
		else if (ENOENT == errno)
		{
			const int dir_err = system((std::string("mkdir -p ") + TMPFILESPATH).c_str());
			if (-1 == dir_err){
				std::cerr << "Could not create directory " << TMPFILESPATH << std::endl;
				exit(1);
			}
		}
		else{
			std::cerr << "Could not acess nor create directory " << TMPFILESPATH << std::endl;
			exit(BADFILE_ERROR);
		}
		s=TMPFILESPATH"/";
#else
		s="";
#endif
	}
	else
		s="";

	s+=tmpfilename;
	return s;
}


void FileEncoder::setTmpFileName(const std::string & filename){
	this->tmpfilename = filename;
}

