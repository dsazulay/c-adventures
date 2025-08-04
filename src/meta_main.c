#include "base/base_string.h"
#include "base/base_io.h"
#include "meta/meta_core.h"

i32 main(i32 argc, char **argv)
{
    String file = readFile("tests/test_meta.c");
    parseString(file);
    strRelease(file);

    return 0;
}

