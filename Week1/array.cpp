/*• arrays.cpp:	compute	the	average,	variance	and	standard	deviation	of	an	array.
							You	can	use	the	drand48()	function	to	fill	the	array	with	random	numbers.	*/
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h>
using namespace std;

void stampa(float v[], int n){
  int i;
  for(i=0;i<n;i++){
    cout << "v[" << i <<"] = " << v[i] << endl;
  }
}

void Average(float v[], int n){
  int i;
  float s=0,d=0;
  for(i=0;i<n;i++){
    s=s+v[i];
  }
  cout << "MEDIA = " << s/n << endl;
  for(i=0;i<n;i++){
    d=d+(v[i]-s/n)*(v[i]-s/n);
  }
  cout << "VAR = " << d/n << endl;
  cout << "DEVSTD = " << sqrt(d/n) << endl;
}

int main(){
  int i,n;
  cout << "Dimensione array: "; cin >> n;
  float v[n];
  srand(time(NULL));
  for(i=0;i<n;i++){
    v[i]=rand()%11;
  }
  //stampa(v,n);
  Average(v,n);
  return 0;
}
