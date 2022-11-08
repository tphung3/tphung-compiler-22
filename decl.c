#include <stdio.h>
#include <stdlib.h>
#include "decl.h"
#include "symbol.h"

struct decl* decl_create(char* name, struct type* type, struct expr* value, struct stmt* code, struct symbol* symbol, struct decl* next)
{
    struct decl* d = malloc(sizeof(*d));
    d->name = name;
    d->type = type;
    d->value = value;
    d->code = code;
    d->symbol = symbol;
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

void decl_resolve(struct decl* d)
{
    if (!d)
        return;

    if (scope_lookup_current(d->name))
    {
        fprintf(stderr, "Variable named %s is already declared in the current scope of level %d\n", d->name, scope_level());
        decl_resolve(d->next);
        return;
    }
    
    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    struct symbol* s = symbol_create(kind, d->type, d->name, 0);
    scope_bind(d->name, s);

    if (d->value)
    {
        expr_resolve(d->value);
    }

    if (d->code)
    {
        scope_enter();
        param_list_resolve(d->type->params, 1);
        stmt_resolve(d->code);        
        scope_exit();
    }
    decl_resolve(d->next);
}
