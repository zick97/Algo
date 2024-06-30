#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(){
  float x=1e+04,y=1e-01;
  int i=0;
  cout << setiosflags(ios::scientific); // notaz scientifica
  cout << endl << "funzione f(x) = sqrt(x^2+1) - 1" << endl << "---------------------" << endl;
  do{
    float fx1=sqrt((x*x) + 1.0) - x; //1.0 per adattare i tipi!!!
    cout << "x = " << x << "  fx1 = " << fx1 << "  fx2 = " << 1/(sqrt((x*x) + 1.0) + x);
    cout << "  f(taylor) = " << (0.5/x) + 1/(8*x*x*x) << endl;
    x=10*x;
    i++;
  }
  while (i<=6);
  i=0;
  cout << endl << "funzione g(y) = 1 - cos(y)" << endl << "---------------------" << endl;
  do{
    float gy1=1.0 - cos(y);
    cout << "y = " << y << "  gy1 = " << gy1 << "  gy2 = " << sin(y)*sin(y)/(1.0+cos(y));
    cout << "  f(taylor) = " << 1.0 - cos(y) + sin(y)*y + cos(y)*y*y << endl;
    y=y/10;
    i++;
  }
  while (i<=6);
  return 0;
}
