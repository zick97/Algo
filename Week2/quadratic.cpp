#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(){
  double x1,x2,x1_1,x2_2;
  cout << "x1 = "; cin >> x1;
  cout << "x2 = "; cin >> x2;
  double a=1,b,c;
  cout << setiosflags(ios::scientific); // notaz scientifica
  b=-(x1+x2);
  c=(x1*x2);
  double delta=b*b-4*a*c;

  x1_1=(-b+sqrt(delta))*0.5; //meglio mettere moltiplicazione perchè divisione è più lenta
  x2_2=(-b-sqrt(delta))*0.5; //meglio non mettere il calcolo esplicito del delta, ma definirlo prima
  cout << "x1_1 = " << x1_1 << "  err% = " << ((x1-x1_1)/x1)*100 << endl;
  cout << "x2_2 = " << x2_2 << "  err% = " << ((x2-x2_2)/x2)*100 << endl;

  //uso una formula alternativa per eliminare la sottrazione
  if (b>=0){
    x1_1=2*c/((-b-sqrt(delta)));
    x2_2=(-b-sqrt(delta))*0.5;
  }
  else{
    x1_1=(-b-sqrt(delta))*0.5;
    x2_2=2*c/((-b-sqrt(delta)));
  }
  cout << "Imponendo la condizione:" << endl << "x1_1 = " << x1_1 << "  err% = " << ((x1-x1_1)/x1)*100 << endl;
  cout << "x2_2 = " << x2_2 << "  err% = " << ((x2-x2_2)/x2)*100 << endl;
  return 0;
}
