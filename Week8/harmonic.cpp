#include "my_header.h"

void Position_verlet(double t, double dt, double *Xmid, double *X, double *V, void (*A_func)(double *, double *), int neq);

void RK2_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);

void d2xdt2(double *X, double *R);

void dYdt(double t, double *Y, double *R);

int main(){
  double t = 0., dt, T = 2 * M_PI, X[1], V[1], Y[2];
  double Xmid[1], E;
  int n_max = 1000000;
  ofstream fdata;

  fdata << setiosflags(ios::scientific);
  fdata.open("harmonic.txt", std::ofstream::out);

  dt = 0.02 * T;

  if (t == 0.){
    X[0] = 1.;
    V[0] = 0.;
  }
  Position_verlet(t, dt, Xmid, X, V, d2xdt2, 1);
  E = 0.5 * V[0] * V[0] + 0.5 * X[0] * X[0];

  fdata << t << "\t" << E << "\n";
  for(int i = 0; i < n_max; i++){
    Position_verlet(t, dt, Xmid, X, V, d2xdt2, 1);

    E = 0.5 * V[0] * V[0] + 0.5 * X[0] * X[0];
    t += dt;

    fdata << t << "\t" << E << "\n";

    if(t > 10. * T) break;
  }

  fdata << "\n \n";

  t = 0.;

  if (t == 0.){
    Y[0] = 1.;
    Y[1] = 0.;
  }
  RK2_step(t, Y, dYdt, dt, 2);
  E = 0.5 * Y[1] * Y[1] + 0.5 * Y[0] * Y[0];

  fdata << t << "\t" << E << "\n";
  for(int i = 0; i < n_max; i++){
    RK2_step(t, Y, dYdt, dt, 2);

    E = 0.5 * Y[1] * Y[1] + 0.5 * Y[0] * Y[0];
    t += dt;

    fdata << t << "\t" << E << "\n";

    if(t > 10. * T) break;
  }

  fdata.close();

  return 0;
}

void Position_verlet(double t, double dt, double *Xmid, double *X, double *V, void (*A_func)(double *, double *), int neq){
  double rhs[neq];

  for(int i = 0; i < neq, i++){
    Xmid[0] = X[0] + 0.5 * dt * V[0];

    A_func(Xmid, rhs);

    V[0] = V[0] + dt * rhs[0];

    X[0] = Xmid[0] + 0.5 * dt * V[0];
  }

}

void d2xdt2(double *X, double *R){
  R[0] = -X[0];
}

void dYdt(double t, double *Y, double *R){
  R[0] = Y[1];
  R[1] = -Y[0];
}
