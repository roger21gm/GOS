#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include "util.h"
#include <utility>
#include <algorithm>
#include <functional>
#include <math.h>

using namespace smtapi;

namespace util
{


void sortCoefsDecreasing(std::vector<int> & Q, std::vector<literal> & X){
  int length = Q.size();

    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (Q[j] < Q[j+1])
            {
                std::swap(Q[j], Q[j+1]);
					 std::swap(X[j],X[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortCoefsDecreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X){
  int length = Q.size();

    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (Q[j][0] < Q[j+1][0])
            {
                std::swap(Q[j], Q[j+1]);
					 std::swap(X[j],X[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortCoefsIncreasing(std::vector<int> & Q, std::vector<literal> & X){
  int length = Q.size();

    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (Q[j] > Q[j+1])
            {
                std::swap(Q[j], Q[j+1]);
					 std::swap(X[j],X[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortCoefsIncreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X){
  int length = Q.size();

    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (Q[j][0] > Q[j+1][0])
            {
                std::swap(Q[j], Q[j+1]);
					 std::swap(X[j],X[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void sortBySimilarityIncreasing(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X){
	int n = Q.size();
	if(n<=1) return;
	int * order = new int[n];
	int ** distance = new int * [n];

	for(int i = 0; i < n; i++)
		distance[i] = new int[n];

	int mindistance = INT_MAX;
	int mini=0;
	int minj=0;
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			std::set<int> sums;
			std::set<int> qi; qi.insert(0);// else
			std::set<int> qj; qj.insert(0);// else

			for(int k : Q[i])
				qi.insert(k);

			for(int l: Q[j])
				qj.insert(l);

			for(int k : qi)
				for(int l : qj)
					sums.insert(k+l);
			distance[i][j]=sums.size();
			distance[j][i]=sums.size();
			if(distance[i][j]<mindistance){
				mindistance=distance[i][j];
				mini=i;
				minj=j;
			}
		}
	}

	std::set<int> toorder;
	for(int i = 0; i < n; i++)
		toorder.insert(i);

	toorder.erase(mini);
	toorder.erase(minj);

	order[0]=mini;
	order[1]=minj;

	for(int i = 2; i < n; i++){
		mindistance = INT_MAX;
		int next;
		for(int j : toorder){
			if(distance[j][order[i-1]] < mindistance){
				mindistance=distance[j][order[i-1]];
				next = j;
			}
		}
		order[i]=next;
		toorder.erase(next);
	}

	setOrder(Q,order);
	setOrder(X,order);

	delete [] order;
	for(int i = 0; i < n; i++)
		delete [] distance[i];
	delete [] distance;
}



void sortCoefsTotalizer(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X, int K){

	int n = Q.size();
	if(n <= 1)
		return;


	int m = (int) ceil(log2(n));
	std::vector<std::pair<int, int> > tree(2*n-1);

	std::vector<treenode *> nodes(n);
	std::vector<treenode *> newnodes;
	std::vector<treenode *> forest;

	for(int i = 0; i < n; i++)
		nodes[i] = new treenode(i,std::set<int>(Q[i].begin(),Q[i].end()));

	while(nodes.size()!=1){
		while(nodes.size() >= 2){
			std::set<int> sums;
			int l;
			int r;
			for(int i = 0; i < nodes.size()-1; i++){
				for(int j = i+1; j < nodes.size(); j++){
					std::set<int> s;
					s.insert(nodes[i]->coefs.begin(),nodes[i]->coefs.end());
					s.insert(nodes[j]->coefs.begin(),nodes[j]->coefs.end());
					for(int ii : nodes[i]->coefs)
						for(int jj : nodes[j]->coefs)
							if(ii+jj <= K)
								s.insert(ii + jj);

					if(s.size() < sums.size() || sums.empty()){
						sums=s;
						l = i;
						r = j;
					}
				}
			}
			newnodes.push_back(new treenode(nodes[l],nodes[r],sums));
			nodes.erase(nodes.begin()+r);
			nodes.erase(nodes.begin()+l);//l has to be erased second to not shift r
		}
		if(!nodes.empty())
			forest.push_back(nodes[0]);
		nodes = newnodes;
		newnodes.clear();
	}

	std::vector<std::vector<int> > Q2;
	std::vector<std::vector<literal> > X2;

	forest.push_back(nodes[0]);

	for(int i = forest.size()-1; i >=0 ; i--){
		addElementsToOrder(forest[i],Q,X,Q2,X2);
		delete forest[i];
	}

	int nlast = (2*n -1) - (1<<((int)ceil(log2(n)))) + 1;
//	std::cout << "N last: " << nlast << std::endl;
	if(nlast != 0)
		rotate(Q.begin(),Q.begin()+nlast,Q.end());
	Q=Q2;
	X=X2;
}

void sortCoefsTotalizerDifs(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> > & X){

	int n = Q.size();
	if(n <= 1)
		return;

	std::vector<std::pair<int,int> > sets;
	std::vector<std::vector<int> > Q2=Q;
	std::vector<std::vector<literal> > X2=X;

    for(int i = 0; i < n; i++){
		std::set<int> s(Q[i].begin(),Q[i].end());
		sets.push_back(std::pair<int,int>(i,s.size()));
	}

	int pos = 0;
	while(!sets.empty()){
		int idx;
		int s = INT_MAX;
		for(int i = 0; i < sets.size(); i++){
			if(sets[i].second < s){
				idx = i;
				s = sets[i].second;
			}
		}
		Q[pos] = Q2[sets[idx].first];
		X[pos] = X2[sets[idx].first];
		pos++;
		sets.erase(sets.begin()+idx);
	}
}


void addElementsToOrder(treenode * node,
		const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X,
		std::vector<std::vector<int> > & Q2, std::vector<std::vector<literal> > & X2){

	if(node->lchild == NULL){
		Q2.push_back(Q[node->idx]);
		X2.push_back(X[node->idx]);
	}
	else{
		addElementsToOrder(node->lchild,Q,X,Q2,X2);
		addElementsToOrder(node->rchild,Q,X,Q2,X2);
	}
}

template<typename T>
void setOrder(std::vector<T> & data, int * order){
	std::vector<T> aux = data;
	for(int i = 0; i < data.size(); i++){
		data[i]=aux[order[i]];
	}
}

bool isPowerOf2(int x) {
    return x > 0 && !(x & (x-1));
}

bool nthBit(int x, int n){
	return (x >> n) & 1;
}

int cardinality(int x){
	int count = 0; 
	while(x) 
	{ 
	    count += x & 1; 
	    x >>= 1; 
	} 
	return count; 
}



std::string getFileName(const std::string& s) {
   char sep = '/';
#ifdef _WIN32
   sep = '\\';
#endif
   size_t i = s.rfind(sep, s.length());
   if (i != std::string::npos) {
      return(s.substr(i+1, s.length() - i));
   }
   return("");
}


void floydWarshall(int ** adjMatrix, int size){
	for (int k=0;k<size;k++){
		for (int i=0;i<size;i++){
			for (int j=0;j<size;j++){
				if (adjMatrix[i][k]>=0 && adjMatrix[k][j]>=0) {
					int aux=adjMatrix[i][k]+adjMatrix[k][j];
					if (aux>adjMatrix[i][j])
						adjMatrix[i][j]=aux;
				}
			}
		}
	}
}


void insertSortedIfNotExists(std::vector<int> & v, int x) {
	std::vector<int>::iterator it = std::lower_bound(v.begin(),v.end(),x,std::greater<int>());
	if(it==v.end() || (*it)!=x){
		v.insert(it,x);
	}
}


void reduceByEO(std::vector<std::vector<int> > & Q, std::vector<std::vector<literal> >& X, int & K){

	for(int i = 0; i < Q.size(); i++){
		int min = *min_element(Q[i].begin(),Q[i].end());
		for(int j = 0; j < Q[i].size(); j++){
			if(Q[i][j]== min){
				Q[i].erase(Q[i].begin()+j);
				X[i].erase(X[i].begin()+j);
				j--;
			}
			else
				Q[i][j]-=min;
		}
		if(Q[i].empty()){
			Q.erase(Q.begin()+i);
			X.erase(X.begin()+i);
			i--;
		}
		K-=min;
	}

}


void printAMOPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > & X, int K){
	for(const std::vector<int> & q : Q){
		std::cout << "<";
		for(int qi : q){
			std::cout << qi << " ";
		}
		std::cout << "> ";
	}
	std::cout << "   <=  " << K << std::endl;
}

void PBtoAMOPB(const std::vector<int> & Q, const std::vector<literal> & X, std::vector<std::vector<int> > & QQ, std::vector<std::vector<literal> > &XX){
	QQ.clear();	QQ.resize(Q.size());
	XX.clear();	XX.resize(Q.size());
	for(int i = 0; i < Q.size(); i++){
		QQ[i].push_back(Q[i]);
		XX[i].push_back(X[i]);
	}
}


void AMOPBtoPB(const std::vector<std::vector<int> > & Q, const std::vector<std::vector<literal> > &X, std::vector<int> & QQ, std::vector<literal> & XX){
	QQ.clear();
	XX.clear();
	for(int i = 0; i < Q.size(); i++){
		for(int j = 0; j < Q[i].size(); j++){
			QQ.push_back(Q[i][j]);
			XX.push_back(X[i][j]);
		}
	}


}

int sum(const std::vector<int> & v){
	int s = 0;
	for(int i : v)
		s+=i;
	return s;
}

}


