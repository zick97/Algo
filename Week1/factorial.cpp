/*Implement	the	algorithm	using	two	different	strategies:
1. Using	a	standard	for()	loop	(or	a	recursive	function)	and	integer	arithmetic.	Verify
its	implementation.	What	is	the	maximum	number	for	which	the	factorial	can	be
computed	?
2. Add	a	second	function	that	employs	double	precision	arithmetic;	can	you	take	the
factorial	of	larger	numbers	?	Explain	why.*/
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

void fac(int k){
  int v[1000],i=0,j=0,f,n=1;
  v[0]=1;
  do{
    f=1;
    for(i=1;i<=n;i++){
      f=f*i;
    }
    v[j]=f;
    j++;
    n++;
  }
  while(v[j]<INT_MAX);
  for(j=0;j<(n-1);j++){
    cout << j+1 << "! = " << v[j] << endl;
  }
}
int fac_1(int);
int rec_fac1(int);//ottengo risultati sbagliati per n>12 a causa delle dimensioni di memoria dell'int
double fac_2(double);
double rec_fac2(double);

int main(){
  int k;
  double x;
  fac(k);
  cout << "k = "; cin >> k;
  cout << "n! = " << fac_1(k) << endl;
  cout << "(recursion) n! = " << rec_fac1(k) << endl;
  cout << "x = "; cin >> x;
  cout << "x! = " << fac_2(x) << endl;
  cout << "(recursion) x! = " << rec_fac2(x) << endl;
  return 0;
}

int rec_fac1(int n){
    if(n>1){
      return n*rec_fac1(n-1);
    }
    else return 1;
}

double rec_fac2(double n){
  if(n>1){
    return n*rec_fac2(n-1);
  }
  else return 1;
}

int fac_1(int n){
  int i;
  int f=1;
  for(i=0;i<n;i++){
    f=f*(n-i);
  }
  return f;
}

double fac_2(double n){
  int i;
  double f=1;
  for (i=0;i<n;i++){
    f=f*(n-i);
  }
  return f;
}
