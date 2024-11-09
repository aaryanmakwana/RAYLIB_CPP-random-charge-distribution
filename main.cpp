#include "./lib/custom.hpp"
#define WIDTH 1000
#define HEIGHT 1000
#include <math.h>


int main(){

  InitWindow(WIDTH, HEIGHT, "CHARGE SIMULATION");


  //Particle PTS[2];
  Particle PTS[n];

  srand(time(NULL));

  for (int i = 0; i < n; i++) {
    PTS[i].Disp.x = rand_betw(-400,400);
    PTS[i].Disp.y = rand_betw(-400,400);
    PTS[i].Vel.y = rand_betw(-5,5);
    PTS[i].Vel.x = rand_betw(-5,5);
    PTS[i].Mass = rand_betw(5,10);
    PTS[i].Charge = rand_betw(-5,5);
  }

  SetTargetFPS(FPS);


  while (!(WindowShouldClose())) {
      BeginDrawing();
      ClearBackground(BlackCol);

      Particle center = PTS[0];

      for (int i = 1; i < n; i++) {
        Draw_Particle(PTS[i]);
        center = merge_particles(center,PTS[i]);
      }
      //Draw_Particle(center);

      if(IsKeyPressed(KEY_K)){
        for (int i = 0; i < n; i++) {
          PTS[i].Disp.x = rand_betw(-400,400);
          PTS[i].Disp.y = rand_betw(-400,400);
          PTS[i].Vel.y = rand_betw(-5,5);
          PTS[i].Vel.x = rand_betw(-5,5);
          PTS[i].Mass = rand_betw(5,10);
          PTS[i].Charge = rand_betw(-5,5);
        }

      }

      //DrawText(TextFormat("%d\n",FRAME),5,5,20,WhiteCol);
      EndDrawing();
  }

  return 0;
}

/*
eval cc main.cpp $(pkg-config --libs --cflags raylib) -o App
*/
