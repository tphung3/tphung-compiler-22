/* regular expressions matching tokens in bminor language */

%{
    #include "token.h"
%}

/* shorthands */
NOZERO  [1-9]
DIGIT   [0-9]
BOOLEAN (true | false)
ALPHA   [a-zA-Z]

/* rules */
%%

("\t"|" "|"\n"|"\r")                    /* whitespace chars, do nothing */
\/\*(\*[^\/]|[^\*])*\*\/                /* long comments */
\/\/[^"\n"]*"\n"                        /* line comments */

array                                   { return TOKEN_ARRAY; }
auto                                    { return TOKEN_AUTO; }
boolean                                 { return TOKEN_BOOLEAN; }
char                                    { return TOKEN_CHAR; }
else                                    { return TOKEN_ELSE; }
false                                   { return TOKEN_FALSE; }
for                                     { return TOKEN_FOR; }
function                                { return TOKEN_FUNCTION; }
if                                      { return TOKEN_IF; }
integer                                 { return TOKEN_INTEGER; }
print                                   { return TOKEN_PRINT; }
return                                  { return TOKEN_RETURN; }
string                                  { return TOKEN_STRING; }
true                                    { return TOKEN_TRUE; }
void                                    { return TOKEN_VOID; }
while                                   { return TOKEN_WHILE; }

("-"|"+")?{NOZERO}{DIGIT}*              { return TOKEN_INTEGER_LITERAL; }

"("                                     { return TOKEN_OPEN_PARENTHESIS; }
")"                                     { return TOKEN_CLOSE_PARENTHESIS; }
"["                                     { return TOKEN_OPEN_BRACKET; }
"]"                                     { return TOKEN_CLOSE_BRACKET; }
"{"                                     { return TOKEN_OPEN_BRACE; }
"}"                                     { return TOKEN_CLOSE_BRACE; }
"+""+"                                  { return TOKEN_POST_INC; }
"-""-"                                  { return TOKEN_POST_DEC; }
"-"                                     { return TOKEN_SUB; }
"!""="                                  { return TOKEN_NE; }
"!"                                     { return TOKEN_LOGICAL_NOT; }
"^"                                     { return TOKEN_EXP; }
"*"                                     { return TOKEN_MULT; }
"/"                                     { return TOKEN_DIV; }
"%"                                     { return TOKEN_REMAINDER; }
"+"                                     { return TOKEN_ADD; }
"<""="                                  { return TOKEN_LE; }
"<"                                     { return TOKEN_LT; }
">""="                                  { return TOKEN_GE; }
">"                                     { return TOKEN_GT; }
"=""="                                  { return TOKEN_EQ; }
"="                                     { return TOKEN_ASSIGNMENT; }
"|""|"                                  { return TOKEN_LOGICAL_OR; }
"&""&"                                  { return TOKEN_LOGICAL_AND; }
","                                     { return TOKEN_COMMA; }
":""?"                                  { return TOKEN_TERNARY; }
":"                                     { return TOKEN_COLON; }
";"                                     { return TOKEN_SEMICOLON; }

({ALPHA}|"_")({ALPHA}|{DIGIT}|"_")*     { if (yyleng <= 255)
                                            return TOKEN_IDENTIFIER;
                                          else
                                            return TOKEN_IDENTIFIER_ERROR;
                                        }

\'((\\)?[^\']|(\\\'))\'                 { return TOKEN_CHARACTER_LITERAL; }

\"((\\[^n])|([^\"\\]))*\"             { if (yyleng <= 255)
                                            return TOKEN_STRING_LITERAL;
                                          else
                                            return TOKEN_STRING_ERROR;
                                        }

.                                       { return TOKEN_SCAN_ERROR; }

%%

/* end of scanner */
int yywrap() { return 1; }
