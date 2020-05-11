#include <vector>
#include "smtapi.h"


namespace smtapi
{

intprod operator*(const intvar &v, int coef){
		return coef*v;
}

intprod operator*(int coef, const intvar &v){
	intprod p;
	p.varid=v.id;
	p.coef=coef;
	return p;
}

intsum operator-(const intsum &e){
	intsum s;
	for(const intprod & p : e.v){
		intprod p2;
		p2.varid = p.varid;
		p2.coef=-p.coef;
		s.v.push_back(p2);
	}
	return s;
}

intsum operator+(const intsum &e1, const intsum &e2){
	intsum s;
	s.v.insert(s.v.end(),e1.v.begin(),e1.v.end());
	s.v.insert(s.v.end(),e2.v.begin(),e2.v.end());
	return s;
}

intsum operator-(const intsum &e1, const intsum &e2){
	intsum s;
	s.v.insert(s.v.end(),e1.v.begin(),e1.v.end());
	for(const intprod & p : e2.v){
		intprod p2;
		p2.varid = p.varid;
		p2.coef = -p.coef;
		s.v.push_back(p2);
	}
	return s;
}

literal operator!(const literal &l){
	literal l2;
	l2.arith=l.arith;
	l2.sign=!l.sign;
	l2.cmp=l.cmp;
	l2.v=l.v;
	return l2;
}


literal operator<=(const intsum &sum, int x){
	literal l;
	l.arith=true;
	l.sign=true;	
	l.cmp.eq=false;
	l.cmp.s=sum;
	l.cmp.k=x;
	return l;
}

literal operator<=(const intsum &sum1, const intsum &sum2){
	return sum1 - sum2 <= 0;
}

literal operator<=(int x, const intsum &sum){
	return !(sum <= (x-1));
}

literal operator<(const intsum &s1, const intsum &s2){
	return s1 - s2 < 0;
}

literal operator<(const intsum &s, int x){
	return s <= x-1;
}

literal operator<(int x, const intsum &s){
	return !(s<=x);
}

literal operator>=(const intsum &s1, const intsum &s2){
	return s2 <= s1;
}

literal operator>=(const intsum &s, int x){
	return x <= s;
}

literal operator>=(int x, const intsum &s){
	return s <= x;
}

literal operator>(const intsum &s1, const intsum &s2){
	return s2 < s1;
}

literal operator>(const intsum &s, int x){
	return x < s;
}

literal operator>(int x, const intsum &s){
	return s < x;
}


literal operator==(const intsum &s, int x){
	literal l;
	l.arith=true;
	l.sign=true;	
	l.cmp.eq=true;
	l.cmp.s=s;
	l.cmp.k=x;
	return l;
}

literal operator==(const intsum &s1, const intsum &s2){
	return s1 - s2 == 0;
}
literal operator==(int x, const intsum &s){
	return s == x;
}

literal operator!=(const intsum &s1, const intsum &s2){
	return !(s1==s2);
}

literal operator!=(const intsum &s, int x){
	return !(s==x);
}

literal operator!=(int x, const intsum &s){
	return !(x==s);
}


clause operator|(const clause &c1, const clause &c2){
	clause c;
	c.v.insert(c.v.end(),c1.v.begin(),c1.v.end());
	c.v.insert(c.v.end(),c2.v.begin(),c2.v.end());
	return c;
}

clause operator||(const clause &c1, const clause &c2){
	return c1 | c2;
}

}


