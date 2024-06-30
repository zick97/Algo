#include "my_header.h"

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
