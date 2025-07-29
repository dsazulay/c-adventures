#include "base_tester.h"
#include "base_log.h"
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
        printflnColor(COLOR_GREEN, "[TEST] Test %d succeeded", currentTest);
    }
    else
    {
        ++failedCount;
        printflnColor(COLOR_RED, "[TEST] Test %d failed: %s",
                      currentTest, test);
    }
}


void _run(const char *name, i32 n, ...)
{
    printfln("Running test %s", name);

    va_list args;
    va_start(args, n);

    for (i32 i = 0; i < n; ++i)
    {
        printfln("Case: %s", va_arg(args, char *));
        funcType f = va_arg(args, funcType);
        f();
    }

    if (failedCount == 0)
    {
        printflnColor(COLOR_GREEN, "[TEST] %d of %d succeeded",
                      currentTest, testCount);
        printflnColor(COLOR_GREEN, "[TEST] All tests succeeded");
    }
    else
    {
        printflnColor(COLOR_RED, "[TEST] %d of %d failed",
                      failedCount, testCount);
    }

    va_end(args);
}
