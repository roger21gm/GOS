#ifndef AMOPBMDDBUILDER_DEF
#define AMOPBMDDBUILDER_DEF

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <climits>
#include <algorithm>
#include "mddbuilder.h"
#include "mdd.h"


struct R_M;

class AMOPBMDDBuilder : public MDDBuilder {

private:
	std::vector<std::vector<MDD *> > L_MDDs;
	std::vector<std::vector<R_M> > L;
	int K;
	std::vector<std::vector<int> > Q;
	std::vector<std::vector<literal> > X;

	void initL();
	void mostrarL(int i_l=0);
	void insertMDD(R_M rb_in,int i_l);
	int inf_sum(int possible_inf, int x);

	R_M searchMDD(int i_k,int i_l);

	R_M MDDConstruction(int i_l, int i_k);
	int getmax(const std::vector<int> & v);

	void createGraphviz(MDD * mdd, std::ostream & os, bool * visited) const;

protected:
	virtual MDD * buildMDD();

public:

	//Constructor
	AMOPBMDDBuilder(const std::vector<std::vector<int> > &Q,const std::vector<std::vector<literal> > &X, int K, bool longedges=true);
	AMOPBMDDBuilder(const std::vector<int> &Q,const std::vector<literal> &X, int K, bool longedges=true);
	~AMOPBMDDBuilder();

	MDD * addRoot(int k);

	virtual void createGraphviz(std::ostream & os, std::vector<std::vector<int> > * labels = NULL) const;
};


//Encapsulation of an MDD with its interval [B,Y]
struct R_M {
MDD *mdd;
int B;
int Y;
R_M() {
    mdd=NULL;
    B=0;
    Y=0;
}
R_M(MDD * m, int b, int y) {
    mdd=m;
    B=b;
    Y=y;
}
};


#endif
