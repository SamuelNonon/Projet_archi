#include "operation.h"

void egal (Programme* programme){
    if (programme->memoire[--programme->SP] == programme->memoire[programme->SP-1])
        programme->memoire[programme->SP-1] = 1;
    else 
        programme->memoire[programme->SP-1] = 0;
}


void non_egal (Programme* programme){
    if (programme->memoire[--programme->SP] == programme->memoire[programme->SP-1])
        programme->memoire[programme->SP-1] = 0;
    else 
        programme->memoire[programme->SP-1] = 1;
}


void sup_egal (Programme* programme){
    if (programme->memoire[--programme->SP-1] >= programme->memoire[programme->SP])
        programme->memoire[programme->SP-1] = 1;
    else 
        programme->memoire[programme->SP-1] = 0;
}


void inf_egal (Programme* programme){
    if (programme->memoire[--programme->SP-1] <= programme->memoire[programme->SP])
        programme->memoire[programme->SP-1] = 1;
    else 
        programme->memoire[programme->SP-1] = 0;
}


void sup (Programme* programme){
    if (programme->memoire[--programme->SP-1] > programme->memoire[programme->SP])
        programme->memoire[programme->SP-1] = 1;
    else 
        programme->memoire[programme->SP-1] = 0;
}


void inf (Programme* programme){
    if (programme->memoire[--programme->SP-1] < programme->memoire[programme->SP])
        programme->memoire[programme->SP-1] = 1;
    else 
        programme->memoire[programme->SP-1] = 0;
}


void ou (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] | programme->memoire[programme->SP];
}


void ou_exclusif (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] ^ programme->memoire[programme->SP];
}


void et (Programme* programme){
    programme->memoire[--programme->SP-1] =  programme->memoire[programme->SP-1] & programme->memoire[programme->SP];
}


void non (Programme* programme){
    programme->memoire[programme->SP-1] = ~ programme->memoire[programme->SP-1];
}


void addition (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] + programme->memoire[programme->SP];
}


void soustraction (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] - programme->memoire[programme->SP];
}


void multiplication (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] * programme->memoire[programme->SP];
}


void division (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] / programme->memoire[programme->SP];
}


void modulo (Programme* programme){
    programme->memoire[--programme->SP-1] = programme->memoire[programme->SP-1] % programme->memoire[programme->SP];
}


void oppose (Programme* programme){
    programme->memoire[programme->SP-1] = - programme->memoire[programme->SP-1];
}