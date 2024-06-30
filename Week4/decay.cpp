#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main(){
  ofstream fdata;
  double lambda = 0.01;
  int i, t = 1, decay, delta, N0 = 10000, N = N0;
  fdata.open("decay.txt", std::ofstream::out);
  srand48(time(NULL));
  do{
    delta = 0;
    for(i = 0; i < N; i++){
      decay = drand48();
      if (decay < lambda) delta++; // se qui metto N-- escludo gli atomi che non decadono -> devo fare conteggio su quanti decadono e solo dopo sottrarre
    }
    N = N - delta;
    fdata << t << " " << (double)N/N0 << " " << "\n"; // write to file
    t++;
  }
  while (N > 0);
  fdata.close();
  return 0;
}
