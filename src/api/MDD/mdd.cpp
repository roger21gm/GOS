#include "mdd.h"
#include <list>

MDD * MDD::mddtrue = NULL;
MDD * MDD::mddfalse = NULL;

MDD::MDD(int id,int nvars) {
	this->id = id;
	istrivialtrue=false;
	istrivialfalse=false;
	vardepth=nvars+1;
	realdepth = 0;
}

MDD::MDD(bool b){
	id = b ? 1 : 0;
	istrivialtrue = b;
	istrivialfalse = !b;
	vardepth = 1;
	realdepth = 1;
}


MDD * MDD::MDDFalse() {
	if(mddfalse==NULL)
		mddfalse = new MDD(false);
	return mddfalse;
}

MDD * MDD::MDDTrue() {
	if(mddtrue==NULL)
		mddtrue = new MDD(true);
	return mddtrue;
}

MDD::~MDD(){}

const std::vector<literal> & MDD::getSelectors() const{
	return selectors;
}

MDD * MDD::getChildByIdx(int idx) const{
	return children[idx];
}

MDD * MDD::getChild(literal selector)const{
	for(int i = 0; i < selectors.size(); i++)
		if(selectors[i].v.id==selector.v.id)
			return children[i];
	return NULL;
}

MDD * MDD::getElseChild()const{
	return elsechild;
}

int MDD::getId() const{
	return id;
}
	
int MDD::getVarDepth() const{
	return vardepth;
}

int MDD::getRealDepth() const{
	return realdepth;
}

int MDD::getSize() const{
	if(isLeafMDD()) return 1;
	
	bool * visited = new bool[id+1];
	for(int i = 0; i < id+1; i++)
		visited[i]=false;
	int size = 0;
	getSize(visited,size);
	delete [] visited;
	return size;
}

void MDD::getSize(bool * visited, int & size) const{
	if(!visited[id]){
		visited[id]=true;
		size+=1;
		if(!isLeafMDD()){
			for(MDD * child : children)
				child->getSize(visited, size);
			elsechild->getSize(visited, size);
		}
	}
}

int MDD::getIdBasedSize() const{
	return isLeafMDD() ? 1 : id+1;
}
	
int MDD::getLayerWidth() {
	bool * visited = new bool[id+1];
	for(int i = 0; i < id+1; i++)
		visited[i]=false;
 	std::list<MDD *> q;
	std::list<MDD *> * layers = new std::list<MDD *>[getVarDepth()];
	q.push_back(this);
	visited[getId()]=true;
	
	while(!q.empty()){
		MDD * m = q.front();
		q.pop_front();
		layers[m->getVarDepth()-1].push_back(m);
		if(!m->isLeafMDD()){
			for(MDD * child : m->children){
				if(!visited[child->getId()]){
					q.push_back(child);
					visited[child->getId()]=true;
				}
			}
			MDD * child = m->elsechild;
			if(!visited[child->getId()]){
				q.push_back(child);
				visited[child->getId()]=true;
			}
		}
	}
	int maxWidth = 0;
	for(int i = 0; i < getVarDepth(); i++){
		if(layers[i].size()>maxWidth)
			maxWidth = layers[i].size();
	}
	
	delete [] layers;	
	delete [] visited;

	return maxWidth;
}

int MDD::getNBinClauses() const{
	return isLeafMDD() ? 0 : getSize()-2;
}

int MDD::getNTernClauses(){
	if(isLeafMDD())
		return 0;
	
	int nclauses = 0;
		
	bool * visited = new bool[id+1];
	for(int i = 0; i < id+1; i++)
		visited[i]=false;
 	std::list<MDD *> q;
	q.push_back(this);
	visited[getId()]=true;
	
	while(!q.empty()){
		MDD * m = q.front();
		q.pop_front();
		if(!m->isLeafMDD()){
			for(MDD * child : m->children){
				if(child != m->elsechild)
					nclauses++;
				if(!visited[child->getId()]){
					q.push_back(child);
					visited[child->getId()]=true;
				}
			}
			MDD * child = m->elsechild;
			if(!visited[child->getId()]){
				q.push_back(child);
				visited[child->getId()]=true;
			}
		}
	}

	delete [] visited;

	return nclauses;
}

int MDD::getNSelectors() const{
	return selectors.size();
}

bool MDD::isLeafMDD() const{
	return istrivialtrue || istrivialfalse;
}

bool MDD::isTrueMDD() const{
	return istrivialtrue;
}

bool MDD::isFalseMDD() const{
	return istrivialfalse;
}

std::pair<literal,MDD*> MDD::getSelectorAndChild(int idx) const{
	return std::pair<literal,MDD*> (selectors[idx],children[idx]);
}

void MDD::addChild(literal selector, MDD * child){
	children.push_back(child);
	selectors.push_back(selector);
	if(child->realdepth >= this->realdepth)
		this->realdepth = child->realdepth+1;
}

void MDD::setElseChild(MDD * child){
	elsechild = child;
	if(child->realdepth >= this->realdepth)
		this->realdepth = child->realdepth+1;
}

std::ostream & operator<<(std::ostream & s, const MDD & m){
	bool * printed = new bool[m.id+1];
	for(int i = 0; i <= m.id; i++)
		printed[i]=false;
	m.print(s,printed);
	delete [] printed;
	return s;
}

void MDD::print(std::ostream & s, bool *printed) const{
	if(!printed[id]){
		printed[id] = true;
		if(istrivialtrue)
			s << "id:1, vardepth:" << vardepth << ", realdepth:" << realdepth  << std::endl;
		else if(istrivialfalse)
			s << "id:0, vardepth:" << vardepth << ", realdepth:" << realdepth  << std::endl;
		else{
			s << "id:" << id << ", vardepth:" << vardepth << ", realdepth:" << realdepth << std::endl;
			for(int i = 0; i < selectors.size(); i++)
				s << "sel " << ((selectors[i].sign ? "" : "-") + selectors[i].v.id) 
				<< ":" << children[i]->getId() << std::endl; 
			s << "else:" << elsechild->getId() << std::endl;
			
			for(int i = 0; i < selectors.size(); i++)
				children[i]->print(s,printed);
			elsechild->print(s,printed);
		}
	}
}

