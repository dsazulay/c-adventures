#ifndef BASE_LOG_H
#define BASE_LOG_H

#include <stdio.h>

#define COLOR_DEFAULT "\033[39m"
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_GREY "\033[90m"
#define COLOR_LIGHT_RED "\033[91m"
#define COLOR_LIGHT_GREEN "\033[92m"
#define COLOR_LIGHT_YELLOW "\033[93m"
#define COLOR_LIGHT_BLUE "\033[94m"
#define COLOR_LIGHT_MAGENTA "\033[95m"
#define COLOR_LIGHT_CYAN "\033[96m"
#define COLOR_WHITE "\033[97m"
#define COLOR_NONE "\033[0m"

typedef const char *terminalColor;

void printfln(const char *format, ...);
void printfColor(terminalColor color, const char *format, ...);
void printflnColor(terminalColor color, const char *format, ...);
void setTextColor(terminalColor color);
void clearTextColor();

#define _printfDecodeFormat(x) _Generic((x),    \
    char: "%c",                                 \
    signed char: "%hhd",                        \
    unsigned char: "%hhu",                      \
    signed short: "%hd",                        \
    unsigned short: "%hu",                      \
    signed int: "%d",                           \
    unsigned int: "%u",                         \
    long int: "%ld",                            \
    unsigned long int: "%lu",                   \
    long long int: "%lld",                      \
    unsigned long long int: "%llu",             \
    float: "%f",                                \
    double: "%lf",                              \
    long double: "%Lf",                         \
    char *: "%s",                               \
    const char *: "%s",                         \
    void *: "%p")

#define _getFuncName(_0, _1, name, ...) name
#define _println_noarg() printf("\n")
#define _println(x) printf(_printfDecodeFormat(x), x); _println_noarg()

#define print(x) printf(_printfDecodeFormat(x), x)

#define println(...) _getFuncName(_0 __VA_OPT__(,) __VA_ARGS__, _println, _println_noarg)(__VA_ARGS__)

#endif
