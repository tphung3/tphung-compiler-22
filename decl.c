#include <stdio.h>
#include <stdlib.h>
#include "decl.h"

struct decl* decl_create(char* name, struct type* type, struct expr* value, struct stmt* code, struct decl* next)
{
    struct decl* d = malloc(sizeof(*d));
    d->name = name;
    d->type = type;
    d->value = value;
    d->code = code;
    d->next = next;
    return d;
}

void decl_print(struct decl* d, int indent)
{
    if (!d)
        return;
    int i;
    
    printf("%s: ", d->name);
    type_print(d->type);
    
    if (d->value)
    {
        printf(" = ");
        expr_print(d->value);
        printf(";\n");
    }
    else if (d->code)
    {
        printf(" =\n");
        stmt_print(d->code, indent);
        printf("\n");
    }
    else
    {
        printf(";\n");
    }
    
    decl_print(d->next, indent);
}
