#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Arcade");

    Rectangle paddle = {350, 550, 100, 20};
    int paddleSpeed = 8;

    Vector2 ballPos = {400, 300};
    Vector2 ballSpeed = {5.0f, -5.0f};
    float ballRadius = 10.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_LEFT))
            paddle.x -= paddleSpeed;
        if (IsKeyDown(KEY_RIGHT))
            paddle.x += paddleSpeed;

        if (paddle.x <= 0){
            paddle.x = 0;
        }
        if (paddle.x + paddle.width >= 800){
            paddle.x = 800 - paddle.width;
        }

        ballPos.x += ballSpeed.x;
        ballPos.y += ballSpeed.y;

        if (ballPos.x - ballRadius <= 0 || ballPos.x + ballRadius >= 800){
            ballSpeed.x *= -1;
        }

        if (ballPos.y - ballRadius <= 0 || ballPos.y + ballRadius >= 600){
            ballSpeed.y *= -1;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangleRec(paddle, BLACK);

        DrawCircleV(ballPos, ballRadius, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}