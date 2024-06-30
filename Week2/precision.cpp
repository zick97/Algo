/*precision.cpp:	write	a	computer	program	to	determine	the	machine	precision.
Define	1	in	float	(or	double)	precision	arithmetic	and	keep	adding	epsilon	(àepsilon/
10)	until	1+eps	=	1.*/
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h>
using namespace std;
const double oned=1;//definisco costanti in precisione differente per avere la certezza che il cfr avvenga correttamente
const float onef=1;

int main(){
  double epsilon_d=1,d=0;
  do{
    d=oned+(epsilon_d);
    epsilon_d=epsilon_d/10;
  }
  while(d!=/*(double)*/oned); //per aver la sicurezza bisogna specificare il tipo! Altrimenti definisco altre costanti!
  cout << "epsilon(double) = " << 10*epsilon_d << endl;

  float epsilon_f=1,f=0;
  do{
    f=onef+(epsilon_f);
    epsilon_f=epsilon_f/10;
  }
  while(f!=onef);
  cout << "epsilon(float) = " << 10*epsilon_f << endl;

  return 0;
}
