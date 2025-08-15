#define MAP_IMPLEMENTATION
#include "base_map.h"

u64 _mapHashStr(String key)
{
    u64 h = 0x100;
    for (u64 i = 0; i < key.length; ++i) {
        h ^= key.data[i];
        h *= 1111111111111111111u;
    }
    return h;
}

