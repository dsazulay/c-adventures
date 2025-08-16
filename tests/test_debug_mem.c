#include "base/base_tester.h"
#include <stdlib.h>

#define DEBUG_MEM
#include "base/base_debug_mem.h"

void testDebugMem()
{
    void *ptr = 0;
    void *ptr2 = 0;

    ptr = malloc(sizeof(i64));
    Check(ptr != 0);

    ptr2 = malloc(sizeof(i64));
    Check(ptr2 != 0);

    free(ptr);
    ptr = 0;

    ptr2 = malloc(sizeof(i64));
    ptr2 = 0;

    memoryReport();
}

TestRun("DebugMem", 1, TestCase(testDebugMem));
