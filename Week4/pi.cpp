#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main(){
  ofstream fdata;
  double x, y, I, err;
  long int i, N = 2, Nin;
  srand48(time(NULL));

  fdata.open("pi.txt", std::ofstream::out);
  do{
    Nin = 0;
    for(i = 0; i < N; i++){
      x = 2. * (drand48() - 0.5);
      y = 2. * (drand48() - 0.5);
      if (x*x + y*y <= 1){
        Nin++;
      }
    }
    I = 4 * (double)Nin/N;
    err = abs(I/M_PI - 1.);
    fdata << N << " " << err << " " << "\n"; // write to file
    N *= 2;
  }
  while (err > 1.e-4);
  fdata.close();
  cout << "N = " << N << endl << "pi = " << std::setprecision(12) << M_PI << " ; I = " << std::setprecision(12) << I << endl;
  return 0;
}
