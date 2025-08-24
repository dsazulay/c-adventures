#include "game.h"

#include "base/base_io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>

GameMemory *gMem;

void gameInit()
{
    gMem = malloc(sizeof(GameMemory));
    gMem->player.x = 400;
    gMem->player.y = 225;
    gMem->frame = 0;
}

void loadResources()
{
    gMem->player.sprite = LoadTexture("../resources/main_ship_full.png");

    gMem->background[0] = LoadTexture("../resources/background_01.png");
    gMem->background[1] = LoadTexture("../resources/background_02.png");
    gMem->background[2] = LoadTexture("../resources/background_03.png");
}

void processInput()
{
    if (IsKeyPressed(KEY_UP))
    {
        gMem->player.velocity += 1;
        gMem->player.velocity = gMem->player.velocity > 3 ?
            3 : gMem->player.velocity;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        gMem->player.velocity -= 1;
        gMem->player.velocity = gMem->player.velocity > 0 ?
            gMem->player.velocity : 0;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        gMem->player.angle -= 1.0f;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        gMem->player.angle += 1.0f;
    }

}

void gameInitWindow()
{
    InitWindow(800, 450, "Window");
    SetTargetFPS(60);

    loadResources();
}

void drawBackground()
{
    i32 bgCount = arrayCount(gMem->background);
    i32 animIndex = (gMem->frame / 8) % 9;
    for (i32 i = 0; i < 1; ++i)
    {
        Texture2D bg = gMem->background[i];
        Rectangle uv = { (bg.width / 9.0f) * animIndex, 0.0f,
            bg.width / 9.0f, bg.height };
        Rectangle position = { 400.0f, 225.0f, 800.0f, 450.0f };
        Vector2 origin = { 400.0f, 225.0f };

        DrawTexturePro(bg, uv, position, origin, 0.0f, WHITE);
    }
}

bool gameUpdate()
{
    gMem->frame += 1;

    processInput();

    f32 angle = gMem->player.angle * DEG2RAD;
    gMem->player.x += gMem->player.velocity * 0.3 * sin(angle);
    gMem->player.y -= gMem->player.velocity * 0.3 * cos(angle);

    BeginDrawing();
    ClearBackground(BLACK);

    drawBackground();

    Rectangle uv = { 0.0f, 0.0f, gMem->player.sprite.width,
        gMem->player.sprite.height };
    Rectangle position = { gMem->player.x, gMem->player.y,
        gMem->player.sprite.width, gMem->player.sprite.height };
    Vector2 origin = { gMem->player.sprite.width / 2.0f,
        gMem->player.sprite.height / 2.0f };

    DrawTexturePro(gMem->player.sprite, uv, position, origin,
                   gMem->player.angle, WHITE);

    EndDrawing();

    return WindowShouldClose();
}

void gameShutdown()
{
    free(gMem);
}

void unloadResources()
{
    UnloadTexture(gMem->player.sprite);
    i32 bgCount = arrayCount(gMem->background);
    for (i32 i = 0; i < bgCount; ++i)
    {
        UnloadTexture(gMem->background[i]);
    }
}

void gameShutdownWindow()
{
    unloadResources();

    CloseWindow();
}

void *gameMemory()
{
    return gMem;
}

void gameHotReloaded(GameMemory *mem)
{
    gMem = mem;
}
