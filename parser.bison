%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decl.h"
#include "expr.h"
#include "param_list.h"
#include "stmt.h"
#include "type.h"

struct decl* parser_result = 0;
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

%union{
    struct decl* decl;
    struct stmt* stmt;
    struct type* type;
    struct expr* expr;
    struct param_list* param_list;
}

%type <decl> program global_decl_list global_decl global_var_decl global_array_decl global_func_decl local_decl local_var_decl local_array_decl
%type <stmt> stmt if_only others block stmt_list return print for_header global_func_decl_optional
%type <type> global_var_type atomic_type global_function_type function_return_type global_argument_type loose_array_type_list loose_array_type expr_array_type_list
%type <expr> global_var_decl_optional global_var_initializer literal global_array_decl_optional expr_array_element_list expr expr_lv0_0 assignment_expr expr_lv_0_1 ternary_expr expr_lv_1_0 logical_or_expr expr_lv_2_0 logical_and_expr expr_lv_3_0 less_expr expr_lv_3_1 less_equal_expr expr_lv_3_2 greater_expr expr_lv_3_3 greater_equal_expr expr_lv_3_4 equal_expr expr_lv_3_5 not_equal_expr expr_lv_4_0 add_expr expr_lv_4_1 sub_expr expr_lv_5_0 mult_expr expr_lv_5_1 div_expr expr_lv_5_2 remainder_expr expr_lv_6_0 exponent_expr expr_lv_7_0 expr_lv_7_1 expr_lv_8_0 expr_lv_8_1 expr_lv_9_0 grouping_expr expr_lv_9_1 arr_sub_expr arr_index_list expr_lv_9_2 func_call_expr expr_list_empty expr_list expr_lv_10_0 local_var_decl_optional local_var_initializer expr_array_type local_array_decl_optional expr_array_element if_else_condition empty_expr_after_open_paren empty_expr_after_semi expr_array_literal identifier
%type <param_list> global_function_argument_list_w_empty global_function_argument_list global_function_argument

%%
/* Rules here */
program: global_decl_list {parser_result = $1;}
    | /* Nothing */ {$$ = 0;};

global_decl_list: global_decl global_decl_list {$1->next = $2; $$ = $1;}
    | global_decl {$$ = $1;};

global_decl: global_var_decl {$$ = $1;}
    | global_array_decl {$$ = $1;}
    | global_func_decl {$$ = $1;};

/* GLOBAL VARIABLE DECLARATIONS */
global_var_decl: identifier TOKEN_COLON global_var_type global_var_decl_optional {$$ = decl_create((char*) $1->name, $3, $4, 0, 0);};

identifier: TOKEN_IDENTIFIER {$$ = expr_create_name(strdup(yytext));}

global_var_type: atomic_type {$$ = $1;}
    | TOKEN_AUTO {$$ = type_create(TYPE_AUTO, 0, 0, 0);};

atomic_type: TOKEN_INTEGER {$$ = type_create(TYPE_INTEGER, 0, 0, 0);}
    | TOKEN_STRING {$$ = type_create(TYPE_STRING, 0, 0, 0);}
    | TOKEN_CHAR {$$ = type_create(TYPE_CHARACTER, 0, 0, 0);}
    | TOKEN_BOOLEAN {$$ = type_create(TYPE_BOOLEAN, 0, 0, 0);};

global_var_decl_optional: TOKEN_ASSIGNMENT global_var_initializer TOKEN_SEMICOLON {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};

global_var_initializer: expr {$$ = $1;};

literal: TOKEN_INTEGER_LITERAL {$$ = expr_create_integer_literal(atoi(strdup(yytext)));}
    | TOKEN_STRING_LITERAL {$$ = expr_create_string_literal(strdup(yytext));}
    | TOKEN_CHARACTER_LITERAL {$$ = expr_create_char_literal(strdup(yytext));}
    | TOKEN_FALSE {$$ = expr_create_boolean_literal(0);}
    | TOKEN_TRUE {$$ = expr_create_boolean_literal(1);};

/* GLOBAL ARRAY DECLARATIONS */
global_array_decl: identifier TOKEN_COLON expr_array_type_list global_array_decl_optional {$$ = decl_create((char*) $1->name, $3, $4, 0, 0);};

global_array_decl_optional: TOKEN_ASSIGNMENT expr_array_literal TOKEN_SEMICOLON {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};

/* GLOBAL FUNCTION DECLARATIONS */
global_func_decl: identifier TOKEN_COLON global_function_type global_func_decl_optional {$$ = decl_create((char*) $1->name, $3, 0, $4, 0);};

global_function_type: TOKEN_FUNCTION function_return_type TOKEN_OPEN_PARENTHESIS global_function_argument_list_w_empty TOKEN_CLOSE_PARENTHESIS {$$ = type_create(TYPE_FUNCTION, $2, $4, 0);};

function_return_type: atomic_type {$$ = $1;}
    | TOKEN_VOID {$$ = type_create(TYPE_VOID, 0, 0, 0);};

global_function_argument_list_w_empty: global_function_argument_list {$$ = $1;}
    | /* Nothing */ {$$ = 0;};

global_function_argument_list: global_function_argument TOKEN_COMMA global_function_argument_list {$1->next = $3; $$ = $1;}
    | global_function_argument {$$ = $1;};

global_function_argument: identifier TOKEN_COLON global_argument_type {$$ = param_list_create((char*) $1->name, $3, 0);};

global_argument_type: loose_array_type_list {$$ = $1;}
    | atomic_type {$$ = $1;};

loose_array_type_list: loose_array_type loose_array_type_list {$1->subtype = $2; $$ = $1;}
    | loose_array_type atomic_type {$1->subtype = $2; $$ = $1;};

loose_array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET TOKEN_CLOSE_BRACKET {$$ = type_create(TYPE_ARRAY, 0, 0, 0);};

global_func_decl_optional: TOKEN_ASSIGNMENT block {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};

/* EXPRESSIONS */
expr: expr_lv0_0 {$$ = $1;};

expr_lv0_0: assignment_expr expr_lv0_0 {$$ = expr_create(EXPR_ASSIGN, $1, $2, 0);}
    | expr_lv_0_1 {$$ = $1;}; 

assignment_expr: expr_lv_0_1 TOKEN_ASSIGNMENT {$$ = $1;};

expr_lv_0_1: ternary_expr {$$ = $1;}
    | expr_lv_1_0 {$$ = $1;};

/* first part can't be ternary, I hope */
ternary_expr: expr_lv_1_0 TOKEN_QUESTION expr_lv_0_1 TOKEN_COLON expr_lv_0_1 {$$ = expr_create(EXPR_TERNARY, $1, $5, $3);};

expr_lv_1_0: logical_or_expr expr_lv_1_0 {$$ = expr_create(EXPR_LOGICAL_OR, $1, $2, 0);}
    | expr_lv_2_0 {$$ = $1;};

logical_or_expr: expr_lv_2_0 TOKEN_LOGICAL_OR {$$ = $1;};

expr_lv_2_0: logical_and_expr expr_lv_2_0 {$$ = expr_create(EXPR_LOGICAL_AND, $1, $2, 0);}
    | expr_lv_3_0 {$$ = $1;};

logical_and_expr: expr_lv_3_0 TOKEN_LOGICAL_AND {$$ = $1;};

expr_lv_3_0: less_expr expr_lv_3_0 {$$ = expr_create(EXPR_LESS, $1, $2, 0);}
    | expr_lv_3_1 {$$ = $1;};

less_expr: expr_lv_3_1 TOKEN_LT {$$ = $1;};

expr_lv_3_1: less_equal_expr expr_lv_3_1 {$$ = expr_create(EXPR_LE, $1, $2, 0);}
    | expr_lv_3_2 {$$ = $1;};

less_equal_expr: expr_lv_3_2 TOKEN_LE {$$ = $1;};

expr_lv_3_2: greater_expr expr_lv_3_2 {$$ = expr_create(EXPR_GREATER, $1, $2, 0);}
    | expr_lv_3_3 {$$ = $1;};

greater_expr: expr_lv_3_3 TOKEN_GT {$$ = $1;};

expr_lv_3_3: greater_equal_expr expr_lv_3_3 {$$ = expr_create(EXPR_GE, $1, $2, 0);}
    | expr_lv_3_4 {$$ = $1;};

greater_equal_expr: expr_lv_3_4 TOKEN_GE {$$ = $1;};

expr_lv_3_4: equal_expr expr_lv_3_4 {$$ = expr_create(EXPR_EQ, $1, $2, 0);}
    | expr_lv_3_5 {$$ = $1;};

equal_expr: expr_lv_3_5 TOKEN_EQ {$$ = $1;};

expr_lv_3_5: not_equal_expr expr_lv_3_5 {$$ = expr_create(EXPR_NOT_EQ, $1, $2, 0);}
    | expr_lv_4_0 {$$ = $1;};

not_equal_expr: expr_lv_4_0 TOKEN_NE {$$ = $1;};

expr_lv_4_0: add_expr expr_lv_4_0 {$$ = expr_create(EXPR_ADD, $1, $2, 0);}
    | expr_lv_4_1 {$$ = $1;};

add_expr: expr_lv_4_1 TOKEN_ADD {$$ = $1;};

expr_lv_4_1: sub_expr expr_lv_4_1 {$$ = expr_create(EXPR_SUB, $1, $2, 0);}
    | expr_lv_5_0 {$$ = $1;};

sub_expr: expr_lv_5_0 TOKEN_SUB {$$ = $1;};

expr_lv_5_0: mult_expr expr_lv_5_0 {$$ = expr_create(EXPR_MULT, $1, $2, 0);}
    | expr_lv_5_1 {$$ = $1;};

mult_expr: expr_lv_5_1 TOKEN_MULT {$$ = $1;};

expr_lv_5_1: div_expr expr_lv_5_1 {$$ = expr_create(EXPR_DIV, $1, $2, 0);}
    | expr_lv_5_2 {$$ = $1;};

div_expr: expr_lv_5_2 TOKEN_DIV {$$ = $1;};

expr_lv_5_2: remainder_expr expr_lv_5_2 {$$ = expr_create(EXPR_MOD, $1, $2, 0);}
    | expr_lv_6_0 {$$ = $1;};

remainder_expr: expr_lv_6_0 TOKEN_REMAINDER {$$ = $1;};

expr_lv_6_0: exponent_expr expr_lv_6_0 {$$ = expr_create(EXPR_EXP, $1, $2, 0);}
    | TOKEN_SUB expr_lv_6_0 {$$ = expr_create(EXPR_SINGLE_SUB, $2, 0, 0);}
    | expr_lv_7_0 {$$ = $1;};

exponent_expr: expr_lv_7_0 TOKEN_EXP {$$ = $1;};

expr_lv_7_0: expr_lv_7_1 {$$ = $1;};

expr_lv_7_1: TOKEN_LOGICAL_NOT expr_lv_7_1 {$$ = expr_create(EXPR_LOGICAL_NOT, $2, 0, 0);}
    | expr_lv_8_0 {$$ = $1;};

expr_lv_8_0: expr_lv_8_0 TOKEN_POST_INC {$$ = expr_create(EXPR_POST_INC, $1, 0, 0);}
    | expr_lv_8_1 {$$ = $1;};

expr_lv_8_1: expr_lv_8_1 TOKEN_POST_DEC {$$ = expr_create(EXPR_POST_DEC, $1, 0, 0);}
    | expr_lv_9_0 {$$ = $1;};

expr_lv_9_0: grouping_expr {$$ = $1;};

grouping_expr: TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS {$$ = expr_create(EXPR_GROUPING, $2, 0, 0);}
    | expr_lv_9_1 {$$ = $1;};

expr_lv_9_1: arr_sub_expr {$$ = $1;};

arr_sub_expr: identifier arr_index_list {$$ = expr_create(EXPR_SUBSCRIPT, $1, $2, 0);}
    | expr_lv_9_2 {$$ = $1;};

arr_index_list: TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET arr_index_list {$$ = expr_create(EXPR_SUBSCRIPT, $2, $4, 0);}
    | TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET {$$ = $2;};

expr_lv_9_2: func_call_expr {$$ = $1;};

func_call_expr: identifier TOKEN_OPEN_PARENTHESIS expr_list_empty TOKEN_CLOSE_PARENTHESIS {$$ = expr_create(EXPR_CALL, $1, $3, 0);}
    | expr_lv_10_0 {$$ = $1;};

expr_list_empty: expr_list {$$ = $1;}
    | /* Nothing */ {$$ = 0;};

expr_list: expr TOKEN_COMMA expr_list {$$ = expr_create(EXPR_ARG, $1, $3, 0);}
    | expr {$$ = $1;};

expr_lv_10_0: literal {$$ = $1;}
    | identifier {$$ = $1;};

/* STATEMENTS */
stmt: if_only {$$ = $1;}
    | others {$$ = $1;};

/* BLOCK */
block: TOKEN_OPEN_BRACE stmt_list TOKEN_CLOSE_BRACE {$$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0);}
    | TOKEN_OPEN_BRACE TOKEN_CLOSE_BRACE {$$ = 0;};

stmt_list: stmt stmt_list {$1->next = $2; $$ = $1;}
    | stmt {$$ = $1;};

/* LOCAL DECLARATIONS */
local_decl: local_var_decl {$$ = $1;}
    | local_array_decl {$$ = $1;};

local_var_decl: identifier TOKEN_COLON global_var_type local_var_decl_optional {$$ = decl_create((char*) $1->name, $3, $4, 0, 0);};

local_var_decl_optional: TOKEN_ASSIGNMENT local_var_initializer TOKEN_SEMICOLON {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};

local_var_initializer: expr {$$ = $1;};

local_array_decl: identifier TOKEN_COLON expr_array_type_list local_array_decl_optional {$$ = decl_create((char*) $1->name, $3, $4, 0, 0);};

expr_array_type_list: expr_array_type expr_array_type_list {$$ = type_create(TYPE_ARRAY, $2, 0, $1);}
    | expr_array_type global_var_type {$$ = type_create(TYPE_ARRAY, $2, 0, $1);};

expr_array_type: TOKEN_ARRAY TOKEN_OPEN_BRACKET expr TOKEN_CLOSE_BRACKET {$$ = $3;}
    | TOKEN_ARRAY TOKEN_OPEN_BRACKET TOKEN_CLOSE_BRACKET {$$ = 0;};

local_array_decl_optional: TOKEN_ASSIGNMENT expr_array_literal TOKEN_SEMICOLON {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};

expr_array_literal: TOKEN_OPEN_BRACE expr_array_element_list TOKEN_CLOSE_BRACE {$$ = expr_create(EXPR_ARRAY_LITERAL, $2, 0, 0);};

expr_array_element_list: expr_array_element TOKEN_COMMA expr_array_element_list {$$ = expr_create(EXPR_ARG, $1, $3, 0);}
    | expr_array_element {$$ = $1;};

expr_array_element: expr_array_literal {$$ = $1;}
    | expr {$$ = $1;};

/* IF ELSE */
if_only: TOKEN_IF if_else_condition stmt {$$ = stmt_create(STMT_IF_ELSE, 0, 0, $2, 0, $3, 0, 0);}
    | TOKEN_IF if_else_condition others TOKEN_ELSE if_only {$$ = stmt_create(STMT_IF_ELSE, 0, 0, $2, 0, $3, $5, 0);}
    | for_header if_only {$1->body = $2; $$ = $1;};

others: TOKEN_IF if_else_condition others TOKEN_ELSE others {$$ = stmt_create(STMT_IF_ELSE, 0, 0, $2, 0, $3, $5, 0);}
    | expr TOKEN_SEMICOLON {$$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0, 0);}
    | block {$$ = $1;}
    | print {$$ = $1;}
    | return {$$ = $1;}
    | for_header others {$1->body = $2; $$ = $1;}
    | local_decl {$$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0);};

if_else_condition: TOKEN_OPEN_PARENTHESIS expr TOKEN_CLOSE_PARENTHESIS {$$ = $2;};

/* RETURN */
return: TOKEN_RETURN expr TOKEN_SEMICOLON {$$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0, 0);}
    | TOKEN_RETURN TOKEN_SEMICOLON {$$ = stmt_create(STMT_RETURN, 0, 0, 0, 0, 0, 0, 0);};

/* PRINT */
print: TOKEN_PRINT expr_list_empty TOKEN_SEMICOLON {$$ = stmt_create(STMT_PRINT, 0, 0, $2, 0, 0, 0, 0);};

/* FOR */
for_header: TOKEN_FOR empty_expr_after_open_paren empty_expr_after_semi empty_expr_after_semi TOKEN_CLOSE_PARENTHESIS {$$ = stmt_create(STMT_FOR, 0, $2, $3, $4, 0, 0, 0);};

empty_expr_after_open_paren: TOKEN_OPEN_PARENTHESIS expr {$$ = $2;}
    | TOKEN_OPEN_PARENTHESIS {$$ = 0;};

empty_expr_after_semi: TOKEN_SEMICOLON expr {$$ = $2;}
    | TOKEN_SEMICOLON {$$ = 0;};
%%

void yyerror (char const *s) {
    fprintf(stderr, "parse error: %s. ", s);
    fprintf(stderr, "Last token is: %s\n", strdup(yytext));
}
