#include "raylib.h"

#include "brick.c"
#include "snake.c"
#include "flappy.c"

int main(void)
{
    InitWindow(800, 600, "Arcade");
    InitAudioDevice(); 
    
    SetExitKey(0); 
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("ARCADE Menu", 200, 100, 40, DARKBLUE);
        DrawText("Press 1 to play BREAKOUT", 250, 240, 20, DARKGRAY);
        DrawText("Press 2 to play SNAKE", 250, 290, 20, DARKGRAY);
        DrawText("Press 3 to play FLAPPY BIRD", 250, 340, 20, DARKGRAY);
        DrawText("Close the window to quit", 250, 450, 20, LIGHTGRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE))
        {
            PlayBrick();
            SetTargetFPS(60); 
        }
        if (IsKeyPressed(KEY_TWO))
        {
            PlaySnake();    
            SetTargetFPS(60);
        }
        if (IsKeyPressed(KEY_THREE))
        {
            PlayFlappy();    
            SetTargetFPS(60);
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}