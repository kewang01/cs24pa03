#include<cassert>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<climits>
#include "poly1.h"

using namespace std;

namespace main_savitch_4
{
  const unsigned int polynomial::DEFAULT_CAPACITY;

  polynomial::polynomial(double c,unsigned int exponent){
    if(exponent<DEFAULT_CAPACITY){
      coef=new double[DEFAULT_CAPACITY];
      size=DEFAULT_CAPACITY;
      for(unsigned int i=0;i<DEFAULT_CAPACITY;i++){
	coef[i]=0;
      }
      if(c==0){
	current_degree=0;
      }
      else{
	coef[exponent]=c;
	current_degree=exponent;
      }
    }
    else{
      coef=new double[exponent+1];
      size=exponent+1;
      for(unsigned int i=0;i<=exponent;i++){
	coef[i]=0;
      }
      if(c==0){
	current_degree=0;
      }
      else{
	coef[exponent]=c;
	current_degree=exponent;
      }
    }

  }

  polynomial::polynomial(const polynomial& source){
    coef=new double[source.size];
    size=source.size;
    current_degree=source.current_degree;
    copy(source.coef,source.coef+size,coef);
  }

  polynomial::~polynomial(){
    delete [] coef;
  }

  

  void polynomial::reserve(unsigned int number){
    if(number<=size){
      number=size;
    }
    double* larger;
    larger=new double[number];
    copy(coef,coef+size,larger);
    delete [] coef;
    coef=larger;
    size=number;
  }

  void polynomial::operator=(const polynomial& source){
    if(this==&source)
      return;
    double *ass=new double[source.size];
    delete [] coef;
    coef=ass;
    size=source.size;
    current_degree=source.current_degree;
    copy(source.coef,source.coef+size,coef);
  }

  void polynomial::add_to_coef(double amount,unsigned int exponent){
    if(exponent<size){
      coef[exponent]+=amount;
      if(coef[exponent]!=0 && exponent>current_degree){
	current_degree=exponent;
      }
      if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)<size){
	current_degree=previous_term(exponent);
      }
      if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)>=size){
	current_degree=0;
      }
    }
    else{
      reserve(exponent+1);
      size=exponent+1;
      coef[exponent]+=amount;
      if(amount!=0){
	current_degree=exponent;
      }
    }
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    if(exponent<size){
      coef[exponent]=coefficient;
      if(coef[exponent]!=0 && exponent>current_degree){
	current_degree=exponent;
      }
      if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)<size){
	current_degree=previous_term(exponent);
      }
      if(exponent==current_degree && coef[exponent]==0 && previous_term(exponent)>=size){
	current_degree=0;
      }
    }
    else{
      reserve(exponent+1);
      size=exponent+1;
      coef[exponent]=coefficient;
      if(coefficient!=0){
	current_degree=exponent;
      }
    }
  }

  void polynomial::clear(){
    for(int i=0;i<size;i++){
      coef[i]=0.0;
    }
    current_degree=0;
  }

  //CONST FUNCS

  double polynomial::coefficient(unsigned int exponent) const{
    assert(exponent<size);
    return coef[exponent];
  }

  polynomial polynomial::derivative()const{
    polynomial deriv;
    for(int i=0;i<current_degree;i++){
      deriv.coef[i]=(i+1)*coef[i+1];
    }
    if(current_degree==0)
      deriv.current_degree=0;
    else
      deriv.current_degree=current_degree-1;
    return deriv;
  }

  double polynomial::eval(double x)const{
    double sum=0;
    for(int i=0;i<=current_degree;i++){
      sum=sum+coef[i]*pow(x,i);
    }
    return sum;
  }

  unsigned int polynomial::next_term(unsigned int e)const{
    if(e>=current_degree)
      return 0;
    unsigned int i=e+1;
    while(coef[i]==0 && i<=current_degree){
      i++;
    }
    return i;
  }

  unsigned int polynomial::previous_term(unsigned int e)const{
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

  void polynomial::find_root(double& answer,bool& success,unsigned int& iterations,double guess,unsigned int maximum_iterations,double epsilon)const{
    iterations=0;
    while(abs(eval(guess))>epsilon && iterations<maximum_iterations && abs(derivative().eval(guess))>epsilon){
      guess=guess-(eval(guess)*1.0)/derivative().eval(guess);
      iterations++;
    }
    if(abs(derivative().eval(guess))<=epsilon){
	answer=guess;
	success=false;
        
    }
    if(abs(eval(guess))<=epsilon){
      answer=guess;
      success=true;
    }
    if(iterations==maximum_iterations){
      answer=guess;
      success=false;
    }
  }

  polynomial operator+(const polynomial& p1,const polynomial& p2){
    unsigned int size;
    if(p1.degree()>p2.degree())
      size=p1.degree();
    else
      size=p2.degree();
    polynomial ssum(0,size+1);
    for(int i=0;i<size+1;i++){
      ssum.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
    }
    return ssum;
  }

  polynomial operator-(const polynomial& p1,const polynomial& p2){
    unsigned int size;
    if(p1.degree()>p2.degree())
      size=p1.degree();
    else
      size=p2.degree();
    polynomial ssum(0,size+1);
    for(int i=0;i<size+1;i++){
      ssum.assign_coef(p1.coefficient(i)-p2.coefficient(i),i);
    }
    return ssum;
  }

  polynomial operator *(const polynomial& p1,const polynomial& p2){
    unsigned int size=p1.degree()+p2.degree()+1;
    polynomial product(0,size);
    for(int i=0;i<=p1.degree();i++){
      for(int j=0;j<=p2.degree();j++){
	product.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
      }
    }
    return product;
  }

  std::ostream& operator << (std::ostream& out, const polynomial& p){
    if(p.degree()==0 && p.coefficient(0)==0){
      out<<0;
      return out;
    }
    for(int i=0;i<=p.degree();i++){
      out<<out<<"+"<<p.coefficient(i)<<"x^"<<i;
    }
    return out;
  }

}
  
  
  
	
      
    
    
      
  
      
  

