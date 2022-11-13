#include "symbol.h"

struct symbol* symbol_create(symbol_t kind, struct type* type, char* name, int which)
{
    struct symbol* s = malloc(*s);
    s->kind = kind;
    s->type = type;
    s->name = name;
    s->which = which;

    return s;
}
