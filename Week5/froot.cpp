#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

double func(double x);

double dvfunc(double x);

int Bracket(double (*F)(double), int a, int b, int N, double xL[], double xR[], int maxSize);

int	Bisection(double	(*F)(double), double a,	double b,	double tol);

int False_position(double (*F)(double), double a, double b, double tol);

int Secant(double (*F)(double), double a, double b, double tol);

int Newton(double (*F)(double), double (*dvF)(double), double a, double b, double tol);

int main(){
  double tol = 1.e-7;
  // double a = -1., b = 1.; //Session #1
  //double a = -5., b = 0.;  //Session #2
  //double a = 0., b = 2.;   //Session #3
  double a = -10., b = 10.;
  int maxSize = 10;
  int k, N = 5;
  double xL[N], xR[N];
  Bracket(func, a, b, N, xL, xR, maxSize);

  cout << setiosflags(ios::scientific);
  for (k = 0; k < N; k++){
    a = xL[k];
    b = xR[k];

    cout << "Bisection =====================================================================================" << endl << endl;
    if (Bisection(func, a, b, tol) == 1){
      cout << "La funzione non ammette zeri sull'intervallo [a,b]!" << endl;
    }

    else cout << "Nessun errore rilevato." << endl << endl;
    cout << "False Position ================================================================================" << endl << endl;
    if (False_position(func, a, b, tol) == 1){
      cout << "La funzione non ammette zeri sull'intervallo [a,b]!" << endl;
    }

    else cout << "Nessun errore rilevato." << endl << endl;
    cout << "Secant ========================================================================================" << endl << endl;
    if (Secant(func, a, b, tol) == 0){
      cout << "Nessun errore rilevato" << endl << endl;
    }

    cout << "Newton ========================================================================================" << endl << endl;
    if (Newton(func, dvfunc, a, b, tol) == 0){
      cout << "Nessun errore rilevato" << endl;
    }
  }

  return 0;
}

/*double func(double x){
  return exp(-x) - x;
}                                                                   //Session #1

double dvfunc(double x){
  return -exp(-x) - 1.;
}*/

/*double func(double x){
  return 5. + x * (x * x - 3. * x + 1.);
}                                                                   //Session #2

double dvfunc(double x){
  return 1. + x * (3 * x - 6.);
}*/

/*double func(double x){
  return exp(1. / (x + 0.5)) - (3. + 2. * x) / (1. + x);
}                                                                   //Session #3

double dvfunc(double x){
  return -1. / ((x + 0.5) * (x + 0.5)) * exp(1. / (x + 0.5)) - (2. * (1. + x) - (3. + 2. * x)) / ((1. + x) * (1. + x));
}*/

double func(double x){
  return sin(x) - (((x * x) / 100.) + x / 5. - 1. / 3.);
}                                                                   //Session #4

double dvfunc(double x){
  return cos(x) - (x / 50. + 1. / 5.);
}

int Bracket(double (*F)(double), int a, int b, int N, double xL[], double xR[], int maxSize){
  // Tries to bracket the roots of a given function
  // Returns the number of roots bracketed or a (negative) error code
  // -1 = Over array maxSize

  double dx = (b - a) / (double) N;

  // Is the function positive?
  bool pos = (F(a) >= 0);

  // Mid points
  double x, fx;
  int r = 0;
  for(int i = 1; i < N + 1; ++i){
    x = a + (i * dx);
    fx = F(x);

    if ((pos && (fx < 0)) || (!pos && (fx >= 0))){
      if (r > maxSize) return -1;

      pos = !pos;
      xR[r] = x;
      xL[r] = x - dx;
      r++;
    }
  }

  return r;
}


int Bisection(double (*F)(double), double a, double b, double tol){
  int k = 1;
  double xm, dx, fm, fa = F(a), fb = F(b);
  if (fa * fb < 0){
      do{
        dx = b - a;
        xm = (b + a) * 0.5;
        fm = F(xm);
        cout << "Bisection();  k = " << std::setprecision(1) << k << "  [" << std::setprecision(6) << a << " , " << b << "]" << endl;
        cout << "              xm = " << xm << "  dx = " << dx << "  fm = " << fm << endl << endl;
        if (fa * fm > 0.){
          a = xm;
          fa = fm;
        }
        if (fa * fm < 0.){
          b = xm;
        }
        if (fa * fm == 0.) dx = 0.;
        k++;
      }
      while (abs(dx) > tol || abs(fm) > tol); // non appena una delle due è verificata, esco
      return 0;
    }
    else return 1;
}

int False_position(double (*F)(double), double a, double b, double tol){
  int k = 1;
  double xm, dx, dy, fm, fa = F(a), fb = F(b), kang, prev;
  if (fa * fb < 0){
      do{
        prev = a;
        dx = b - a;
        dy = fb - fa;
        kang = dy / dx;
        xm = a - fa / kang;
        fm = F(xm);
        cout << "False_position();  k = " << std::setprecision(1) << k << "  [" << std::setprecision(6) << a << " , " << b << "]" << endl;
        cout << "                  xm = " << xm << "  delta = " << abs(prev - xm)  << "  fm = " << fm << endl << endl;
        if (fa * fm > 0.){
          a = xm;
          fa = fm;
        }
        if (fa * fm < 0.){
          b = xm;
          fb = fm;
        }
        if (fa * fm == 0.) break;
        k++;
      }
      while (abs(prev - a) > tol || abs(fm) > tol); // non appena una delle due è verificata, esco
      return 0;
    }
    else return 1;
}

int Secant(double (*F)(double), double a, double b, double tol){
  double fa = F(a), fb = F(b);
  double dx = b - a;
  int k = 1;
  while (abs(dx) > tol){
    dx = fb * (b - a) / (fb - fa);
    cout << "Secant();  k = " << std::setprecision(1) << k << "  xa = " << std::setprecision(6) << a << "  xb = " << b << "  dx = " << dx << endl;
    a = b;
    b = b - dx;
    fa = fb;      //guardare il grafico per capire le sostituzioni
    fb = F(b);
    k++;
  }
  return 0;
}

int Newton(double (*F)(double), double (*dvF)(double), double a, double b, double tol){
  double xm = 0.5 * (a + b), prev;
  double fxm, dvf;
  double delta;
  int k = 1;
  do{
    fxm = F(xm);
    dvf = dvF(xm);
    delta = fxm / dvf;
    cout << "Newton();  k = " << std::setprecision(1) << k << "  xm = " << std::setprecision(6) << xm << "  delta = " << abs(delta) << endl;
    xm -= delta;
    k++;
  }
  while (abs(delta) > tol);
  return 0;
}
