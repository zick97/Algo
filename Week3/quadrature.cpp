#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

double rectangular(double (*F)(double),	double a,	double b,	int	N);//*F è il puntatore alla funzione da integrare
double trapezoidal(double (*F)(double),	double a,	double b,	int	N);
double simpson(double (*F)(double), double a, double b, int N);
double gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng);
double func(double x);
double func1(double x);



int main(){
  double a,b,N,Ng,x;
  double tol;
  int i;
  cout << setiosflags(ios::scientific); // notaz scientifica
  cout << "Enter number of intervals: ";
  cin >> N;
  cout << "Enter interval min and max: ";
  cin >> a >> b;
  cout << "Enter Ng: ";
  cin >> Ng;

  double val, n1=N, n2=N, n3=N, integral;

  val = rectangular(func, a, b, N);
  for(i=1; ;i++){
    n1 *= 2;
    integral = rectangular(func, a, b, n1);
    if(abs(integral - val) < 1.e-05) break;
    val = integral; //aggiorno il valore che fa da confronto con quello appena calcolato, in modo da non richiamare 2 volte la funzione
  }

  val = trapezoidal(func, a, b, N);
  for(i=1; ;i++){
    n2 *= 2;
    integral = trapezoidal(func, a, b, n2);
    if(abs(integral - val) < 1.e-05) break;
    val = integral; //aggiorno il valore che fa da confronto con quello appena calcolato, in modo da non richiamare 2 volte la funzione
  }

  val = simpson(func, a, b, N);
  for(i=1; ;i++){
    n3 *= 2;
    integral = simpson(func, a, b, n3);
    if(abs(integral - val) < 1.e-05) break;
    val = integral; //aggiorno il valore che fa da confronto con quello appena calcolato, in modo da non richiamare 2 volte la funzione
  }


  //fixed toglie la notaz scientifica
  cout << "Exact = " << fixed << std::setprecision(12) << 1/exp(a) - 1/exp(b) << endl;  //6.321205588286e-01
  cout << "Rectangular = " << std::setprecision(12) << rectangular(func, a, b , N);
  cout << " ; N = " << std::setprecision(0) << n1 << endl; //7.144244988813e-01
  cout << "Trapezoidal = " << std::setprecision(12) << trapezoidal(func, a, b , N);
  cout << " ; N = " << std::setprecision(0) << n2 << endl; //6.354094290277e-01
  cout << "Simpson     = " << std::setprecision(12) << simpson(func, a, b, N);
  cout << " ; N = " << std::setprecision(0) << n3 << endl;//6.321341753205e-01
  cout << "Gaussian    = " << std::setprecision(12) << gaussian(func, a, b, N, Ng) << endl;
  cout << "================================================================================" << endl;
  cout << "Simpson = " << std::setprecision(12) << simpson(func1, a, b, N) << ";" << endl;
  cout << "Gauss   = " << std::setprecision(12) << gaussian(func1, a, b, N, Ng) << ";" << endl;

  return 0;
}

double rectangular(double (*F)(double),	double a,	double b,	int	N){
  double h=(b - a)/N,sum=0;
  int i;
  for(i=0;i<N;i++){
    sum=sum + (F(a + i*h)*h); //cambio direttamente argomento della funzione
  }
  return sum;
}

double trapezoidal(double (*F)(double),	double a,	double b,	int	N){
  double h=(b - a)/N,sum;
  int i;            //lo faccio così per non dover richiamare la funzione più di una volta per loop
  sum=0.5*(F(a) + F(b));
  for(i=1;i<N;i++){
    sum=sum + (F(a + i*h));
  }
  return h*sum;     //meglio moltiplicare fuori per avere una sola moltiplicazione
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
  if(Ng==2){
    x[0] = -1.0/sqrt(3.0) ; x[1] =	1.0/sqrt(3.0);
    w[0] =  1.0; w[1] = 1.0;
  }
  if(Ng==3){
    x[0]	= -sqrt(3.0/5.0); x[1] = 0; x[2] = sqrt(3.0/5.0);
    w[0]	=	5.0/9.0; w[1] = 8.0/9.0; w[2] = 5.0/9.0;
  }
  double h = (b - a)/N;
  for (i = 0;	i	<	N;	i++){ // Loop	over	intervals
    sumk	=	0.0;            // Initialize	sum	for	this	interval
    x0 = a + (i * h);
    x1 = b - ((N - 1 - i) * h);                              //Define left	and	right	interval endpoints	x0	&	x1
    for	(k = 0;	k	<	Ng;	k++){
      sumk = sumk + w[k] * F((0.5 * (x1 - x0) * x[k]) + (0.5 * (x1 + x0))); //	Apply	Gaussian	rule	to	sub-interval
    }
    sum = sum + sumk;                                                          //	Add	partial	sum	to	total integral
  }
  return	0.5 * (x1 - x0) * sum;
}

double func(double x){
  return exp(-x);
}
double func1(double x){
  return sqrt(1 + x);
}
