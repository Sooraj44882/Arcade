#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Arcade");

    Rectangle paddle = {350, 550, 100, 20};
    int paddleSpeed = 8;

    Vector2 ballPos = {400, 300};
    Vector2 ballSpeed = {5.0f, -5.0f};
    float ballRadius = 10.0f;

    Rectangle bricks[5][10];
    int active[5][10];

    int startX = 40; 
    int startY = 50;

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 10; j++) {
            bricks[i][j].x = startX + j * 70;
            bricks[i][j].y = startY + i * 35;
            bricks[i][j].width = 60;
            bricks[i][j].height = 20;
            active[i][j] = 1;
        }
    }

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

        if (ballPos.y - ballRadius <= 0 ){
            ballSpeed.y *= -1;
        }
        if (ballPos.y + ballRadius >= 600){
            ballSpeed.y=0;
        }

        if (CheckCollisionCircleRec(ballPos, ballRadius, paddle)){
            ballSpeed.y *= -1;
            ballPos.y = paddle.y - ballRadius;
        }

        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 10; j++){
                if (active[i][j] == 1){
                    if (CheckCollisionCircleRec(ballPos, ballRadius, bricks[i][j])) {
                        active[i][j] = 0;
                        ballSpeed.y *= -1;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangleRec(paddle, BLACK);
        DrawCircleV(ballPos, ballRadius, RED);

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (active[i][j] == 1) {
                    DrawRectangleRec(bricks[i][j], DARKGRAY);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}