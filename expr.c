#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

//array corresponding to expr_t enum in expr.h
expr_t precedence_level[] = {112, //function call
                            111, //array subscript
                            110, //grouping
                            101, //post decrement
                            100, //post increment
                            91, //logical not
                            90, //unary negation
                            80, //exponent
                            72, //modular
                            71, //division
                            70, //multiplication
                            61, //subtraction
                            60, //addition
                            55, //ne
                            54, //eq
                            53, //ge
                            52, //g
                            51, //le
                            50, //l
                            40, //logic and
                            30, //logic or
                            21, //ternary
                            20, //assign
                            0, //arg
                            200, //name
                            200, //integer_lit
                            200, //string_lit
                            200, //char_lit
                            200, //boolean_lit
                            200, //array_lit
                            };

struct expr* expr_create(expr_t kind, 
                        struct expr* L, 
                        struct expr* R,
                        struct expr* mid)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = kind;
    e->left = L;
    e->right = R;
    e->mid = mid;
    e->name = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_name(const char* n)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_NAME;
    e->name = n;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_integer_literal(int c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_INTEGER_LITERAL;
    e->literal_value = c;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_boolean_literal(int c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_BOOLEAN_LITERAL;
    e->literal_value = c;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_char_literal(char* c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_CHAR_LITERAL;
    e->literal_value = 0;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = c;
    return e;
}

struct expr* expr_create_string_literal(const char* s)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_STRING_LITERAL;
    e->string_literal = s;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    return e;
}

void expr_print(struct expr* e)
{
    if (!e)
        return;
   
    struct expr* tmp;
    int grouped = 0;

    if (e->kind == EXPR_NAME)
    {
        printf("%s", e->name);
        return;
    }
    else if (e->kind == EXPR_INTEGER_LITERAL)
    {
        printf("%d", e->literal_value);
        return;
    }
    else if (e->kind == EXPR_BOOLEAN_LITERAL)
    {
        if (e->literal_value)
            printf("true");
        else
            printf("false");
        return;
    }
    else if (e->kind == EXPR_STRING_LITERAL)
    {
        printf("%s", e->string_literal);
        return;
    }
    else if (e->kind == EXPR_CHAR_LITERAL)
    {
        printf("%s", e->string_literal);
        return;
    }
    else if (e->kind == EXPR_ARRAY_LITERAL)
    {
        printf("{");
        expr_print(e->left);
        printf("}");
        return;
    }
    else if (e->kind == EXPR_CALL)
    {
        expr_print(e->left);
        printf("(");
        expr_print(e->right);
        printf(")");
        return;
    }
    else if (e->kind == EXPR_SUBSCRIPT)
    {
        expr_print(e->left);
        printf("[");
        expr_print(e->right);
        printf("]");
        return;
    }
    else if (e->kind == EXPR_GROUPING)
    {
        while ((e->left) && (e->left->kind == EXPR_GROUPING))
        {
            e = e->left;
        }
        expr_print(e->left);
        return;
    }
    else if (e->kind == EXPR_POST_DEC)
    {
        unary_post_operator_print(e, "--");
        return;
    }
    else if (e->kind == EXPR_POST_INC)
    {
        unary_post_operator_print(e, "++");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_NOT)
    {
        unary_pre_operator_print(e, "!");
        return;
    }
    else if (e->kind == EXPR_SINGLE_SUB)
    {
        unary_pre_operator_print(e, "-");
        return;
    }
    else if (e->kind == EXPR_EXP)
    {
        binary_operator_print(e, "^");
        return;
    }
    else if (e->kind == EXPR_MOD)
    {
        binary_operator_print(e, "%");
        return;
    }
    else if (e->kind == EXPR_DIV)
    {   
        binary_operator_print(e, "/");
        return;
    }
    else if (e->kind == EXPR_MULT)
    {
        binary_operator_print(e, "*");
        return;
    }
    else if (e->kind == EXPR_SUB)
    {
        binary_operator_print(e, "-");
        return;      
    }
    else if (e->kind == EXPR_ADD)
    {
        binary_operator_print(e, "+");
        return;
    }
    else if (e->kind == EXPR_NOT_EQ)
    {
        binary_operator_print(e, "!=");
        return;
    }
    else if (e->kind == EXPR_EQ)
    {
        binary_operator_print(e, "==");
        return;
    }
    else if (e->kind == EXPR_GE)
    {
        binary_operator_print(e, ">=");
        return;
    }
    else if (e->kind == EXPR_GREATER)
    {
        binary_operator_print(e, ">");
        return;
    }
    else if (e->kind == EXPR_LE)
    {
        binary_operator_print(e, "<=");
        return;
    }
    else if (e->kind == EXPR_LESS)
    {
        binary_operator_print(e, "<");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_AND)
    {
        binary_operator_print(e, "&&");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_OR)
    {
        binary_operator_print(e, "||");
        return;
    }
    else if (e->kind == EXPR_TERNARY)
    {
        expr_print(e->left);
        printf("?");
        if (e->mid->kind == EXPR_TERNARY)
        {
            printf("(");
            expr_print(e->mid);
            printf(")");
        }
        else
        {
            expr_print(e->mid);
        }
        printf(":");
        if (e->right->kind == EXPR_TERNARY)
        {
            printf("(");
            expr_print(e->right);
            printf(")");
        }
        else
        {
            expr_print(e->right);
        }
        return;
    }
    else if (e->kind == EXPR_ASSIGN)
    {
        expr_print(e->left);
        printf(" = ");
        expr_print(e->right);
        return;
    }
    else if (e->kind == EXPR_ARG)
    {
        expr_print(e->left);
        printf(", ");
        expr_print(e->right);
        return;
    }
}

int right_higher_than_left(expr_t l, expr_t r)
{
    if (precedence_level[r] > precedence_level[l])
        return 1;
    return 0;
}

void binary_operator_print(struct expr* e, char* op)
{
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;
    }
    if (right_higher_than_left(e->left->kind, e->kind))
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    else
    {
        expr_print(e->left);
    }
    
    printf("%s", op);
    
    e->left = e->right;

    int grouped = 0;
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        grouped = 1;
        e->left = e->left->left;
    }

    if ((!right_higher_than_left(e->kind, e->left->kind)) && grouped)
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    else
    {
        expr_print(e->left);
    }
    return;   
}

void unary_pre_operator_print(struct expr* e, char* op)
{
    printf("%s", op);
    
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;   
    }
    if (right_higher_than_left(e->kind, e->left->kind))
    {
        expr_print(e->left);
    }
    else
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    return;
}

void unary_post_operator_print(struct expr* e, char* op)
{
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;   
    }
    if (right_higher_than_left(e->kind, e->left->kind))
    {
        expr_print(e->left);
    }
    else
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    
    printf("%s", op);
    
    return;
}

void expr_resolve(struct expr* e)
{
    if (!e)
        return;

    if (e->kind == EXPR_NAME)
    {
        struct symbol* s;
        s = scope_lookup(e->name);
        if (!s)
        {
            fprintf(stderr, "variable named %s isn't declared anywhere\n", e->name);
        }
        else
        {
            e->symbol = s;
        }
    }
    else
    {
        expr_resolve(e->left);
        expr_resolve(e->mid);
        expr_resolve(e->right);
    }
}
