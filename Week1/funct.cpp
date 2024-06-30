/*
• sum.cpp:	compute	the	sum	of	two	integers	(or	floats)
• add_one.cpp:	add	one	to	a	number.
• quotient.cpp: write	a	function	that	computes	the	quotient	and	remainder	of	the
division	of	two	integers,	a	and	b.	Example
– 10/7	=	1	remainder	3
– 13/6	=	2	remainder	1,	etc..	*/
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

float sum(float a, float b){
  return a+b;
}

float add_one(float a){
  return a+1;
}

void quotient(int a, int b){
  if(b==0) cout << "Operazione non valida" << endl;
  cout << "a/b = " << a/b << " resto " << a%b << endl;
}

int main(){
  float x,y,v[20];
  int ix,iy,i;
  cout << "Inserire x e y: "; cin >> x >> y; cout << endl;
  cout << "x + y = " << sum(x,y) << endl;
  cout << "x + 1 = " << add_one(x) << endl << endl;
  cout << "Inserire due numeri interi: "; cin >> ix >> iy; cout << endl;
  quotient(ix,iy);
  return 0;
}
