#include "my_header.h"
#include "my_header_1.h"

void dYdr(double x, double *Y, double *R);

double Residual(double k);

double g_k;

int main(){
  double k = 1., Y[2], xm;
  double xL[100], xR[100];
  double a, b;

  cout << setiosflags(ios::scientific);

  do{
    Residual(k);
    k++;
  }
  while (k <= 5.);

  int nint = Bracket(Residual, 0., 20., 100, xL, xR);
  cout << "Bracketing has found " << nint << " intervals where the functions changes sign." << endl << endl;

  for(int i = 0; i < nint; i++){
    a = xL[i];
    b = xR[i];

    cout << "Bisection root #" << i + 1 << " = ";
    Bisection(Residual, a, b, 1.e-7, xm);
    cout << endl;
  }

  return 0;
}

void dYdx(double x, double *Y, double *R){
  R[0] = Y[1];
  R[1] = -(g_k * g_k) * Y[0];
}

double Residual(double k){
  double x, dx, a = 0., b = 1., Y[2];
  int N = 100;

  g_k = k;

  dx = b / (double)N;

  x = a;
  Y[0] = 0.;
  Y[1] = 1.;

  for(int i = 0; i < N; i++){
    RK4_step(x, Y, dYdx, dx, 2);
    x += dx;
  }

  return Y[0];  // 1 è il valore atteso della funzione in b
}
