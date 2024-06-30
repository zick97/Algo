#include "my_header.h"

void dYdt(double t, double *Y, double *R);

int main(){
  int n = 4, i;
  double t, dt, Y[2], ta = 0, tb = 3., abs_err;

  ofstream fdata;


  fdata << setiosflags(ios::scientific);
  fdata.open("cvg_euler.txt", std::ofstream::out);
  //Euler_step//////////////////////////////////////////////////////////////////
    fdata << "dt" << "\t \t" << "abs_err" << "\n";

    do{
      t = 0.;
      dt = (tb - ta) / (double)n;
      if(t == 0){ Y[0] = 1.; Y[1] = 0; }
      //Euler_step(t, Y, dYdt, dt, 1);
      //fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\n";

      for(i = 1; i <= n; i++){
        Euler_step(t, Y, dYdt, dt, 2);
        t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
      }
      abs_err = abs(Y[0] - cos(3.));
      fdata << dt << "\t" << std::setprecision(6) << abs_err << "\n";
      n *= 2;
    }
    while(n <= 2048);

  fdata.close();

  fdata.open("cvg_RK2.txt", std::ofstream::out);
  //RK2_step//////////////////////////////////////////////////////////////////
    fdata << "dt" << "\t \t" << "abs_err" << "\n";

    n = 4;
    do{
      t = 0.;
      dt = (tb - ta) / (double)n;
      if(t == 0){ Y[0] = 1.; Y[1] = 0; }

      for(i = 1; i <= n; i++){
        RK2_step(t, Y, dYdt, dt, 2);
        t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
        //fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\n";
      }
      abs_err = abs(Y[0] - cos(3.));
      fdata << dt << "\t" << std::setprecision(6) << abs_err << "\n";
      n *= 2;
    }
    while(n <= 2048);

  fdata.close();

  fdata.open("cvg_RK4.txt", std::ofstream::out);
  //RK4_step//////////////////////////////////////////////////////////////////
    fdata << "dt" << "\t \t" << "abs_err" << "\n";

    n = 4;
    do{
      t = 0.;
      dt = (tb - ta) / (double)n;
      if(t == 0){ Y[0] = 1.; Y[1] = 0; }

      for(i = 1; i <= n; i++){
        RK4_step(t, Y, dYdt, dt, 2);
        t = i * dt;                               // lo aggiorno qui perchè eulero restituisce Y(t + dt) ma voglio Y(t)
        //fdata << dt << "\t" << t << "\t" << Y[0] << "\t" << Y[1] << "\n";
      }
      abs_err = abs(Y[0] - cos(3.));
      fdata << dt << "\t" << std::setprecision(6) << abs_err << "\n";
      n *= 2;
    }
    while(n <= 2048);

  fdata.close();

  return 0;
}

void dYdt(double t, double *Y, double *R){ // è la rhs di fatto, Y e R si passano per indirizzo proprio per poter richiamare gli array nella f precedente
  double x = Y[0], y = Y[1];                         // guardando il metodo di eulero, si va quindi a creare una ricorsione a partire dal valore iniziale
  R[0] = y;
  R[1] = -x;
}
