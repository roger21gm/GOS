#include "amopbmddbuilder.h"
#include "./util/util.h"



AMOPBMDDBuilder::AMOPBMDDBuilder(const std::vector<std::vector<int> > &Q,const std::vector<std::vector<literal> > &X, int K, bool longedges)
	: MDDBuilder(){
	this->Q=Q;
	this->X=X;
	this->K=K;

	this->longedges=longedges;

	for(int i = 0; i < Q.size(); i++) //The literals of each group are ordered by coefficient
		util::sortCoefsDecreasing(this->Q[i],this->X[i]);

	this->depth = Q.size()+1;
	this->initL();
	this->L_MDDs.resize(Q.size());
}

AMOPBMDDBuilder::AMOPBMDDBuilder(const std::vector<int> &Q,const std::vector<literal> &X, int K, bool longedges)
	: MDDBuilder(){

	for(int q : Q)
		this->Q.push_back(std::vector<int>(1,q));

	for(const literal & x : X)
		this->X.push_back(std::vector<literal>(1,x));

	this->K=K;

	this->longedges=longedges;

	this->depth = Q.size()+1;
	this->initL();
	this->L_MDDs.resize(Q.size());
}

AMOPBMDDBuilder::~AMOPBMDDBuilder(){
  for(const std::vector<MDD *> & layer : L_MDDs)
    for(MDD * m : layer)
      delete m;
}

MDD * AMOPBMDDBuilder::buildMDD(){
	return MDDConstruction(0,K).mdd;
}

void AMOPBMDDBuilder::mostrarL(int i_l) {
    int i=0,j=0,max=0;
    R_M rm;

    if(i_l>0) {
        max=i_l+1;
    } else {
        max=L.size();
    }

    for(i=i_l;i<max;i++) {
        std::cout << "Layer " << i << ":" << std::flush;
        for(j=0;j<L[i].size();j++) {
            rm=L[i][j];
            std::cout << "{" << rm.B << "," << rm.Y << "}"<< std::flush;
        }
        std::cout << std::endl;
    }
}

int AMOPBMDDBuilder::inf_sum(int possible_inf, int x){
  if(possible_inf == INT_MAX)
    return INT_MAX;
  else if(possible_inf == INT_MIN)
    return INT_MIN;
  else return possible_inf + x;

}

//Insert ordered with respect to the intervals [B,Y].
//The vector 'layer' is order, so we can use dicotomic search
// Precondition: rm_in doesnt exists in layer
void AMOPBMDDBuilder::insertMDD(R_M rm_in,int i_l) {
    R_M act;

    std::vector<R_M> & layer=L[i_l];

    if(layer.empty()){
      layer.push_back(rm_in);
      return;
    }
    int n=layer.size();
    int i=0,min=0,max=n-1;

    i=(max-min)/2;

    while(min<max) {
        act=layer[i];
        if(act.B>rm_in.Y){
            max=i-1;
        } else { //if(act->Y<rm_in->B) { //otherwise
            min=i+1;
        }
        i=min+(max-min)/2;
    }

    act=layer[i]; // min=max=i
    std::vector<R_M>::iterator it;
    it = L[i_l].begin();
    if(act.B>rm_in.Y){
        //i==i;
    } else { //if(act.Y<rm_in.B) { //otherwise
        i++;
    }
    L[i_l].insert(it+i,rm_in);

}

R_M AMOPBMDDBuilder::searchMDD(int i_k,int i_l) {
	 std::vector<R_M> & layer = L[i_l];

	 R_M res,act;
    res.mdd = NULL;
    int n=layer.size();
    int i=0,min=0,max=0;
    bool trobat=false;

    if(n>0) {
        max=n-1;

        i=(max-min)/2;
        while(min<=max && !trobat) {
            act=layer[i];
            if(i_k>=act.B && i_k<=act.Y) {
                res=act;
                trobat=true;
            } else if(act.B>i_k){
                max=i-1;
            } else { //if(act.Y<i_k) { //otherwise
                min=i+1;
            }
            i=min+(max-min)/2;
        }
    }
    return res;
}

R_M AMOPBMDDBuilder::MDDConstruction(int i_l,int i_k) {
	R_M rm_cert,rm_fals,rm_new;
	MDD *mdd_new=NULL;

	rm_new=searchMDD(i_k,i_l);

	if(rm_new.mdd==NULL){
		std::vector<R_M> rmdds;
		std::vector<MDD *> mdds;
		int maxB = INT_MIN;
		int minY = INT_MAX;
		bool allequal = true;
		MDD * m = NULL;

		for(int i = 0; i < Q[i_l].size(); i++){
			int i_a=Q[i_l][i];
			R_M rm = MDDConstruction(i_l+1,i_k-i_a);
			rmdds.push_back(rm);
			mdds.push_back(rm.mdd);
			if(m==NULL)
				m = rm.mdd;
			else
				allequal = allequal && m==rm.mdd;

			if(inf_sum(rm.B,i_a) > maxB) maxB = inf_sum(rm.B,i_a);
			if(inf_sum(rm.Y,i_a) < minY) minY = inf_sum(rm.Y,i_a);
		}

		//Else case, same as coefficient 0
		R_M rm = MDDConstruction(i_l+1,i_k);
		rmdds.push_back(rm);
		mdds.push_back(rm.mdd);
		allequal = allequal && m==rm.mdd;

		if(rm.B > maxB) maxB = rm.B;
		if(rm.Y < minY) minY = rm.Y;


		bool reusechild = longedges && allequal;

		if(reusechild) {
			rm_new=R_M();
			rm_new.mdd=mdds[0];
			rm_new.B=maxB;
			rm_new.Y=rmdds[0].Y;
		} else {
			mdd_new=new MDD(nodeCount++,X.size() - i_l);
			for(int i = 0; i < mdds.size()-1; i++)
				mdd_new->addChild(X[i_l][i],mdds[i]);
			mdd_new->setElseChild(mdds[mdds.size()-1]);
			L_MDDs[i_l].push_back(mdd_new);
			rm_new=R_M(mdd_new,maxB,minY);
			insertMDD(rm_new,i_l);
		}
	}
	return rm_new;
}

MDD * AMOPBMDDBuilder::addRoot(int k){
    return MDDConstruction(0,k).mdd;
}

int AMOPBMDDBuilder::getmax(const std::vector<int> & v){
	int max = INT_MIN;
	for(int i : v)
		if(i > max)
			max = i;
	return max;
}

// sum(Q) <= k
void AMOPBMDDBuilder::initL() {
   std::vector<int> sums_max(depth);
    L.resize(depth);
    R_M rm_fals,rm_cert;

    sums_max[depth-1] = 0; // for the leaves
    for(int i=depth-2;i>= 0;i--) {
	sums_max[i] = sums_max[i+1] + getmax(Q[i]);
    }

    rm_fals=R_M();
    rm_fals.mdd=MDD::MDDFalse();
    rm_fals.B=INT_MIN;
    rm_fals.Y=-1;

    if(longedges){
      for(int i=0;i<depth-1;i++) {
	  L[i].push_back(rm_fals);
	  rm_cert=R_M();
	  rm_cert.mdd=MDD::MDDTrue();
	  rm_cert.B=sums_max[i];
	  rm_cert.Y=INT_MAX;
	  L[i].push_back(rm_cert);
      }
    }

    rm_cert=R_M();
    rm_cert.mdd=MDD::MDDTrue();
    rm_cert.B=0;
    rm_cert.Y=INT_MAX;
    L[depth-1].push_back(rm_fals);
    L[depth-1].push_back(rm_cert);
}

void AMOPBMDDBuilder::createGraphviz(std::ostream & os, std::vector<std::vector<int> > * labels) const{

  	if(root == NULL)
		return;

  bool * visited = new bool [nodeCount];
  for(int i = 0; i < nodeCount; i++)
	  visited[i]=false;

  os << "digraph G {" << std::endl;

  //Comment full expressions
  os << "#";
   for(int i = 0; i < Q.size()-1; i++){
      os << "{" << Q[i][0];
      for(int j = 1; j < Q[i].size(); j++)
	os << "," << Q[i][j];
      os << "},";
    }
    os << "{" << Q[Q.size()-1][0];
    for(int j = 1; j < Q[Q.size()-1].size(); j++)
      os << "," << Q[Q.size()-1][j];
    os << "} <= " << K  << std::endl;


    for(MDD * m : L_MDDs[0])
		createGraphviz(m,os,visited);

  for(int i = 0; i < L_MDDs.size(); i++){
	  os << "{rank=same";
	  for(int j = 0; j < L_MDDs[i].size(); j++){
		  os << " n_" << L_MDDs[i][j]->getId();
	  }
	  os << "}" << std::endl;
  }
  os << "{rank=same n_" << MDD::MDDTrue()->getId() << " n_" << MDD::MDDFalse()->getId() << "}" << std::endl;

  os << "}" << std::endl;
  delete [] visited;
}


void AMOPBMDDBuilder::createGraphviz(MDD * mdd, std::ostream & os, bool * visited) const{
	visited[mdd->getId()]=true;
	if(mdd->isTrueMDD())
		os << "n_" << mdd->getId() << "[label=\"1\",shape=box];" << std::endl;
	else if(mdd->isFalseMDD())
		os << "n_" << mdd->getId() << "[label=\"0\",shape=box];" << std::endl;
	else{
		os << "n_" << mdd->getId() << "[label=\"";
		int l = depth - mdd->getVarDepth();
		os << "{" << Q[l][0];
		for(int j = 1; j < Q[l].size(); j++)
			os << "," << Q[l][j];
		os << "}";
		if(l < depth-2)
			os << "+[...]";
		//os << " <= [" << B << "," << Y << "]\"];" << std::endl;
		os << "\"];" << std::endl;


		for(int i = 0; i < mdd->getNSelectors(); i++){
			MDD * child = mdd->getChildByIdx(i);
			if(!visited[child->getId()])
				createGraphviz(child,os,visited);
			os << "n_" << mdd->getId() << " -> n_" << child->getId() << " [label=\"" << Q[l][i] << "\"];" << std::endl;
		}
		MDD * child = mdd->getElseChild();
		if(!visited[child->getId()])
			createGraphviz(child,os,visited);
		os << "n_" << mdd->getId() << " -> n_" << child->getId() << " [label=\"else\"];" << std::endl;
	}
}
