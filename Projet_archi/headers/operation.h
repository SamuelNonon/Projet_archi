#ifndef OPERATION
#define OPERATION

#include <stdio.h>
#include <stdlib.h>
#include "programme.h"

typedef struct programme Programme;

void egal (Programme* programme);
void non_egal (Programme* programme);
void sup_egal (Programme* programme);
void inf_egal (Programme* programme);
void sup (Programme* programme);
void inf (Programme* programme);
void ou (Programme* programme);
void ou_exclusif (Programme* programme);
void et (Programme* programme);
void non (Programme* programme);
void addition (Programme* programme);
void soustraction (Programme* programme);
void multiplication (Programme* programme);
void division (Programme* programme);
void modulo (Programme* programme);
void oppose (Programme* programme);

#endif