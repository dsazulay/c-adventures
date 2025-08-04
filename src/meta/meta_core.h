#ifndef META_CORE_H
#define META_CORE_H 

#include "base/base_dynarray.h"
#include "base/base_string.h"

#define Reflect(x)

typedef enum
{
    Token_Unknown,
    Token_Identifier,
    Token_String,
    Token_Colon,
    Token_Semicolon,
    Token_Asterisk,
    Token_OpenParen,
    Token_CloseParen,
    Token_OpenBracket,
    Token_CloseBracket,
    Token_OpenBraces,
    Token_CloseBraces,
    Token_EOF,
} TokenType;

typedef struct
{
    TokenType type;
    String text;
} Token;

typedef struct
{
    char *at;
} Tokenizer;

typedef enum
{
    Meta_i8,
    Meta_i16,
    Meta_i32,
    Meta_i64,
    Meta_f32,
    Meta_f64,
    Meta_String,
} MetaType;

typedef struct
{
    MetaType type;
    const char *name;
    u64 offset;
} StructMember;

void removeWhiteSpacesAndComments(Tokenizer *tokenizer);
b8 requireToken(Tokenizer *tokenizer, TokenType desiredType);
Token getToken(Tokenizer *tokenizer);

void parseMember(Tokenizer *tokenizer, Token structToken);
void parseStruct(Tokenizer *tokenizer, ArrayString *structs);
void parseReflectable(Tokenizer *tokenizer, ArrayString *structs);

void parseString(String str);

void _metaPrint(void *obj, StructMember *membersArray, i32 arraySize);

#endif
