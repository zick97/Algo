#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>    // to export data to be executed by gnuplot
using namespace std;

int main(){
  ofstream fdata;           // declare output stream class to operate on files
  int n, i;                 // open the file to be saved
  double sum1 = 0, err, number;
  fdata.open("random.txt", std::ofstream::out);
  for(n = 1; n < 1000000; n *= 2){
    srand48(time(NULL));
    for (i = 1; i <= n; i++){
      number = drand48();
      sum1 = sum1 + number;
    }
    err = abs(sum1/n - 0.5);  //REMEMBER TO SPECIFY 1.0 WHEN OPERATING IN DOUBLE PRECISION!!!!!
    fdata << n << " " << err << " " << "\n"; // write to file
    sum1 = 0;
  }
  fdata.close();
  return 0;
}
