/* Listings of all categories of tokens in bminor */

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {

    TOKEN_EOF = 0, //End-of-file token
    
    /* Start of bminor keywords */
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
    /* End of bminor keywords */

    TOKEN_IDENTIFIER,    //Identifiers
    TOKEN_INTEGER_LITERAL,  //Decimal numbers
    TOKEN_CHARACTER_LITERAL,
    TOKEN_STRING_LITERAL
} token_t;

#endif
