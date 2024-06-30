#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

double trapezoidal(double (*F)(double),	double a, double b,	int	N);

double simpson( double(*F)(double), double a, double b, int N);

double gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng);

double func(double x);

double functay(double x);

int main(){
  double a = 1.e-15, b = 0.8, sum_trapezoidal, sum_simpson, sum_gauss;
  int N = 1;
  cout << setiosflags(ios::scientific);
  do{
    sum_trapezoidal = trapezoidal(func, a, b, N) + trapezoidal(functay, 0.0, a, N); // si svolge la somma su due intervalli:
    sum_simpson = simpson(func, a, b, N) + simpson(functay, 0.0, a, N);             // vicino a 0 (x < 1.e-5) (per cui si usa lo sviluppo di taylor)
                                                                                    // e "lontano" da 0 per cui si usa la funzione originale

    cout << "h = " << std::setprecision(1) << b / N << " ; trapezoidal = " << std::setprecision(10) << sum_trapezoidal;
    cout << " ; simpson = " << std::setprecision(10) << sum_simpson << endl;
    N *= 2;
  }
  while (N <= 8);
  sum_gauss = gaussian(func, a, b, 1, 3) + gaussian(functay, 0.0, a, 1, 3);
  cout << "gaussian = " << std::setprecision(10) << sum_gauss << endl;
}

double trapezoidal(double (*F)(double),	double a,	double b,	int	N){
  double h = (b - a) / N, sum;
  int i;
  sum = 0.5 * (F(a) + F(b));
  for(i = 1; i < N; i++){
    sum = sum + (F(a + i * h));
  }
  return h * sum;
}

double simpson(double (*F)(double), double a, double b, int N){ // # di intervalli pari -> N dispari
  double h = (b - a) / N, sum;
  int i, j;
  sum = F(a) + F(b);
  for(i = 1; i < N; i++){
    if((i % 2) == 0) j = 2;
    else j = 4;
    sum = sum + j * (F(a + i * h));
  }
  return sum * (h / 3.0);
}

double	gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng){
  double w[32], x[32];
  int k,i;
  double x0,x1;
  double sum =	0.0, sumk;
  if(Ng == 2){
    x[0] = -1.0 / sqrt(3.0) ; x[1] =	1.0 / sqrt(3.0);
    w[0] =  1.0; w[1] = 1.0;
  }
  if(Ng == 3){
    x[0] = -sqrt(3.0 / 5.0); x[1] = 0; x[2] = sqrt(3.0 / 5.0);
    w[0] =	5.0 / 9.0; w[1] = 8.0 / 9.0; w[2] = 5.0 / 9.0;
  }
  double h = (b - a) / N;
  for (i = 0;	i	<	N;	i++){
    sumk	=	0.0;
    x0 = a + (i * h);	x1 = b - ((N - 1 - i) * h);
    for	(k = 0;	k	<	Ng;	k++){
      sumk = sumk + w[k] * F((0.5 * (x1 - x0) * x[k]) + (0.5 * (x1 + x0)));
    }
    sum = sum + sumk;
  }
  return	0.5 * (x1 - x0) * sum;
}

double func(double x){     // si usa per valori di a "lontani" da 0
  return sin(x) / x;
}

double functay(double x){  // si usa per valori di a molto vicini a 0
  return 1 - (x * x) / 6.0 + (x * x * x * x) / 120.0 - (x * x * x * x * x * x) / 5040.0;
}
