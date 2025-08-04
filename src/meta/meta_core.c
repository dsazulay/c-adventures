#include "meta_core.h"

#include "base/base_io.h"
#include "base/base_text.h"
#include <stdbool.h>

void removeWhiteSpacesAndComments(Tokenizer *tokenizer)
{
    while (true)
    {
        if (isWhiteSpace(tokenizer->at[0]))
        {
            ++tokenizer->at;
        }
        else if (tokenizer->at[0] == '/' && tokenizer->at[1] == '/')
        {
            tokenizer->at += 2;
            while (tokenizer->at[0] && !isEndOfLine(tokenizer->at[0]))
            {
                ++tokenizer->at;
            }
        }
        else if (tokenizer->at[0] == '/' && tokenizer->at[1] == '*')
        {
            tokenizer->at += 2;
            while (tokenizer->at[0] && !(tokenizer->at[0] == '*' && tokenizer->at[1] == '/'))
            {
                ++tokenizer->at;
            }
            if (tokenizer->at[0] == '*')
            {
                tokenizer->at += 2;
            }
        }
        else
        {
            break;
        }
    }
}

b8 requireToken(Tokenizer *tokenizer, TokenType desiredType)
{
    Token token = getToken(tokenizer);
    return token.type == desiredType;
}

Token getToken(Tokenizer *tokenizer)
{
    removeWhiteSpacesAndComments(tokenizer);

    Token t = {0};
    t.text.length = 1;
    t.text.data = tokenizer->at;
    char c = tokenizer->at[0];
    ++tokenizer->at;

    switch (c)
    {
        case '\0': t.type = Token_EOF; break;
        case ':' : t.type = Token_Colon; break;
        case ';' : t.type = Token_Semicolon; break;
        case '*' : t.type = Token_Asterisk; break;
        case '(' : t.type = Token_OpenParen; break;
        case ')' : t.type = Token_CloseParen; break;
        case '[' : t.type = Token_OpenBracket; break;
        case ']' : t.type = Token_CloseBracket; break;
        case '{' : t.type = Token_OpenBraces; break;
        case '}' : t.type = Token_CloseBraces; break;
        case '"' :
            {
                t.text.data = tokenizer->at;
                t.type = Token_String;
                while (tokenizer->at[0] && tokenizer->at[0] != '"')
                {
                    if (tokenizer->at[0] == '\\' && tokenizer->at[1])
                    {
                        ++tokenizer->at;
                    }
                    ++tokenizer->at;
                }
                t.text.length = tokenizer->at - t.text.data;
                if (tokenizer->at[0] == '"')
                {
                    ++tokenizer->at;
                }
            }
            break;
        default:
            {
                if (isAlpha(c))
                {
                    t.type = Token_Identifier;
                    while (isAlpha(tokenizer->at[0]) ||
                           isNumber(tokenizer->at[0]) ||
                           tokenizer->at[0] == '_')
                    {
                        ++tokenizer->at;
                    }
                    t.text.length = tokenizer->at - t.text.data;
                }
                else if (isNumber(c))
                {
                    //parseNumber();
                }
                else
                {
                    t.type = Token_Unknown;
                }
            }
            break;
    }
    return t;
}

void parseMember(Tokenizer *tokenizer, Token structToken)
{
    b8 parsing = true;
    while (parsing)
    {
        Token token = getToken(tokenizer);
        switch (token.type)
        {
            case Token_Asterisk:
                break;
            case Token_Identifier:
                printf(" \"%.*s\", (u64)&((%.*s *)0)->%.*s ",
                       (i32)token.text.length, token.text.data,
                       (i32)structToken.text.length, structToken.text.data,
                       (i32)token.text.length, token.text.data);
                break;
            case Token_Semicolon:
            case Token_EOF:
                parsing = false;
                break;
            default:
                printfln("Strange token type: %d - %.*s", token.type,
                         token.text.length, token.text.data);
        }
    }
}

void parseStruct(Tokenizer *tokenizer, ArrayString *structs)
{
    print("StructMember membersOf");
    if (requireToken(tokenizer, Token_OpenBraces))
    {
        Tokenizer current = *tokenizer;

        Token t = getToken(tokenizer);
        while (t.type != Token_CloseBraces) { t = getToken(tokenizer); }
        t = getToken(tokenizer);
        printfln("%.*s[] =\n{", t.text.length, t.text.data);
        dynArrayPush(structs, t.text);
        *tokenizer = current;

        while (true)
        {
            Token token = getToken(tokenizer);
            if (token.type == Token_CloseBraces)
            {
                break;
            }
            else
            {
                printf("    { Meta_%.*s,", (i32)token.text.length,
                       token.text.data);
                parseMember(tokenizer, t);
                println("},");
            }
        }
    }
    println("};\n");
}

void parseReflectable(Tokenizer *tokenizer, ArrayString *structs)
{
    if (requireToken(tokenizer, Token_OpenParen) &&
        requireToken(tokenizer, Token_CloseParen))
    {
        Token token = getToken(tokenizer);
        if (strCompare(token.text, S("typedef")))
        {
            token = getToken(tokenizer);
            if (strCompare(token.text, S("struct")))
            {
                parseStruct(tokenizer, structs);
            }
            else
            {
                println("Error: missing struct keyword");
            }
        }
        else
        {
            println("Error: missing typedef keyword");
        }
    }
    else
    {
        println("Error: missing ()");
    }
}

void parseString(String str)
{
    Tokenizer tokenizer = {0};
    tokenizer.at = str.data;
    b8 parsing = true;
    ArrayString structs = {0};

    println("#include \"meta/meta_core.h\"\n");

    while(parsing)
    {
        Token token = getToken(&tokenizer);
        switch (token.type)
        {
            case Token_Unknown:
                break;
            case Token_Identifier:
                if (strCompare(token.text, S("Reflect")))
                {
                    parseReflectable(&tokenizer, &structs);
                }
                break;
            case Token_EOF:
                parsing = false;
                break;
            default:
                break;
        }
    }

    println("#define _getMembersArray(x) _Generic((x), \\");
    for (i32 i = 0; i < structs.count - 1; ++i)
    {
        printfln("    %.*s: membersOf%.*s, \\",
                 (i32)structs.data[i].length, structs.data[i].data,
                 (i32)structs.data[i].length, structs.data[i].data);
    }
    i32 i = structs.count - 1;
    printfln("    %.*s: membersOf%.*s \\",
             (i32)structs.data[i].length, structs.data[i].data,
             (i32)structs.data[i].length, structs.data[i].data);
    println(")\n");

    println("#define metaPrint(x) _metaPrint((void *)&x, \
_getMembersArray(x), arrayCount(_getMembersArray(x)))\n");
}

void _metaPrint(void *obj, StructMember *membersArray, i32 arraySize)
{
    for (i32 i = 0; i < arraySize; ++i)
    {
        StructMember *member = &membersArray[i];
        void *memberPtr = ((u8 *)obj) + member->offset;

        printf("%s: ", member->name);
        switch(member->type)
        {
            case Meta_String:
                printStr(*(String *)memberPtr);
                break;
            case Meta_i32:
                print(*(i32 *)memberPtr);
                break;
            case Meta_f32:
                print(*(f32 *)memberPtr);
                break;
            default:
                break;
        }
        println();
    }
}
