#include <stdlib.h>
#include <stdio.h>
#include "stmt.h"

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
