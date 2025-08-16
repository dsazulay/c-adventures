#ifndef BASE_DEBUG_MEM_H
#define BASE_DEBUG_MEM_H

#include "base_core.h"

extern void *_debugMalloc(u64 size, char *file, u32 line);
extern void _debugFree(void *ptr, char *file, u32 line);
extern void memoryReport();

#ifdef DEBUG_MEM

#define malloc(size) _debugMalloc(size, __FILE__, __LINE__)
#define free(ptr) _debugFree(ptr, __FILE__, __LINE__)

#endif

#endif
