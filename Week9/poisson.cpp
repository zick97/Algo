#include "my_header.h"
#include "my_header_1.h"

void dYdr(double r, double *Y, double *R);

double Residual(double s);

double Phi(double r);

int main(){
  double s = 0., Y[2], xm, s1;
  ofstream fdata;

  cout << setiosflags(ios::scientific);
  fdata << setiosflags(ios::scientific);
  fdata.open("poisson.txt", std::ofstream::out);

  do{
    fdata << s << "\t" << Residual(s) << "\n";
    s += 0.2;
  }
  while (s < 5.1);

  fdata.close();

  Bisection(Residual, 0., 5., 1.e-7, xm);
  s = xm;

  Bisection(Phi, 0., 5., 1.e-7, xm);
  s1 = xm;

  cout << endl << std::setprecision(6) << abs(s - s1);

  return 0;
}

void dYdr(double r, double *Y, double *R){
  R[0] = Y[1];
  R[1] = -0.5 * r * exp(-r);
}

double Residual(double s){
  double r, dr, b = 20., Y[2];
  int N = 1000;

  dr = b / (double)N;

  r = 0.;
  Y[0] = 0.;
  Y[1] = s;

  for(int i = 0; i < N; i++){
    RK4_step(r, Y, dYdr, dr, 2);
    r += dr;
  }

  return Y[0] - 1.;  // 1 è il valore atteso della funzione in b
}

double Phi(double r){
  return 1. - 0.5 * (r + 2.) * exp(-r);
}
