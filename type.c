#include <stdlib.h>
#include <stdio.h>
#include "type.h"

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
