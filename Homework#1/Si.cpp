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
  double a = 0.0, b = 1.0, sum_trapezoidal, sum_simpson, sum_gauss;
  double val = 1.618194443708e+00;  // given value
  double err_trapezoidal, err_simpson, err_gauss;
  int N = 3;
  cout << setiosflags(ios::scientific);
  // Compute the sum of 15 sub-intervals, from x = 0 to x = 15.
  // Each sub-interval has the same length: xb - xa = 1.
  do{
    sum_trapezoidal = sum_trapezoidal + trapezoidal(func, a, b, N);
    sum_simpson = sum_simpson + simpson(func, a, b, N);
    sum_gauss = sum_gauss + gaussian(func, a, b, 1, 3);
    cout << "x = " << std::setprecision(1) << b << "    ";
    cout << std::setprecision(4) << sum_gauss;
    cout << "    " << std::setprecision(4) << sum_simpson;
    cout << "    " << std::setprecision(4) << sum_trapezoidal << endl;
    a++;
    b++;
  }
  while (b <= 15.0);
  // Error is calculated only for x = 15;
  cout << endl;
  err_trapezoidal = abs(sum_trapezoidal - val);
  err_simpson = abs(sum_simpson - val);
  err_gauss = abs(sum_gauss - val);
  cout << "Err =          " << std::setprecision(4) << err_gauss;
  cout << "    " << err_simpson << "    " << err_trapezoidal << endl;
  return 0;
}
//Trapezoidal Quadrature
double trapezoidal(double (*F)(double),	double a,	double b,	int	N){
  double h = (b - a) / N, sum;
  int i;
  sum = 0.5 * (F(a) + F(b));
  for(i = 1; i < N; i++){
    sum = sum + (F(a + i * h));
  }
  return h * sum;
}
// Simpson Quadrature
double simpson(double (*F)(double), double a, double b, int N){
  double h = (b - a) / N, sum;
  int i, j;
  sum = F(a) + F(b);
  for(i = 1; i < N; i++){
    if((i % 2) == 0) j = 2;
    else j = 4;
    sum = sum + j * (F(a + i * h));
  }
  return sum * h / 3.0;
}
// Gaussian Quadrature
double	gaussian (double	(*F)(double),	double	a,	double	b,	int	N,	int	Ng){
  double w[32], x[32];
  int k, i;
  double x0, x1;
  double sum = 0.0, sumk;
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

double func(double x){
  if (x > 1.e-16) return sin(x) / x;    // use for x != 0
  else return 1.;                       // use for x = 0 -> extension in continuity
}
