#include "base_core.h"
#include "base_io.h"
#include <stdlib.h>

#define NUM_BLOCKS 128

typedef struct
{
    void *addr;
    u64 size;
    char *file;
    u32 line;
} MemBlock;

static MemBlock blocks[NUM_BLOCKS];
static u64 totalAllocated = 0;
static u64 totalFreed = 0;

void *_debugMalloc(u64 size, char *file, u32 line)
{
    void *ptr = malloc(size);

    for (u64 i = 0; i < NUM_BLOCKS; ++i)
    {
        if (blocks[i].addr == 0)
        {
            blocks[i].addr = ptr;
            blocks[i].size = size;
            blocks[i].file = file;
            blocks[i].line = line;
            break;
        }
    }

    totalAllocated += size;

    return ptr;
}

void _debugFree(void *ptr, char *file, u32 line)
{
    for (u64 i = 0; i < NUM_BLOCKS; ++i)
    {
        if (blocks[i].addr == ptr)
        {
            totalFreed += blocks[i].size;
            blocks[i].addr = 0;
            blocks[i].size = 0;
            blocks[i].file = file;
            blocks[i].line = line;
            break;
        }
    }

    free(ptr);
}

void memoryReport()
{
    printfln("Total allocated: %llu", totalAllocated);
    printfln("Total freed: %llu", totalFreed);

    u64 bytesLeaked = totalAllocated - totalFreed;

    if (bytesLeaked != 0)
    {
        for (u64 i = 0; i < NUM_BLOCKS; ++i)
        {
            if (blocks[i].addr != 0)
            {
                printfln("%llu bytes allocated on %s:%u were not freed",
                         blocks[i].size,
                         blocks[i].file,
                         blocks[i].line);
            }
            else
            {
                if (blocks[i].line == 0)
                {
                    break;
                }
            }
        }
        printflnColor(COLOR_RED, "%llu bytes leaked", bytesLeaked);
    }
    else
    {
        printflnColor(COLOR_GREEN, "No bytes leaked");
    }
}
