#include "my_header.h"
#include "my_header_1.h"

void dYdx(double x, double *Y, double *R);

double Residual(double E);

double g_E;

int main(){
  double E = 0., Y_left[2], Y_right[2], a = 0., b = 7.;
  double xL[100], xR[100], xm;
  ofstream fdata;

  cout << setiosflags(ios::scientific);

  fdata.open("qho.txt", std::ofstream::out);

  do{
    fdata << E << "\t" << Residual(E) << "\n";  // to plot the Residual function of E
    E += 0.01;
  }
  while (E <= 7);

  fdata.close();

  int nint = Bracket(Residual, a, b, 100, xL, xR);
  cout << "Bracketing has found " << nint << " intervals where the residual function changes sign." << endl << endl;

  for(int i = 0; i < nint; i++){
    a = xL[i];
    b = xR[i];

    Bisection(Residual, a, b, 1.e-7, xm);

    cout << "Bisection root #" << i + 1 << " = " << std::setprecision(8) << xm << endl << endl;
  }

  return 0;

}

void dYdx(double x, double *Y, double *R){
  R[0] = Y[1];
  R[1] = 2. * Y[0] * (0.5 * x * x - (g_E));
}

double Residual(double E){
  double x, dx, xm = 0.8, a = -10., b = 10., Y_left[2], Y_right[2], D;
  int N = 800;

  g_E = E;

  x = a;
  Y_left[0] = exp(-0.5 * x * x);
  Y_left[1] = -x;

  dx = abs(x - xm) / (double)N;

  for(int i = 0; i < N; i++){
    RK4_step(x, Y_left, dYdx, dx, 2);

    x += dx;
  }

  x = b;
  Y_right[0] = exp(-0.5 * x * x);
  Y_right[1] = -x;

  dx = abs(x - xm) / (double)N;

  for(int i = 0; i < N; i++){
    RK4_step(x, Y_right, dYdx, -dx, 2);

    x -= dx;
  }

  D = sqrt(((Y_left[1] * Y_right[0]) * (Y_left[1] * Y_right[0])) + ((Y_right[1] * Y_left[0]) * (Y_right[1] * Y_left[0])));
  return (Y_left[1] * Y_right[0] - Y_right[1] * Y_left[0]) / D;
}
