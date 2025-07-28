#include "base_core.h"
#include "base_string.h"
#include "base_arena.h"
#include "base_dynarray.h"
#include "base_map.h"

#include <raylib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/stat.h>

void printMapElement(KVStrI32 *e)
{
    printf("%s: %d\n", e->key.data, e->value);
}
/*
i32 main(i32 argc, char **argv)
{

    ArrayF32 array = {0};
    dynArrayReserve(&array, 2);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);

    dynArrayPush(&array, 23.f);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);


    dynArrayPush(&array, 25.f);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);

    dynArrayPush(&array, 27.f);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);

    for (i64 i = 0; i < array.count; ++i)
    {
        printf("%f ", array.data[i]);
    }
    printf("\n");

    f32 test = dynArrayPop(&array);
    printf("%.2f\n", test);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);

    for (i64 i = 0; i < array.count; ++i)
    {
        printf("%f ", array.data[i]);
    }
    printf("\n");

    dynArrayRelease(&array);
    printf("%lld\n", array.count);
    printf("%lld\n", array.capacity);

    MapStrI32 map = {0};
    mapReserve(&map, 2);
    printf("%lld\n", map.count);
    printf("%lld\n", map.maxSize);
    printf("%lld\n", map.capacity);

    mapInsert(&map, S("Diego"), 10);
    mapIterate(&map, printMapElement);
    printf("\n");
    mapInsert(&map, S("Azul"), 20);
    mapIterate(&map, printMapElement);
    printf("%lld %lld %lld", map.count, map.maxSize, map.capacity);
    printf("\n");
    mapInsert(&map, S("Bzul"), 20);
    mapIterate(&map, printMapElement);
    printf("\n");
    mapInsert(&map, S("Taiane"), 8);
    mapIterate(&map, printMapElement);
    printf("\n");
    printf("Another test\n\n");
    KVStrI32 *ptr = mapFind(&map, S("Diego"));
    if (ptr != NULL)
    {
        printf("found %s: %d\n", ptr->key.data, ptr->value);
        ptr->value = 100;
    }

    for (i64 i = 0; i < map.capacity; ++i)
    {
    }

    ptr = mapErase(&map, S("Azul"));
    if (ptr == NULL)
    {
        printf("Last element\n");
    }
    else
    {
        printf("Next element: %s - %d\n", ptr->key.data, ptr->value);
    }

    mapIterate(&map, printMapElement);

    ptr = mapErase(&map, S("Diego"));
    if (ptr == NULL)
    {
        printf("Last element\n");
    }
    else
    {
        printf("Next element: %s - %d\n", ptr->key.data, ptr->value);
    }

    ptr = mapFind(&map, S("Test"));
    if (ptr == NULL)
    {
        printf("not found %s\n", "Test");
    }

    mapIterate(&map, printMapElement);

    mapRelease(&map);
    printf("%lld\n", map.count);
    printf("%lld\n", map.maxSize);
    printf("%lld\n", map.capacity);

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); 


}
*/
typedef struct {
    void(*init)();
    void(*initWindow)();
    bool(*update)();
    void (*shutdown)();
    void (*shutdownWindow)();
    void *(*memory)();
    void (*hotReloaded)(void *);
    void *lib;
    i64 dllTime;
    i32 apiVersion;
} GameAPI;

GameAPI loadGameAPI(i32 apiVersion)
{
    struct stat st = {0};
    i32 dllTimeError = lstat("game.dll", &st);
    if (dllTimeError == -1)
    {
        printf("Could not fetch last write date of game.dll\n");
        return (GameAPI) {0};
    }
    i64 dllTime = st.st_mtimespec.tv_sec;

    char dllName[20];
    snprintf(dllName, 20, "game_%d.dll", apiVersion);
    printf("%s\n", dllName);

    char copyCmd[30];
    snprintf(copyCmd, 30, "cp game.dll %s", dllName);

    if (system(copyCmd) != 0)
    {
        printf("Failed to copy game.dll to %s\n", dllName);
        return (GameAPI) {0};
    }

    void *lib = dlopen(dllName, RTLD_NOW);
    if (!lib)
    {
        printf("Falied loading game DLL\n");
        return (GameAPI) {0};
    }

    GameAPI api = {0};
    api.init = dlsym(lib, "gameInit");
    api.initWindow = dlsym(lib, "gameInitWindow");
    api.update = dlsym(lib, "gameUpdate");
    api.shutdown = dlsym(lib, "gameShutdown");
    api.shutdownWindow = dlsym(lib, "gameShutdownWindow");
    api.memory = dlsym(lib, "gameMemory");
    api.hotReloaded = dlsym(lib, "gameHotReloaded");
    api.lib = lib;
    api.dllTime = dllTime;
    api.apiVersion = apiVersion;

    if (api.init == NULL ||
       api.update == NULL ||
       api.shutdown == NULL ||
       api.memory == NULL ||
       api.hotReloaded == NULL)
    {
            dlclose(api.lib);
            printf("Game DLL missing required procedure\n");
            return (GameAPI) {0};
    }

    return api;
}

void unloadGameAPI(GameAPI api)
{
    if (api.lib != NULL)
    {
        dlclose(api.lib);
    }

    char delCmd[20];
    snprintf(delCmd, 20, "rm game_%d.dll", api.apiVersion);
    if (system(delCmd) != 0)
    {
        printf("Failed to remove game_%d.dll copy", api.apiVersion);
    }
}

i32 main(i32 argc, char **argv)
{
    i32 gameAPIVersion = 0;

    GameAPI gameAPI = loadGameAPI(gameAPIVersion);
    if (gameAPI.lib == NULL)
    {
        printf("Failed to load Game API\n");
        return -1;
    }

    gameAPIVersion += 1;

    gameAPI.init();
    gameAPI.initWindow();

    while (true)
    {
        if (gameAPI.update())
        {
            printf("Window should close\n");
            break;
        }
        struct stat st = {0};
        i32 dllTimeError = lstat("game.dll", &st);

        i64 dllTime = st.st_mtimespec.tv_sec;
        bool reload = gameAPI.dllTime != dllTime && dllTimeError != -1;

        if (reload)
        {
            GameAPI newAPI = loadGameAPI(gameAPIVersion);
            if (newAPI.lib != NULL)
            {
                void *gameMemory = gameAPI.memory();
                unloadGameAPI(gameAPI);
                gameAPI = newAPI;
                gameAPI.hotReloaded(gameMemory);
                gameAPIVersion += 1;
            }
        }
    }

    gameAPI.shutdownWindow();
    gameAPI.shutdown();
    unloadGameAPI(gameAPI);
}

