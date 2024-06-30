#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

double func(double x){
  return 1./(0.5 * sqrt(2. * M_PI)) * exp(-0.5 * (x/0.5) * (x/0.5));
}

int main(){
  ofstream fdata;
  double C = func(0), x, y;
  int i, N = 1.e+5;
  fdata.open("gauss_distr.txt", std::ofstream::out);
  srand48(time(NULL));

  for(i = 0; i < N; i++){
    x = 2. * (drand48() * 5. - 2.5) ;
    y = drand48();
    if (y < func(x)){
      fdata << x << " " << y << " " << "\n"; // write to file
    }
  }
  fdata.close();
  return 0;
}
