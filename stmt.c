#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stmt.h"
#include "scope.h"
#include "codegen_helpers.h"

extern int resolve_fail;
extern int typecheck_fail;

extern int pos_in_stack;

extern int end_label_func;

extern char* outf;

extern char* register_arguments[];

int in_print_stmt = 0;

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
            decl_resolve(s->decl, pos_in_stack);
            ++pos_in_stack;
            break;
        case STMT_EXPR:
            expr_resolve(s->expr);
            break;
        case STMT_IF_ELSE:
            expr_resolve(s->expr);
            stmt_resolve(s->body, pos_in_stack);
            stmt_resolve(s->else_body, pos_in_stack);
            break;
        case STMT_FOR:
            expr_resolve(s->init_expr);
            expr_resolve(s->expr);
            expr_resolve(s->next_expr);
            stmt_resolve(s->body, pos_in_stack);
            break;
        case STMT_PRINT:
            expr_resolve(s->expr);
            break;
        case STMT_RETURN:
            expr_resolve(s->expr);
            break;
        case STMT_BLOCK:
            scope_enter();
            stmt_resolve(s->body, pos_in_stack);
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

static int count_num_args(struct stmt* s)
{
    struct expr* tmp_e = s->expr;
    int i = 0;
    while (tmp_e)
    {
        ++i;
        if (tmp_e->kind != EXPR_ARG)
            break;
        tmp_e = tmp_e->right;
        
    }
    return i;
}

void stmt_codegen(struct stmt* s)
{
    if (!s)
        return;

    FILE* f;
    struct expr* tmp_e;
    struct expr* true_e;
    struct type* true_e_type;
    switch (s->kind)
    {
        case STMT_DECL:
            decl_codegen(s->decl, SCOPE_LOCAL);
            break;
        case STMT_EXPR:
            expr_codegen(s->expr, SCOPE_LOCAL);
            scratch_free(s->expr->reg);
            break;
        case STMT_IF_ELSE:
            expr_codegen(s->expr, SCOPE_LOCAL);
            int else_label = label_create();
            int done_label = label_create();
            f = fopen(outf, "a");
            fprintf(f, "cmp $0, %s\n", scratch_name(s->expr->reg));
            scratch_free(s->expr->reg);
            fprintf(f, "je %s\n", label_name(else_label));
            fclose(f);
            stmt_codegen(s->body);
            f = fopen(outf, "a");
            fprintf(f, "jmp %s\n", label_name(done_label));
            fprintf(f, "%s:\n", label_name(else_label));
            fclose(f);
            stmt_codegen(s->else_body);
            f = fopen(outf, "a");
            fprintf(f, "%s:\n", label_name(done_label));
            fclose(f);
            break;
        case STMT_FOR:
            break;
        case STMT_PRINT:
            tmp_e = s->expr;
            in_print_stmt = 1;
            while (tmp_e)
            {
                if (tmp_e->kind == EXPR_ARG)
                {
                    true_e = tmp_e->left;
                }
                else
                    true_e = tmp_e;
                true_e_type = expr_typecheck(true_e);
                expr_codegen(true_e, SCOPE_LOCAL);
                f = fopen(outf, "a");
                fprintf(f, "movq %s, \%rdi\n", scratch_name(true_e->reg));
                scratch_free(true_e->reg);
                char* help_func;
                if (true_e_type->kind == TYPE_BOOLEAN)
                    help_func = strdup("boolean");
                else if (true_e_type->kind == TYPE_INTEGER)
                    help_func = strdup("integer");
                else if (true_e_type->kind == TYPE_STRING)
                    help_func = strdup("string");
                else if (true_e_type->kind == TYPE_CHARACTER)
                    help_func = strdup("character");
                fprintf(f, "pushq \%r10\npushq \%r11\ncall print_%s\npopq \%r11\npopq \%r10\n",help_func);
                fclose(f);
                if (tmp_e->kind == EXPR_ARG)
                    tmp_e = tmp_e->right;
                else
                    break;
            }
            in_print_stmt = 0;
            break;
        case STMT_RETURN:
            expr_codegen(s->expr, SCOPE_LOCAL);
            f = fopen(outf, "a");
            fprintf(f, "movq %s, \%rax\n", scratch_name(s->expr->reg));
            fprintf(f, "jmp %s\n", label_name(end_label_func));
            scratch_free(s->expr->reg);
            fclose(f);
            break;
        case STMT_BLOCK:
            stmt_codegen(s->body);
            break;
    }
    stmt_codegen(s->next);
}
