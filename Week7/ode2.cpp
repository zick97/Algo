#include "my_header.h"

void dYdt(double t, double *Y, double *R);

int main(){
  int n = 200, i;
  double t = 0, dt, Y[2], ta = 0, tb = 20. * M_PI, r;
  dt = (tb - ta) / (double)n;

  ofstream fdata;


  fdata << setiosflags(ios::scientific);
  fdata.open("ode2_euler.txt", std::ofstream::out);
  //Euler_step//////////////////////////////////////////////////////////////////
    fdata << "h" << "\t \t" << "t" << "\t \t" << "X(t)" << "\t \t" << "Y(t)" << "\t \t" << "R" << "\n";

    if(t == 0){ Y[0] = 1.; Y[1] = 0; }
    r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
    //Euler_step(t, Y, dYdt, dt, 1);
    fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";

    for(i = 1; i <= n; i++){
      Euler_step(t, Y, dYdt, dt, 2);
      t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
      r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
      fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";
    }

  fdata.close();

  t = 0.;
  fdata.open("ode2_RK2.txt", std::ofstream::out);
  //RK2_step//////////////////////////////////////////////////////////////////
    fdata << "h" << "\t \t" << "t" << "\t \t" << "X(t)" << "\t \t" << "Y(t)" << "\t \t" << "R" << "\n";

    if(t == 0){ Y[0] = 1.; Y[1] = 0; }
    r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
    //Euler_step(t, Y, dYdt, dt, 1);
    fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";

    for(i = 1; i <= n; i++){
      RK2_step(t, Y, dYdt, dt, 2);
      t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
      r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
      fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";
    }

  fdata.close();

  t = 0.;
  fdata.open("ode2_RK4.txt", std::ofstream::out);
  //RK4_step//////////////////////////////////////////////////////////////////
    fdata << "h" << "\t \t" << "t" << "\t \t" << "X(t)" << "\t \t" << "Y(t)" << "\t \t" << "R" << "\n";

    if(t == 0){ Y[0] = 1.; Y[1] = 0; }
    r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
    //Euler_step(t, Y, dYdt, dt, 1);
    fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";

    for(i = 1; i <= n; i++){
      RK4_step(t, Y, dYdt, dt, 2);
      t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
      r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
      fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << r << "\n";
    }

  fdata.close();
  return 0;
}

void dYdt(double t, double *Y, double *R){ // è la rhs di fatto, Y e R si passano per indirizzo proprio per poter richiamare gli array nella f precedente
  double x = Y[0], y = Y[1];                         // guardando il metodo di eulero, si va quindi a creare una ricorsione a partire dal valore iniziale
  R[0] = y;
  R[1] = -x;
}
