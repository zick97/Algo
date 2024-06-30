#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void Gauss_elim(double **A, double N, double b[]);

int main(){
  int i, j, k;
  double b[10];

  int N = 4;

  //pointer to pointer method
  double **A;
  A = new double*[N];
  A[0] = new double [N*N];
  for(i = 1; i < N; i++){
    A[i] = A[i - 1] + N;
  }

  if (N == 3){
    A[0][0] = 2.;   A[0][1] = -1.;  A[0][2] = 0.;
    A[1][0] = -1.;  A[1][1] = 2.;   A[1][2] = -1.;
    A[2][0] = 0.;   A[2][1] = -1.;  A[2][2] = 2.;

    b[0] = 1.;
    b[1] = 2.;
    b[2] = 1.;
  }

else if (N == 4){
    A[0][0] = 1.;   A[0][1] = 2.;   A[0][2] = 1.;   A[0][3] = -1.;
    A[1][0] = 3.;   A[1][1] = 6.;   A[1][2] = 4.;   A[1][3] = 4.;
    A[2][0] = 4.;   A[2][1] = 4.;   A[2][2] = 3.;   A[2][3] = 4.;
    A[3][0] = 2.;   A[3][1] = 0.;   A[3][2] = 1.;   A[3][3] = 5.;

    b[0] = 5.;
    b[1] = 16.;
    b[2] = 22.;
    b[3] = 15.;
  }

  Gauss_elim(A, N, b);

  delete A[0];
  delete A;

  return 0;
}

void Gauss_elim(double **A, double N, double b[]){
  int i, j, k, jmax;
  double x[10], A_tmp, b_tmp;
  double g, tmp;
  for(k = 0; k <= N - 2; k++){
    jmax = k;                                           // partial pivoting
    for(j = k + 1; j <= N - 1; j++){
      if(fabs(A[j][k]) >= fabs(A[jmax][k])) jmax = j;   // cerco elemento massimo nella colonna
    }

    for(i = 0; i < N; i++){
      A_tmp = A[jmax][i];                               // per ogni colonna i-esima, scambio l'elemento di riga corrispondente
      A[jmax][i] = A[k][i];
      A[k][i] = A_tmp;
    }
    b_tmp = b[jmax];                                    // bisogna cambiare anche b, di cui però si ha un solo elemento
    b[jmax] = b[k];
    b[k] = b_tmp;

    for(i = k + 1; i <= N - 1; i++){
      g = A[i][k] / A[k][k];
      for(j = k + 1; j <= N - 1; j++){ A[i][j] -= g * A[k][j]; }
      A[i][k] = 0.;
      b[i] -= g * b[k];
    }
  }

  for(i = N - 1; i >= 0; i--){
    tmp = b[i];
    for(j = N - 1; j > i; j--){ tmp -= x[j] * A[i][j]; }
    x[i] = tmp / A[i][i];
  }

  cout << endl << "[ ";
  for(i = 0; i < N; i++){
    cout << x[i] << " ";
  }
  cout << "]" << endl;
}
