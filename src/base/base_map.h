#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "base_core.h"
#include "base_string.h"
#include <stdlib.h>

#define THRESHOLD_CAPACITY 0.75

#define _MapHeader_ struct { u64 count; u64 maxSize; u64 capacity; }

u64 _mapHashStr(String key);

#define mapHash(key) _mapHashStr(key);

#ifdef MAP_IMPLEMENTATION
#define _defineMap(TName, K, V)                                         \
    typedef struct {                                                    \
        K key;                                                          \
        V value;                                                        \
    } KV##TName;                                                        \
                                                                        \
    typedef struct {                                                    \
        KV##TName *content;                                             \
        i64 *psl;                                                       \
        _MapHeader_;                                                    \
    } Map##TName;                                                       \
                                                                        \
    void _mapResize_Map##TName(Map##TName *map);                        \
    void _mapReserve_Map##TName(Map##TName *map, u64 cap);              \
    void _mapRelease_Map##TName(Map##TName *map);                       \
    void _mapInsert_Map##TName(Map##TName *map, K k, V v);              \
    i64 _mapFindIndex_Map##TName(Map##TName *map, K k);                 \
    KV##TName *_mapFind_Map##TName(Map##TName *map, K k);               \
    KV##TName *_mapErase_Map##TName(Map##TName *map, K k);              \
    void _mapIterate_Map##TName(                                        \
        Map##TName *map,                                                \
        void(*f)(KV##TName *element)                                    \
    );                                                                  \
                                                                        \
    void _mapResize_Map##TName(Map##TName *map)                         \
    {                                                                   \
        u64 oldCapacity = map->capacity;                                \
        KV##TName *oldContent = map->content;                           \
        i64 *oldPsl = map->psl;                                         \
        map->capacity *= 2;                                             \
        map->maxSize = (u64)(map->capacity * THRESHOLD_CAPACITY);       \
        map->count = 0;                                                 \
        map->content = (KV##TName *) malloc(                            \
            map->capacity * sizeof(*map->content)                       \
        );                                                              \
        map->psl = (i64 *) malloc(map->capacity * sizeof(i64));         \
                                                                        \
        for (i64 i = 0 ; i < map->capacity; ++i) { map->psl[i] = -1; }  \
                                                                        \
        for (i64 i = 0; i < oldCapacity; ++i)                           \
        {                                                               \
            if (oldPsl[i] != -1)                                        \
            {                                                           \
                _mapInsert_Map##TName(map,                              \
                                      oldContent[i].key,                \
                                      oldContent[i].value               \
                );                                                      \
            }                                                           \
        }                                                               \
                                                                        \
        free(oldContent);                                               \
        free(oldPsl);                                                   \
    }                                                                   \
                                                                        \
    void _mapReserve_Map##TName(Map##TName *map, u64 cap)               \
    {                                                                   \
        map->content = (KV##TName *) malloc(                            \
            sizeof(*map->content) * cap                                 \
        );                                                              \
        map->psl = (i64 *) malloc(sizeof(i64) * cap);                   \
        map->capacity = cap;                                            \
        map->maxSize = (u64)(cap * THRESHOLD_CAPACITY);                 \
        map->count = 0;                                                 \
        for (i64 i = 0; i < cap; ++i) { map->psl[i] = -1; }             \
    }                                                                   \
                                                                        \
    void _mapRelease_Map##TName(Map##TName *map)                        \
    {                                                                   \
        free(map->content);                                             \
        free(map->psl);                                                 \
        map->capacity = 0;                                              \
        map->maxSize = 0;                                               \
        map->count = 0;                                                 \
    }                                                                   \
                                                                        \
    void _mapInsert_Map##TName(Map##TName *map, K k, V v)               \
    {                                                                   \
        if (map->count + 1 > map->maxSize)                              \
        {                                                               \
            _mapResize_Map##TName(map);                                 \
        }                                                               \
                                                                        \
        u64 hash = mapHash(k);                                          \
        i64 index = hash % map->capacity;                               \
        K newKey = k;                                                   \
        V newValue = v;                                                 \
        i64 newPsl = 0;                                                 \
        while (map->psl[index] != -1)                                   \
        {                                                               \
            if (newPsl > map->psl[index])                               \
            {                                                           \
                K tmpKey = map->content[index].key;                     \
                V tmpValue = map->content[index].value;                 \
                i64 tmpPsl = map->psl[index];                           \
                map->content[index] = (KV##TName) { newKey, newValue }; \
                map->psl[index] = newPsl;                               \
                newKey = tmpKey;                                        \
                newValue = tmpValue;                                    \
                newPsl = tmpPsl;                                        \
            }                                                           \
            index = (index + 1) % map->capacity;                        \
            newPsl++;                                                   \
        }                                                               \
        map->content[index] = (KV##TName) { newKey, newValue };         \
        map->psl[index] = newPsl;                                       \
        map->count++;                                                   \
    }                                                                   \
                                                                        \
    i64 _mapFindIndex_Map##TName(Map##TName *map, K k)                  \
    {                                                                   \
        u64 hash = mapHash(k);                                          \
        i64 index = hash % map->capacity;                               \
        i64 newPsl = 0;                                                 \
        while (k.data != map->content[index].key.data)                  \
        {                                                               \
            if (map->psl[index] == -1 || newPsl > map->psl[index])      \
            {                                                           \
                return -1;                                              \
            }                                                           \
            index = (index + 1) % map->capacity;                        \
            newPsl++;                                                   \
        }                                                               \
        return index;                                                   \
    }                                                                   \
                                                                        \
    KV##TName *_mapFind_Map##TName(Map##TName *map, K k)                \
    {                                                                   \
        i64 index = _mapFindIndex_Map##TName(map, k);                   \
        if (index == -1)                                                \
        {                                                               \
            return NULL;                                                \
        }                                                               \
        return &map->content[index];                                    \
    }                                                                   \
                                                                        \
    KV##TName *_mapErase_Map##TName(Map##TName *map, K k)               \
    {                                                                   \
        i64 index = _mapFindIndex_Map##TName(map, k);                   \
        if (index == -1)                                                \
        {                                                               \
            return NULL;                                                \
        }                                                               \
        i64 currentIndex = index;                                       \
        while (index + 1 < map->capacity                                \
            && map->psl[index + 1] != -1                                \
            && map->psl[index + 1] > 0)                                 \
        {                                                               \
            map->content[index] = map->content[index + 1];              \
            map->psl[index] = map->psl[index + 1] - 1;                  \
            ++index;                                                    \
        }                                                               \
        map->content[index] = (KV##TName) {0};                          \
        map->psl[index] = -1;                                           \
                                                                        \
        if (map->psl[currentIndex] == -1)                               \
        {                                                               \
            do {                                                        \
                ++currentIndex;                                         \
            } while (currentIndex < map->capacity                       \
                  && map->psl[currentIndex] == -1);                     \
        }                                                               \
        --map->count;                                                   \
        if (currentIndex >= map->capacity) { return NULL; }             \
        return &map->content[currentIndex];                             \
    }                                                                   \
                                                                        \
    void _mapIterate_Map##TName(Map##TName *map,                        \
        void(*f) (KV##TName *element)                                   \
    )                                                                   \
    {                                                                   \
        for (u64 i = 0; i < map->capacity; ++i)                         \
        {                                                               \
            if (map->psl[i] != -1) { f(&map->content[i]); }             \
        }                                                               \
    }
#else
#define _defineMap(TName, K, V)                                         \
    typedef struct {                                                    \
        K key;                                                          \
        V value;                                                        \
    } KV##TName;                                                        \
                                                                        \
    typedef struct {                                                    \
        KV##TName *content;                                             \
        i64 *psl;                                                       \
        _MapHeader_;                                                    \
    } Map##TName;                                                       \
                                                                        \
    void _mapResize_Map##TName(Map##TName *map);                        \
    void _mapReserve_Map##TName(Map##TName *map, u64 cap);              \
    void _mapRelease_Map##TName(Map##TName *map);                       \
    void _mapInsert_Map##TName(Map##TName *map, K k, V v);              \
    i64 _mapFindIndex_Map##TName(Map##TName *map, K k);                 \
    KV##TName *_mapFind_Map##TName(Map##TName *map, K k);               \
    KV##TName *_mapErase_Map##TName(Map##TName *map, K k);              \
    void _mapIterate_Map##TName(                                        \
        Map##TName *map,                                                \
        void(*f)(KV##TName *element)                                    \
    );
#endif

_defineMap(StrF32, String, f32);
_defineMap(StrI32, String, i32);

#define mapResize(map) _Generic((map),          \
        MapStrF32 *: _mapResize_MapStrF32,      \
        MapStrI32 *: _mapResize_MapStrI32       \
    )(map)
#define mapReserve(map, cap) _Generic((map),    \
        MapStrF32 *: _mapReserve_MapStrF32,     \
        MapStrI32 *: _mapReserve_MapStrI32      \
    )(map, cap)
#define mapRelease(map) _Generic((map),         \
        MapStrF32 *: _mapRelease_MapStrF32,     \
        MapStrI32 *: _mapRelease_MapStrI32      \
    )(map)
#define mapInsert(map, k, v) _Generic((map),    \
        MapStrF32 *: _mapInsert_MapStrF32,      \
        MapStrI32 *: _mapInsert_MapStrI32       \
    )(map, k, v)
#define mapFindIndex(map, k) _Generic((map),    \
        MapStrF32 *: _mapFindIndex_MapStrF32,   \
        MapStrI32 *: _mapFindIndex_MapStrI32    \
    )(map, k)
#define mapFind(map, k) _Generic((map),         \
        MapStrF32 *: _mapFind_MapStrF32,        \
        MapStrI32 *: _mapFind_MapStrI32         \
    )(map, k)
#define mapErase(map, k) _Generic((map),        \
        MapStrF32 *: _mapErase_MapStrF32,       \
        MapStrI32 *: _mapErase_MapStrI32        \
    )(map, k)
#define mapIterate(map, f) _Generic((map),      \
        MapStrF32 *: _mapIterate_MapStrF32,     \
        MapStrI32 *: _mapIterate_MapStrI32      \
    )(map, f)

#endif

