#ifndef UTIL_DEFINITION
#define UTIL_DEFINITION

#include <vector>
#include <set>
#include <string>
#include <map>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "smtapi.h"

using namespace smtapi;

struct treenode{
	treenode * lchild;
	treenode * rchild;
	std::set<int> coefs;
	int idx;
	treenode(treenode *l, treenode *r, const std::set<int> & s){
		this->lchild = l;
		this->rchild = r;
		this->coefs = s;
		this->idx=-1;
	}
	treenode(int idx, const std::set<int> & s){
		this->idx = idx;
		this->lchild = NULL;
		this->rchild = NULL;
		this->coefs = s;
	}
	~treenode(){
		if(lchild!=NULL) delete lchild;
		if(rchild!=NULL) delete rchild;
	}
};

namespace util
{

void sortCoefsDecreasing(std::vector<int> & Q, std::vector<literal> & X);
void sortCoefsDecreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X);
void sortCoefsIncreasing(std::vector<int> & Q, std::vector<literal> & X);
void sortCoefsIncreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X);
void sortBySimilarityIncreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X);
void sortCoefsTotalizer(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X, int K);
void sortCoefsTotalizerDifs(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X);
void addElementsToOrder(treenode * node,
		const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X,
		std::vector<std::vector<int> > & Q2, std::vector<std::vector<literal> > & X2);
bool isPowerOf2(int x);
bool nthBit(int x, int n);
int cardinality(int x);
std::string getFileName(const std::string& s);

template<typename T>
void setOrder(std::vector<T> & data, int *order);

void insertSortedIfNotExists(std::vector<int> & v, int x);

void floydWarshall(int ** adjMatrix, int size);

void reduceByEO(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> >& X, int & K);

void printAMOPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K);

void PBtoAMOPB(const std::vector<int> & Q, const std::vector<literal> & X, std::vector<std::vector<int> > & QQ, std::vector<std::vector<literal> > &XX);

void AMOPBtoPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > &X, std::vector<int> & QQ, std::vector<literal> & XX);

int sum(const std::vector<int> & v);

template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
  std::vector<TK> retval;
  for (auto const& element : input_map)
    retval.push_back(element.first);
  return retval;
}

template<typename TK, typename TV>
std::vector<TV> extract_values(std::map<TK, TV> const& input_map) {
  std::vector<TV> retval;
  for (auto const& element : input_map)
    retval.push_back(element.second);
  return retval;
}

//Return true if 'vals' contains 'val'
inline bool defined(const std::set<std::string> & vals, const std::string & val){
	return vals.find(val)!=vals.end();
}

inline bool boolstring(const std::string & s){
	return s=="0" || s == "1";
}

inline bool isInteger(const std::string & s)
{
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
		return false ;

	char * p ;
	strtol(s.c_str(), &p, 10) ;

	return (*p == 0) ;
}

inline void show_list(const std::set<std::string> & vs){
	bool comma=false;
	for(const std::string & s : vs)
	{
		if(comma) std::cerr << ",";
		else comma=true;
		std::cerr << " " << s;
	}
	std::cerr << std::endl;
}

inline void show_list(const std::vector<std::string> & vs){
	bool comma=false;
	for(const std::string & s : vs)
	{
		if(comma) std::cerr << ",";
		else comma=true;
		std::cerr << " " << s;
	}
	std::cerr << std::endl;
}

}

#endif

