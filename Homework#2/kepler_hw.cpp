#include "my_header.h"
#include <fstream>

double anomaly(double t, double E);

double dv_anomaly(double t, double E);

double x_func(double t, double E, double a);

double y_func(double t, double E, double a);

const double e = 0.55;

int main(){
  int i, N = 100;
  double T = 1., a = 1., sx = -1., dx = 6., tol = 1.e-7, E;
  double dt = T / (double)N;
  static double t = 0.;
  ofstream fdata;

  fdata << setiosflags(ios::scientific);

  fdata.open("kepler.txt", std::ofstream::out);
  fdata << "t" << "\t \t" << "x(t)" << "\t \t" << "y(t)" << "\n";

  for(i = 0; i < N; i++){
    E = Newton(anomaly, dv_anomaly, sx, dx, tol, t);

    fdata << std::setprecision(6) << t << "\t" << x_func(t, E, a);
    fdata << "\t" << y_func(t, E, a) << "\n";

    t += dt;
  }

  fdata.close();

  return 0;
}

double anomaly(double t, double E){
  return (2 * M_PI) * t + (e * sin(E)) - E;  //since T = 1., T is not included
                                             //in the definition
}

double dv_anomaly(double t, double E){
  return e * cos(E) - 1.;
}

double x_func(double t, double E, double a){
  return a * (cos(E) - e);
}

double y_func(double t, double E, double a){
  return a * sqrt(1. - e * e) * sin(E);
}
