#include "base/base_tester.h"
#include "base/base_arena.h"

void testArena()
{
    Arena arena = {0};

    arenaReserve(&arena, 128);
    Check(arena.reserved == 128);

    i32 *a = arenaPush(&arena, sizeof(i32));
    Check(arena.used == 4);

    f64 *b = arenaPush(&arena, sizeof(f64));
    Check(arena.used == 12);

    arenaPop(&arena, 8);
    Check(arena.used == 4);

    arenaRelease(&arena);
    Check(arena.used == 0);
    Check(arena.reserved == 1);
}

TestRun("Arena", 1, TestCase(testArena));
