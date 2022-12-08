#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "codegen_helpers.h"

//hacky mapping of register ids [0-6] to their names and whether they are inuse
static char* register_names[] = {"%rbx", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15"};

//0 or 1 only
static int inuse[] = {0, 0, 0, 0, 0, 0, 0};

static int NUM_SCRATCH = 7;

//global label counter
static int lcount = 0;

//label cannot get larger than this
static int MAX_COUNTER = 10000000;  //10 million

//alloc a scratch id, exit if run out of scratch
int scratch_alloc()
{
    int i;
    for (i = 0; i < NUM_SCRATCH; ++i)
    {
        if (inuse[i] == 0)
        {
            inuse[i] = 1;
            return i;
        }
    }
    printf("codegen error: run out of scratch registers\n");
    exit(1);
}

//check if scratch id in correct range
static void check_scratch_id(int r)
{
    if (r <= 6 && r >= 0)
        return;
    printf("codegen error: scratch id %d is not valid\n", r);
    exit(1);
}

void scratch_free(int r)
{
    check_scratch_id(r);
    if (inuse[r])
        inuse[r] = 0;
    else
        printf("codegen warning: scratch register %d is already free\n", r);
}

//return name of scratch register
const char* scratch_name(int r)
{
    check_scratch_id(r);
    return strdup(register_names[r]);
}

int label_create()
{
    return ++lcount;
}

const char* label_name(int label)
{
    char* s = malloc(sizeof(*s) * MAX_COUNTER);
    sprintf(s, ".L%d", label);
    return s;
}

int current_label()
{
    return lcount;
}
