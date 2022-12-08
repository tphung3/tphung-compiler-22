#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "symbol.h"

//max length of a symbol in assembly
static int MAX_LENGTH = 20;

struct symbol* symbol_create(symbol_t kind, struct type* type, char* name, int which)
{
    struct symbol* s = malloc(sizeof(*s));
    s->kind = kind;
    s->type = type;
    s->name = name;
    s->which = which;

    return s;
}

struct symbol* symbol_copy(struct symbol* s)
{
    if (!s)
        return 0;
    return symbol_create(s->kind, type_copy(s->type), strdup(s->name), s->which);
}

void symbol_delete(struct symbol* s)
{
    if (!s)
        return;
    type_delete(s->type);
    free(s->name);
    free(s);
}

const char* symbol_codegen(struct symbol* s)
{
    if (s->kind == SYMBOL_GLOBAL)
        return s->name;

    char* str = malloc(sizeof(*str) * MAX_LENGTH);
    sprintf(str, "-%d(\%rbp)", (s->which + 1) * 8);
    return str;
}
