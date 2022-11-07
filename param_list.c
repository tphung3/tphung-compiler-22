#include <stdlib.h>
#include <stdio.h>
#include "param_list.h"

struct param_list* param_list_create(char* name, struct type* type, struct param_list* next)
{
    struct param_list* pl = malloc(sizeof(*pl));
    pl->name = name;
    pl->type = type;
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