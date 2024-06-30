#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>    // to export data to be executed by gnuplot
using namespace std;

double func(double x);

double dvfunc(double x);

int main(){
  ofstream fdata;           // declare output stream class to operate on files
  double h = 0.5, xi, fd, bd, cd, hod;
  cout << "Insert xi: ";
  cin >> xi;

  fdata.open("derivative.txt", std::ofstream::out);
  for(int i = 0; i < 10; i++){
    fd = (func(xi + h) - func(xi)) / h;
    fdata << 1. / h << " " << abs(dvfunc(xi) - fd)  << " " << "\n";
    h *= 0.5;
  }
  h = 0.5;
  fdata << "\n" << "\n";
  for(int i = 0; i < 10; i++){
    bd = (func(xi) - func(xi - h)) / h;
    fdata << 1. / h << " " << abs(dvfunc(xi) - bd) << " " << "\n";
    h *= 0.5;
  }
  h = 0.5;
  fdata << "\n" << "\n";
  for(int i = 0; i < 10; i++){
    cd = (func(xi + h) - func(xi - h)) / (2. * h);
    fdata << 1. / h << " " << abs(dvfunc(xi) - cd) << " " << "\n";
    h *= 0.5;
  }
  h = 0.5;
  fdata << "\n" << "\n";
  for(int i = 0; i < 10; i++){
    hod = (1. / (12. * h)) * (func(xi - 2. * h) - 8. * func(xi - h) + 8. * func(xi + h) - func(xi + 2. * h));
    fdata << 1. / h << " " << abs(dvfunc(xi) - hod) << " " << "\n";
    h *= 0.5;
  }
  fdata.close();
  return 0;
}

double func(double x){
  return sin(x);
}

double dvfunc(double x){
  return cos(x);
}
