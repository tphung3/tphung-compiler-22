#include "token.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yylex();
extern char *yytext;

int open_file(FILE *yyin, char *fname)
{
    
}

int parse_cmd(int argc, char **argv)
{
    if ( strncmp(*(argv + 1), "-scan") && argc == 3)
    {
        scan(*(argv + 2));
        return 0;
    }
    else
    {
        fprintf(stderr, "Invalid command-line arguments.\n");
        return 1;
    }
}

int scan(char *fname)
{   
    yyin = fopen(fname, 'r');
    if (yyin == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", fname);
        return 1;
    }

    while(1)
    {
        token_t t = yylex();
        if (t == TOKEN_EOF) break;
        printf("token: %d text: %s\n", t, yytext);
    }
    return 0;
}

int main(int argc, char **argv)
{
    FILE *fp;
    parse_cmd(argc, argv);    
}
