#include "raylib.h"
typedef enum FlappyScreen
{
    F_START,
    F_PLAY,
    F_GAMEOVER
} FlappyScreen;

void PlayFlappy(void)
{
    Sound flapSound = LoadSound("bounce.wav");
    Sound crashSound = LoadSound("crash.wav");

    FlappyScreen currentScreen = F_START;

    Vector2 birdPos = {200, 300};
    float birdVelocity = 0.0f;
    float gravity = 0.6f;
    float jumpStrength = -8.5f;
    float birdRadius = 15.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        switch (currentScreen)
        {
        case F_START:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                birdPos = (Vector2){200, 300};
                birdVelocity = 0.0f;
                currentScreen = F_PLAY;
            }
        }
        break;

        case F_PLAY:
        {
            birdVelocity += gravity;
            birdPos.y += birdVelocity;

            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
            {
                birdVelocity = jumpStrength;
                PlaySound(flapSound);
            }

            if (birdPos.y + birdRadius >= 600 || birdPos.y - birdRadius <= 0)
            {
                PlaySound(crashSound);
                currentScreen = F_GAMEOVER;
            }
        }
        break;

        case F_GAMEOVER:
        {
            if (IsKeyPressed(KEY_ENTER))
                currentScreen = F_START;
            if (IsKeyPressed(KEY_R))
            {
                birdPos = (Vector2){200, 300};
                birdVelocity = 0.0f;
                currentScreen = F_PLAY;
            }
        }
        break;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        switch (currentScreen)
        {
        case F_START:
        {
            DrawText("FLAPPY BIRD", 230, 200, 50, BLACK);
            DrawText("PRESS ENTER TO START", 250, 300, 20, DARKGRAY);
        }
        break;

        case F_PLAY:
        {
            DrawCircleV(birdPos, birdRadius, YELLOW);
        }
        break;

        case F_GAMEOVER:
        {
            DrawText("GAME OVER", 250, 200, 50, RED);
            DrawText("PRESS R TO RETRY", 300, 320, 20, DARKGRAY);
            DrawText("PRESS ESC TO RETURN TO MENU", 220, 360, 20, DARKGRAY);
        }
        break;
        }
        EndDrawing();
    }

    UnloadSound(flapSound);
    UnloadSound(crashSound);
}