#ifndef SCOPE_H
#define SCOPE_H

#include "hash_table.h"
#include "symbol.h"

#define MAX_SCOPES 127
#define SCOPE_RATE 2

typedef enum
{
    SCOPE_GLOBAL,
    SCOPE_LOCAL
} scope_t;

void scope_enter();
void scope_exit();
int scope_level();

void scope_bind(const char* name, struct symbol* sym);
struct symbol* scope_lookup(const char* name);
struct symbol* scope_lookup_current(const char* name);

#endif
