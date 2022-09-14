/* Listings of all categories of tokens in bminor */

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {

    TOKEN_EOF = 0, //End-of-file token
    
    /* Start of keywords */
    TOKEN_ARRAY,
    TOKEN_AUTO,
    TOKEN_BOOLEAN,
    TOKEN_CHAR,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FOR,
    TOKEN_FUNCTION,
    TOKEN_IF,
    TOKEN_INTEGER,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_STRING,
    TOKEN_TRUE,
    TOKEN_VOID,
    TOKEN_WHILE,
    /* End of keywords */

    /* Start of symbols */
    TOKEN_OPEN_PARENTHESIS,
    TOKEN_CLOSE_PARENTHESIS,
    TOKEN_OPEN_BRACKET,
    TOKEN_CLOSE_BRACKET,
    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,
    TOKEN_POST_INC,
    TOKEN_POST_DEC,
    TOKEN_SUB,
    TOKEN_NE,
    TOKEN_LOGICAL_NOT,
    TOKEN_EXP,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_REMAINDER,
    TOKEN_ADD,
    TOKEN_LE,
    TOKEN_LT,
    TOKEN_GE,
    TOKEN_GT,
    TOKEN_EQ,
    TOKEN_ASSIGNMENT,
    TOKEN_LOGICAL_OR,
    TOKEN_LOGICAL_AND,
    TOKEN_COMMA,
    TOKEN_TERNARY,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    /* End of symbols */

    TOKEN_INTEGER_LITERAL,  
    TOKEN_IDENTIFIER,    
    TOKEN_CHARACTER_LITERAL,
    TOKEN_STRING_LITERAL,

    TOKEN_ERROR
} token_t;

#endif
