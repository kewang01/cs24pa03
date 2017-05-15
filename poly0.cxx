#include<cassert>
#include<iostream>
#include<cmath>
#include<climits>
#include "poly0.h"
using namespace std;

namespace main_savitch_3
{
  const unsigned int polynomial::CAPACITY;
  const unsigned int polynomial::MAX_EX;

  polynomial::polynomial(double c,unsigned int exponent){
    assert(exponent<=MAX_EX);
    for(unsigned int i=0;i<CAPACITY;i++){
      coef[i]=0;
    }
    coef[exponent]=c;
    current_degree=exponent;
  }

  void polynomial::add_to_coef(double amount,unsigned int exponent){
    assert(exponent<=MAX_EX);
    coef[exponent]+=amount;
    if(coef[exponent]!=0 && exponent>current_degree){
      current_degree=exponent;
    }
    if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)<CAPACITY){
      current_degree=previous_term(exponent);
    }
    if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)>=CAPACITY){
      current_degree=0;
    }
    
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    assert(exponent<=MAX_EX);
    coef[exponent]=coefficient;
    if(coefficient!=0 && exponent>current_degree){
      current_degree=exponent;
    }
    if(coefficient==0 && exponent==current_degree && previous_term(exponent)<CAPACITY){
      current_degree=previous_term(exponent);
    }
    if(coefficient==0 && exponent==current_degree && previous_term(exponent)>=CAPACITY){
      current_degree=previous_term(exponent);
    }
    
  }

  void polynomial::clear(){
    for(int i=0;i<current_degree+1;i++){
      coef[i]=0.0;
    }
    current_degree=0;
  }

  double polynomial:: coefficient(unsigned int exponent) const{
    if(exponent>MAX_EX){
      return 0;
    }
    return coef[exponent];
  }

  polynomial polynomial::derivative() const{
    polynomial deriv;
    for(unsigned int i=0;i<current_degree;i++){
      deriv.coef[i]=(i+1)*coef[i+1];
    }
    if(current_degree==0)
      deriv.current_degree=0;
    else
      deriv.current_degree=current_degree-1;
    return deriv;
  }

  double polynomial::eval(double x) const{
    double sum=0;
    for(int i=0;i<=current_degree;i++){
      sum=sum+coef[i]*pow(x,i);
    }
    return sum;
  }

  unsigned int polynomial::next_term(unsigned int e) const{
    if(e>=current_degree){
      return 0;
    }
    unsigned int i=e+1;
    while(coef[i]==0 && i<=current_degree){
      i++;
    }
    return i;
  }

  unsigned int polynomial::previous_term(unsigned int e) const{
    if(e==0){
      return UINT_MAX;
    }
    unsigned int i=e-1;
    while(coef[i]==0 && i>0){
      i--;
    }
    if(i==0 && coef[0]==0){
      return UINT_MAX;
    }
    else
      return i;
  }


  polynomial operator -(const polynomial& p1,const polynomial& p2){
    polynomial substr;
    for(unsigned int i=0;i<=polynomial::MAX_EX;i++){
      substr.assign_coef(p1.coefficient(i)-p2.coefficient(i),i);
    }
    return substr;
  }

  polynomial operator +(const polynomial& p1,const polynomial& p2){
    polynomial sum;
    for(unsigned int i=0;i<polynomial::MAX_EX;i++){
      sum.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
    }
    return sum;
  }

  polynomial operator *(const polynomial& p1,const polynomial& p2){
    assert(p1.degree()+p2.degree()<=polynomial::MAX_EX);
    polynomial product;
    for(unsigned int i=0;i<=p1.degree();i++){
      for(unsigned int j=0;j<=p2.degree();j++){
	product.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
      }
    }
    return product;
  }

  std::ostream& operator <<(std::ostream& out,const polynomial& p){
    if(p.degree()==0 && p.coefficient(0)==0){
      out<<0;
      return out;
    }

    for(unsigned int i=0;i<=polynomial::MAX_EX;i++){
      out<<out<<"+"<<p.coefficient(i)<<"x^"<<i;
    }
    
    // out<<"";  
    //for(unsigned int i=p.degree();i>=0;i--){
    // if(p.coefficient(i)!=0){
    //out<<"+"<<"("<<p.coefficient(i)<<")"<<"x^"<<i;
    // }
    //}
    //out<<p.degree()<<" "<<p.coefficient(5);
    return out;
  }
    
      
}

      
      

  
    




