#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void Print(double A[][4]);

void Print_pointer(double **A, int nrow, int ncol);

void Matrix_vect(double **A, int nrow, int ncol, double bs[4]);

#define g_nrow 4
#define g_ncol 4

int main(){
  int i, j;

  //native method
  double As[g_nrow][g_ncol] = { {1., 3., 2., -4} , {7., 2., 4., 1.} , {0., -1., 2., 2.} , {6., 3., 0., 1.} };
  double bs[g_ncol] = {1., 0., 3., 2.};

  Print(As);

  //pointer to pointer method
  double **Ad;
  int nrow = g_nrow, ncol = g_ncol;
  Ad = new double*[nrow];
  Ad[0] = new double [ncol*nrow];

  for(i = 1; i < nrow; i++){
    Ad[i] = Ad[i -1] + ncol;
  }
  delete Ad[0];
  delete Ad;

  for(i = 0; i < ncol; i++){
    for(j = 0; j < nrow; j++){
      Ad[i][j] = As[i][j];
    }
  }

  Print_pointer(Ad, nrow, ncol);

  cout << endl;

  Matrix_vect(Ad, nrow, ncol, bs);

  return 0;
}

void Print(double A[][4]){
  cout << fixed << setprecision(4) << endl;

  for(int i = 0; i < g_ncol; i++){
    for(int j = 0; j < g_nrow; j++){
      cout << setw(10) << right << A[i][j] << "  ";
    }
    cout << endl;
  }
}

void Print_pointer(double **A, int nrow, int ncol){
  cout << fixed << setprecision(4) << endl;

  for(int i = 0; i < ncol; i++){
    for(int j = 0; j < nrow; j++){
      cout << setw(10) << right << A[i][j] << "  ";
    }
    cout << endl;
  }
}

void Matrix_vect(double **A, int nrow, int ncol, double bs[4]){
  double V[4];

  for(int i = 0; i < nrow; i++){
    V[i] = 0.;
    for(int j = 0; j < ncol; j++){
      V[i] += A[i][j] * bs[j];
    }
  }

  for(int i = 0; i < nrow; i++){
    cout << setw(10) << right << V[i] << endl;
  }
}
