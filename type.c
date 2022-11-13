#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "expr.h"

extern int resolve_fail;

extern int typecheck_fail;

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params, struct expr* expr)
{
    struct type* t = malloc(sizeof(*t));
    t->kind = kind;
    t->subtype = subtype;
    t->expr = expr;
    t->params = params;
    return t;
}

void type_print( struct type *t )
{
    if (!t)
        return;
    
    switch (t->kind)
    {
        case TYPE_VOID:
            printf("void");
            return;
        case TYPE_BOOLEAN:
            printf("boolean");
            return;
        case TYPE_CHARACTER:
            printf("char");
            return;
        case TYPE_INTEGER:
            printf("integer");
            return;
        case TYPE_STRING:
            printf("string");
            return;
        case TYPE_AUTO:
            printf("auto");
            return;
        case TYPE_ARRAY:
            printf("array [");
            expr_print(t->expr);
            printf("] ");
            type_print(t->subtype);
            return;
        case TYPE_FUNCTION:
            printf("function ");
            type_print(t->subtype);
            printf(" (");
            param_list_print(t->params);
            printf(")");
            return;
    }   
}

int type_equals(struct type* a, struct type* b)
{
    if (!a && !b)
        return 1;
    
    if (!a || !b)
        return 0;

    if (a->kind == b->kind)
    {
        if (a->kind == TYPE_ARRAY && a->expr->literal_value == b->expr->literal_value)
            return type_equals(a->subtype, b->subtype);
        else if (a->kind == TYPE_FUNCTION)
            return type_equals(a->subtype, b->subtype) && param_list_equals(a->params, b->params);
        else if (a->kind == TYPE_AUTO) //auto means uninitialized value -> not equal type
            return 0;
        else
            return 1;   //any other type is equal   
    }
    else
        return 0;
}

struct type* type_copy(struct type* t)
{
    if (!t)
        return 0;
    return type_create(t->kind, type_copy(t->subtype), param_list_copy(t->params), expr_copy(t->expr));
}

void type_delete(struct type* t)
{
    if (!t)
        return;
    type_delete(t->subtype);
    param_list_delete(t->params);
    expr_delete(t->expr);
    free(t);
}

int type_array_check_valid(struct type* t)
{
    if (!t)
    {
        printf("type error: array have no type to check\n");
        typecheck_fail = 1;
        return 0;
    }
    while (t->subtype)
    {
        if (t->kind == TYPE_ARRAY && t->expr && t->expr->kind == EXPR_INTEGER_LITERAL)
            t = t->subtype;
        else
        {
            if (t->kind != TYPE_ARRAY)
            {
                printf("type error: array is of type ");
                type_print(t);
                printf(" instead of type array\n");
            }
            if (t->expr->kind == EXPR_INTEGER_LITERAL)
            {
                printf("type error: size of array must be fixed, i.e., an integer literal, isntead of type ");
                type_print(expr_typecheck(t->expr));
                printf("\n");
            }
            return 0;
        }
    }
    if (t->kind == TYPE_BOOLEAN || t->kind == TYPE_CHARACTER || t->kind == TYPE_INTEGER || t->kind == TYPE_STRING || t->kind == TYPE_AUTO)
        return 1;
    else 
    {
        printf("primitive type of array is ");
        type_print(t);
        printf(" so it is invalid\n");
        return 0;
    }
}

struct type* get_atomic_type_array(struct type* t)
{
    if (!t)
        return 0;

    while (t->subtype)
    {
        if (t->kind == TYPE_ARRAY)
            t = t->subtype;
        else
            return 0;
    }
    return type_create(t->kind, 0, 0, 0);
}

int set_atomic_type_array(struct type* t, type_t kind)
{
    if (!t)
        return 0;

    while (t->subtype)
    {
        if (t->kind == TYPE_ARRAY)
            t = t->subtype;
        else
            return 0;
    }
    t->kind = kind;
    return 1;
}

int type_function_check_valid(struct type* t)
{
    if (t->subtype->kind == TYPE_ARRAY || t->subtype->kind == TYPE_FUNCTION)
    {
        printf("type error: function cannot return type ");
        type_print(t->subtype);
        typecheck_fail = 1;
        printf("\n");
        return 0;
    }
    struct param_list* tmp_param = t->params;
    while (tmp_param)
    {
        if (tmp_param->type->kind == TYPE_FUNCTION || tmp_param->type->kind == TYPE_VOID || tmp_param->type->kind == TYPE_AUTO)
        {
            typecheck_fail = 1;
            printf("type error: function cannot have parameter %s of type ", tmp_param->name);
            type_print(tmp_param->type);
            printf("\n");
            return 0;
        }
        tmp_param = tmp_param->next;
    }
    return 1;
}

int type_normal_check_valid(struct type* t)
{
    if (t->kind == TYPE_VOID || t->kind == TYPE_ARRAY || t->kind == TYPE_FUNCTION)
    {
        printf("type error: cannot declare a variable of type ");
        type_print(t);
        printf("\n");
        typecheck_fail = 1;
        return 0;
    }
    return 1;
}
