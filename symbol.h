
#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	symbol_t kind;
	struct type *type;
	char *name;
	int which;  //for locals and params, their positions. for functions, whether it is defined (-1) or not(-2: only declared)
};

struct symbol * symbol_create( symbol_t kind, struct type *type, char *name, int which);

struct symbol* symbol_copy(struct symbol* s);

void symbol_delete(struct symbol* s);

#endif
