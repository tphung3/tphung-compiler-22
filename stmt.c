#include <stdlib.h>
#include <stdio.h>
#include "stmt.h"

extern int resolve_fail;
extern int typecheck_fail;

struct stmt* stmt_create(stmt_t kind, 
                        struct decl *decl, 
                        struct expr *init_expr, 
                        struct expr *expr, 
                        struct expr *next_expr, 
                        struct stmt *body, 
                        struct stmt *else_body, 
                        struct stmt *next)
{
    struct stmt* s = malloc(sizeof(*s));
    s->kind = kind;
    s->decl = decl;
    s->init_expr = init_expr;
    s->expr = expr;
    s->next_expr = next_expr;
    s->body = body;
    s->else_body = else_body;
    s->next = next;
    return s;
}

void stmt_print(struct stmt* s, int indent)
{
    if (!s)
        return;
    
    int i;
    for (i = 0; i < indent; ++i)
        printf("\t");
    if (s->kind == STMT_DECL)
    {
        decl_print(s->decl, indent);
    }
    else if (s->kind == STMT_EXPR)
    {
        expr_print(s->expr);
        printf(";\n");
    }
    else if (s->kind == STMT_IF_ELSE)
    {
        printf("if (");
        expr_print(s->expr);
        printf(")\n");
        if (s->body->kind != STMT_BLOCK)
        {
            stmt_print(s->body, indent+1);
        }
        else
        {
            stmt_print(s->body, indent);
        }
        if (s->else_body)
        {
            for (i = 0; i < indent; ++i)
                printf("\t");
            printf("else\n");
            if (s->else_body->kind != STMT_BLOCK)
                stmt_print(s->else_body, indent+1);
            else
                stmt_print(s->else_body, indent);
        }
    }
    else if (s->kind == STMT_FOR)
    {
        printf("for (");
        expr_print(s->init_expr);
        printf("; ");
        expr_print(s->expr);
        printf("; ");
        expr_print(s->next_expr);
        printf(")\n");
        if (s->body->kind != STMT_BLOCK)
            stmt_print(s->body, indent+1);
        else
            stmt_print(s->body, indent);    
    }
    else if (s->kind == STMT_PRINT)
    {
        printf("print ");
        expr_print(s->expr);
        printf(";\n");
    }
    else if (s->kind == STMT_RETURN)
    {
        printf("return ");
        expr_print(s->expr);
        printf(";\n");
    }
    else if (s->kind == STMT_BLOCK)
    {
        printf("{\n");
        stmt_print(s->body, indent+1);
        for (i = 0; i < indent; ++i)
            printf("\t");
        printf("}\n");
    }
    stmt_print(s->next, indent);
    return;
}

void stmt_resolve(struct stmt* s, int which)
{
    if (!s)
        return;

    switch (s->kind)
    {
        case STMT_DECL:
            decl_resolve(s->decl, which);
            ++which;
            break;
        case STMT_EXPR:
            expr_resolve(s->expr);
            break;
        case STMT_IF_ELSE:
            expr_resolve(s->expr);
            stmt_resolve(s->body, 0);
            stmt_resolve(s->else_body, 0);
            break;
        case STMT_FOR:
            expr_resolve(s->init_expr);
            expr_resolve(s->expr);
            expr_resolve(s->next_expr);
            stmt_resolve(s->body, 0);
            break;
        case STMT_PRINT:
            expr_resolve(s->expr);
            break;
        case STMT_RETURN:
            expr_resolve(s->expr);
            break;
        case STMT_BLOCK:
            scope_enter();
            stmt_resolve(s->body, 0);
            scope_exit();
            break;
    }
    stmt_resolve(s->next, which);
}


void stmt_typecheck(struct stmt* s, struct symbol* sym)
{
    if (!s)
       return;

    switch (s->kind)
    {
    case STMT_DECL:
        decl_typecheck(s->decl);
        break;
    case STMT_EXPR:
        expr_typecheck(s->expr);
        break;
    case STMT_IF_ELSE:
        if (!type_equals(expr_typecheck(s->expr), type_create(TYPE_BOOLEAN, 0, 0, 0)))
        {
            printf("type error: expression ");
            expr_print(s->expr);
            printf(" of type ");
            type_print(expr_typecheck(s->expr)); 
            printf(" is not of type boolean in an if else statement\n");
            typecheck_fail = 1;
        }
        stmt_typecheck(s->body, sym);
        stmt_typecheck(s->else_body, sym);
        break;
    case STMT_FOR:
        expr_typecheck(s->init_expr);
        expr_typecheck(s->expr);
        expr_typecheck(s->next_expr);
        stmt_typecheck(s->body, sym);
        break;
    case STMT_PRINT:
        expr_typecheck(s->expr);
        break;
    case STMT_RETURN:
        if (sym->type->subtype->kind == TYPE_AUTO)
        {
            if (!s->expr)
            {
                sym->type->subtype->kind = TYPE_VOID;               
                printf("notice: function %s that returns type auto now returns type void\n", sym->name);
            }
            else
            {
                struct type* tmp_t = expr_typecheck(s->expr);
                if (tmp_t->kind == TYPE_ARRAY || tmp_t->kind == TYPE_FUNCTION)
                {
                    printf("type error: function %s cannot have a return statement that has a return type ", sym->name);
                    type_print(tmp_t);
                    printf(" , so setting its return type to TYPE_INTEGER instead\n");
                    sym->type->subtype->kind = TYPE_INTEGER;
                    typecheck_fail = 1;
                }
                else
                {
                    if (tmp_t->kind == TYPE_ARRAY || tmp_t->kind == TYPE_FUNCTION || tmp_t->kind == TYPE_AUTO)
                    {
                        printf("type error: cannot return expression ");
                        expr_print(s->expr);
                        printf(" of type ");
                        type_print(tmp_t);
                        printf("\n");
                        typecheck_fail = 1;
                    }
                    else
                    {
                        sym->type->subtype->kind = tmp_t->kind;
                        printf("notice: function %s that returns type auto now returns type ", sym->name);
                        type_print(tmp_t);
                        printf("\n");
                    }
                }
            }
        }
        if (s->expr)
        {
            struct type* tmp_t = expr_typecheck(s->expr);
            if (!type_equals(tmp_t, sym->type->subtype))
            {
                printf("type error: function %s of return type ", sym->name);
                type_print(sym->type->subtype);
                printf(" cannot have a return statement return expression ");
                expr_print(s->expr);
                printf(" of type ");
                type_print(tmp_t);
                printf("\n");
                typecheck_fail = 1;
            }
            else if (tmp_t->kind == TYPE_ARRAY || tmp_t->kind == TYPE_FUNCTION || tmp_t->kind == TYPE_AUTO)
            {
                printf("type error: cannot return expression ");
                expr_print(s->expr);
                printf(" of type ");
                type_print(tmp_t);
                printf("\n");
                typecheck_fail = 1;
            }
        }
        else
        {
            if (sym->type->subtype->kind == TYPE_VOID)
                ;
            else
            {
                printf("type error: function %s of return type ", sym->name);
                type_print(sym->type->subtype);
                printf(" cannot have a return statement return nothing\n");
                typecheck_fail = 1;
            }
        }
        break;
    case STMT_BLOCK:
        scope_enter();
        stmt_typecheck(s->body, sym);
        scope_exit();
        break;
    } 
    stmt_typecheck(s->next, sym);
}
