#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "scope.h"

typedef enum {
    EXPR_GROUPING = 0,
    EXPR_SUBSCRIPT,
    EXPR_CALL,
    EXPR_POST_DEC,
    EXPR_POST_INC,
    EXPR_LOGICAL_NOT,
    EXPR_SINGLE_SUB, //(e.g., -1)
    EXPR_EXP,
    EXPR_MOD,
    EXPR_DIV,
    EXPR_MULT,
	EXPR_SUB,
	EXPR_ADD,
    EXPR_NOT_EQ,
    EXPR_EQ,
    EXPR_GE,
    EXPR_GREATER,
    EXPR_LE,
	EXPR_LESS,
    EXPR_LOGICAL_AND,
    EXPR_LOGICAL_OR,
    EXPR_TERNARY,
    EXPR_ASSIGN,
    EXPR_ARG,
    EXPR_NAME,
    EXPR_INTEGER_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_CHAR_LITERAL,
    EXPR_BOOLEAN_LITERAL,
    EXPR_ARRAY_LITERAL
} expr_t;

struct expr {
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;
    struct expr *mid;

	/* used by various leaf exprs */
	const char *name;
	int literal_value;
	const char * string_literal;
	struct symbol *symbol;
    int reg;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right, struct expr* mid );

struct expr * expr_create_name( const char *n );

struct expr * expr_create_integer_literal( int c );

struct expr * expr_create_boolean_literal( int c );

struct expr * expr_create_char_literal( char* c );

struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );

void expr_resolve(struct expr* e);

struct expr* expr_copy(struct expr* e);

struct type* expr_typecheck(struct expr* e);

//1 if valid, 0 if not
int expr_global_array_check_valid(struct expr* e, struct symbol* t);

void expr_codegen(struct expr* e, scope_t s);

#endif
