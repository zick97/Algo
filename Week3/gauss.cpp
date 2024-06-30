#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;
double simpson(double (*F)(double), double a, double b, int N);
double	gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng);
double func(double x);
int main(){
  double a,b,x;
  int N1,N2,Ng;
  cout << setiosflags(ios::scientific); // notaz scientifica
  cout << "Enter number of intervals for Simpson: ";
  cin >> N1;
  cout << "Enter number of intervals for Gauss: ";
  cin >> N2;
  cout << "Enter interval min and max: ";
  cin >> a >> b;
  cout << "Enter Ng: ";
  cin >> Ng;
  cout << "================================================================================" << endl;
  cout << "Exact   = " << std::setprecision(12) << -(66.0/5.0) << ";" << endl;
  cout << "Simpson = " << std::setprecision(12) << simpson(func, a, b, N1) << ";" << endl;
  cout << "Gauss   = " << std::setprecision(12) << gaussian(func, a, b, N2, Ng) << ";" << endl;

  return 0;
}
double simpson(double (*F)(double), double a, double b, int N){ //N dev'essere pari!!!
  double h=(b - a)/N,sum;
  int i,j;
  sum = F(a) + F(b);
  for(i=1;i<N;i++){
    if((i%2)==0) j=2;
    else j=4;
    sum=sum + j*(F(a + i*h));
    //per sostituire l'if posso: - scrivere j = 6.0 - j perchè mi restituisce sempre i valori alternati, dove j è il peso
    //                           - scrivere j = 2 + 2*(i%2) così da avere 2 per indici pari e 4 per indici dispari
  }
  return sum*(h/3); //anche qui divido alla fine
}

double	gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng){
  double w[32], x[32];
  int k,i;
  double x0,x1;
  double sum	=	0.0, sumk;
  if(Ng > 4){cout << "Gauss not defined for N > 4 " << endl;}
  if(Ng==2){
    x[0] = -1.0/sqrt(3.0) ; x[1] =	1.0/sqrt(3.0);
    w[0] =  1.0; w[1] = 1.0;
  }
  if(Ng==3){
    x[0]	= -sqrt(3.0/5.0); x[1] = 0; x[2] = sqrt(3.0/5.0);
    w[0]	=	5.0/9.0; w[1] = 8.0/9.0; w[2] = 5.0/9.0;
  }
  if(Ng==4){
    x[0]	= -sqrt((3.0/7.0) + (2.0/7.0) * sqrt(6.0/5.0)); x[1] = -sqrt((3.0/7.0) - (2.0/7.0) * sqrt(6.0/5.0));
    x[2] = sqrt((3.0/7.0) - (2.0/7.0) * sqrt(6.0/5.0)); x[3] = sqrt((3.0/7.0) + (2.0/7.0) * sqrt(6.0/5.0));
    w[0]	=	(18.0 - sqrt(30.0))/36.0; w[1] = (18.0 + sqrt(30.0))/36.0;
    w[2] = (18.0 + sqrt(30.0))/36.0; w[3] = (18.0 - sqrt(30.0))/36.0;
  }
  double h = (b - a)/(double)N;
  for (i = 0;	i	<	N;	i++){ // Loop	over	intervals
    sumk	=	0.0;            // Initialize	sum	for	this	interval
    x0 = a + (i * h);	x1 = b - ((N - 1 - i) * h);                              //Define left	and	right	interval endpoints	x0	&	x1 -->
                                                                               //questo perchè faccio la moltiplicazione sui
                                                                               //che cambiano estremi ad ogni iterazione sottointervalli,

    for	(k = 0;	k	<	Ng;	k++){
      sumk = sumk + w[k] * F((0.5 * (x1 - x0) * x[k]) + (0.5 * (x1 + x0)));    //	Apply	Gaussian	rule	to	sub-interval
    }
    sum = sum + sumk;                                                          //	Add	partial	sum	to	total integral
  }
  return	0.5 * (x1 - x0) * sum;
}

double func(double x){
  return 1 - x + 2 * x * x + (x * x * x)/2 + (x * x * x * x)/4 - (x * x * x * x * x)/8; //se prendo un polinomio di grado 5
                                                                                        //vuol dire che gauss è corretto
}
