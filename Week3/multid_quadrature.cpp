#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

static double g_ycoord;// dico che la y fissata per calcolare gauss su g deve rimanere fissata
static int g_numint = 1;   // anche il numero di intervalli per gauss su g rimane costante

double gaussian_quadrature (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng);
double Gfunc1D(double y);
double FFunc1D(double x);
double input_func(double x, double y);


int main(){
  double y0 = -1., y1 = 1.; // dato che questo dato serve a gauss su g lo metto in main
  double pi1, pi0 = atan(1)*4, err;
  cout << setiosflags(ios::scientific); // notaz scientifica
  //cout << "Exact = " << std::setprecision(12) << 412./45. << endl;
  do{
    pi1 = gaussian_quadrature(Gfunc1D, y0, y1, g_numint, 4);
    g_numint++;//funziona anche così: viene aggiornato il valore della variabile, ma rimane statica e quindi recepita da tutto il programma
    err = abs(pi1 - pi0);
  }
  while (err > 1.e-5);
  cout << "Exact pi = " << std::setprecision(12) << pi0 << endl;
  cout << "Gauss = " << std::setprecision(12) << pi1 << " ; N = " << g_numint << endl;
  //cout << "Exact = " << std::setprecision(12) << 412./45. << endl;
  //cout << "Gauss = " << std::setprecision(12) << gaussian_quadrature(Gfunc1D, y0, y1, g_numint, 3) << endl;
  //cout << "Errore = " << abs(gaussian_quadrature(Gfunc1D, y0, y1, g_numint, 3) -  412./45.) << endl;
  return 0;
}

/*double input_func(double x, double y){
  return x*x*x*x*y*y + 2 * x*x*y*y - y*x*x +2;
}*/

double input_func(double x, double y){
  if (sqrt(x*x + y*y) <= 1) return 1.;
  else return 0.;
}

double Gfunc1D(double y){
  double gaus_x;            // mi serve perchè sto facendo l'integrale di g (a y fissata) lungo x
  double x0 = -1., x1 = 1.; // definisco gli estremi per l'integrale lungo x
  g_ycoord = y;             // lo faccio qui per avere una y fissata ma dipendente da f (vedi funzioni sotto)

  gaus_x = gaussian_quadrature(FFunc1D, x0, x1, g_numint, 4);
  return gaus_x;
}

double FFunc1D(double x){
  return input_func(x, g_ycoord);
}


double	gaussian_quadrature (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng){
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
