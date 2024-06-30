/*count.cpp:	write	a	program	that	prints	the	integers	numbers	from	1	to	10,	using	for
and	while	loops.
• Modify	the	previous	code	to	print	only	odd	numbers.
• operations.cpp:	given	two	float	numbers	and	two	integer	numbers,	perform
simple	arithmetic	operations	(+,	-,	*,	/)	-->	watch	out	integer	division	!	*/
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

void numerifor(int n){
  int i;
  for(i=1;i<=n;i++){
    cout << i << " ";
  }
  cout << "con for" << endl;
}

void numeriwhile(int n){
  int i=1;
  while(i<=n){
    cout << i << " ";
    i++;
  }
  cout << "con while" << endl;
}

void numeridisparifor(int n){
  int i;
  for (i=1;i<=n;i++){
    if (i%2==1) cout << i << " ";
  }
  cout << "con for" << endl;
}

void numeridispariwhile(int n){
  int i=1;
  while(i<=n){
    if (i%2==1) cout << i << " ";
    i++;
  }
  cout << "con while" << endl;
}

int main(){
  int n=10;
  int a,b;
  float x,y;
  numerifor(n);
  numeriwhile(n);
  numeridisparifor(n);
  numeridispariwhile(n);
  cout << endl << "Inserire a: "; cin >> a;
  cout << "Inserire b: "; cin >> b;
  cout << "Inserire x: "; cin >> x;
  cout << "Inserire y: "; cin >> y; cout << endl;
  cout << "a + y = " << a+y << endl;
  cout << "b + x = " << b+y << endl;
  cout << "a - b = " << a-b << endl;
  cout << "a - y = " << a-y << endl;
  cout << "a/x = " << (float)a/x << endl;
  cout << "a/b (no casting) = " << a/b << endl; //no casting
  cout << "a/b (casting) = " << (float)a/b << endl; //casting
  cout << "y/b = " << y/(float)b << endl;
  cout << "x*b = " << x*(float)b << endl;
  cout << "a*x = " << (float)a*x << endl;
  return 0;
}
