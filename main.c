#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Snake Game");

    int cellSize = 20;

    int snakeX[100] = {400};
    int snakeY[100] = {300};
    int snakeLength = 1;

    int speedX = cellSize;
    int speedY = 0;

    int foodX = 200;
    int foodY = 200;

    SetTargetFPS(10);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_UP) && speedY == 0){
            speedX = 0;
            speedY = -cellSize;
        }
        if (IsKeyPressed(KEY_DOWN) && speedY == 0){
            speedX = 0;
            speedY = cellSize;
        }
        if (IsKeyPressed(KEY_LEFT) && speedX == 0){
            speedX = -cellSize;
            speedY = 0;
        }
        if (IsKeyPressed(KEY_RIGHT) && speedX == 0){
            speedX = cellSize;
            speedY = 0;
        }

        for (int i = snakeLength - 1; i > 0; i--){
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        snakeX[0] += speedX;
        snakeY[0] += speedY;

        if (snakeX[0] < 0 || snakeX[0] >= 800 || snakeY[0] < 0 || snakeY[0] >= 600){
            snakeLength = 1;
            snakeX[0] = 400;
            snakeY[0] = 300;
            speedX = cellSize;
            speedY = 0;
        }

        if (snakeX[0] == foodX && snakeY[0] == foodY){
            snakeLength++;
            foodX = GetRandomValue(0, (800 / cellSize) - 1) * cellSize;
            foodY = GetRandomValue(0, (600 / cellSize) - 1) * cellSize;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(foodX, foodY, cellSize, cellSize, RED);

        for (int i = 0; i < snakeLength; i++){
            DrawRectangle(snakeX[i], snakeY[i], cellSize, cellSize, DARKGREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}