#include "my_header.h"

void d2xdt2(double *X, double *R);

void dYdt(double t, double *Y, double *R);

int main(){
  double t = 0., dt = 0.1, X[1], V[1], Y[2]; // The period is 2Pi*omega, but omega is sqrt(g/L)=1
  double Xmid[1], E, cont = 0., prev;
  int n_max = 10000000;

  ofstream fdata;

  fdata << setiosflags(ios::scientific);
  fdata.open("pendulum.txt", std::ofstream::out);
  fdata << "theta \t \t omega" << "\n";

  X[0] = M_PI / 4.;
  V[0] = 0.;  // define V=omega, so that the axis will be rescalated with L

  for (int i = 0; i < n_max; i++){
    prev = V[0];

    Position_verlet(t, dt, Xmid, X, V, d2xdt2, 1);

    t += dt;

    fdata << X[0] << "\t" << V[0] << "\n";

    if (prev * V[0] < 0) cont++;

    if (cont > 1.e+3) break;
  }

  fdata << "\n" << "\n";

  t = 0; cont = 0;

  // Initial Condition, it is not necessary to compute RK2 because it gives the value at t+1
  Y[0] = M_PI / 4.;  // Y[0] is the angular position
  Y[1] = 0.;         // Y[1] is the angular velocity

  for (int i = 0; i < n_max; i++){
    prev = Y[1];

    RK2_step(t, Y, dYdt, dt, 2);

    t += dt;

    fdata << Y[0] << "\t" << Y[1] << "\n";

    if (prev * Y[1] < 0) cont++;

    if (cont > 1.e+3) break;
  }

  fdata.close();

  return 0;
}

void d2xdt2(double *X, double *R){
  R[0] = -sin(X[0]);
}

void dYdt(double t, double *Y, double *R){
  R[0] = Y[1];
  R[1] = -sin(Y[0]);
}
