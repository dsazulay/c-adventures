#include "base_text.h"

b8 isEndOfLine(char c)
{
    return c == '\n' || c == '\r';
}

b8 isWhiteSpace(char c)
{
    return c == ' ' || c == '\t' || isEndOfLine(c);
}

b8 isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

b8 isNumber(char c)
{
    return c >= '0' && c <= '9';
}
