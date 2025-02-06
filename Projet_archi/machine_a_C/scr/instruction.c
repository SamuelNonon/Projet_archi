#include "instruction.h"

Instruction* creer_instruction (int operation, int donnee){
    Instruction* res = malloc(sizeof(Instruction));
    res->operation = operation;
    res->donnee = donnee;
    res->suivant = NULL;
    res->precedent = NULL;
    return res;
}


