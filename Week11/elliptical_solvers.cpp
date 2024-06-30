#include "my_header.h"

#if SESSION == 1
double func(double x, double y){
  double S = 0.;
  return exp(-M_PI * x) * sin(-M_PI * y) + (0.25 * S * (x * x + y * y));
}

void Boundary_conditions(double *x, double *y, double **phi, double h){
  for(int i = 0; i < NX; i++){
    phi[i][0] = func(x[i], y[0]);
    phi[i][NY - 1] = func(x[i], y[NY - 1]);
  }

  for(int j = 0; j < NY; j++){
    phi[0][j] = func(x[0], y[j]);
    phi[NX - 1][j] = func(x[NX - 1], y[j]);
  }
}

void Jacobi_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double **phi_1, double *x, double *y, double h, double tol){
  double err, S = 0.;
  double **tmp;
  int cont = 0;

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi_1[i][j] = 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S);
      }
    }
    tmp = phi;
    phi = phi_1;
    phi_1 = tmp;

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S);
      }
    }

    cont++;
  }
  while(err > tol);

  cout << endl << "Jacobi: " << cont << endl;
}

void Gauss_Seidel_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol){
  double err;
  double S = 0.;
  int cont = 0;

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi[i][j] = 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S);
      }
    }

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S);
      }
    }

    cont++;
  }
  while(err > tol);

  cout << endl << "Gauss-Seidel: " << cont << endl;
}

void SOR_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol){
  double err;
  double S = 0.;
  int cont = 0;
  double omega = 2. / (1. + M_PI / (double)NX);

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi[i][j] = (1. - omega) * phi[i][j] + omega * 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S);
      }
    }

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S);
      }
    }

    cont++;
  }
  while(err > tol);

  cout << endl << "SOR: " << cont << endl;
}


#elif SESSION == 2
double func(double x, double y){
  double a = 0.1, rho_0 = 1.;
  double r = sqrt(x * x + y * y);

  if(r <= a) return -0.25 * r * r * rho_0;
  else return -0.5 * a * a * rho_0 * (log(r / a) + 0.5);
}

double S(double x, double y){
  double r = sqrt(x * x + y * y);
  double a = 0.1, rho_0 = 1.;
  if (r <= a) return -rho_0;
  else return 0.;
}

void Boundary_conditions(double *x, double *y, double **phi, double h){
  for(int i = 0; i < NX; i++){
    phi[i][0] = func(x[i], y[0]);
    phi[i][NY - 1] = func(x[i], y[NY - 1]);
  }

  for(int j = 0; j < NY; j++){
    phi[0][j] = func(x[0], y[j]);
    phi[NX - 1][j] = func(x[NX - 1], y[j]);
  }
}


void Jacobi_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double **phi_1, double *x, double *y, double h, double tol){
  double err;
  double **tmp;
  int cont = 0;

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi_1[i][j] = 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S(x[i], y[j]));
      }
    }
    tmp = phi;
    phi = phi_1;
    phi_1 = tmp;

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S(x[i], y[j]));
      }
    }

    cont++;
  }
  while(err > tol);

  cout << endl << "Jacobi: " << cont << endl;
}

void Gauss_Seidel_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol){
  double err;
  int cont = 0;

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi[i][j] = 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S(x[i], y[j]));
      }
    }

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S(x[i], y[j]));
      }
    }
    cont++;
  }
  while(err > tol);

  cout << endl << "Gauss-Seidel: " << cont << endl;
}

void SOR_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol){
  double err;
  int cont = 0;
  double omega = 2. / (1. + M_PI / (double)NX);

  do{
    Boundary_conditions(x, y, phi, h);
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        phi[i][j] = (1. - omega) * phi[i][j] + omega * 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1] - h * h * S(x[i], y[j]));
      }
    }

    err = 0.;
    for(int i = IBEG; i <= IEND; i++){
      for(int j = JBEG; j <= JEND; j++){
        err += fabs((phi[i + 1][j] - 2. * phi[i][j] + phi[i - 1][j]) + (phi[i][j + 1] - 2. * phi[i][j] + phi[i][j - 1]) - h * h * S(x[i], y[j]));
      }
    }
    cout << cont << " \t " << err << endl;
    cont++;
  }
  while(err > tol);

  cout << endl << "SOR: " << cont << endl;
}
#endif
