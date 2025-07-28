#include "base_tester.h"
#include <stdio.h>
#include <stdarg.h>

static int testCount = 0;
static int currentTest = 0;
static int failedCount = 0;

void _check(const char *test, b8 pass)
{
    ++testCount;
    ++currentTest;
    if (pass)
    {
        printf("[TEST] Test %d succeeded\n", currentTest);
    }
    else
    {
        ++failedCount;
        printf("[TEST] Test %d failed: %s\n", currentTest, test);
    }
}


void _run(const char *name, i32 n, ...)
{
    printf("Running test %s\n", name);

    va_list args;
    va_start(args, n);

    for (i32 i = 0; i < n; ++i)
    {
        printf("[TEST] Case: %s\n", va_arg(args, char *));
        funcType f = va_arg(args, funcType);
        f();
    }

    if (failedCount == 0)
    {
        printf("[TEST] %d of %d succeeded\n", currentTest, testCount);
        printf("[TEST] All tests succeeded\n");
    }
    else
    {
        printf("[TEST] %d of %d failed\n", failedCount, testCount);
    }

    va_end(args);
}
