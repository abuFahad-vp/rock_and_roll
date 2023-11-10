#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define GRID_SIZE 20
#define screenWidth 800
#define screenHeight 460
#define windowWidth 800
#define windowHeight 550


int main_1() {
    const int windowwidth = 800;
    const int windowheight = 480;

    InitWindow(windowwidth, windowheight, "Dice Roll Animation");

    SetTargetFPS(60);

    int current = 1;
    int rollDuration = 30;
    int rollCounter = 0;

    while (!WindowShouldClose()) {
        // Update
        if (rollCounter < rollDuration) {
            // Simulate dice roll animation by updating dice face frequently
            current = GetRandomValue(1, 6);
            rollCounter++;
        } else {
            // Display the final result after animation completes
            DrawText(TextFormat("Dice: %d", current), windowWidth / 2 - 40, windowHeight / 2 - 10, 40, BLACK);

            // Check for key press to trigger a new roll
            if (IsKeyPressed(KEY_SPACE)) {
                rollCounter = 0;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (rollCounter < rollDuration) {
            // Display the rolling animation
            DrawText(TextFormat("Rolling... %d", current), windowWidth / 2 - 80, windowHeight / 2 - 10, 30, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int main(void) {

  InitWindow(windowWidth, windowHeight, "Rock and Roll");

  SetTargetFPS(10);

  // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

  Image worm;
  Texture2D texture;

  worm = LoadImage("textures/worm1.png");  
  ImageFlipHorizontal(&worm);
  ImageResize(&worm, 6*GRID_SIZE, GRID_SIZE); 
  texture = LoadTextureFromImage(worm);
  UnloadImage(worm);

  int pos[6] = {0};
  // int tex_index[6] = {0};
  bool iswin = false;
  int winner = 0;
  char dice[5] = "";
  int current = 1;
  int rollDuration = 20;
  int rollCounter = 0;

  while (!WindowShouldClose()) {
    for(int i=0;i<6;i++) {
      if (pos[i] + 6*GRID_SIZE >= (screenWidth-90)) {
        iswin = true;
        winner = i+1;
      }
    }

   // Update
   if (rollCounter < rollDuration) {
       // Simulate dice roll animation by updating dice face frequently
       current = (GetRandomValue(1, 6) - 1);
       rollCounter++;
   } else {
       sprintf(dice,"%d", current);

       if (IsKeyPressed(KEY_SPACE)) {
        pos[current] += 50;
        rollCounter = 0;
       }
   }
      // Draw
      BeginDrawing();

      ClearBackground(WHITE);

      if (!iswin) {

        if (rollCounter < rollDuration) {
            // Display the rolling animation
            DrawText(TextFormat("Rolling...%d",current), windowWidth / 2 - 80, windowHeight - 60, 30, BLACK);
        }else {

          sprintf(dice, "%d",current + 1);
          DrawText(dice, windowWidth / 2 - 40, windowHeight - 60, 60, DARKGRAY);
        }
      
        DrawRectangle(screenWidth-90, 0, 60, screenHeight, DARKGRAY);

        for(int i=0;i<6;i++) {
          DrawTexture(texture, pos[i], 80*i+10, WHITE);
          char num[4];
          sprintf(num, "%d", i+1);
          DrawText(num,screenWidth-70,80*i+10,30,RAYWHITE);
        }
      } else {
        char msg[50];
        sprintf(msg, "Player %d wins", winner);
        DrawText(msg,windowWidth / 2 - 100, windowHeight / 2 - 30, 30, GRAY);
        if(IsKeyPressed(KEY_SPACE)) {
          for(int i = 0;i<6;i++) {
            pos[i] = 0;
            // tex_index[i] = 0;
          }
          current = 0;
          iswin = false;
          winner = 0;
          sprintf(dice,"");
        };
      }

      EndDrawing();
  }

  UnloadTexture(texture);

  // De-allocate resources
  CloseWindow();
  return 0;
}
