#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

double Newton(double (*F)(double ,double), double (*dvF)(double, double), double a, double b, double tol, double t);

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

    fdata << std::setprecision(6) << t << "\t" << x_func(t, E, a) << "\t" << y_func(t, E, a) << "\n";

    t += dt;
  }

  fdata.close();

  return 0;
}

double Newton(double (*F)(double ,double), double (*dvF)(double, double), double a, double b, double tol, double t){
  double xm = 0.5 * (a + b), prev;
  double fxm, dvf;
  double delta;
  int k = 1;
  do{
    fxm = F(t, xm);
    dvf = dvF(t, xm);
    delta = fxm / dvf;

    xm -= delta;
    k++;
  }
  while (abs(delta) > tol);
  return xm;
}

double anomaly(double t, double E){
  return (2 * M_PI) * t + (e * sin(E)) - E;  //function of the anomaly: the zero of the function is the solution for a certain t
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
