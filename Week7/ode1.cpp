#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

void Euler_step(double	t,	double	*Y,	void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);

void RK2_step(double t, double	*Y, void	(*RHSFunc)(double,	double	*,	double	*), double	dt,	int	neq);

void dYdt(double t, double *Y, double *R);

int main(){
  int n = 6, i;
  double t, dt, Y[1], abs_err, rel_err;

  ofstream fdata;

  fdata.open("ode1_euler.txt", std::ofstream::out);
  fdata << setiosflags(ios::scientific);

  //Euler_step//////////////////////////////////////////////////////////////////
  for(int k = 0; k < 2; k++){
    fdata << "h" << "\t \t" << "t" << "\t \t" << "Y(t)" << "\t \t" << "abs_err" << "\t \t" << "rel_err" << "\n";

    t = 0;
    dt = 3. / (double)n;

    if(t == 0) Y[0] = 1.;
    //Euler_step(t, Y, dYdt, dt, 1);
    abs_err = abs(Y[0] - exp(-0.5 * t * t));
    rel_err = abs_err / exp(-0.5 * t * t);      // definzione errore relativo
    fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << abs_err << "\t" << rel_err << "\n";

    for(i = 1; i <= n; i++){
      Euler_step(t, Y, dYdt, dt, 1);
      t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
      abs_err = abs(Y[0] - exp(-0.5 * t * t));
      rel_err = abs_err / exp(-0.5 * t * t);
      fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << abs_err << "\t" << rel_err << "\n";
    }
    fdata << "\n" << "\n";
    n = 15;
  }
  fdata.close();

  //RK2_step////////////////////////////////////////////////////////////////////
  fdata.open("ode1_RK2.txt", std::ofstream::out);
  t = 0;
  n = 6;
  for(int k = 0; k < 2; k++){
    fdata << "h" << "\t \t" << "t" << "\t \t" << "Y(t)" << "\t \t" << "abs_err" << "\t \t" << "rel_err" << "\n";

    t = 0;
    dt = 3. / (double)n;

    if (t == 0) Y[0] = 1.;
    //RK2_step(t, Y, dYdt, dt, 1);
    abs_err = abs(Y[0] - exp(-0.5 * t * t));
    rel_err = abs_err / exp(-0.5 * t * t);      // definzione errore relativo
    fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << abs_err << "\t" << rel_err << "\n";

    for(i = 1; i <= n; i++){
      RK2_step(t, Y, dYdt, dt, 1);
      t = i * dt;                               // lo aggiorno qui perchè RK2 restituisce Y(t + dt) ma voglio Y(t)
      abs_err = abs(Y[0] - exp(-0.5 * t * t));
      rel_err = abs_err / exp(-0.5 * t * t);
      fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << abs_err << "\t" << rel_err << "\n";
    }
    fdata << "\n" << "\n";
    n = 15;
  }

  fdata.close();
  return 0;
}

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

void dYdt(double t, double *Y, double *R){ // è la rhs di fatto, Y e R si passano per indirizzo proprio per poter richiamare gli array nella f precedente
  double y = Y[0];                         // guardando il metodo di eulero, si va quindi a creare una ricorsione a partire dal valore iniziale
  R[0] = -(t * y);
}
