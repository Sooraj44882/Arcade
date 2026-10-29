#include "raylib.h"

typedef enum GameScreen { START, PLAY, GAMEOVER } GameScreen;

int main(void)
{
    InitWindow(800, 600, "Arcade");

    GameScreen currentScreen = START;

    Rectangle paddle = {350, 550, 100, 20};
    int paddleSpeed = 8;

    Vector2 ballPos = {400, 300};
    Vector2 ballSpeed = {5.0f, -5.0f};
    float ballRadius = 10.0f;

    Rectangle bricks[5][10];
    int active[5][10];

    int startX = 40; 
    int startY = 50;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (currentScreen) {
            case START:
            {
                if (IsKeyPressed(KEY_ENTER)) 
                {
                    ballPos = (Vector2){400, 300};
                    ballSpeed = (Vector2){5.0f, -5.0f};
                    paddle.x = 350;

                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 10; j++) {
                            bricks[i][j].x = startX + j * 70;
                            bricks[i][j].y = startY + i * 35;
                            bricks[i][j].width = 60;
                            bricks[i][j].height = 20;
                            active[i][j] = 1;
                        }
                    }
                    currentScreen = PLAY;
                }
            } break;

            case PLAY:
            {
                if (IsKeyDown(KEY_LEFT)) paddle.x -= paddleSpeed;
                
                if (IsKeyDown(KEY_RIGHT)) paddle.x += paddleSpeed;

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
                if (ballPos.y - ballRadius <= 0 ) ballSpeed.y *= -1;
                if (ballPos.y + ballRadius >= 600) {
                    currentScreen = GAMEOVER; 
                }

                if (CheckCollisionCircleRec(ballPos, ballRadius, paddle)) {
                    ballSpeed.y *= -1;
                    ballPos.y = paddle.y - ballRadius;
                }

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (active[i][j] == 1) {
                            if (CheckCollisionCircleRec(ballPos, ballRadius, bricks[i][j])) {
                                active[i][j] = 0;
                                ballSpeed.y *= -1;
                            }
                        }
                    }
                }
            } break;

            case GAMEOVER:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    currentScreen = START;
                }
                if (IsKeyPressed(KEY_R)) {
                    ballPos = (Vector2){400, 300};
                    ballSpeed = (Vector2){5.0f, -5.0f};
                    paddle.x = 350;

                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 10; j++) {
                            active[i][j] = 1;
                        }
                    }

                    currentScreen = PLAY;
                }
            } break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) 
        {
            case START:
            {
                DrawText("Brick Break", 250, 200, 50, BLACK);
                DrawText("PRESS ENTER TO START", 250, 300, 20, DARKGRAY);
            } break;

            case PLAY:
            {
                DrawRectangleRec(paddle, BLACK);
                DrawCircleV(ballPos, ballRadius, RED);

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (active[i][j] == 1) {
                            DrawRectangleRec(bricks[i][j], DARKGRAY);
                        }
                    }
                }
            } break;

            case GAMEOVER:
            {
                DrawText("GAME OVER", 250, 200, 50, RED);
                DrawText("PRESS R TO Retry", 180, 300, 50, BLACK);
                DrawText("PRESS ENTER TO RETURN TO Menu", 220, 400, 20, DARKGRAY);
            } break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}