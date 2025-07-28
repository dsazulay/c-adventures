#ifndef BASE_ARENA_H
#define BASE_ARENA_H

#include "base_core.h"
#include "base_string.h"

typedef struct {
    void *base;
    u64 used;
    u64 reserved;
} Arena;

void *_arenaPush(Arena *arena, u64 size);
void arenaReserve(Arena *arena, u64 size);
void arenaPop(Arena *arena, u64 size);
void arenaClear(Arena *arena);
void arenaRelease(Arena *arena);

#define arenaPush(arena, size)             _arenaPush(arena, size)
#define arenaPushStruct(arena, type)       (type *)_arenaPush(arena, sizeof(type))
#define arenaPushArray(arena, type, count) (type *)_arenaPush(arena, count * sizeof(type))

#endif
