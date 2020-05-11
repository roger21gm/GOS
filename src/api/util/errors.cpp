#include <iostream>
#include <string>
#include "errors.h"




namespace smtapierrors
{

void fatalError(std::string message, int errorCode){
	std::cerr << "ERROR: " << message << std::endl;
	exit(errorCode);
}

void warning(std::string message){
	std::cerr << "WARNING: " << message << std::endl;
}

}


