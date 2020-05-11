#ifndef SMTAPI_DEFINITION
#define SMTAPI_DEFINITION

#include <vector>


/*
 * This API is meant to provide a concise and intuitive way to define 
 * SMT clauses by means of operator overriding.
 * It only supports the theory of Linear Integer Arithmetic
 * It lets expressions of the form:
 * 	clause c = b1 | b2 | !b3
 * 	clause c = b1 | 3*i1 + i2 >= 0 | !b3
 * 	clause c = i1 == i2
 * 	intsum s = i1; s += 2*i2; s-=2*i3; clause c = !(s <= 0); 
 * 	clause c; c|= b1; c|= b2 | !b3;
 * Integer constants can never occur in the same side of a (in)equality
 * than integer variables. Ex: (i1 + 2 <= i2) is not allowed.
 * Boolean and Int variables are both identified by integer ids. 
 * It is the responsibility of the user of the API to ensure a coherent
 * identification of the variables.
 * The following type promotions are allowed by means of constructors.
 * 	- boolvar -> literal
 * 	- intvar -> intprod
 * 	- intvar -> intsum
 * 	- intprod -> intsum
 * 	- boolvar -> clause
 * 	- literal -> clause
 */


namespace smtapi
{

//Boolean variable type
struct boolvar {
	int id;
	boolvar(){id=0;}
	boolvar(const boolvar &v){
		this->id = v.id;
	}
};

//Integer variable type
struct intvar {
	int id;
	intvar(){id=0;}
	intvar(const intvar &v){
		this->id = v.id;
	}
};

//Integer product between a variable and a coefficient.
struct intprod {
	int varid; //Id of the Int variable
	int coef; //Coefficient
	intprod(){}
	intprod(const intprod &p){
		this->varid = p.varid;
		this->coef = p.coef;
	}
	intprod(const intvar &v){
		varid=v.id;
		coef=1;
	}
};


//Sum of integer products
struct intsum{
	std::vector<intprod> v; //Products of the sum
	intsum(){};
	intsum(const intsum & s){
		this->v = s.v;
	}
	intsum(const intprod &p){
		v.push_back(p);
	}
	intsum(const intvar &var){
		v.push_back(var);
	}
	intsum& operator+=(const intsum &e){
		v.insert(v.end(),e.v.begin(),e.v.end());
		return *this;
	}
	intsum& operator-=(const intsum &e){
		for(const intprod & p : e.v){
			intprod p2;
			p2.varid = p.varid;
			p2.coef = -p.coef;
			v.push_back(p2);
		}
		return *this;
	}
};

//Arithmetic expression. Either an equality (sum == constant) 
// or a strict minus inequality (sum <= constant)
struct arithcmp{
	intsum s; //lhs sum of intprod
	int k; //rhs int constant
	bool eq; //true if ==, false if '<='
	arithcmp(){}
	arithcmp(const arithcmp & a){
		this->s = a.s;
		this->eq = a.eq;
		this->k = a.k;
	}
};


//Literal type. It is either a variable or a (in)equality, 
// or a negation of a variable or a (in)equality,
struct literal{
	bool sign; //false iff negated
	bool arith; //true if (in)equality, false if boolvar
	boolvar v; //boolvar, only considered if arith==false
	arithcmp cmp; //(in)equality, only considered if arith=true
	literal(){}
	literal(const literal & l){
			this->sign = l.sign;
			this->arith = l.arith;
			this->v = l.v;
			this->cmp = l.cmp;
	}
	literal(const boolvar &var){
		sign=true;
		arith=false;
		v=var;
	}
	literal(const arithcmp &c){
		sign=true;
		arith=true;
		cmp=c;
	}
};

//Clause type, defined as a std::vector of literals
struct clause{
	std::vector<literal> v;
	clause(){}
	clause(const clause & c){
		this->v = c.v;
	}
	clause(const literal &lit){
		v.push_back(lit);
	}
	clause(const boolvar &b){
		v.push_back(b);
	}
	clause(const std::vector<literal> & vec){
		v=vec;
	}
	clause& operator|=(const clause &c){
		v.insert(v.end(),c.v.begin(),c.v.end());
		return *this;
	}
};

intprod operator*(const intvar &v,int coef);
intprod operator*(int coef, const intvar &v);
intsum operator-(const intsum &e);
intsum operator+(const intsum &e1, const intsum &e2);
intsum operator-(const intsum &e1, const intsum &e2);
literal operator!(const literal &l);
literal operator<(const intsum &s, int x);
literal operator<(const intsum &s1, const intsum &s2);
literal operator<(int x, const intsum &s);
literal operator<=(const intsum &s1, const intsum &s2);
literal operator<=(const intsum &s, int x);
literal operator<=(int x, const intsum &s);
literal operator>=(const intsum &s1, const intsum &s2);
literal operator>=(const intsum &s, int x);
literal operator>=(int x, const intsum &s);
literal operator>(const intsum &s1, const intsum &s2);
literal operator>(const intsum &s, int x);
literal operator>(int x, const intsum &s);
literal operator==(const intsum &s1, const intsum &s2);
literal operator==(const intsum &s, int x);
literal operator==(int x, const intsum &s);
literal operator!=(const intsum &s1, const intsum &s2);
literal operator!=(const intsum &s, int x);
literal operator!=(int x, const intsum &s);
clause operator|(const clause &c1, const clause &c2);	
clause operator||(const clause &c1, const clause &c2);

}

#endif

