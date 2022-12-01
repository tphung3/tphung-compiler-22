#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "symbol.h"
#include "expr.h"

extern int resolve_fail;
extern int typecheck_fail;

//create a decl
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

//print a decl
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

static void decl_func_resolve(struct decl* d, struct symbol* s)
{
    d->symbol = s;
    scope_enter();
    param_list_resolve(d->type->params, 0);
    stmt_resolve(d->code, 0);        
    scope_exit();   
    decl_resolve(d->next, which);
    return;
}

//resolve name in decl
void decl_resolve(struct decl* d, int which)
{
    if (!d)
        return;
    
    //lookup if name already exists
    struct symbol* first_s = scope_lookup_current(d->name);
    
    if (first_s && first_s->which == -1)    //function already defined
    {
        if (d->code)    //redefine means error
        {
            printf("resolve error: %s is a function already defined in the current scope of level %d and cannot be redefined\n", d->name, scope_level());
            resolve_fail = 1;
            decl_resolve(d->next, which);
            return;
        }
        else
        {
            if (type_equals(first_s->type, d->type))    //redeclare of same type is ok
            {
                d->symbol = first_s;
                scope_enter();
                param_list_resolve(d->type->params, 0);
                stmt_resolve(d->code, 0);        
                scope_exit();   
                decl_resolve(d->next, which);
                return;
            }
            else    //redeclare with different type is error
            {
                printf("type error: function named %s was declared with type ", first_s->name);
                type_print(first_s->type);
                printf(" but is attempted to be defined with type ");
                type_print(d->type);
                printf("\n");
                resolve_fail = 1;
                decl_resolve(d->next, which);
                return;
            }
        }
    }
    else if (first_s && first_s->which == -2)   //function only declared
    {
        if (d->code)    //if decl has code
        {
            if (!type_equals(first_s->type, d->type))
            {
                printf("type error: function named %s was declared with type ", first_s->name);
                type_print(first_s->type);
                printf(" but is attempted to be defined with type ");
                type_print(d->type);
                printf("\n");
                resolve_fail = 1;
                decl_resolve(d->next, which);
                return;
            }
            else
            {
                d->symbol = first_s;
                first_s->which = -1;
                printf("%s was declared as a function and is now defined with code\n", first_s->name);
                scope_enter();
                param_list_resolve(d->type->params, 0);
                stmt_resolve(d->code, 0);        
                scope_exit();   
                decl_resolve(d->next, which);            
                return;
            }
            
        }  
        else if (d->type->kind == TYPE_FUNCTION)    //if redeclare a function
        {
            if (!type_equals(first_s->type, d->type)) 
            {
                printf("type error: function named %s was declared with type ", first_s->name);
                type_print(first_s->type);
                printf(" but is attempted to be re-declared with type ");
                type_print(d->type);
                printf("\n");
                resolve_fail = 1;
                decl_resolve(d->next, which);
                return;
            }
            else    //okay w function redeclaration
            {
                d->symbol = first_s;
                scope_enter();
                param_list_resolve(d->type->params, 0);
                stmt_resolve(d->code, 0);        
                scope_exit();   
                decl_resolve(d->next, which);
                return;
            }
        }
        else    //attempted to reuse name already used for a function
        {
            printf("resolve error: %s is a function already declared in the current scope of level %d\n", d->name, scope_level());
            resolve_fail = 1;
            decl_resolve(d->next, which);
            return;
        }
    }

    if (first_s)    //not a function decl so local/global var/arr decl
    {
        printf("resolve error: %s is already declared in the current scope of level %d\n", d->name, scope_level());
        resolve_fail = 1;
        decl_resolve(d->next, which);
        return;
    }
    
    //create symbol and add to scope and decl struct
    symbol_t kind = scope_level() > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    struct symbol* s = symbol_create(kind, d->type, d->name, which);
    d->symbol = s;
    scope_bind(d->name, s);

    char* kind_str;
    if (scope_level() == 1)
        kind_str = strdup("global");
    else
        kind_str = strdup("local");
    if (!scope_lookup(d->name))
        printf("cannot find %s in decl\n", d->name);
    else
    {
        if (kind == SYMBOL_GLOBAL)
            printf("%s is declared and stored as %s %s\n", s->name, kind_str, s->name);
        else
            printf("%s is declared and stored as %s %d\n", s->name, kind_str, which);
    }
    if (d->value)
    {
        expr_resolve(d->value);
    }

    if (d->type->kind == TYPE_FUNCTION) //if new function
    {
        scope_enter();
        param_list_resolve(d->type->params, 0);
        if (d->code)
        {
            s->which = -1;
            stmt_resolve(d->code, 0);
        }
        else
            s->which = -2;
        scope_exit();
    }
    
    if (scope_level() == 1)
        decl_resolve(d->next, which);
    else
        decl_resolve(d->next, ++which);
}

void decl_typecheck(struct decl* d)
{
    if (!d)
        return;

    struct type* t;
    if (d->symbol->kind == SYMBOL_GLOBAL)
    {
        if (d->symbol->type->kind == TYPE_ARRAY)    //global array
        {
            if (type_array_check_valid(d->symbol->type))    //check if array's type is allowed, i.e., check if it is actually an array of type {boolean, char, integer, string, auto} and is initialized with fixed size
            {
                if (d->value && expr_global_array_check_valid(d->value, d->symbol)) //check initializer of array is constant, if array is auto assign its symbol too
                {
                    t = expr_typecheck(d->value);
                    if (type_equals(d->symbol->type, t))
                    {
                        ;   //check next decl
                    }
                    else
                    {
                        printf("type error: cannot define global variable %s of type ", d->name);
                        type_print(d->symbol->type);
                        printf(" to expression ");
                        expr_print(d->value);
                        printf(" of type ");
                        type_print(t);
                        typecheck_fail = 1;
                        printf("\n");
                    }
                }
                else
                {
                    if (!d->value)
                        ;   //check next decl
                    //global array check valid is false, and its error message is already handled
                    ;   //so move to check next decl
                }
            }
            else
            {
                //assume type array check valid already prints error message so move on to check next decl
                ; 
            } 
        }
        else if (d->symbol->type->kind == TYPE_FUNCTION)
        {
            if (type_function_check_valid(d->symbol->type))    //check if function's type is allowed
            {
                if (d->code)
                {
                    stmt_typecheck(d->code, d->symbol);   //check return type, if function's return type is auto then set it too
                }
                else
                {
                    //if function doesn't have code then just move on to next decl
                    ;
                }
            }
            else
            {
                //type_function_check_valid already prints error message so move on to next decl
                ;
            }
        }
        else
        {
            if (type_normal_check_valid(d->symbol->type))   //check if variable has valid types
            {
                if (d->value)
                {
                    if (d->value->kind != EXPR_INTEGER_LITERAL && d->value->kind != EXPR_STRING_LITERAL && d->value->kind != EXPR_CHAR_LITERAL && d->value->kind != EXPR_BOOLEAN_LITERAL)
                    {
                        printf("type error: global variable %s must be initialized with constants\n", d->name);
                        typecheck_fail = 1;
                    }
                    else
                    {
                        t = expr_typecheck(d->value);

                        if (d->symbol->type->kind == TYPE_AUTO) //set type of variable if it is auto
                        {
                            if (t->kind == TYPE_VOID || t->kind == TYPE_ARRAY || t->kind == TYPE_FUNCTION || t->kind == TYPE_AUTO)
                            {
                                printf("type error: cannot assign local variable %s of type auto to expression ", d->name);
                                expr_print(d->value);
                                printf(" of type ");
                                type_print(t);
                                printf("\n");
                                typecheck_fail = 1;
                            }
                            else
                            {
                                printf("notice: global variable %s had type auto and now has type ", d->name);
                                d->symbol->type->kind = t->kind;
                                type_print(d->symbol->type);
                                printf("\n");
                            }
                        }
                        if (type_equals(d->symbol->type, t))
                        {
                            //if type is equal, move on to next decl
                            ;
                        }
                        else if (d->symbol->type->kind == TYPE_AUTO)
                        {
                            d->symbol->type = t;
                        }
                        else
                        {
                            printf("type error: cannot define global variable %s of type ", d->name);
                            type_print(d->symbol->type);
                            printf(" to expression ");
                            typecheck_fail = 1;
                            expr_print(d->value);
                            printf(" of type ");
                            type_print(t);
                            printf("\n");
                        }                   
                    }

                }    
            }
            else
            {
                printf("type error: cannot have global variable %s of type ");
                type_print(d->symbol->type);
                typecheck_fail = 1;
                printf("\n");
            }
        }
    }    
    else if (d->symbol->kind == SYMBOL_LOCAL)
    {
        if (d->symbol->type->kind == TYPE_ARRAY)
        {
            if (type_array_check_valid(d->symbol->type))    //check if array's type is allowed
            {
                if (d->value)
                {
                    printf("type error: local array named %s cannot be initialized\n", d->name);
                    typecheck_fail = 1;
                }
                else
                {
                    //all good, move to next decl
                    ;
                }
            }
            else
            {
                printf("type error: cannot have local array %s of type ");
                typecheck_fail = 1;
                type_print(d->symbol->type);
                printf("\n");
            } 
        }       
        else    //local
        {
            if (type_normal_check_valid(d->symbol->type))
            {
                if (d->value)
                {
                    t = expr_typecheck(d->value);
                    if (type_equals(d->symbol->type, t))
                    {
                        ;
                    }
                    else if (d->symbol->type->kind == TYPE_AUTO)
                    {
                        if (t->kind == TYPE_VOID || t->kind == TYPE_ARRAY || t->kind == TYPE_FUNCTION || t->kind == TYPE_AUTO)
                        {
                            printf("type error: cannot assign local variable %s of type auto to expression ", d->name);
                            expr_print(d->value);
                            printf(" of type ");
                            type_print(t);
                            printf("\n");
                            typecheck_fail = 1;
                        }
                        else
                        {    
                            printf("notice: local variable %s had type auto and now has type ", d->name);
                            d->symbol->type->kind = t->kind;
                            type_print(d->symbol->type);
                            printf("\n");
                        }
                    }
                    else
                    {
                        printf("type error: cannot define local variable %s of type ", d->name);
                        type_print(d->symbol->type);
                        typecheck_fail = 1;
                        printf(" to expression ");
                        expr_print(d->value);
                        printf(" of type ");
                        type_print(t);
                        printf("\n");
                    }
                }    
            }
            else
            {
                printf("type error: cannot have local variable %s of type ");
                type_print(d->symbol->type);
                typecheck_fail = 1;
                printf("\n");
            }
        }
    } 
    decl_typecheck(d->next);
}

void decl_codegen(struct decl* d)
{
    return;
}
