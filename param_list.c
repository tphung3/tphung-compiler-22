#include <stdlib.h>
#include <stdio.h>
#include "param_list.h"

struct param_list* param_list_create(char* name, struct type* type, struct param_list* next)
{
    struct param_list* pl = malloc(sizeof(*pl));
    pl->name = name;
    pl->type = type;
    pl->symbol = 0;
    pl->next = next;
    return pl;
}

void param_list_print(struct param_list* a)
{
    if (!a)
        return;
    printf("%s: ", a->name);
    type_print(a->type);
    if (!a->next)
        return;
    printf(", ");
    param_list_print(a->next);
    return;
}

void param_list_resolve(struct param_list* a, int which)
{
    if (!a)
        return;

    if (scope_lookup_current(a->name))
    {
        fprintf(stderr, "name %s is already defined in the current scope\n", a->name);
        param_list_resolve(a->next, ++which);
        return;
    }

    struct symbol* s = symbol_create(SYMBOL_PARAM, a->type, a->name, which);
    scope_bind(a->name, s);

    param_list_resolve(a->next, ++which);
}
