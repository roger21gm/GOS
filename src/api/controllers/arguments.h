#ifndef ARGUMENTS_DEFINITION
#define ARGUMENTS_DEFINITION


#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include "../util/errors.h"


namespace arguments{

enum OptionType{
	INT_TYPE,
	BOOL_TYPE,
	STRING_TYPE
};

struct Argument{
	public:

	std::string name;
	std::string description;
};

Argument arg(const std::string & name, const std::string & description);

template<class OptionT>
struct Option{

	public:
		std::string shortname;
		std::string longname;
		OptionT option;
		OptionType type;
		std::string description;


		int ival;
		bool bval;
		std::string sval;
		std::vector<std::string> valid_values;

		std::string typeDesc() const{
			switch(type){
				case INT_TYPE:
					return "INT";
				break;

				case BOOL_TYPE:
					return "BOOL";
				break;

				default:
					if(valid_values.empty())
						return "STRING";
					else
						return "ENUM";
				break;
			}
			return "";
		}

		Option(){}
};

template<class OptionT>
Option<OptionT> sop(const std::string & shortname, const std::string & longname, OptionT option, const std::string & defval, const std::string & description){
	Option<OptionT> o;
	o.shortname = shortname;
	o.longname = longname;
	o.option = option;
	o.description = description;
	o.type = STRING_TYPE;
	o.sval = defval;
	return o;
}

template<class OptionT>
Option<OptionT> sop(const std::string & shortname, const std::string & longname, OptionT option, const std::string & defval, const std::vector<std::string> & values, const std::string & description){
	Option<OptionT> o;
	o.shortname = shortname;
	o.longname = longname;
	o.option = option;
	o.description = description;
	o.type = STRING_TYPE;
	o.sval = defval;
	o.valid_values = values;
	return o;
}

template<class OptionT>
Option<OptionT> iop(const std::string & shortname, const std::string & longname, OptionT option, int defval, const std::string & description){
	Option<OptionT> o;
	o.shortname = shortname;
	o.longname = longname;
	o.option = option;
	o.description = description;
	o.type = INT_TYPE;
	o.ival = defval;
	return o;
}

template<class OptionT>
Option<OptionT> bop(const std::string & shortname, const std::string & longname, OptionT option, bool defval, const std::string & description){
	Option<OptionT> o;
	o.shortname = shortname;
	o.longname = longname;
	o.option = option;
	o.description = description;
	o.type = BOOL_TYPE;
	o.bval = defval;
	return o;
}


template<class OptionT>
class Arguments{

private:
	std::string description;

	std::vector<std::string> arguments;
	std::vector<std::string> arguments_description;
	int mandatory;

	std::vector<std::string> argument_value;



	std::map<std::string,OptionT> name_option;
	std::map<OptionT,OptionType> option_type;
	std::map<OptionT,std::string> option_description;
	std::map<OptionT,std::vector<std::string> > option_svalues;

	std::map<OptionT,int> intOptions;
	std::map<OptionT,bool> boolOptions;
	std::map<OptionT,std::string> stringOptions;

protected:

	std::vector<Option<OptionT> > options;


public:

	Arguments(const std::vector<Argument> & arguments, int mandatory, const std::vector<Option<OptionT> > & options, const std::string & description);

	std::string getDescription() const;

	void addArgument(const std::string & arg);
	std::string getArgument(int idx) const;
	std::string getArgumentName(int idx) const;
	std::string getArgumentDesc(int idx) const;
	int getNArguments() const;
	int getAllowedArguments() const;
	int getMinimumArguments() const;

	bool hasOption(const std::string & s) const;
	OptionT getOptionRef(const std::string & s) const;
	OptionType getOptionType(OptionT option) const;
	void setOption(OptionT option, int value);
	void setOption(OptionT option, bool value);
	void setOption(OptionT option, const std::string & value);
	int getIntOption(OptionT option) const;
	bool getBoolOption(OptionT option) const;
	std::string getStringOption(OptionT option) const;
	int getNOptions() const;

	void printOptions() const;

	static Arguments<int> * nullProgArgs();


};

Arguments<int> * nullProgArgs();

template<class OptionT>
Arguments<OptionT>::Arguments(const std::vector<Argument> & arguments, int mandatory, const std::vector<Option<OptionT> > & options, const std::string & description){

	this->description = description;

	for(const Argument & a : arguments){
		this->arguments.push_back(a.name);
		this->arguments_description.push_back(a.description);
	}

	this->mandatory = mandatory;

	this->options = options;

	for(const Option<OptionT> & o: options){
		if(o.shortname != ""){
			if(name_option.find("-"+o.shortname) != name_option.end()){
				std::cerr << "Option " << ("-"+o.shortname) << " defined twice" << std::endl;
				exit(BADARGUMENTS_ERROR);
			}
			else
				name_option["-"+o.shortname] = o.option;
		}
		if(o.longname == ""){
			std::cerr << "It is required to specify a long name for each option" << std::endl;
			exit(BADARGUMENTS_ERROR);
		}
		else{
			if(name_option.find("--"+o.longname) != name_option.end()){
				std::cerr << "Option " << ("--"+o.longname) << " defined twice" << std::endl;
				exit(BADARGUMENTS_ERROR);
			}
			else
				name_option["--"+o.longname] = o.option;
		}
		option_type[o.option] = o.type;
		option_description[o.option] = o.description;
		option_svalues[o.option] = o.valid_values;

		switch(o.type){
			case INT_TYPE:
				this->setOption(o.option, o.ival);
				break;
			case BOOL_TYPE:
				this->setOption(o.option, o.bval);
				break;
			case STRING_TYPE:
				this->setOption(o.option,o.sval);
				break;
		}
	}

}

template<class OptionT>
std::string Arguments<OptionT>::getDescription() const{
	return description;
}

template<class OptionT>
void Arguments<OptionT>::addArgument(const std::string & arg){
	argument_value.push_back(arg);
}

template<class OptionT>
std::string Arguments<OptionT>::getArgument(int idx) const{
	return argument_value[idx];
}

template<class OptionT>
std::string Arguments<OptionT>::getArgumentName(int idx) const{
	return arguments[idx];
}

template<class OptionT>
std::string Arguments<OptionT>::getArgumentDesc(int idx) const{
	return arguments_description[idx];
}

template<class OptionT>
bool Arguments<OptionT>::hasOption(const std::string & s) const{
	return name_option.find(s) != name_option.end();
}

template<class OptionT>
OptionT Arguments<OptionT>::getOptionRef(const std::string & s) const{
	return name_option.find(s)->second;
}

template<class OptionT>
OptionType Arguments<OptionT>::getOptionType(OptionT option) const{
	return option_type.find(option)->second;
}

template<class OptionT>
void Arguments<OptionT>::setOption(OptionT option, int value){
	intOptions[option]=value;
}

template<class OptionT>
void Arguments<OptionT>::setOption(OptionT option, bool value){
	boolOptions[option]=value;
}

template<class OptionT>
void Arguments<OptionT>::setOption(OptionT option, const std::string & value){
	const std::vector<std::string> & values = option_svalues.find(option)->second;
	if(!values.empty() && find(values.begin(),values.end(),value) == values.end()){
		std::cerr << "Unsupported option value '" << value << "'" << std::endl;
		exit(BADARGUMENTS_ERROR);
	}
	stringOptions[option]=value;
}

template<class OptionT>
int Arguments<OptionT>::getIntOption(OptionT option) const{
	return intOptions.find(option)->second;
}

template<class OptionT>
bool Arguments<OptionT>::getBoolOption(OptionT option) const{
	return boolOptions.find(option)->second;
}

template<class OptionT>
std::string Arguments<OptionT>::getStringOption(OptionT option) const{
	return stringOptions.find(option)->second;
}

template<class OptionT>
int Arguments<OptionT>::getNOptions() const{
	return option_type.size();
}

template<class OptionT>
int Arguments<OptionT>::getNArguments() const{
	return argument_value.size();
}

template<class OptionT>
int Arguments<OptionT>::getAllowedArguments() const{
	return arguments.size();
}

template<class OptionT>
int Arguments<OptionT>::getMinimumArguments() const{
	return mandatory;
}

template<class OptionT>
void Arguments<OptionT>::printOptions() const{
	for(const arguments::Option<OptionT> & o : options){

		if(o.shortname == ""){
			printf("          --%s=%s",
			o.longname.c_str(),o.typeDesc().c_str());
		}
		else{
			printf("  -%s=%-4s --%s=%s",
			o.shortname.c_str(),o.typeDesc().c_str(),
			o.longname.c_str(),o.typeDesc().c_str());
		}

		if(!o.valid_values.empty()){
			std::cout << " : ";
			bool comma=false;
			for(const std::string & s : o.valid_values){
				if(comma)
					std::cout << ", ";
				else
					comma=true;
				std::cout << s;
			}
		}

		std::cout << std::endl;

		std::cout << "            " << o.description << std::endl << std::endl;
	}
}

}

#endif

