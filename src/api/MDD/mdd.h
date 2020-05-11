#ifndef MDDDEF
#define MDDDEF

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>

#include "../smtapi.h"

using namespace smtapi;


/*
 * This class represents a Multi-Desision Diagram
 * It can be either
 * 	- a trivial/leaf true/false MDD
 * 	- an MDD with a set of selector literals  'selectors', and a child
 * 		MDD associated to each selector (not necessarily different for each child).
 * 		It also has an 'else' child, which has no associated selector literal
 */
class MDD {

private:

	//Invariant: id > id of any child (not only direct child)
	int id;

	std::vector<literal> selectors;
	std::vector<MDD *> children;
	MDD * elsechild;

	bool istrivialtrue;
	bool istrivialfalse;

   //Number of variables in the Boolean function that this MDD represents, plus 1
	//It is equivalent to the depth of an OMDD without any long edge (i.e. all variables appear in the MDD)
	int vardepth;

	//Number of layers with some node in the MDD. Notice that realdepth<=vardepth
	int realdepth;
	//Example: let F:( x1 /\ x2) v (x1 /\ -x2)
	//The MDD is:
	//Root node, selector x1:  ----x1----> T
	//                         ---else---> F
	//In this case, vardepth=3 and realdepth=2

	static MDD * mddtrue; //True leaf node
    static MDD * mddfalse; //False leaf node

	MDD(bool b); //Trivial MDD constructor

	//Auxilliary function for the ostream operator
	void print(std::ostream & s, bool *printed) const;

	//Compute MDD size taking into acount the already visited nodes
	void getSize(bool * visited, int & size) const;

public:

	//Constructor
	MDD(int id,int nvars);

	//Destructor
	~MDD();

	//Get leaf nodes
	static MDD * MDDTrue();
	static MDD * MDDFalse();

	//Get the i-th selector and its child
	std::pair<literal,MDD*> getSelectorAndChild(int idx) const;

	//Get all the selectors
	const std::vector<literal> & getSelectors() const;

	//Get the i-th chile
	MDD * getChildByIdx(int idx) const;

	//Get the child pointed by 'selector'
	MDD * getChild(literal selector) const;

	//Get the else child
	MDD * getElseChild()const;

	//Get id
	int getId() const;

	//Get number of selectors
	int getNSelectors() const;

	//Get vardepth
	int getVarDepth() const;

	//Get realdepth
	int getRealDepth() const;

	//Get size, linear cost
	int getSize() const;

	//Get Id-based size, constant cost, soundness not guaranteed for nodes
	//different than the root
	int getIdBasedSize() const;

	//Get maximum width of a layer
	int getLayerWidth();

	//Get number of binary clauses
	int getNBinClauses() const;

	//Get number of ternary clauses
	int getNTernClauses();

	//Check if the MDD is leaf (either true or false)
	bool isLeafMDD() const;

	//Check if the MDD is the true leaf
	bool isTrueMDD() const;

	//Check if the MDD is the false leaf
	bool isFalseMDD() const;

	//Ostream operator
	friend std::ostream & operator<<(std::ostream & s, const MDD & m);

	//Add a child to the MDD
	void addChild(literal selector, MDD * child);

	//Set the else child of the MDD
	void setElseChild(MDD * child);

};

#endif
