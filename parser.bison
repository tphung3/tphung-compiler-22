%{
#include <stdio.h>
void yyerror(char const *);
extern char *yytext;
%}

%define parse.error verbose
%define parse.lac none
%define parse.trace

%token TOKEN_EOF 0

/* Start of keywords */
%token TOKEN_ARRAY 1
%token TOKEN_AUTO 2
%token TOKEN_BOOLEAN 3
%token TOKEN_CHAR 4
%token TOKEN_ELSE 5
%token TOKEN_FALSE 6
%token TOKEN_FOR 7
%token TOKEN_FUNCTION 8
%token TOKEN_IF 9
%token TOKEN_INTEGER 10
%token TOKEN_PRINT 11
%token TOKEN_RETURN 12
%token TOKEN_STRING 13
%token TOKEN_TRUE 14
%token TOKEN_VOID 15
%token TOKEN_WHILE 16
/* End of keywords */

/* Start of symbols */
%token TOKEN_OPEN_PARENTHESIS 17
%token TOKEN_CLOSE_PARENTHESIS 18
%token TOKEN_OPEN_BRACKET 19
%token TOKEN_CLOSE_BRACKET 20
%token TOKEN_OPEN_BRACE 21
%token TOKEN_CLOSE_BRACE 22
%token TOKEN_POST_INC 23
%token TOKEN_POST_DEC 24
%token TOKEN_SUB 25
%token TOKEN_NE 26
%token TOKEN_LOGICAL_NOT 27
%token TOKEN_EXP 28
%token TOKEN_MULT 29
%token TOKEN_DIV 30
%token TOKEN_REMAINDER 31
%token TOKEN_ADD 32
%token TOKEN_LE 33
%token TOKEN_LT 34
%token TOKEN_GE 35
%token TOKEN_GT 36
%token TOKEN_EQ 37
%token TOKEN_ASSIGNMENT 38
%token TOKEN_LOGICAL_OR 39
%token TOKEN_LOGICAL_AND 40
%token TOKEN_COMMA 41
%token TOKEN_QUESTION 42
%token TOKEN_COLON 43
%token TOKEN_SEMICOLON 44
/* End of symbols */

%token TOKEN_INTEGER_LITERAL 45
%token TOKEN_IDENTIFIER 46
%token TOKEN_CHARACTER_LITERAL 47
%token TOKEN_STRING_LITERAL 48

%token TOKEN_STRING_ERROR 49
%token TOKEN_IDENTIFIER_ERROR 50
%token TOKEN_SCAN_ERROR 51

%%
/* Rules here */
program: global_decl_list
    | /* Nothing */;

global_decl_list: global_decl global_decl_list
    | global_decl;

global_decl: var_decl | array_decl | func_decl; 

var_decl: TOKEN_IDENTIFIER TOKEN_COLON atomic_type var_decl_optional;

var_decl_optional: TOKEN_ASSIGNMENT literal TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

literal: TOKEN_INTEGER_LITERAL 
    | TOKEN_STRING_LITERAL 
    | TOKEN_CHARACTER_LITERAL 
    | TOKEN_FALSE;
    | TOKEN_TRUE;

atomic_type: TOKEN_INTEGER 
    | TOKEN_STRING 
    | TOKEN_CHAR
    | TOKEN_BOOLEAN;

array_decl: TOKEN_IDENTIFIER TOKEN_COLON array_type_list atomic_type array_decl_optional;

array_type_list: array_type array_type_list
    | array_type;

array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET TOKEN_INTEGER_LITERAL TOKEN_CLOSE_BRACKET;

array_decl_optional: TOKEN_ASSIGNMENT TOKEN_OPEN_BRACE array_element_list TOKEN_CLOSE_BRACE TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

array_element_list: array_element TOKEN_COMMA array_element_list
    | array_element;

array_element: TOKEN_OPEN_BRACE array_element_list TOKEN_CLOSE_BRACE
    | literal;

function_return_type: atomic_type
    | TOKEN_VOID;

array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET TOKEN_CLOSE_BRACKET;

function_type: TOKEN_FUNCTION function_return_type TOKEN_OPEN_PARENTHESIS function_argument_list_w_empty TOKEN_CLOSE_PARENTHESIS;

compound_type: atomic_type
    | array_type compound_type
    | function_type;

function_argument_list_w_empty: function_argument_list
    | /* Nothing */;

function_argument_list: function_argument TOKEN_COMMA function_argument_list
    | function_argument;

function_argument: TOKEN_IDENTIFIER TOKEN_COLON compound_type;

local_decl: var_decl
    | array_decl;
    
expr: expr_lv0_0;

expr_lv0_0: assignment_expr expr_lv0_0
    | expr_lv_0_1; 

assignment_expr: expr_lv_0_1 TOKEN_ASSIGNMENT;

expr_lv_0_1: ternary_expr
    | expr_lv_1_0;

/* first part can't be ternary, I hope */
ternary_expr: expr_lv_1_0 TOKEN_QUESTION expr_lv_0_1 TOKEN_COLON expr_lv_0_1;

expr_lv_1_0: logical_or_expr expr_lv_1_0
    | expr_lv_2_0;

logical_or_expr: expr_lv_2_0 TOKEN_LOGICAL_OR; 

expr_lv_2_0: logical_and_expr expr_lv_2_0
    | expr_lv_3_0;

logical_and_expr: expr_lv_3_0 TOKEN_LOGICAL_AND;

expr_lv_3_0: less_expr expr_lv_3_0 
    | expr_lv_3_1;

less_expr: expr_lv_3_1 TOKEN_LT;

expr_lv_3_1: less_equal_expr expr_lv_3_1
    | expr_lv_3_2;

less_equal_expr: expr_lv_3_2 TOKEN_LE;

expr_lv_3_2: greater_expr expr_lv_3_2
    | expr_lv_3_3;

greater_expr: expr_lv_3_3 TOKEN_GT;

expr_lv_3_3: greater_equal_expr expr_lv_3_3
    | expr_lv_3_4;

greater_equal_expr: expr_lv_3_4 TOKEN_GE;

expr_lv_3_4: equal_expr expr_lv_3_4
    | expr_lv_3_5;

equal_expr: expr_lv_3_5 TOKEN_EQ;

expr_lv_3_5: not_equal_expr expr_lv_3_5
    | expr_lv_4_0;

not_equal_expr: expr_lv_4_0 TOKEN_NE;

expr_lv_4_0: add_expr expr_lv_4_0
    | expr_lv_4_1;

add_expr: expr_lv_4_1 TOKEN_ADD;

expr_lv_4_1: sub_expr expr_lv_4_1
    | expr_lv_5_0;

sub_expr: expr_lv_5_0 TOKEN_SUB;

expr_lv_5_0: mult_expr expr_lv_5_0
    | expr_lv_5_1;

mult_expr: expr_lv_5_1 TOKEN_MULT;

expr_lv_5_1: div_expr expr_lv_5_1
    | expr_lv_5_2;

div_expr: expr_lv_5_2 TOKEN_DIV;

expr_lv_5_2: remainder_expr expr_lv_5_2
    | expr_lv_6_0;

remainder_expr: expr_lv_6_0 TOKEN_REMAINDER;

expr_lv_6_0: exponent_expr expr_lv_6_0
    | TOKEN_SUB expr_lv_6_0
    | expr_lv_7_0;

exponent_expr: expr_lv_7_0 TOKEN_EXP;

expr_lv_7_0: expr_lv_7_1;

expr_lv_7_1: logical_not_expr expr_lv_7_1
    | expr_lv_8_0;

logical_not_expr: TOKEN_LOGICAL_NOT;

expr_lv_8_0: expr_lv_8_0 post_incre_expr
    | expr_lv_8_1;

post_incre_expr: TOKEN_POST_INC;

expr_lv_8_1: expr_lv_8_1 post_decre_expr
    | expr_lv_9_0;

post_decre_expr: TOKEN_POST_DEC;

expr_lv_9_0: grouping_expr;

grouping_expr: TOKEN_OPEN_PARENTHESIS grouping_expr TOKEN_CLOSE_PARENTHESIS
    | expr_lv_9_1;

expr_lv_9_1: arr_sub_expr;

arr_sub_expr: TOKEN_OPEN_BRACKET arr_sub_expr TOKEN_CLOSE_BRACKET
    | expr_lv_9_2;

expr_lv_9_2: func_call_expr;

func_call_expr: TOKEN_IDENTIFIER TOKEN_OPEN_PARENTHESIS func_call_expr TOKEN_CLOSE_PARENTHESIS
    | expr_lv_10_0;

expr_lv_10_0: literal
    | TOKEN_IDENTIFIER;

if_else: TOKEN_IF if_else_condition body_if
    | TOKEN_IF if_else_condition stmt_w_full_if_else TOKEN_ELSE body_else;

if_else_condition: TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS;

body_if: stmt;

full_if_else: TOKEN_IF if_else_condition stmt_w_full_if_else TOKEN_ELSE stmt_w_full_if_else;

body_else: stmt;

for: TOKEN_FOR TOKEN_OPEN_PARENTHESIS expr TOKEN_SEMICOLON expr TOKEN_SEMICOLON expr TOKEN_CLOSE_PARENTHESIS block; 

print: TOKEN_PRINT expr_list_empty TOKEN_SEMICOLON;

expr_list_empty: expr_list
    | /* Nothing */;

expr_list: expr TOKEN_COMMA expr_list
    | expr;

/***************** DONE *****************/

func_decl: TOKEN_IDENTIFIER TOKEN_COLON function_type func_decl_optional;

func_decl_optional: block
    | TOKEN_SEMICOLON;

block: TOKEN_OPEN_BRACE stmt_list TOKEN_CLOSE_BRACE;

stmt_list: stmt_list stmt
    | stmt;

/* LOOK TO IF ELSE AND CHANGE ACCORDINGLY */
stmt: local_decl
    | expr TOKEN_SEMICOLON
    | block
    | for
    | print
    | return
    | if_else;

/*stmt: local_decl
    | expr
    | if_else
    | for
    | print
    | return
    | block;*/


/* LOOK ABOVE AND CHANGE ACCORDINGLY */
stmt_w_full_if_else: local_decl
    | expr TOKEN_SEMICOLON
    | block
    | for
    | print
    | return
    | full_if_else;


return: TOKEN_RETURN expr TOKEN_SEMICOLON;

/**************** TESTING ******************/


/**************** TODO ********************/
%%

void yyerror (char const *s) {
    fprintf(stderr, "parse error: %s\n", s);
    fprintf(stderr, "Last token is: %s\n", yytext);
}
