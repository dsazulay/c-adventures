#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

GameMemory *gMem;

void gameInit()
{
    gMem = malloc(sizeof(GameMemory));
    gMem->x = 100;
    gMem->y = 200;
}

void gameInitWindow()
{
//    rl.InitWindow(400, 400, "Processing")
//    rl.SetTargetFPS(60)
}

bool gameUpdate()
{

    printf("diego\n");
                      /*
    rl.BeginDrawing()
    defer rl.EndDrawing()

    if rl.IsMouseButtonPressed(rl.MouseButton.LEFT) {
            g_mem.base_color = rl.Color {
                    u8(rand.int_max(256)),
                    u8(rand.int_max(256)),
                    u8(rand.int_max(256)),
                    255,
            }
            g_mem.accent_color = rl.Color {
                    u8(rand.int_max(256)),
                    u8(rand.int_max(256)),
                    u8(rand.int_max(256)),
                    255,
            }
    }

    rl.ClearBackground(rl.DARKGRAY)

    if rl.IsKeyDown(rl.KeyboardKey.A) {
            g_mem.x -= 1
    } else if rl.IsKeyDown(rl.KeyboardKey.D) {
            g_mem.x += 1
    }

    if rl.IsKeyDown(rl.KeyboardKey.W) {
            g_mem.y -= 1
    } else if rl.IsKeyDown(rl.KeyboardKey.S) {
            g_mem.y += 1
    }

    g_mem.origin_x = 0
    g_mem.origin_y = 0
    g_mem.origin_angle = 0

    draw_frac_tree()
    //draw_ship(g_mem.x, g_mem.y)

    return rl.WindowShouldClose() */
    return false;
}

void gameShutdown()
{
    free(gMem);
}

void gameShutdownWindow()
{
    //rl.CloseWindow()
}

void *gameMemory()
{
    return gMem;
}

void gameHotReloaded(GameMemory *mem)
{
    gMem = mem;
}
