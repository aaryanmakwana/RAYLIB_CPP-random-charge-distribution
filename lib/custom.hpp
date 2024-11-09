#include <iostream>
#include <raylib.h>
#include "cstdlib"
#include <time.h>

#define n 10
#define K 9000000000.0
#define FPS 60
#define G 0.000000000066734

#define x1 GetScreenWidth()/2
#define y1 GetScreenHeight()/4

double TIME  = 1/FPS;
int FRAME = 0;

Color RedCol = {255,0,0,255};
Color BlueCol = {0,0,255,255};
Color GreenCol = {0,255,0,255};
Color BlackCol = {0,0,0,255};
Color WhiteCol = {255,255,255,255};
Color GreyCol = {12,13,10};

struct displacement{
  double x;
  double y;
};

struct velocity{
  double x;
  double y;
};

struct force{
  double x;
  double y;
};

struct Particle{
  velocity Vel;
  displacement Disp;
  double Mass;
  double Charge;
};

Color Charge_col(float a){
  if (a < 0)
    return RedCol;
  else
    return BlueCol;
}

Particle merge_particles(Particle a, Particle b){
  Particle c;

  c.Disp.x = (a.Disp.x + b.Disp.x)/2;
  c.Disp.x = (a.Disp.x + b.Disp.x)/2;
  c.Vel.y = (a.Mass*a.Vel.y + b.Mass*b.Vel.y)/(a.Mass + b.Mass);
  c.Vel.x = (a.Mass*a.Vel.x + b.Mass*b.Vel.x)/(a.Mass + b.Mass);
  c.Mass = a.Mass + b.Mass;
  c.Charge = a.Charge + b.Charge;

  return c;
}

void Draw_Particle(Particle a){
  DrawCircle(a.Disp.y+500, a.Disp.x+500, a.Mass, Charge_col(a.Charge));
}

double sqr(double a){
    return a*a;
}

double TSQ = sqr(TIME);

double rand_betw(double a, double b){
  //double add = rand()%(int)(b-a);
  return a+rand()%(int)(b-a);
}

double calc_dist(displacement a, displacement b){
  return sqrt(sqr(b.x-a.x) + sqr(b.y-a.y));
}

void walk_Particle(Particle * points, force * F){
  for (int i = 0; i < n; i++) {
    double old_pos_x = (*(points + i)).Disp.x;
    double old_pos_y = (*(points + i)).Disp.y;

    double acc_x = (*(F + i)).x/(*(points + i)).Mass;
    double acc_y = (*(F + i)).y/(*(points + i)).Mass;

    (*(points + i)).Disp.x += (*(points + i)).Vel.x * TIME + TSQ*acc_x;
    (*(points + i)).Disp.y += (*(points + i)).Vel.y * TIME + TSQ*acc_y;

    (*(points + i)).Vel.y += acc_y*TIME;
    (*(points + i)).Vel.x += acc_x*TIME;
  }
}

void Forward_Physics(Particle * points){
  force F[n];

   for (int i = 0; i < n; i++) {
    F[i].x = 0.0;
    F[i].y = 0.0;

    for (size_t j = 0; j < n; j++) {
      double D = calc_dist((*(points + i)).Disp,(*(points + j)).Disp);
      double Q_1 = (*(points + i)).Charge;
      double Q_2 = (*(points + j)).Charge;

      if(D != 0.0){

        double mag = K*Q_1*Q_2/D;

        F[i].x += mag*((*(points + j)).Disp.x - (*(points + i)).Disp.x)/D;
        F[i].y += mag*((*(points + j)).Disp.y - (*(points + i)).Disp.y)/D;

        if (mag > 0){
          F[i].x *= -1;
          F[i].y *= -1;
        }

      }
    }
  }

  FRAME ++;
  walk_Particle(&(*points), F);
}
