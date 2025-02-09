#ifndef INSTRUCTION
#define INSTRUCTION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "programme.h"
#include "operation.h"

typedef struct programme Programme;

short pop (Programme* programme);
short ipop (Programme* programme);
short push (Programme* programme);
short ipush (Programme* programme);
short push_immediate (Programme* programme);
short jmp (Programme* programme);
short jnz (Programme* programme);
short call (Programme* programme);
short ret (Programme* programme);
short read (Programme* programme);
short write (Programme* programme);
short op (Programme* programme);
short rnd (Programme* programme);
short dup (Programme* programme);

#endif