#include "base_core.h"
#include "base_string.h"

#include <assert.h>
#include <stdlib.h>

String S(const char *str)
{
    String s;
    s.data = (char *)str;
    u64 count = 0;
    while (str[count] != '\0')
    {
        ++count;
    }
    s.length = count;
    return s;
}

String strFrom(String str, u32 from)
{
    assert(from < str.length);

    String s = {
        .data = str.data + from,
        .length = str.length - from,
    };
    return s;
}

String strFromTo(String str, u32 from, u32 to)
{
    assert(from < str.length);
    assert(to < str.length);
    assert(from <= to);

    String s = {
        .data = str.data + from,
        .length = to - from + 1,
    };
    return s;
}

String strFromWithSize(String str, u32 from, u32 size)
{
    assert(from < str.length);
    assert(from + size < str.length);

    String s = {
        .data = str.data + from,
        .length = size,
    };
    return s;
}

void strRelease(String str)
{
    free(str.data);
    str.length = 0;
}
