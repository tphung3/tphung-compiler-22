#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "param_list.h"
#include "type.h"
#include "symbol.h"

extern int resolve_fail;
extern int typecheck_fail;

struct param_list* param_list_create(char* name, struct type* type, struct symbol* symbol, struct param_list* next)
{
    struct param_list* pl = malloc(sizeof(*pl));
    pl->name = name;
    pl->type = type;
    pl->symbol = symbol;
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
        fprintf(stderr, "resolve error: name %s is already defined in the current scope\n", a->name);
        resolve_fail = 1;
        param_list_resolve(a->next, ++which);
        return;
    }

    struct symbol* s = symbol_create(SYMBOL_PARAM, a->type, a->name, which);
    scope_bind(a->name, s);
    a->symbol = s;
    printf("%s is declared as a parameter with position %d\n", a->name, which);
    param_list_resolve(a->next, ++which);
}

struct param_list* param_list_copy(struct param_list* p)
{
    if (!p)
        return 0;
    return param_list_create(strdup(p->name), type_copy(p->type), symbol_copy(p->symbol), param_list_copy(p->next));
}

int param_list_equals(struct param_list* p1, struct param_list* p2)
{
    if (!p1 && !p2)
        return 1;
    if (!p1 || !p2)
        return 0;
    if (type_equals(p1->type, p2->type) && param_list_equals(p1->next, p2->next))
        return 1;
    return 0;
}

void param_list_delete(struct param_list* p)
{
    if (!p)
        return;
    free(p->name);
    type_delete(p->type);
    symbol_delete(p->symbol);
    param_list_delete(p->next);
    free(p);
}
