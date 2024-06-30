#include "my_header.h"

double func(double x);

double dvfunc(double x);

int Bracket(double (*F)(double), int a, int b, int N, double xL[], double xR[]);

//int Bisection(double (*F)(double), double a, double b, double tol);

//int Newton(double (*F)(double), double (*dvF)(double), double a, double b, double tol);*/

int main(){
  double tol = 1.e-7;
  double a = -10., b = 10.;
  int N = 100;
  double xL[N], xR[N];

  int nint = Bracket(func, a, b, N, xL, xR);
  cout << "Bracketing has found " << nint << " intervals where the functions changes sign." << endl << endl;

  for(int i = 0; i < nint; i++){
    a = xL[i];
    b = xR[i];

    cout << "Bisection root #" << i + 1 << " = ";
    Bisection(func, a, b, tol);
    cout << endl;
  }

  cout << endl;

  for(int i = 0; i < nint; i++){
    a = xL[i];
    b = xR[i];

    cout << "Newton root #" << i + 1 << " = ";
    Newton(func, dvfunc, a, b, tol);
    cout << endl;
  }
  return 0;
}

double func(double x){  //Session #4
  return sin(x) - ((x * x) / 100.) - (x / 5.) - (1. / 3.);
}

double dvfunc(double x){
  return cos(x) - (x / 50.) + (1. / 5.);
}

int Bracket(double (*F)(double), int a, int b, int N, double xL[], double xR[]){
  double h = (b - a) / (double)N;
  double cond;
  int k = 0;

  for(int i = 1; i < N + 1; i++){
    cond = F(a + i * h) * F(a + (i + 1) * h);

    if (cond < 0.){
      xL[k] = a + i * h;
      xR[k] = a + (i + 1) * h;
      k++;
    }
  }
  return k; // returns the number of intervals where F changes sign
}
