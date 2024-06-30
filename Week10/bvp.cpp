#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

void Tridiag(double *r, double *a, double *c, double *b, double *x, int N);

double F(double t);

int main(){
  int i, N = 31;
  double x_f = 1., x_i = 0., A = 0, B = 0, h = (x_f - x_i) / (double)N;
  ofstream fdata;

  double *y;
  y = new double[N];
  y[0] = A; y[N] = B;  // metto N perchè il numero N rappresenta i separatori, N + 1 il numero di intervalli

  double *r;
  r = new double[N];

  double *a;
  a = new double[N];

  double *b;
  b = new double[N];

  double *c;
  c = new double[N];


  for(i = 1; i < N; i++){
    a[i] = 1.;
    b[i] = -2.;
    c[i] = 1.;

    r[i] = h * h * F(x_i + (double)i * h);
  }
  r[1] = h * h * F(x_i + 2. * h) - A;
  r[N - 2] = h * h * F(x_i + ((double)N - 1.) * h) - B;

  Tridiag(r + 1, a + 1, c + 1, b + 1, y + 1, N - 1);  // ho solo più N - 2 elementi, ovvero da 1 a n-1 escluso (per come è costruita tridiag)
                                                      // passando gli array +1, sostanzialmente sto escludendo il primo elemento, perchè non si risolve l'equazione a indice 0
  fdata.open("bvp.txt", std::ofstream::out);

  for(i = 0; i <= N; i++){
    fdata << (double)i * h << "\t" << y[i] << "\n";
  }

  fdata.close();

  delete r;
  delete a;
  delete c;
  delete b;
  delete y;

  return 0;
}

void Tridiag(double *r, double *a, double *c, double *b, double *x, int N){
  int i;
  double *h;
  h = new double[N];
  double *p;
  p = new double[N];

  h[0] = c[0] / b[0];
  p[0] = r[0] / b[0];
  for(i = 1; i < N; i++){
    h[i] = c[i] / (b[i] - (a[i] * h[i - 1]));
    p[i] = (r[i] - (a[i] * p[i - 1])) / (b[i] - (a[i] * h[i - 1]));
  }

  x[N - 1] = p[N - 1];
  for(i = N - 2; i >= 0; i--){
    x[i] = p[i] - (h[i] * x[i + 1]);
  }

  delete h;
  delete p;
}

double F(double t){
  return 1.;
}
