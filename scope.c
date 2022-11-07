#include "scope.h"

struct stack_scopes
{
    struct hash_table* arr;
    int length;
    int max_length;
};


static struct stack_scopes* global_stack = 0;

static void create_stack()
{
    global_stack = malloc(sizeof(*global_stack));
    global_stack->arr = calloc(MAX_SCOPES, sizeof(*arr));
    global_stack->length = 0;
    global_stack->max_length = MAX_SCOPES;
}

static void resize_stack()
{
    int new_max_scopes = global_stack->max_length * SCOPE_RATE;

    struct stack_scopes* new_global_stack = malloc(sizeof(*global_stack));
    new_global_stack->arr = calloc(new_max_scopes, sizeof(*arr));
    
    for (int i = 0; i < global_stack->length; ++i)
    {
        *((new_global_stack->arr) + i) = *((global_stack->arr) + i);
    }

    new_global_stack->length = global_stack->length;
    new_global_stack->max_length = new_max_scopes;
    global_stack = new_global_stack;
}

void scope_enter()
{
    if (!global_stack)
        create_stack();

    if (global_stack->length == global_stack->max_length)
        resize_stack();

    struct hash_table* ht = hash_table_create(0, 0);
    arr[global_stack->length] = ht;
    hash_table_delete(ht);
    ++global_stack->length;
}   

void scope_exit()
{
    if (global_stack->length == 1)
        printf("Cannot exit scope as already in global scope\n");
        exit(1);
    --global_stack->length;
}

int scope_level()
{
    if (!global_stack)
        scope_enter();
    return global_stack->length;
}

void scope_bind(const char* name, struct symbol* sym)
{
    hash_table_insert((global_stack->arr) + length - 1, name, (const void *) sym);
}

struct symbol* scope_lookup(const char* name)
{
    int l = global_stack->length;
    struct symbol* ret;
    for (int i = l - 1; i > -1; --i)
    {
        if (!(ret = hash_table_lookup((global->stack->arr) + i, name)))
        {
            return ret;
        }
    }
    return 0;
}

struct symbol* scope_lookup_current(const char* name)
{
    if (!global_stack)
        scope_enter();
    struct symbol* ret;
    if (!(ret = hash_table_lookup((global->stack->arr) + global->stack->length - 1, name)))
        {
            return ret;
        }
    return 0;
}
