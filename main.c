#include "raylib.h"

#include "brick.c"
#include "snake.c"

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

        DrawText("ARCADE Menu", 200, 150, 40, DARKBLUE);
        DrawText("Press 1 to play BREAKOUT", 250, 280, 20, DARKGRAY);
        DrawText("Press 2 to play SNAKE", 250, 330, 20, DARKGRAY);
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
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}