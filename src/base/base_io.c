#include "base_io.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void printfln(const char * format, ...)
{
    va_list argptr;

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    println();
}

void printfColor(TerminalColor color, const char * format, ...)
{
    va_list argptr;

    print(color);

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    print(COLOR_NONE);
}

void printflnColor(TerminalColor color, const char * format, ...)
{
    va_list argptr;

    print(color);

    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);

    println();
    print(COLOR_NONE);
}

void printStr(String str)
{
    for (i32 i = 0; i < str.length; ++i)
    {
        print(str.data[i]);
    }
}

void printlnStr(String str)
{
    printStr(str);
    println();
}

void setTextColor(TerminalColor color)
{
    print(color);
}

void clearColor()
{
    print(COLOR_NONE);
}

String readFile(const char *fileName)
{
    String result = {0};

    FILE *file = fopen(fileName, "r");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        result.data = malloc(fileSize + 1);
        result.length = fileSize;

        fread(result.data, fileSize, 1, file);
        result.data[fileSize] = '\0';

        fclose(file);
    }

    return result;
}

