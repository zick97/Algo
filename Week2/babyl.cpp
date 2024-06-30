#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(){
  double s,x,err;
  int i=1;
  cout << setiosflags(ios::scientific); // notaz scientifica
  cout << "Enter a real number: "; cin >> s;
  cout << "Enter your guess: "; cin >> x;
  do{
    x=((s/x)+x)/2;
    err=abs(x-sqrt(s));
    cout << "Iteration # " << i << "  x = " << std::setprecision(9) << x << "  error = " << std::setprecision(9) << err << endl; //setprecision per il numero di cifre da visulaizzare
    i++;
  }
  while (err > 1e-14); //esce quando la condizione non è più verificata
  //altrimenti posso scrivere for infinito come for(i=0;1;i++) [...] if (err<eps) break;
  cout << "=============================================" << endl;
  cout << "The square root of " << s << " is " << std::setprecision(9) << x << endl << "The exact value is " << std::setprecision(9) << sqrt(s) << endl;
  return 0;
}
