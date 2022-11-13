#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "expr.h"

extern int resolve_fail;
extern int typecheck_fail;

//array corresponding to expr_t enum in expr.h
expr_t precedence_level[] = {112, //function call
                            111, //array subscript
                            110, //grouping
                            101, //post decrement
                            100, //post increment
                            91, //logical not
                            90, //unary negation
                            80, //exponent
                            72, //modular
                            71, //division
                            70, //multiplication
                            61, //subtraction
                            60, //addition
                            55, //ne
                            54, //eq
                            53, //ge
                            52, //g
                            51, //le
                            50, //l
                            40, //logic and
                            30, //logic or
                            21, //ternary
                            20, //assign
                            0, //arg
                            200, //name
                            200, //integer_lit
                            200, //string_lit
                            200, //char_lit
                            200, //boolean_lit
                            200, //array_lit
                            };

struct expr* expr_create(expr_t kind, 
                        struct expr* L, 
                        struct expr* R,
                        struct expr* mid)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = kind;
    e->left = L;
    e->right = R;
    e->mid = mid;
    e->name = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_name(const char* n)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_NAME;
    e->name = n;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_integer_literal(int c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_INTEGER_LITERAL;
    e->literal_value = c;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_boolean_literal(int c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_BOOLEAN_LITERAL;
    e->literal_value = c;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = NULL;
    return e;
}

struct expr* expr_create_char_literal(char* c)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_CHAR_LITERAL;
    e->literal_value = 0;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->string_literal = c;
    return e;
}

struct expr* expr_create_string_literal(const char* s)
{
    struct expr* e = malloc(sizeof(*e));
    e->kind = EXPR_STRING_LITERAL;
    e->string_literal = s;
    e->name = NULL;
    e->left = NULL;
    e->right = NULL;
    e->mid = NULL;
    e->symbol = NULL;
    e->literal_value = 0;
    return e;
}

void expr_print(struct expr* e)
{
    if (!e)
        return;
   
    struct expr* tmp;
    int grouped = 0;

    if (e->kind == EXPR_NAME)
    {
        printf("%s", e->name);
        return;
    }
    else if (e->kind == EXPR_INTEGER_LITERAL)
    {
        printf("%d", e->literal_value);
        return;
    }
    else if (e->kind == EXPR_BOOLEAN_LITERAL)
    {
        if (e->literal_value)
            printf("true");
        else
            printf("false");
        return;
    }
    else if (e->kind == EXPR_STRING_LITERAL)
    {
        printf("%s", e->string_literal);
        return;
    }
    else if (e->kind == EXPR_CHAR_LITERAL)
    {
        printf("%s", e->string_literal);
        return;
    }
    else if (e->kind == EXPR_ARRAY_LITERAL)
    {
        printf("{");
        expr_print(e->left);
        printf("}");
        return;
    }
    else if (e->kind == EXPR_CALL)
    {
        expr_print(e->left);
        printf("(");
        expr_print(e->right);
        printf(")");
        return;
    }
    else if (e->kind == EXPR_SUBSCRIPT)
    {
        expr_print(e->left);
        printf("[");
        expr_print(e->right);
        printf("]");
        return;
    }
    else if (e->kind == EXPR_GROUPING)
    {
        while ((e->left) && (e->left->kind == EXPR_GROUPING))
        {
            e = e->left;
        }
        expr_print(e->left);
        return;
    }
    else if (e->kind == EXPR_POST_DEC)
    {
        unary_post_operator_print(e, "--");
        return;
    }
    else if (e->kind == EXPR_POST_INC)
    {
        unary_post_operator_print(e, "++");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_NOT)
    {
        unary_pre_operator_print(e, "!");
        return;
    }
    else if (e->kind == EXPR_SINGLE_SUB)
    {
        unary_pre_operator_print(e, "-");
        return;
    }
    else if (e->kind == EXPR_EXP)
    {
        binary_operator_print(e, "^");
        return;
    }
    else if (e->kind == EXPR_MOD)
    {
        binary_operator_print(e, "%");
        return;
    }
    else if (e->kind == EXPR_DIV)
    {   
        binary_operator_print(e, "/");
        return;
    }
    else if (e->kind == EXPR_MULT)
    {
        binary_operator_print(e, "*");
        return;
    }
    else if (e->kind == EXPR_SUB)
    {
        binary_operator_print(e, "-");
        return;      
    }
    else if (e->kind == EXPR_ADD)
    {
        binary_operator_print(e, "+");
        return;
    }
    else if (e->kind == EXPR_NOT_EQ)
    {
        binary_operator_print(e, "!=");
        return;
    }
    else if (e->kind == EXPR_EQ)
    {
        binary_operator_print(e, "==");
        return;
    }
    else if (e->kind == EXPR_GE)
    {
        binary_operator_print(e, ">=");
        return;
    }
    else if (e->kind == EXPR_GREATER)
    {
        binary_operator_print(e, ">");
        return;
    }
    else if (e->kind == EXPR_LE)
    {
        binary_operator_print(e, "<=");
        return;
    }
    else if (e->kind == EXPR_LESS)
    {
        binary_operator_print(e, "<");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_AND)
    {
        binary_operator_print(e, "&&");
        return;
    }
    else if (e->kind == EXPR_LOGICAL_OR)
    {
        binary_operator_print(e, "||");
        return;
    }
    else if (e->kind == EXPR_TERNARY)
    {
        expr_print(e->left);
        printf("?");
        if (e->mid->kind == EXPR_TERNARY)
        {
            printf("(");
            expr_print(e->mid);
            printf(")");
        }
        else
        {
            expr_print(e->mid);
        }
        printf(":");
        if (e->right->kind == EXPR_TERNARY)
        {
            printf("(");
            expr_print(e->right);
            printf(")");
        }
        else
        {
            expr_print(e->right);
        }
        return;
    }
    else if (e->kind == EXPR_ASSIGN)
    {
        expr_print(e->left);
        printf(" = ");
        expr_print(e->right);
        return;
    }
    else if (e->kind == EXPR_ARG)
    {
        expr_print(e->left);
        printf(", ");
        expr_print(e->right);
        return;
    }
}

int right_higher_than_left(expr_t l, expr_t r)
{
    if (precedence_level[r] > precedence_level[l])
        return 1;
    return 0;
}

void binary_operator_print(struct expr* e, char* op)
{
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;
    }
    if (right_higher_than_left(e->left->kind, e->kind))
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    else
    {
        expr_print(e->left);
    }
    
    printf("%s", op);
    
    e->left = e->right;

    int grouped = 0;
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        grouped = 1;
        e->left = e->left->left;
    }

    if ((!right_higher_than_left(e->kind, e->left->kind)) && grouped)
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    else
    {
        expr_print(e->left);
    }
    return;   
}

void unary_pre_operator_print(struct expr* e, char* op)
{
    printf("%s", op);
    
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;   
    }
    if (right_higher_than_left(e->kind, e->left->kind))
    {
        expr_print(e->left);
    }
    else
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    return;
}

void unary_post_operator_print(struct expr* e, char* op)
{
    while ((e->left) && (e->left->kind == EXPR_GROUPING))
    {
        e->left = e->left->left;   
    }
    if (right_higher_than_left(e->kind, e->left->kind))
    {
        expr_print(e->left);
    }
    else
    {
        printf("(");
        expr_print(e->left);
        printf(")");
    }
    
    printf("%s", op);
    
    return;
}

void expr_resolve(struct expr* e)
{
    if (!e)
        return;

    if (e->kind == EXPR_NAME)
    {
        struct symbol* s;
        s = scope_lookup(e->name);
        if (!s)
        {
            printf("resolve error: %s is not declared\n", e->name);
            resolve_fail = 1;
        }
        else
        {   
            if (s->kind == SYMBOL_GLOBAL)
            {
                printf("%s resolves to %s %s\n", s->name, "global", s->name);
            }
            else if (s->kind == SYMBOL_PARAM)
            {
                printf("%s resolves to %s %d\n", s->name, "param", s->which);
            }
            else
                printf("%s resolves to %s %d\n", s->name, "local", s->which);
            e->symbol = s;
        }
    }
    else
    {
        expr_resolve(e->left);
        expr_resolve(e->mid);
        expr_resolve(e->right);
    }
}

struct expr* expr_copy(struct expr* e)
{
    if(!e)
    return 0;

    struct expr* ret = malloc(sizeof(*ret));
    ret->kind = e->kind;
    ret->left = expr_copy(e->left);   
    ret->right = expr_copy(e->right);   
    ret->mid = expr_copy(e->mid);
    ret->name = e->name ? strdup(e->name) : 0;
    ret->literal_value = e->literal_value;
    ret->string_literal = e->string_literal ? strdup(e->string_literal) : 0;
    ret->symbol = symbol_copy(e->symbol);
    return ret;
}

void expr_delete(struct expr* e)
{
    if (!e)
        return;
    expr_delete(e->left);
    expr_delete(e->mid);
    expr_delete(e->right);
    symbol_delete(e->symbol);
    free(e);

}

struct type* expr_typecheck(struct expr* e)
{
    if (!e)
        return 0;

    struct type* lt = expr_typecheck(e->left);
    struct type* mt = expr_typecheck(e->mid);
    struct type* rt = expr_typecheck(e->right);

    struct type* ret;
    switch (e->kind)
    {
        case EXPR_GROUPING:
            return type_copy(lt);
        case EXPR_SUBSCRIPT:
            if (!lt)
            {
                printf("type error: left operand of array subscript doesn't exist\n");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else if (lt->kind == TYPE_ARRAY)
            {
                if (!rt)
                {
                    printf("type error: right operand of array subscript doesn't exist\n");
                    typecheck_fail = 1;
                    return type_copy(lt);   
                }
                else if (rt->kind == TYPE_INTEGER)
                {
                    return type_copy(lt->subtype);
                }
                else
                {
                    printf("type error: index of array must be an integer literal instead of expression ");
                    typecheck_fail = 1;
                    expr_print(e->right);
                    printf("\n");
                    return type_copy(lt);
                }
            }
            else
            {
                printf("type error: left operand of array subscript must be of TYPE_ARRAY instead of ");
                typecheck_fail = 1;
                type_print(lt);
                printf("\n");
                return type_copy(lt);
            }
        case EXPR_CALL:
            if (!lt)
            {
                printf("type error: left operand of function call doesn't exist\n");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else if (lt->kind == TYPE_FUNCTION)
            {
                if (!rt)
                {
                    if (!lt->params)
                    {
                        return type_copy(lt->subtype);
                    }
                    else
                    {
                        printf("type error: %s is a function having param list as ");
                        typecheck_fail = 1;
                        param_list_print(lt->params);
                        printf(" but is called with no arguments\n");
                        return type_copy(lt->subtype);
                    }
                }
                else
                {
                    if (!lt->params)
                    {
                        printf("type error: %s is a function having no parameters but is called with parameters\n");
                        typecheck_fail = 1;
                        return type_copy(lt->subtype);
                    }
                    else
                    {
                        struct param_list* tmp_param_list = lt->params;
                        struct expr* tmp_expr = e->right; 
                        while (tmp_param_list->next && tmp_expr->kind == EXPR_ARG && tmp_expr->right)
                        {
                            if (type_equals(tmp_param_list->type, expr_typecheck(tmp_expr->left)))
                            {
                                if (!tmp_param_list->next && !tmp_expr->right)
                                    return type_copy(lt->subtype);
                                if (!tmp_param_list->next || !tmp_expr->right)
                                {
                                    printf("type error: %s is called with wrong number of arguments\n", e->left->name);
                                    typecheck_fail = 1;
                                    return type_copy(lt->subtype);
                                }
                                tmp_param_list = tmp_param_list->next;
                                tmp_expr = tmp_expr->right;
                            }
                            else
                            {
                                printf("type error: %s is called with arguments of wrong types\n", e->left->name);
                                typecheck_fail = 1;
                                return type_copy(lt->subtype);
                            }
                        }
                        if (!tmp_param_list->next && !tmp_expr->right)
                            return type_copy(lt->subtype);
                        printf("type error: %s is called with wrong number of arguments\n", e->left->name);
                        typecheck_fail = 1;
                        return type_copy(lt->subtype);
                    }
                }
            }
            else
            {
                printf("type error: left operand of array subscript must be of TYPE_FUNCTION instead of ");
                typecheck_fail = 1;
                type_print(lt);
                printf("\n");
                return type_copy(lt);
            }
        case EXPR_POST_DEC:
            return expr_typecheck_unary_int_operators(lt, "post decrement");
        case EXPR_POST_INC:
            return expr_typecheck_unary_int_operators(lt, "post increment");
        case EXPR_LOGICAL_NOT:
            if (!lt)
            {
                printf("type error: operand of %s doesn't exist\n", "logical not");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else
            {
                if (lt->kind == TYPE_BOOLEAN)
                {
                    return type_copy(lt);
                }
                else
                {
                    printf("type error: operand of %s must be an integer\n", "logical not");
                    typecheck_fail = 1;
                    return type_copy(lt);
                }
            }
        case EXPR_SINGLE_SUB:
            return expr_typecheck_unary_int_operators(lt, "single sub");
        case EXPR_EXP:
            return expr_typecheck_binary_int_operators(lt, rt, "exponent");
        case EXPR_MOD:
            return expr_typecheck_binary_int_operators(lt, rt, "modulo");
        case EXPR_DIV:
            return expr_typecheck_binary_int_operators(lt, rt, "division");
        case EXPR_MULT:
            return expr_typecheck_binary_int_operators(lt, rt, "multiplication");
        case EXPR_SUB:
            return expr_typecheck_binary_int_operators(lt, rt, "subtraction");
        case EXPR_ADD:
            return expr_typecheck_binary_int_operators(lt, rt, "addition");
        case EXPR_NOT_EQ:
            return expr_typecheck_binary_equality_operators(lt, rt, "not equal");
        case EXPR_EQ:
            return expr_typecheck_binary_equality_operators(lt, rt, "equal");
        case EXPR_GE:
            return expr_typecheck_binary_int_return_boolean_operators(lt, rt, "greater or equal");
        case EXPR_GREATER:
            return expr_typecheck_binary_int_return_boolean_operators(lt, rt, "greater");
        case EXPR_LE:
            return expr_typecheck_binary_int_return_boolean_operators(lt, rt, "less than or equal");
        case EXPR_LESS:
            return expr_typecheck_binary_int_return_boolean_operators(lt, rt, "less than");
        case EXPR_LOGICAL_AND:
            return expr_typecheck_binary_boolean_return_boolean_operators(lt, rt, "logical and");
        case EXPR_LOGICAL_OR:
            return expr_typecheck_binary_boolean_return_boolean_operators(lt, rt, "logical or");
        case EXPR_TERNARY:
            if (!lt)
            {
                printf("type error: left operand of %s doesn't exist\n", "ternary");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else if (!rt)
            {
                printf("type error: right operand of %s doesn't exist\n", "ternary");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else
            {
                if (lt->kind == TYPE_BOOLEAN)
                {
                    if (type_equals(mt, rt))
                    {
                        return type_copy(rt);
                    }
                    else
                    {
                        printf("type error: return values of %s are of different types\n", "ternary");
                        typecheck_fail = 1;
                        return type_copy(mt);
                    }
                }
                else
                {
                    printf("type error: condition operand of %s must be a boolean\n", "ternary");
                    typecheck_fail = 1;
                    return type_copy(mt);
                }
            }
        case EXPR_ASSIGN:
            if (e->left->kind != EXPR_NAME && e->left->kind != EXPR_SUBSCRIPT)
            {
                printf("type error: left operand of assign must be a name or an array subscript\n");
                typecheck_fail = 1;
                return type_copy(lt);
            }
            else
            {
                if (lt->kind == TYPE_ARRAY)
                {
                    if (get_atomic_type_array(lt)->kind == TYPE_AUTO)
                    {
                        if (rt->kind == TYPE_ARRAY)
                        {
                            struct type* tmp_t = get_atomic_type_array(rt);
                            if (tmp_t->kind == TYPE_VOID || tmp_t->kind == TYPE_ARRAY || tmp_t->kind == TYPE_FUNCTION || tmp_t->kind == TYPE_AUTO)
                            {
                                printf("type error: array cannot have elements of type ");
                                type_print(tmp_t);
                                printf("\n");
                                typecheck_fail = 1;
                                return type_copy(rt);
                            }
                            set_atomic_type_array(lt, tmp_t->kind);
                            if (type_equals(lt, rt))
                            {
                                struct expr* tmp_e = e;
                                while (tmp_e->left)
                                    tmp_e = tmp_e->left;
                                if (tmp_e->kind != EXPR_NAME)
                                {
                                    printf("type error: left most expression must be a name to index an array instead of ");
                                    expr_print(tmp_e);
                                    printf(" of type ");
                                    type_print(expr_typecheck(tmp_e));
                                    printf("\n");
                                    typecheck_fail = 1;
                                    return type_copy(lt);
                                }
                                set_atomic_type_array(tmp_e->symbol->type, tmp_t->kind);
                                return type_copy(lt);
                            }
                            else
                            {
                                printf("type error: cannot assign expression ");
                                expr_print(e->left);
                                printf(" of type ");
                                set_atomic_type_array(lt, TYPE_AUTO);
                                type_print(lt);
                                printf(" to an expression ");
                                expr_print(e->right);
                                printf(" of type ");
                                typecheck_fail = 1;
                                type_print(rt);
                                printf("\n");
                                return type_copy(lt);
                            }
                        }
                        else    
                        {
                            printf("type error: cannot assign expression ");
                            expr_print(e->left);
                            printf(" of type ");
                            type_print(lt);
                            printf(" to an expression ");
                            expr_print(e->right);
                            printf(" of type ");
                            typecheck_fail = 1;
                            type_print(rt);
                            printf("\n");
                            return type_copy(lt);
                        }
                    }
                    else 
                    {
                        if (type_equals(lt, rt))
                        {
                            return type_copy(lt); 
                        }
                        else
                        {
                            printf("type error: cannot assign expression ");
                            expr_print(e->left);
                            printf(" of type ");
                            type_print(lt);
                            printf(" to an expression ");
                            expr_print(e->right);
                            printf(" of type ");
                            typecheck_fail = 1;
                            type_print(rt);
                            printf("\n");
                            return type_copy(lt);
                        }
                    } 
                }
                else
                {
                    if (lt->kind == TYPE_AUTO)
                    {
                        if (rt->kind == TYPE_BOOLEAN || rt->kind == TYPE_CHARACTER || rt->kind == TYPE_INTEGER || rt->kind == TYPE_STRING)
                        {
                            e->left->symbol->type->kind = rt->kind;
                            return type_copy(rt);
                        }
                        else
                        {
                            printf("type error: cannot assign a variable to type ");
                            type_print(rt);
                            printf("\n");
                            typecheck_fail = 1;
                            return type_copy(rt);
                        }
                    }
                    else
                    {
                        if (rt->kind == TYPE_BOOLEAN || rt->kind == TYPE_CHARACTER || rt->kind == TYPE_INTEGER || rt->kind == TYPE_STRING)
                        {
                            if (type_equals(lt, rt))
                            {
                                return type_copy(lt);
                            }
                            else
                            {
                                printf("type error: cannot assign expression ");
                                expr_print(e->left);
                                printf(" of type ");
                                type_print(lt);
                                printf(" to an expression ");
                                expr_print(e->right);
                                printf(" of type ");
                                typecheck_fail = 1;
                                type_print(rt);
                                printf("\n");
                                return type_copy(lt);   
                            }
                        }
                        else
                        {
                            printf("type error: cannot assign expression ");
                            expr_print(e->left);
                            printf(" of type ");
                            type_print(lt);
                            printf(" to an expression ");
                            expr_print(e->right);
                            printf(" of type ");
                            typecheck_fail = 1;
                            type_print(rt);
                            printf("\n");
                            return type_copy(lt);
                        }
                    }
                }
            }
        case EXPR_ARG:
            return type_copy(lt);
        case EXPR_NAME:
            return type_copy(e->symbol->type);
        case EXPR_INTEGER_LITERAL:
            return type_create(TYPE_INTEGER, 0, 0, 0);
        case EXPR_STRING_LITERAL:
            return type_create(TYPE_STRING, 0, 0, 0);
        case EXPR_CHAR_LITERAL:
            return type_create(TYPE_CHARACTER, 0, 0, 0);
        case EXPR_BOOLEAN_LITERAL:
            return type_create(TYPE_BOOLEAN, 0, 0, 0);
        case EXPR_ARRAY_LITERAL:
            if (!e->left)
            {
                printf("type error: array literal with no value, return empty array instead\n");
                typecheck_fail = 1;
                return type_create(TYPE_ARRAY, type_copy(lt), 0, 0);
            }
            int i = 0;
            struct expr* tmp_e = e->left;   //expr_arg
            struct type* tmp_t = lt;
            while(tmp_e)
            {
                if (type_equals(tmp_t, lt))
                {
                    ++i;
                    tmp_e = e->right;
                    tmp_t = expr_typecheck(tmp_e);
                }
                else
                {
                    printf("type error: expression ");
                    expr_print(tmp_e);
                    printf(" of type ");
                    type_print(tmp_t);
                    printf(" is not of type ");
                    type_print(lt);
                    printf(" which is the correct element type in array literal ");
                    expr_print(e);
                    printf("\n");
                    typecheck_fail = 1;
                    return type_create(TYPE_ARRAY, type_copy(lt), 0, 0);
                }
            }
            return type_create(TYPE_ARRAY, type_copy(lt), 0, expr_create_integer_literal(i));
    }
}

struct type* expr_typecheck_binary_equality_operators(struct type* lt, struct type* rt, char* operator_name)
{
    if (!lt)
    {
        printf("type error: left operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else if (!rt)
    {
        printf("type error: right operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else
    {
        if (lt->kind == TYPE_BOOLEAN || lt->kind == TYPE_CHARACTER || lt->kind == TYPE_INTEGER || lt->kind == TYPE_STRING)
        {
            if (rt->kind == lt->kind)
            {
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
            else
            {
                printf("type error: right operand of %s is not the same as the left operand\n", operator_name);
                typecheck_fail = 1;
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
        }
        else
        {
            printf("type error: left operand of %s is not a valid type\n", operator_name);
            typecheck_fail = 1;
            return type_create(TYPE_BOOLEAN, 0, 0, 0);
        }
    }
}

struct type* expr_typecheck_binary_boolean_return_boolean_operators(struct type* lt, struct type* rt, char* operator_name)
{
    if (!lt)
    {
        printf("type error: left operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else if (!rt)
    {
        printf("type error: right operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else
    {
        if (lt->kind == TYPE_BOOLEAN)
        {
            if (rt->kind == TYPE_BOOLEAN)
            {
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
            else
            {
                printf("type error: right operand of %s must be a boolean\n", operator_name);
                typecheck_fail = 1;
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
        }
        else
        {
            printf("type error: left operand of %s must be a boolean\n", operator_name);
            typecheck_fail = 1;
            return type_create(TYPE_BOOLEAN, 0, 0, 0);
        }
    }
}

struct type* expr_typecheck_binary_int_return_boolean_operators(struct type* lt, struct type* rt, char* operator_name)
{
    if (!lt)
    {
        printf("type error: left operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else if (!rt)
    {
        printf("type error: right operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else
    {
        if (lt->kind == TYPE_INTEGER)
        {
            if (rt->kind == TYPE_INTEGER)
            {
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
            else
            {
                printf("type error: right operand of %s must be an integer\n", operator_name);
                typecheck_fail = 1;
                return type_create(TYPE_BOOLEAN, 0, 0, 0);
            }
        }
        else
        {
            printf("type error: left operand of %s must be an integer\n", operator_name);
            typecheck_fail = 1;
            return type_create(TYPE_BOOLEAN, 0, 0, 0);
        }
    }
}

struct type* expr_typecheck_binary_int_operators(struct type* lt, struct type* rt, char* operator_name)
{
    if (!lt)
    {
        printf("type error: left operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else if (!rt)
    {
        printf("type error: right operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else
    {
        if (lt->kind == TYPE_INTEGER)
        {
            if (rt->kind == TYPE_INTEGER)
            {
                return type_copy(lt);
            }
            else
            {
                printf("type error: right operand of %s must be an integer\n", operator_name);
                typecheck_fail = 1;
                return type_copy(lt);
            }
        }
        else
        {
            printf("type error: left operand of %s must be an integer\n", operator_name);
            typecheck_fail = 1;
            return type_copy(lt);
        }
    }
}

struct type* expr_typecheck_unary_int_operators(struct type* lt, char* operator_name)
{
    if (!lt)
    {
        printf("type error: operand of %s doesn't exist\n", operator_name);
        typecheck_fail = 1;
        return type_copy(lt);
    }
    else
    {
        if (lt->kind == TYPE_INTEGER)
        {
            return type_copy(lt);
        }
        else
        {
            printf("type error: operand of %s must be an integer\n", operator_name);
            typecheck_fail = 1;
            return type_copy(lt);
        }
    }
}

int expr_global_array_check_valid(struct expr* e, struct symbol* t)
{
    if (!e)
           return 1;
    if (e->kind == EXPR_ARRAY_LITERAL)
    {
        if (!e->left)
        {
            printf("type error: array literal ");
            expr_print(e);
            printf(" doesn't have a left value\n");
            typecheck_fail = 1;
            return 0;
        }
        if (e->left->kind == EXPR_ARG)
        {
            struct expr* tmp_e = e->left;
            while ((tmp_e = e->right))
            {
                if (!tmp_e->left)
                {
                    printf("type error: expression ");
                    expr_print(tmp_e);
                    printf(" doesn't have a left value\n");
                    typecheck_fail = 1;
                    return 0;
                }
                if (tmp_e->left->kind == EXPR_INTEGER_LITERAL || tmp_e->left->kind == EXPR_STRING_LITERAL || tmp_e->left->kind == EXPR_CHAR_LITERAL || tmp_e->left->kind == EXPR_BOOLEAN_LITERAL)
                {
                    if (get_atomic_type_array(t->type)->kind == TYPE_AUTO)
                    {
                        switch (tmp_e->left->kind)
                        {
                            case EXPR_INTEGER_LITERAL:
                                set_atomic_type_array(t->type, TYPE_INTEGER);
                                break;
                            case EXPR_STRING_LITERAL:
                                set_atomic_type_array(t->type, TYPE_STRING);
                                break;
                            case EXPR_CHAR_LITERAL:
                                set_atomic_type_array(t->type, TYPE_CHARACTER);
                                break;
                            case EXPR_BOOLEAN_LITERAL:
                                set_atomic_type_array(t->type, TYPE_BOOLEAN);
                                break;
                            default:
                                printf("fail at global array check valid\n");
                                typecheck_fail = 1;
                                return 0;
                        }
                        printf("notice: array name %s having auto as primitive type now has type ");
                        typecheck_fail = 1;
                        type_print(t->type);
                        printf("\n");
                        return 1;
                    }
                    else
                    {
                        if (tmp_e->left->kind == get_atomic_type_array(t->type)->kind)
                            return 1;
                        else
                        {
                            typecheck_fail = 1;
                            printf("type error: expression ");
                            expr_print(tmp_e->left);
                            printf(" of type ");
                            type_print(expr_typecheck(tmp_e->left));
                            printf(" has a mismatch with array %s with primitive type of ", t->name);
                            type_print(get_atomic_type_array(t->type));
                            printf("\n");
                            return 0;
                        }
                    }
                }
                else if (tmp_e->left->kind == EXPR_ARRAY_LITERAL)
                {
                    if (expr_global_array_check_valid(tmp_e->left, t))
                        return 1;
                    else
                        return 0;
                }
                else
                {
                    typecheck_fail = 1;
                    printf("type error: expression ");
                    expr_print(tmp_e->left);
                    printf(" of type ");
                    type_print(expr_typecheck(tmp_e->left));
                    printf(" is not a constant type\n");
                    return 0;
                }
            }
        }
        else
        {
            typecheck_fail = 1;
            printf("type error: direct child node of an array is not of type EXPR_ARG\n");
            return 0;
        }
    }
    else
    {
        typecheck_fail = 1;
        printf("expression ");
        expr_print(e);
        printf(" is not an EXPR_ARRAY_LITERAL\n");
        return 0;
    }
    return 1;
}
