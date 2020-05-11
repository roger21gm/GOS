#include "smtlib2fileencoder.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <iterator>

using namespace smtapi;

SMTLIB2FileEncoder::SMTLIB2FileEncoder(Encoding * enc, const std::string & solver) : FileEncoder(enc){
	logic = "QF_LIA";

	this->solver = solver;
}

SMTLIB2FileEncoder::~SMTLIB2FileEncoder(){

}

bool SMTLIB2FileEncoder::checkSAT(int lb, int ub){

	std::string filename = getTMPFileName();

	if(workingFormula.f==NULL){
		workingFormula = EncodedFormula(enc->encode(lb, ub),lb,ub);
	}
	else{
		bool narrowed = enc->narrowBounds(workingFormula,lastLB, lastUB, lb, ub);
		if(!narrowed){
			delete workingFormula.f;
			workingFormula = EncodedFormula(enc->encode(lb, ub),lb,ub);
		}
	}

	lastLB = lb;
	lastUB = ub;

	std::ofstream os(filename.c_str());
	if(!os.is_open()){
		std::cerr << "Could not open file: " << filename << std::endl;
		std::cerr << "Aborted" << std::endl;
		exit(BADFILE_ERROR);
	}

	createFile(os,workingFormula.f);

	os.close();


	//Recover solution
	std::array<char, 512> buffer;
   std::string result;
	clock_t begin_time = clock();

	std::string sentence;
	if(solver=="yices")
		sentence = "yices-smt2 " + filename + " | sed -re '2,$s/([ ]*[(]*[ ]*[^ ]*[ ]*)//' -e '2,$s/[)]//' -e '2,$s/[)]$//'";
	else if(solver == "optimathsat"){
		if(produceModels())
			sentence = "optimathsat -model_generation=TRUE " + filename + " | sed -re '2,$s/([ ]*[(]*[ ]*[^ ]*[ ]*)//' -e '2,$s/[)]//' -e '2,$s/[)]$//'";
		else
			sentence = "optimathsat " + filename + " | sed -re '2,$s/([ ]*[(]*[ ]*[^ ]*[ ]*)//' -e '2,$s/[)]//' -e '2,$s/[)]$//'";
	}
	else{
		std::cerr << "Unsupported solver " << solver << std::endl;
		exit(BADARGUMENTS_ERROR);
	}

   std::shared_ptr<FILE> pipe(popen(sentence.c_str(),"r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 512, pipe.get()) != nullptr)
            result += buffer.data();
    }

	lastchecktime = float( clock() - begin_time ) /  CLOCKS_PER_SEC;

	std::istringstream iss(result);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());

	bool sat = results[0]=="sat";

	if(sat && produceModels()){
		std::vector<int> imodel(workingFormula.f->getNIntVars()+1);
		std::vector<bool> bmodel(workingFormula.f->getNBoolVars()+1);

		if(results.size() < workingFormula.f->getNIntVars() + workingFormula.f->getNBoolVars() + 1){
			std::cerr << "Error retrieving the solution from the SMT solver";
			exit(SOLVING_ERROR);
		}

		int idx = 1;
		for(int i = 1; i <= workingFormula.f->getNIntVars();i++){
			imodel[i]=stoi(results[idx]);
			idx++;
		}
		for(int i = 1; i <= workingFormula.f->getNBoolVars();i++){
			bmodel[i]=results[idx]=="true";
			idx++;
		}

		enc->setModel(workingFormula,lb,ub,bmodel,imodel);
	}

	remove(filename.c_str());


	return sat;
}

bool SMTLIB2FileEncoder::optimize(int lb, int ub){
	checkSAT(lb,ub);
	return true;
}

void SMTLIB2FileEncoder::createFile(std::ostream & os, SMTFormula * f) const{

	if(produceModels())
		os << "(set-option :produce-models true)" << std::endl;

	os << "(set-logic " << logic << ")" << std::endl;
	for(int i = 1; i <= f->getNIntVars();i++)
		if(f->isDeclareVar(i))
			os << "(declare-fun " << ivn(f->getIntVarNames()[i]) << "() Int)" << std::endl;
	for(int i = 1; i <= f->getNBoolVars();i++)
			os << "(declare-fun " << bvn(f->getBoolVarNames()[i]) << "() Bool)" << std::endl;

	for(int i = 0; i < f->getSoftClauses().size(); i++){
		const clause &c = f->getSoftClauses()[i];
		int weight = f->getWeights()[i];
		intvar var = f->getSoftClauseVars()[i];
		os << "(assert-soft";
		pclause(f,c,os);
		os << " :weight " << weight;
		if(var.id != 0)
			os << " :id " << ivn(f->getIntVarNames()[var.id]);
		os << ")" << std::endl;
	}

	for(const clause &c : f->getClauses()){
		os << "(assert";
		pclause(f,c,os);
		os << ")" << std::endl;
	}

	if(f->getType() == OMTMINFORMULA || f->getType()==OMTMAXFORMULA){
		if(f->getType() == OMTMINFORMULA)
			os << "(minimize ";
		else
			os << "(maximize ";

		psum(f,f->getObjFunc(),os);
		if(f->getLowerBound()!=INT_MIN)
			os << " :lower " << (f->getType() == OMTMINFORMULA ? f->getLowerBound() : f->getLowerBound() - 1);
		if(f->getUpperBound()!=INT_MAX)
			os << " :upper " << (f->getType() == OMTMINFORMULA ? f->getUpperBound() + 1 : f->getUpperBound());
		os << ")" << std::endl;
	}

	os << "(check-sat)" << std::endl;

	if(produceModels()){
		os << "(get-value (";
		for(int i = 1; i <= f->getNIntVars();i++)
			os << " " << ivn(f->getIntVarNames()[i]);
		for(int i = 1; i <= f->getNBoolVars();i++)
			os << " " << bvn(f->getBoolVarNames()[i]);
		os << "))" << std::endl;
	}
	if(solver=="optimathsat")
		os << "(get-objectives)" << std::endl;

	os << "(exit)" << std::endl;
}

inline std::string SMTLIB2FileEncoder::ivn(const std::string &s) const{
	return "i_"+s;
}

inline std::string SMTLIB2FileEncoder::bvn(const std::string &s) const{
	return "b_"+s;
}

void SMTLIB2FileEncoder::pclause(SMTFormula * f, const clause & c, std::ostream & os) const{
	if(c.v.size()==0)
		os << " false";
	else if(c.v.size()==1){
		pliteral(f,c.v[0],os);
	}
	else{
		os << " (or ";
		for(const literal &l : c.v)
			pliteral(f,l,os);
		os << ")";
	}
}

void SMTLIB2FileEncoder::pliteral(SMTFormula * f, const literal & l, std::ostream & os) const{
	if(!l.sign)
		os << " (not";
	if(l.arith){
		if(l.cmp.eq)
			os << " (=";
		else
			os << " (<=";
		psum(f,l.cmp.s,os);
		if(l.cmp.k >= 0)
			os << " " << l.cmp.k;
		else
			os << " (- " << -l.cmp.k << ")";
		os << ")";
	}
	else{
		if(l.v.id<=0 || l.v.id>f->getNBoolVars()){
		std::cerr << "Error: asserted undefined Boolean variable"<< std::endl;
		exit(UNDEFINEDVARIABLE_ERROR);
	}
		os << " " << bvn(f->getBoolVarNames()[l.v.id]);
	}
	if(!l.sign)
		os << ")";
}

void SMTLIB2FileEncoder::psum(SMTFormula * f, const intsum & s,std::ostream & os) const{
	if(s.v.empty())
			os << " 0";
	else if(s.v.size()==1){
		os << " ";
		pprod(f,s.v[0],os);
	}
	else{
		os << " (+";
		for(const intprod & p : s.v){
			os << " ";
			pprod(f,p,os);
		}
		os << ")";
	}
}

void SMTLIB2FileEncoder::pprod(SMTFormula * f, const intprod & p, std::ostream & os) const{
	if(p.varid<=0 || p.varid>f->getNIntVars()){
		std::cerr << "Error: asserted undefined Int variable"<< std::endl;
		exit(UNDEFINEDVARIABLE_ERROR);
	}
	if(p.coef==1)
		os << ivn(f->getIntVarNames()[p.varid]);
	else if(p.coef==-1)
		os << "(- " << ivn(f->getIntVarNames()[p.varid]) << ")";
	else{
		if(p.coef >= 0)
			os << "(* " << p.coef << " " << ivn(f->getIntVarNames()[p.varid]) << ")";
		else
			os << "(* (- " << -p.coef << ") " << ivn(f->getIntVarNames()[p.varid]) << ")";
	}
}


