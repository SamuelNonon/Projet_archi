#include <stdio.h>
#include <stdlib.h>
#include "programme.h"
#include "read.h"

int main (void){
    short nb_instructions = compter_instructions();
    if (nb_instructions == 0){
		printf ("erreur lors de l'ouverture du fichier\n");
		return 1;
	}
    Programme* programme = creer_programme (nb_instructions);
    lire_fichier (programme);
    short etat = 0;
    while (etat == 0){
        programme->PC += 1;
        etat = selectionner_instruction (programme);
    }
    if (etat == 1){
        printf ("Garbage in, garbage out :/\n");
        return 1;
    }
    return 0;
}