#ifndef BASE_STRING_H
#define BASE_STRING_H

#include "base_core.h"

typedef struct
{
    char *data;
    i64 length;
} String;

String S(const char *str);
String strFrom(String str, u32 from);
String strFromTo(String str, u32 from, u32 to);
String strFromWithSize(String str, u32 from, u32 size);
void strRelease(String str);
b8 strCompare(String a, String b);

#endif
