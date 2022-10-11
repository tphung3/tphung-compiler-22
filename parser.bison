%{
#include <stdio.h>
void yyerror(char const *);
extern char *yytext;
%}
%verbose
%define parse.error verbose
%define parse.lac none

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

global_decl: global_var_decl | global_array_decl | global_func_decl; 

/* GLOBAL VARIABLE DECLARATIONS */
global_var_decl: TOKEN_IDENTIFIER TOKEN_COLON global_var_type global_var_decl_optional;

global_var_type: atomic_type
    | TOKEN_AUTO;

atomic_type: TOKEN_INTEGER 
    | TOKEN_STRING 
    | TOKEN_CHAR
    | TOKEN_BOOLEAN;

global_var_decl_optional: TOKEN_ASSIGNMENT global_var_initializer TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

global_var_initializer: expr;

literal: TOKEN_INTEGER_LITERAL 
    | TOKEN_STRING_LITERAL 
    | TOKEN_CHARACTER_LITERAL 
    | TOKEN_FALSE;
    | TOKEN_TRUE;

/* GLOBAL ARRAY DECLARATIONS */
global_array_decl: TOKEN_IDENTIFIER TOKEN_COLON expr_array_type_list global_var_type global_array_decl_optional;

/*fixed_array_type_list: fixed_array_type fixed_array_type_list
    | fixed_array_type;

fixed_array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET;*/

global_array_decl_optional: TOKEN_ASSIGNMENT TOKEN_OPEN_BRACE expr_array_element_list TOKEN_CLOSE_BRACE TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

/* GLOBAL FUNCTION DECLARATIONS */
global_func_decl: TOKEN_IDENTIFIER TOKEN_COLON global_function_type global_func_decl_optional;

global_function_type: TOKEN_FUNCTION function_return_type TOKEN_OPEN_PARENTHESIS global_function_argument_list_w_empty TOKEN_CLOSE_PARENTHESIS;

function_return_type: atomic_type
    | TOKEN_VOID;

global_function_argument_list_w_empty: global_function_argument_list
    | /* Nothing */;

global_function_argument_list: global_function_argument TOKEN_COMMA global_function_argument_list
    | global_function_argument;

global_function_argument: TOKEN_IDENTIFIER TOKEN_COLON global_argument_type;

global_argument_type: global_argument_optional_array_type atomic_type;

global_argument_optional_array_type: loose_array_type_list
    | /* Nothing */;

loose_array_type_list: loose_array_type loose_array_type_list
    | loose_array_type;

loose_array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET TOKEN_CLOSE_BRACKET;

global_func_decl_optional: TOKEN_ASSIGNMENT block
    | TOKEN_SEMICOLON;

/* EXPRESSIONS */
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

grouping_expr: TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS
    | expr_lv_9_1;

expr_lv_9_1: arr_sub_expr;

arr_sub_expr: TOKEN_IDENTIFIER arr_index_list
    | expr_lv_9_2;

arr_index_list: TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET arr_index_list
    | TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET;

expr_lv_9_2: func_call_expr;

func_call_expr: TOKEN_IDENTIFIER TOKEN_OPEN_PARENTHESIS expr_list_empty TOKEN_CLOSE_PARENTHESIS
    | expr_lv_10_0;

expr_list_empty: expr_list
    | /* Nothing */;

expr_list: expr TOKEN_COMMA expr_list
    | expr;

expr_lv_10_0: literal
    | TOKEN_IDENTIFIER;

/* STATEMENTS */
stmt: if_only
    | others;

/* BLOCK */
block: TOKEN_OPEN_BRACE stmt_list TOKEN_CLOSE_BRACE
    | TOKEN_OPEN_BRACE TOKEN_CLOSE_BRACE;

stmt_list: stmt stmt_list
    | stmt;

/* LOCAL DECLARATIONS */
local_decl: local_var_decl 
    | local_array_decl;

local_var_decl: TOKEN_IDENTIFIER TOKEN_COLON global_var_type local_var_decl_optional;

local_var_decl_optional: TOKEN_ASSIGNMENT local_var_initializer TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

local_var_initializer: expr;

local_array_decl: TOKEN_IDENTIFIER TOKEN_COLON expr_array_type_list global_var_type local_array_decl_optional;

expr_array_type_list: expr_array_type expr_array_type_list
    | expr_array_type;

expr_array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET;

local_array_decl_optional: TOKEN_ASSIGNMENT TOKEN_OPEN_BRACE expr_array_element_list TOKEN_CLOSE_BRACE TOKEN_SEMICOLON
    | TOKEN_SEMICOLON;

expr_array_element_list: expr_array_element TOKEN_COMMA expr_array_element_list
    | expr_array_element;

expr_array_element: TOKEN_OPEN_BRACE expr_array_element_list TOKEN_CLOSE_BRACE
    | expr;

/* IF ELSE */
if_only: TOKEN_IF if_else_condition stmt
    | TOKEN_IF if_else_condition others TOKEN_ELSE if_only
    | for_header if_only;

others: TOKEN_IF if_else_condition others TOKEN_ELSE others
    | expr TOKEN_SEMICOLON
    | block
    | print
    | return
    | for_header others
    | local_decl;

if_else_condition: TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS;

/* RETURN */
return: TOKEN_RETURN expr TOKEN_SEMICOLON
    | TOKEN_RETURN TOKEN_SEMICOLON;

/* PRINT */
print: TOKEN_PRINT expr_list_empty TOKEN_SEMICOLON;

/* FOR */
for_header: TOKEN_FOR empty_expr_after_open_paren empty_expr_after_semi empty_expr_after_semi TOKEN_CLOSE_PARENTHESIS;

empty_expr_after_open_paren: TOKEN_OPEN_PARENTHESIS expr
    | TOKEN_OPEN_PARENTHESIS;

empty_expr_after_semi: TOKEN_SEMICOLON expr
    | TOKEN_SEMICOLON;
%%

void yyerror (char const *s) {
    fprintf(stderr, "parse error: %s. ", s);
    fprintf(stderr, "Last token is: %s\n", yytext);
}
