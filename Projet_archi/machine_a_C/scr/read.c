#include "read.h"

void lire_donnee (void){
	FILE* fichier = fopen ("fichier.txt", "r");
	if (!fichier)
		printf ("erreur");
	int instruction, donnee;
	
	while (fscanf (fichier, "%x %x\n", &instruction, &donnee) != EOF) {
	//fscanf (fichier, "%x %x\n", &instruction, &donnee);
		if (donnee > 61440)
			donnee = - 65535 + donnee - 1;
		printf ("%d %d\n", instruction, donnee);
	}
	return;
}



int main (void){
    lire_donnee ();
    return 0;
}
