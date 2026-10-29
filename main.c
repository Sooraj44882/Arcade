#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Arcade");

    Rectangle paddle = {350, 550, 100, 20};
    int paddleSpeed = 8;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_LEFT))
            paddle.x -= paddleSpeed;
        if (IsKeyDown(KEY_RIGHT))
            paddle.x += paddleSpeed;

        if (paddle.x <= 0)
            paddle.x = 0;
        if (paddle.x + paddle.width >= 800)
            paddle.x = 800 - paddle.width;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangleRec(paddle, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}