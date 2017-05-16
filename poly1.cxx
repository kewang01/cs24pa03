#include<cassert>
#include<iostream>
#include<cmath>
#include<algorithm>
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

  polynomial& polynomial::operator=(const polynomial& source){
    if(this==&source)
      return;
    double *ass=new double[source.size];
    delete [] coef;
    coef=ass;
    size=source.size;
    current_degree=source.current_degree;
    copy(source.coef,source.coef+size,coef);
    return *this;
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

  
  
	
      
    
    
      
  
      
  

