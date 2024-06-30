#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void Tridiag(double *r, double *a, double *c, double *b, double *x, int N);

int main(){
  int i, N = 5;

  double *x;
  x = new double[N];

  double *r;
  r = new double[N];
  r[0] = 1.; r[1] = 0.; r[2] = 3.; r[3] = 1.; r[4] = 0.;

  double *a;
  a = new double[N];
  a[0] = 0.; a[1] = 1.; a[2] = 1.; a[3] = 1.; a[4] = 1.;

  double *b;
  b = new double[N];
  b[0] = 2.; b[1] = 2.; b[2] = 2.; b[3] = 2.; b[4] = 2.;

  double *c;
  c = new double[N];
  c[0] = 1.; c[1] = 1.; c[2] = 1.; c[3] = 1.; c[4] = 0.;

  Tridiag(r, a, c, b, x, N);

  cout << endl << "[ ";
  for(i = 0; i < N; i++){
    cout << x[i] << " ";
  }
  cout << "]" << endl;

  delete r;
  delete a;
  delete c;
  delete b;
  delete x;

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
