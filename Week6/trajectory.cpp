#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>    // to export data to be executed by gnuplot
using namespace std;

double func(double t, double a);

double dvfunc(double t, double a);

double dvdvfunc(double t, double a);

int main(){
  ofstream fdata;           // declare output stream class to operate on files
  double x, v, a, t = 0., alpha;
  int N = 1.e+3;
  cout << "Insert alpha: ";
  cin >> alpha;
  double h = alpha / 1.e+3;

  fdata.open("trajectory.txt", std::ofstream::out);
  ///////////////////////////////////////////////////////////////////TRAIETTORIA
  do{
    x = func(t, alpha);
    fdata << t << " " << x << " " << "\n";
    t += h;
  }
  while (t <= alpha);

  /////////////////////////////////////////////////////////////////////VELOCITA'
  t = 0.;
  fdata << "\n" << "\n";

  do{
    if (t < h) v = (0.5 / h)) * (-3. * func(t, alpha) + 4. * func(t + 1., alpha) - func(t + 2., alpha)); // dato che c'è un asintoto si usano solo punti sulla destra

    v = (1. / (12. * h)) * (func(t - 2. * h, alpha) - 8. * func(t - h, alpha) + 8. * func(t + h, alpha) - func(t + 2. * h, alpha));

    fdata << t << " " << v << " " << "\n";
    t += h;
  }
  while (t <= alpha);

  /////////////////////////////////////////////////////////////////ACCELERAZIONE
  t = 0.;
  fdata << "\n" << "\n";

  do{
    if (t < h) a = 
    a = (1. / (h * h)) * (func(t + h, alpha) - 2. * func(t, alpha) + func(t - h, alpha));
    fdata << t << " " << a << " " << "\n";
    t += h;
  }
  while (t <= alpha);
  fdata.close();

  return 0;
}

double func(double t, double alpha){
  return alpha * t * t - (t * t * t) * (1. - exp(-(alpha * alpha) / t));
}
