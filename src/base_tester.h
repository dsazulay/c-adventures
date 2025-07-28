#ifndef BASE_TESTER_H
#define BASE_TESTER_H

#include "base_core.h"

typedef void (*funcType)();

void _check(const char *test, b8 pass);
void _run(const char *name, i32 n, ...);

#define Check(test) _check(#test, test)

#define TestCase(f) #f, f

#define TestRun(name, n, ...)   \
i32 main(int argc, char **argv) \
{                               \
    _run(name, n, __VA_ARGS__); \
    return 0;                   \
}

#endif
