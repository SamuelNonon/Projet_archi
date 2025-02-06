#ifndef PROGRAMME
#define PROGRAMME

#include "instruction.h"

typedef struct instruction Instruction;

typedef struct programme {
    Instruction* PC;
    // Pile* SP;
}Programme;

#endif