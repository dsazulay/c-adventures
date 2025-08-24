#include "base/base_core.h"
#include <raylib.h>

typedef struct {
    f32 x;
    f32 y;
    f32 velocity;
    f32 angle;
    Texture2D sprite;
} Player;

typedef struct {
    Player player;
    Texture2D background[3];
    u64 frame;
} GameMemory;
