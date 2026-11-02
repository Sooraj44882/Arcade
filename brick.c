#include "raylib.h"

typedef enum BreakoutScreen { B_START, B_PLAY, B_GAMEOVER, B_WIN } BrickScreen;

void PlayBrick(void)
{
    Sound bounceSound = LoadSound("bounce.wav");

    BrickScreen currentScreen = B_START;

    Rectangle paddle = {350, 550, 100, 20};
    int paddleSpeed = 8;

    Vector2 ballPos = {400, 300};
    Vector2 ballSpeed = {5.0f, -5.0f};
    float ballRadius = 10.0f;

    Rectangle bricks[5][10];
    int active[5][10];

    int score = 0;
    int totalBricks = 50; 
    
    Color rowColors[5] = { RED, ORANGE, YELLOW, GREEN, BLUE };

    int startX = 40; 
    int startY = 50;

    SetTargetFPS(60);

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        switch (currentScreen) {
            case B_START:
            {
                if (IsKeyPressed(KEY_ENTER)) 
                {
                    ballPos = (Vector2){400, 300};
                    ballSpeed = (Vector2){5.0f, -5.0f};
                    paddle.x = 350;
                    score = 0;
                    totalBricks = 50; 

                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 10; j++) {
                            bricks[i][j].x = startX + j * 70;
                            bricks[i][j].y = startY + i * 35;
                            bricks[i][j].width = 60;
                            bricks[i][j].height = 20;
                            active[i][j] = 1;
                        }
                    }
                    currentScreen = B_PLAY;
                }
            } break;

            case B_PLAY:
            {
                if (IsKeyDown(KEY_LEFT)) paddle.x -= paddleSpeed;
                if (IsKeyDown(KEY_RIGHT)) paddle.x += paddleSpeed;

                if (paddle.x <= 0) paddle.x = 0;
                if (paddle.x + paddle.width >= 800) paddle.x = 800 - paddle.width;
                
                ballPos.x += ballSpeed.x;
                ballPos.y += ballSpeed.y;

                if (ballPos.x - ballRadius <= 0 || ballPos.x + ballRadius >= 800) {
                    ballSpeed.x *= -1;
                    PlaySound(bounceSound); 
                }
                if (ballPos.y - ballRadius <= 0 ) {
                    ballSpeed.y *= -1;
                    PlaySound(bounceSound);
                }
                
                if (ballPos.y + ballRadius >= 600) {
                    currentScreen = B_GAMEOVER; 
                }

                if (CheckCollisionCircleRec(ballPos, ballRadius, paddle)) {
                    ballSpeed.y *= -1;
                    ballPos.y = paddle.y - ballRadius;
                    PlaySound(bounceSound);
                }

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (active[i][j] == 1) {
                            if (CheckCollisionCircleRec(ballPos, ballRadius, bricks[i][j])) {
                                active[i][j] = 0;
                                ballSpeed.y *= -1;
                                score += 100;
                                
                                totalBricks--;
                                
                                PlaySound(bounceSound);

                                if (totalBricks <= 0) {
                                    currentScreen = B_WIN;
                                }
                            }
                        }
                    }
                }
            } break;

            case B_GAMEOVER:
            case B_WIN:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    currentScreen = B_START;
                }
                if (IsKeyPressed(KEY_R)) {
                    ballPos = (Vector2){400, 300};
                    ballSpeed = (Vector2){5.0f, -5.0f};
                    paddle.x = 350;
                    score = 0; 
                    totalBricks = 50; 

                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 10; j++) {
                            active[i][j] = 1;
                        }
                    }

                    currentScreen = B_PLAY;
                }
            } break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) 
        {
            case B_START:
            {
                DrawText("Brick Break", 220, 200, 50, BLACK);
                DrawText("PRESS ENTER TO START", 250, 300, 20, DARKGRAY);
            } break;

            case B_PLAY:
            {
                DrawRectangleRec(paddle, BLACK);
                DrawCircleV(ballPos, ballRadius, RED);

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (active[i][j] == 1) {
                            DrawRectangleRec(bricks[i][j], rowColors[i]);
                        }
                    }
                }
                
                DrawText(TextFormat("SCORE: %i", score), 20, 20, 20, BLACK);
            } break;

            case B_GAMEOVER:
            {
                DrawText("GAME OVER", 250, 200, 50, RED);
                DrawText(TextFormat("FINAL SCORE: %i", score), 260, 260, 30, BLACK);
                DrawText("PRESS R TO Retry", 290, 320, 20, DARKGRAY);
                DrawText("PRESS ENTER TO RETURN TO Menu", 220, 360, 20, DARKGRAY);
            } break;
            
            case B_WIN:
            {
                DrawText("YOU WIN", 280, 200, 50, GREEN);
                DrawText(TextFormat("FINAL SCORE: %i", score), 260, 260, 30, BLACK);
                DrawText("PRESS R TO PLAY AGAIN", 270, 320, 20, DARKGRAY);
                DrawText("PRESS ENTER TO RETURN TO Menu", 220, 360, 20, DARKGRAY);
            } break;
        }

        EndDrawing();
    }

    UnloadSound(bounceSound); 
}