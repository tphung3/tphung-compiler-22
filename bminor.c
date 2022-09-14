#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
extern int yylex();
extern char *yytext;

extern const char * token_map[];
extern const int token_map_len;

/* Parse command line arguments and act accordingly */
int parse_cmd(int argc, char **argv)
{
    if (!strncmp(*(argv + 1), "-scan", 5) && argc == 3)
    {
        return scan(*(argv + 2));
    }
    else
    {
        fprintf(stderr, "Invalid command-line arguments.\n");
        exit(1);
    }
}

/* Dedicated function to print string literal for scanning */
int print_string_literal()
{
    int i = 1;
    while (yytext[i] != '\0')
    {
        if (yytext[i] == '\\' && yytext[i+1] == 'n')
        {
            printf("\n");
            ++i;
        }
        else if (yytext[i] == '\\' && yytext[i+1] == '0')
        {
            printf("\0");
            ++i;
        }
        else if (yytext[i] == '\\')
        {
            printf("%c", yytext[i+1]);
            ++i;
        }
        else if (yytext[i] == '"' && yytext[i+1] == '\0')
            ;
        else
            printf("%c", yytext[i]);
        ++i;
    }    
    printf("\n");
    return 0;
}

/* Dedicated function to print character literal for scanning */
int print_character_literal()
{
    int l = strnlen(yytext, 5);
    if (l == 3)
        printf("%c", yytext[1]);
    else if (l == 4)
    {
        if (yytext[1] == '\\' && yytext[2] == 'n')
            printf("\n");
        else if (yytext[1] == '\\' && yytext[2] == '0')
            printf("\0");
        else if (yytext[1] == '\\')
            printf("%c", yytext[2]);
        else
        {
            fprintf(stderr, "Scanner detects invalid format of a character %s. Please report back to tphung@nd.edu, or else.\n", yytext);
            exit(1);
        }
    }
    printf("\n");
    return 0;
}

/* Implements the scan functionality of compiler */
int scan(char *fname)
{   
    yyin = fopen(fname, "r");
    if (yyin == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", fname);
        exit(1);
    }

    while(1)
    {
        token_t t = yylex();
        if (t == TOKEN_EOF) break;
        
        if (t == TOKEN_INTEGER_LITERAL || t == TOKEN_IDENTIFIER)
            printf("%s %s\n", token_map[t], yytext);
        else if (t == TOKEN_STRING_LITERAL)
        {
            printf("%s ", token_map[t]);
            print_string_literal();
        }
        else if (t == TOKEN_CHARACTER_LITERAL)
        {
            printf("%s ", token_map[t]);
            print_character_literal();
        }
        else if (t == TOKEN_STRING_ERROR)
        {
            fprintf(stderr, "%s: %s is above the 255 character limit.\n", token_map[t], yytext);
            exit(1);
        }   
        else if (t == TOKEN_IDENTIFIER_ERROR)
        {
            fprintf(stderr, "%s: %s is above the 255 character limit.\n", token_map[t], yytext);
            exit(1);
        }
        else if (t == TOKEN_SCAN_ERROR)
        {
            fprintf(stderr, "%s: %s is not a valid character.\n", token_map[t], yytext);
            exit(1);
        }
        else if (t < token_map_len)
            printf("%s\n", token_map[t]);
        else
        {
            fprintf(stderr, "The scanner detects unrecognizable token code: %d. Please report back to tphung@nd.edu, or else.\n", t);
            exit(2);
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    FILE *fp;
    return parse_cmd(argc, argv);    
}
