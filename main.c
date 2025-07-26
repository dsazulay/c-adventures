#include "base_core.h"
#include "base_string.h"
#include "base_arena.h"
#include "base_dynarray.h"
#include "base_map.h"

#include <stdio.h>
#include <raylib.h>

void printMapElement(KVStrI32 *e)
{
    printf("%s: %d\n", e->key.data, e->value);
}

i32 main(i32 argc, char **argv)
{
    Arena arena = {0};

    arenaReserve(&arena, 128);
    printf("%lld\n", arena.used);
    printf("%lld\n", arena.reserved);

    i32 *a = arenaPush(&arena, sizeof(i32));
    *a = 10;
    printf("%d\n", *a);
    printf("%lld\n", arena.used);

    f64 *b = arenaPush(&arena, sizeof(f64));
    printf("%f\n", *b);
    *b = 23.4f;
    printf("%f\n", *b);
    printf("%lld\n", arena.used);

    arenaPop(&arena, 8);
    printf("%lld\n", arena.used);

    arenaRelease(&arena);

    /*
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
    */
}

