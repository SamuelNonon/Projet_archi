#ifndef PROGRAMME
#define PROGRAMME

#include <stdlib.h>
#include "instruction.h"

typedef struct programme {
    short nb_instructions;
    short* instructions;
    short* donnees;
    short PC;
    short memoire[5000];
    short SP;
}Programme;

Programme* creer_programme (short nb_instructions);
void supprimer_programme (Programme* programme);
short selectionner_instruction (Programme* programme);

#endif