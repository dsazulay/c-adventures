#include "base_arena.h"
#include <stdlib.h>

void *_arenaPush(Arena *arena, u64 size)
{
    void *ptr = arena->base + arena->used;
    arena->used += size;
    return ptr;
}

void arenaReserve(Arena *arena, u64 size)
{
    arena->base = malloc(size);
    arena->reserved = size;
}

void arenaPop(Arena *arena, u64 size)
{
    arena->used -= size;
}

void arenaClear(Arena *arena)
{
    arena->used = 0;
}

void arenaRelease(Arena *arena)
{
    free(arena->base);
    arena->base = NULL;
    arena->used = 0;
    arena->reserved = 0;
}
