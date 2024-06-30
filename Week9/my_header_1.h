#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int	Bisection(double	(*F)(double), double a,	double b,	double tol, double &xm);

int False_position(double (*F)(double), double a, double b, double tol);

int Secant(double (*F)(double), double a, double b, double tol);

int Newton(double (*F)(double), double (*dvF)(double), double a, double b, double tol);

int Bracket(double (*F)(double), int a, int b, int N, double xL[], double xR[]);
