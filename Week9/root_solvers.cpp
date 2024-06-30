#include "my_header.h"

int Bisection(double (*F)(double), double a, double b, double tol, double &xm){
  int k = 1;
  double dx, fm, fa = F(a), fb = F(b);
  if (fa * fb < 0){
      do{
        dx = b - a;
        xm = (b + a) * 0.5;
        fm = F(xm);

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
      //cout << std::setprecision(10) << xm << endl;    // restituisce solo il valore finale dello 0
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

    xm -= delta;
    k++;
  }
  while (abs(delta) > tol);
  cout << std::setprecision(6) << xm; // restituisce solo il valore finale dello 0
  return 0;
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
