#include "my_header.h"

int main(){
  int i, n = 100;
  double x_r = 10., x_l = 0., x_i;
  double alpha = 0, beta = 1., h = fabs(x_r - x_l) / (double)(n - 1);
  ofstream fdata;

  double *y;
  y = new double[n];
  y[0] = alpha; y[n - 1] = beta;            // initial conditions

  double *r;
  r = new double[n];

  double *a;
  a = new double[n];

  double *b;
  b = new double[n];

  double *c;
  c = new double[n];

  // defining arrays
  for(i = 0; i < n; i++){
    x_i = x_l + (double)i * h;

    a[i] = (2. * x_i * x_i) - (h * x_i);
    b[i] = -(4. * x_i * x_i) + (2. * h * h * (x_i * x_i - 1.));
    c[i] = (2. * x_i * x_i) + (h * x_i);

    r[i] = 0.;
  }
  r[1] = -(alpha * a[0]);                 // the rhs function is not included because
  r[n - 2] = -(beta * c[n - 1]);          // its value is always 0.

  Tridiag(r + 1, a + 1, c + 1, b + 1, y + 1, n - 2);

  fdata << setiosflags(ios::scientific);
  fdata.open("bessel.txt", std::ofstream::out);

  // plot of the y[i] with respect to the x
  for(i = 0; i < n; i++){
    x_i = x_l + (double)i * h;
    fdata << x_i << " \t " << y[i] << "\n";
  }

  fdata.close();

  delete r;
  delete a;
  delete c;
  delete b;
  delete y;

  return 0;
}
