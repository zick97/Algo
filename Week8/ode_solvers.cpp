#include "my_header.h"

void Euler_step(double	t,	double	*Y,	void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq){
  int i;
  double rhs[neq];

  RHSFunc(t, Y, rhs);
  for(i = 0; i < neq; i++){
    Y[i] = Y[i] + dt * rhs[i];             // in c++ non si può richiamare direttamente l'array prodotto dalla funzione, ma bisogna ridefinirlo
  }
}

void RK2_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq){
		double Y1[neq], k1[neq], k2[neq];

		RHSFunc(t, Y, k1);
		for	(int i = 0; i < neq; i++){
      Y1[i]	=	Y[i] + (0.5 * dt * k1[i]);
    }
		RHSFunc(t + (0.5 * dt), Y1, k2);
		for	(int i = 0; i < neq; i++){
      Y[i]	+=	dt * k2[i];
    }
}

void RK4_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq){
		double Y1[neq], Y2[neq], Y3[neq], k1[neq], k2[neq], k3[neq], k4[neq];

		RHSFunc(t, Y, k1);

		for	(int i = 0; i < neq; i++){
      Y1[i]	=	Y[i] + (0.5 * dt * k1[i]);
    }
		RHSFunc(t + (0.5 * dt), Y1, k2);

    for	(int i = 0; i < neq; i++){
      Y2[i]	=	Y[i] + (0.5 * dt * k2[i]);
    }
    RHSFunc(t + (0.5 * dt), Y2, k3);

    for	(int i = 0; i < neq; i++){
      Y3[i]	=	Y[i] + (dt * k3[i]);
    }
    RHSFunc((t + dt), Y3, k4);

    for	(int i = 0; i < neq; i++){
      Y[i] += (dt / 6.) * (k1[i] + (2. * k2[i]) + (2. * k3[i]) + k4[i]);
    }

}
