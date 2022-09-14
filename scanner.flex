/* regular expressions matching tokens in bminor language */

%{
    #include "token.h"
%}

/* shorthands */
DIGIT   [0-9]
BOOLEAN (true | false)
ALPHA   [a-zA-Z]

/* rules */
%%
("\t"|" "|"\n"|"\r")  /* whitespace chars, do nothing */
array                                   { return TOKEN_ARRAY; }
({ALPHA}|"_")({ALPHA}|{DIGIT}|"_")*     { return TOKEN_IDENTIFIER; }
%%

/* end of scanner */
int yywrap() { return 1; }
