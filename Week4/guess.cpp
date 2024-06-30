#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(){
  srand(time(NULL));											//	Initialize	the	sequence
  int number	=	rand()%100+1;		          //	Generate	a	random	number	in	[1,100]
  int a = 1, b = 100, guess;
  int i;
  for(i = 1; ; i++){
    cout << "N in [" << a << "," << b << "]" << endl << "Enter your guess #" << i << " : ";
    cin >> guess;
    if(guess < number) a = guess;
    if(guess > number) b = guess;
    if(guess == number) break;            //  In generale è meglio uscire con una condizione, ad esempio do{} while()      
  }
  cout << "Number found in " << i << " iterations!" << endl;
  return 0;
}
