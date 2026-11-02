#include "raylib.h"

typedef enum SnakeScreen { S_START, S_PLAY, S_GAMEOVER } SnakeScreen;

void PlaySnake(void)
{
    Sound eatSound = LoadSound("eat.wav");
    Sound crashSound = LoadSound("crash.wav");

    SnakeScreen currentScreen = S_START;

    int cellSize = 20;

    int snakeX[100];
    int snakeY[100];
    int snakeLength = 1;

    int speedX = cellSize;
    int speedY = 0;

    int foodX = 200;
    int foodY = 200;

    int score = 0;

    SetTargetFPS(10);

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        switch (currentScreen)
        {
        case S_START:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                snakeLength = 1;
                snakeX[0] = 400;
                snakeY[0] = 300;
                speedX = cellSize;
                speedY = 0;
                score = 0;

                foodX = GetRandomValue(0, (800 / cellSize) - 1) * cellSize;
                foodY = GetRandomValue(0, (600 / cellSize) - 1) * cellSize;

                currentScreen = S_PLAY;
            }
        }
        break;

        case S_PLAY:
        {
            if (IsKeyPressed(KEY_UP) && speedY == 0)
            {
                speedX = 0;
                speedY = -cellSize;
            }
            if (IsKeyPressed(KEY_DOWN) && speedY == 0)
            {
                speedX = 0;
                speedY = cellSize;
            }
            if (IsKeyPressed(KEY_LEFT) && speedX == 0)
            {
                speedX = -cellSize;
                speedY = 0;
            }
            if (IsKeyPressed(KEY_RIGHT) && speedX == 0)
            {
                speedX = cellSize;
                speedY = 0;
            }

            for (int i = snakeLength - 1; i > 0; i--)
            {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }

            snakeX[0] += speedX;
            snakeY[0] += speedY;

            if (snakeX[0] < 0 || snakeX[0] >= 800 || snakeY[0] < 0 || snakeY[0] >= 600)
            {
                PlaySound(crashSound);
                currentScreen = S_GAMEOVER;
            }

            for (int i = 1; i < snakeLength; i++)
            {
                if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
                {
                    PlaySound(crashSound);
                    currentScreen = S_GAMEOVER;
                }
            }

            if (snakeX[0] == foodX && snakeY[0] == foodY)
            {
                PlaySound(eatSound);
                snakeLength++;
                score += 10;

                foodX = GetRandomValue(0, (800 / cellSize) - 1) * cellSize;
                foodY = GetRandomValue(0, (600 / cellSize) - 1) * cellSize;
            }
        }
        break;

        case S_GAMEOVER:
        {
            if (IsKeyPressed(KEY_ENTER))
                currentScreen = S_START;
            if (IsKeyPressed(KEY_R))
            {
                snakeLength = 1;
                snakeX[0] = 400;
                snakeY[0] = 300;
                speedX = cellSize;
                speedY = 0;
                score = 0;
                currentScreen = S_PLAY;
            }
        }
        break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case S_START:
        {
            DrawText("SNAKE", 320, 200, 50, DARKGREEN);
            DrawText("PRESS ENTER TO START", 250, 300, 20, DARKGRAY);
        }
        break;

        case S_PLAY:
        {
            DrawRectangle(foodX, foodY, cellSize, cellSize, RED);

            for (int i = 0; i < snakeLength; i++)
            {
                DrawRectangle(snakeX[i], snakeY[i], cellSize, cellSize, DARKGREEN);
            }

            DrawText(TextFormat("SCORE: %i", score), 10, 10, 20, BLACK);
        }
        break;

        case S_GAMEOVER:
        {
            DrawText("GAME OVER!", 250, 200, 50, RED);
            DrawText(TextFormat("FINAL SCORE: %i", score), 280, 260, 30, BLACK);
            DrawText("PRESS R TO RETRY", 300, 320, 20, DARKGRAY);
        }
        break;
        }

        EndDrawing();
    }

    UnloadSound(eatSound);
    UnloadSound(crashSound);
}