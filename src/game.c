#include "game.h"

#include "base/base_io.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

GameMemory *gMem;

void gameInit()
{
    gMem = malloc(sizeof(GameMemory));
    gMem->x = 100;
    gMem->y = 200;
}

void gameInitWindow()
{
    InitWindow(800, 450, "Window");
    SetTargetFPS(60);
}

bool gameUpdate()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!",
             190, 200, 20, LIGHTGRAY);
    EndDrawing();

    return WindowShouldClose();
}

void gameShutdown()
{
    free(gMem);
}

void gameShutdownWindow()
{
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
