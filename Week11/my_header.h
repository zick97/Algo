#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define SESSION 2
#define METHOD 3
#define NX 128 // ricordarsi di cambiarli: 32 per Session 1, 128 per Session 2, NX129, NY65 per Session 3
#define NY 128

#define IBEG 1
#define IEND NX - 2
#define JBEG 1
#define JEND NY - 2

double S(double x, double y);

double func(double x, double y);

void Boundary_conditions(double *x, double *y, double **phi, double h);

void Jacobi_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double **phi_1, double *x, double *y, double h, double tol);

void Gauss_Seidel_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol);

void SOR_method(void (*Boundary_conditions)(double*, double*, double**, double), double **phi, double *x, double *y, double h, double tol);
