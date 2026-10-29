#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Arcade");
    SetTargetFPS(60); 

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
            
            ClearBackground(RAYWHITE); 
            
            DrawText("hello", 10, 10, 20, DARKGRAY);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}