#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

void Euler_step(double	t,	double	*Y,	void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);

void RK2_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);

void RK4_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);
