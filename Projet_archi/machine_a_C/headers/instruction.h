#ifndef INSTRUCTION
#define INSTRUCTION

#include "programme.h"
#include <stdio.h>


typedef struct programme Programme;


typedef struct instruction {
    int operation;
    int donnee;
    struct instruction* suivant;
    struct instruction* precedent;    //nécessaire ?
} Instruction;

Instruction* creer_instruction (int operation, int donnee);

#endif