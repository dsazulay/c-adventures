#include "base_log.h"

#include <stdio.h>
#include <stdarg.h>

void printfln(const char * format, ...)
{
    va_list argptr;

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    printf("\n");
}

void printfColor(terminalColor color, const char * format, ...)
{
    va_list argptr;

    printf("%s", color);

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    printf("%s", COLOR_NONE);
}

void printflnColor(terminalColor color, const char * format, ...)
{
    va_list argptr;

    printf("%s", color);

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    printf("\n");
    printf("%s", COLOR_NONE);
}

void setTextColor(terminalColor color)
{
    printf("%s", color);
}

void clearColor()
{
    printf("%s", COLOR_NONE);
}
