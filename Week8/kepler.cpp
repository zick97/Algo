#include "my_header.h"

void dYdt(double t, double *Y, double *R);

int main(){
  double t, dt, Y[4], prev, a = 0.5, r, v;
  double vy0 = sqrt(a / 4.);
  double Etot, Ek, Ep;
  //double T = 2 * M_PI * 4. / vy0;
  int count = 0;

  //dt = T / 100.;

  ofstream fdata;
  fdata << setiosflags(ios::scientific);
  fdata.open("kepler.txt", std::ofstream::out);
  fdata << "t \t \t x(t) \t \t y(t) \t \t vx(t) \t \t vy(t) \t \t Ek \t \t Ep \t \t Etot \n";

  t = 0.;
  count = 0.;
  if(t == 0.){
    Y[0] = 4.;
    Y[1] = 0.;
    Y[2] = 0.;
    Y[3] = vy0;
  }
  for(int i = 0; i > -1; i++){
    r = sqrt(Y[0] * Y[0] + Y[1] * Y[1]);
    v = sqrt(Y[2] * Y[2] + Y[3] * Y[3]);
    dt = 0.1 * r / v;                //adaptive time step

    prev = Y[2];

    RK4_step(t, Y, dYdt, dt, 4);

    t += dt;
    fdata << t << "\t" << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t";

    if (Y[2] * prev < 0){           //condition of turning point
      count++;
    }
    Ek = 0.5 * v * v;
    Ep = -1. / r;
    Etot = Ek + Ep;

    fdata << Ek << "\t" << Ep << "\t "<< Etot << "\n";

    if (count == 20) break;         //stops at 10 orbits
  }

  fdata.close();

  return 0;
}


void dYdt(double t, double *Y, double *R){
  double x = Y[0], y = Y[1], vx = Y[2], vy = Y[3];
  double r = sqrt(x * x + y * y);
  R[0] = vx;
  R[1] = vy;
  R[2] = -x / (r * r * r);
  R[3] = -y / (r * r * r);
}
