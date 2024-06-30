#include "my_header.h"

int main(){
  int i, j;
  double tol = 1.e-7;

#if SESSION == 1
  double xl = 0., xr = 1., yl = 0., yr = 1.;

#elif SESSION == 2
  double xl = -1., xr = 1., yl = -1., yr = 1.;

#elif SESSION == 3
  double xl = 0., xr = 2., yl = 0., yr = 1.;
#endif


  double h = fabs(xr - xl) / (double)(NX - 1);

  ofstream fdata;

  double **phi;
  phi = new double*[NX];
  phi[0] = new double [NX*NY];

  for(i = 1; i < NX; i++){
    phi[i] = phi[i - 1] + NY;
  }

  double **phi_1;
  phi_1 = new double*[NX];
  phi_1[0] = new double [NX*NY];
  for(int i = 1; i < NY; i++){
    phi_1[i] = phi_1[i - 1] + NX;
  }

  double *x;
  x = new double[NX];
  double *y;
  y = new double[NX];
  for(i = 0; i < NX; i++){
    x[i] = xl + i * h;
    y[i] = yl + i * h;
  }

  fdata << setiosflags(ios::scientific);
#if SESSION == 1
  fdata.open("elliptic_1.txt", std::ofstream::out);

#elif SESSION == 2
  fdata.open("elliptic_2.txt", std::ofstream::out);
#endif

#if METHOD == 1
  Jacobi_method(Boundary_conditions, phi, phi_1, x, y, h, tol);
  for(int j = 0; j < NX; j++){
    for(int i = 0; i < NY; i++){
      fdata << x[i] << "\t" << y[j] << "\t" << phi_1[i][j] << "\n";
    }
    fdata << "\n";
  }

#elif METHOD == 2
  Gauss_Seidel_method(Boundary_conditions, phi, x, y, h, tol);
  for(int j = 0; j < NX; j++){
    for(int i = 0; i < NY; i++){
      fdata << x[i] << "\t" << y[j] << "\t" << phi[i][j] << "\n";
    }
    fdata << "\n";
  }

#elif METHOD == 3
  SOR_method(Boundary_conditions, phi, x, y, h, tol);
  for(int j = 0; j < NX; j++){
    for(int i = 0; i < NY; i++){
      fdata << x[i] << "\t" << y[j] << "\t" << phi[i][j] << "\n";
    }
    fdata << "\n";
  }
#endif

  fdata.close();

  delete phi[0];
  delete phi;
  delete phi_1[0];
  delete phi_1;
  delete x;
  delete y;

  return 0;
}
