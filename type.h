#ifndef TYPE_H
#define TYPE_H

#include "param_list.h"

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
    TYPE_AUTO,
} type_t;

struct type {
	type_t kind;
	struct type *subtype;
	struct param_list *params;
    struct expr* expr;
};

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params, struct expr* expr);
void type_print( struct type *t );

//1 is equal, 0 is not
int type_equals(struct type* a, struct type* b);

struct type* type_copy(struct type* t);

void type_delete(struct type* t);

//1 is valid, 0 is not
int type_array_check_valid(struct type* t);

struct type* get_atomic_type_array(struct type* t);

int set_atomic_type_array(struct type* t, type_t kind);

int type_function_check_valid(struct type* t);


int type_normal_check_valid(struct type* t);

#endif
