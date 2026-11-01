#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Snake Game");

    int cellSize = 20;
    
    int snakeX = 400;
    int snakeY = 300;

    int speedX = cellSize;
    int speedY = 0;

    int foodX = 200;
    int foodY = 200;

    SetTargetFPS(10); 

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_UP)) {
            speedX = 0;
            speedY = -cellSize;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            speedX = 0;
            speedY = cellSize; 
        }
        if (IsKeyPressed(KEY_LEFT)) {
            speedX = -cellSize; 
            speedY = 0;
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            speedX = cellSize;
            speedY = 0;
        }

        snakeX += speedX;
        snakeY += speedY;

        if (snakeX == foodX && snakeY == foodY)
        {
            foodX = GetRandomValue(0, (800 / cellSize) - 1) * cellSize;
            foodY = GetRandomValue(0, (600 / cellSize) - 1) * cellSize;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(foodX, foodY, cellSize, cellSize, RED);

        DrawRectangle(snakeX, snakeY, cellSize, cellSize, DARKGREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}