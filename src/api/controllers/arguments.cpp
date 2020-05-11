#include "arguments.h"

namespace arguments{

Argument arg(const std::string & name, const std::string & description){
	Argument a;
	a.name = name;
	a.description = description;
	return a;
}

Arguments<int> * nullProgArgs(){
	return new Arguments<int>({},0,{},"");
}

}
