#include "amopbbddbuilder.h"
#include "./util/util.h"



AMOPBBDDBuilder::AMOPBBDDBuilder(const std::vector<std::vector<int> > &Q,const std::vector<std::vector<literal> > &X, int K, bool longedges)
	: MDDBuilder(){
	this->Q=Q;
	this->X=X;
	this->K=K;

	this->longedges=longedges;

	this->depth = 1;
	for(int i = 0; i < Q.size(); i++){
		this->depth += Q[i].size();
		util::sortCoefsDecreasing(this->Q[i],this->X[i]);
	}

	this->initL();
	this->L_BDDs.resize(depth-1);
}

AMOPBBDDBuilder::AMOPBBDDBuilder(const std::vector<int> &Q,const std::vector<literal> &X, int K, bool longedges)
	: MDDBuilder(){

	for(int q : Q)
		this->Q.push_back(std::vector<int>(1,q));

	for(literal x : X)
 		this->X.push_back(std::vector<literal>(1,x));

	this->K=K;

	this->longedges=longedges;

	this->depth = Q.size()+1;
	this->initL();
	this->L_BDDs.resize(Q.size());
}

AMOPBBDDBuilder::~AMOPBBDDBuilder(){
  for(const std::vector<MDD *> & layer : L_BDDs)
	for(MDD * m : layer)
		delete m;
}

MDD * AMOPBBDDBuilder::buildMDD(){
	return BDDConstruction(0,0,0,K).bdd;
}

void AMOPBBDDBuilder::mostrarL(int i_l) {
    int i=0,j=0,max=0;
    R_B rb;

    if(i_l>0) {
        max=i_l+1;
    } else {
        max=L.size();
    }

    for(i=i_l;i<max;i++) {
        std::cout << "Layer " << i << ":" << std::flush;
        for(j=0;j<L[i].size();j++) {
            rb=L[i][j];
            std::cout << "{" << rb.B << "," << rb.Y << "}"<< std::flush;
        }
        std::cout << std::endl;
    }
}

int AMOPBBDDBuilder::inf_sum(int possible_inf, int x){
  if(possible_inf == INT_MAX)
    return INT_MAX;
  else if(possible_inf == INT_MIN)
    return INT_MIN;
  else return possible_inf + x;

}

//Insert ordered with respect to the intervals [B,Y].
//The vector 'layer' is order, so we can use dicotomic search
// Precondition: rb_in doesnt exists in layer
void AMOPBBDDBuilder::insertBDD(R_B rb_in,int i_l) {
    R_B act;

    std::vector<R_B> & layer=L[i_l];

    if(layer.empty()){
      layer.push_back(rb_in);
      return;
    }
    int n=layer.size();
    int i=0,min=0,max=n-1;

    i=(max-min)/2;

    while(min<max) {
        act=layer[i];
        if(act.B>rb_in.Y){
            max=i-1;
        } else { //if(act->Y<rb_in->B) { //otherwise
            min=i+1;
        }
        i=min+(max-min)/2;
    }

    act=layer[i]; // min=max=i
    std::vector<R_B>::iterator it;
    it = L[i_l].begin();
    if(act.B>rb_in.Y){
        //i==i;
    } else { //if(act.Y<rb_in.B) { //otherwise
        i++;
    }
    L[i_l].insert(it+i,rb_in);

}

R_B AMOPBBDDBuilder::searchBDD(int i_k,int l) {
	 std::vector<R_B> & layer = L[l];

	 R_B res,act;
    res.bdd = NULL;
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

R_B AMOPBBDDBuilder::BDDConstruction(int global_l, int local_l, int l, int i_k) {
	R_B rb_new=searchBDD(i_k, l);
	if(rb_new.bdd==NULL){
		int q = Q[global_l][local_l];
		int nextlocal = (local_l+1 == Q[global_l].size()) ? 0 : local_l+1;
		int nextglobal = (nextlocal == 0) ? global_l+1 : global_l;
		int nextl = l + (Q[global_l].size()- local_l);
		R_B rbtrue = BDDConstruction(global_l+1, 0, nextl, i_k - q);
		R_B rbfalse = BDDConstruction(nextglobal, nextlocal, l+1, i_k);

		int B = std::max(inf_sum(rbtrue.B,q),rbfalse.B);
		int Y = std::min(inf_sum(rbtrue.Y,q),rbfalse.Y);

		bool reusechild = longedges && (rbtrue.bdd == rbfalse.bdd);

		if(reusechild) {
			rb_new=R_B();
			rb_new.bdd=rbfalse.bdd;
			rb_new.B=B;
			rb_new.Y=Y;
		} else {
			MDD * bdd_new=new MDD(nodeCount++,depth - l - 1);
			bdd_new->addChild(X[global_l][local_l],rbtrue.bdd);
			bdd_new->setElseChild(rbfalse.bdd);
			L_BDDs[l].push_back(bdd_new);
			rb_new=R_B(bdd_new,B,Y);
			insertBDD(rb_new,l);
		}
	}
	return rb_new;
}

int AMOPBBDDBuilder::getmax(const std::vector<int> & v){
 int max = INT_MIN;
 for(int i : v)
  if(i > max)
    max = i;
 return max;
}

int AMOPBBDDBuilder::getmax(const std::vector<int> & v, int init){
 int max = INT_MIN;
 for(int i = init; i < v.size(); i++)
  if(v[i] > max)
    max = v[i];
 return max;
}

void AMOPBBDDBuilder::initL() {
   std::vector<int> sums_max(Q.size()+1);
    L.resize(depth);
    R_B rb_fals,rb_cert;

    sums_max[Q.size()] = 0; // for the leaves
	 for(int i = Q.size()-1; i >= 0; i--)
		sums_max[i] = sums_max[i+1] + getmax(Q[i]);

    rb_fals=R_B();
    rb_fals.bdd=MDD::MDDFalse();
    rb_fals.B=INT_MIN;
    rb_fals.Y=-1;

	if(longedges){
		int global_l = 0;
		int local_l = 0;
		for(int i=0;i<depth-1;i++) {
			L[i].push_back(rb_fals);
			rb_cert=R_B();
			rb_cert.bdd=MDD::MDDTrue();
			rb_cert.B=sums_max[global_l+1] + getmax(Q[global_l],local_l);
			rb_cert.Y=INT_MAX;
			L[i].push_back(rb_cert);

			local_l++;
			if(local_l==Q[global_l].size()){
				local_l = 0;
				global_l++;
			}
		}
    }

    rb_cert=R_B();
    rb_cert.bdd=MDD::MDDTrue();
    rb_cert.B=0;
    rb_cert.Y=INT_MAX;
    L[depth-1].push_back(rb_fals);
    L[depth-1].push_back(rb_cert);
}

//Pre: v1 and v2 belong to the mdd
bool AMOPBBDDBuilder::hasInconsistentPath(literal v1, literal v2) const {
   //Search the layer of the top-most literal (v1 or v2)
	int layer1st = 0, layer2nd = 0, layer = 0;
	bool found1st = false;
	bool found2nd = false;
	int i = 0;
	while(!found2nd && i < X.size()){
		int  j = 0;
		while(!found2nd && j < X[i].size()){
			if(!found1st){
				if(X[i][j].v.id==v1.v.id || X[i][j].v.id==v2.v.id){
					found1st = true;
					layer1st = layer;
				}
			}
			else{
				if(X[i][j].v.id==v1.v.id || X[i][j].v.id==v2.v.id){
					found2nd=true;
					layer2nd = layer;
				}
			}
			layer++;
			j++;
		}
		i++;
	}

	std::list<MDD *> tovisit;
	bool * visited = new bool[root->getId()+1];
	for(int i = 0; i < root->getId()+1; i++)
		visited[i]=false;

	for(MDD * m : L_BDDs[layer1st])
		if(m->getVarDepth() == depth - layer1st) //If the node of v1 is not supressed
			tovisit.push_back(m->getChildByIdx(0)); //Insert the node with the variable assigned to true into the queue

	bool result = false;
	while(!result && !tovisit.empty()){
		MDD * m = tovisit.front();
		tovisit.pop_front();
		if(!visited[m->getId()]){
			if(m->getVarDepth() == depth - layer2nd)
				result = true;
			else if(m->getVarDepth() < depth - layer2nd){
				tovisit.push_back(m->getChildByIdx(0));
				tovisit.push_back(m->getElseChild());
			}
			visited[m->getId()]=true;
		}
	}

	delete [] visited;
	return result;
}

bool AMOPBBDDBuilder::hasInconsistentPath(const std::list<std::pair<literal,literal> > & mutexes) const {
	for(const std::pair<literal,literal> & mutex : mutexes)
		if(hasInconsistentPath(mutex.first, mutex.second))
			return true;

	return false;
}

void AMOPBBDDBuilder::createGraphviz(std::ostream & os, std::vector<std::vector<int> > * labels) const{
	if(root == NULL)
		return;

  bool * visited = new bool [root->getId()+1];
  int * global_idx = new int[depth];
  int * local_idx = new int[depth];
  int l = 0;
  for(int i =0; i < Q.size(); i++){
	  for(int j = 0; j < Q[i].size(); j++){
		  global_idx[l]=i;
		  local_idx[l]=j;
		  l++;
	  }
  }

  for(int i = 0; i < root->getId()+1; i++)
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


  createGraphviz(root,os,visited,global_idx,local_idx);

  for(int i = 0; i < L_BDDs.size(); i++){
	  os << "{rank=same";
	  for(int j = 0; j < L_BDDs[i].size(); j++){
		  os << " n_" << L_BDDs[i][j]->getId();
	  }
	  os << "}" << std::endl;
  }
  os << "{rank=same n_" << MDD::MDDTrue()->getId() << " n_" << MDD::MDDFalse()->getId() << "}" << std::endl;

  os << "}" << std::endl;
  delete [] global_idx;
  delete [] local_idx;
  delete [] visited;
}


void AMOPBBDDBuilder::createGraphviz(MDD * mdd, std::ostream & os, bool * visited,int * global_idx,int * local_idx) const{
	visited[mdd->getId()]=true;
	if(mdd->isTrueMDD())
		os << "n_" << mdd->getId() << "[label=\"1\",shape=box];" << std::endl;
	else if(mdd->isFalseMDD())
		os << "n_" << mdd->getId() << "[label=\"0\",shape=box];" << std::endl;
	else{
		os << "n_" << mdd->getId() << "[label=\"";
		int l = depth - mdd->getVarDepth();
		int glob = global_idx[l];
		int loc = local_idx[l];

		os << Q[glob][loc];
		if(l < depth-2)
			os << "+[...]\"";
	  //os << " <= [" << B << "," << Y
		os << "];" << std::endl;

		for(int i = 0; i < mdd->getNSelectors(); i++){
			MDD * child = mdd->getChildByIdx(i);
			if(!visited[child->getId()])
				createGraphviz(child,os,visited,global_idx,local_idx);
			os << "n_" << mdd->getId() << " -> n_" << child->getId() << " [label=\"" << Q[glob][loc] << "\"];" << std::endl;
		}
		MDD * child = mdd->getElseChild();
		if(!visited[child->getId()]) createGraphviz(child,os,visited,global_idx,local_idx);
		os << "n_" << mdd->getId() << " -> n_" << child->getId() << " [label=\"else\"];" << std::endl;
	}
}
