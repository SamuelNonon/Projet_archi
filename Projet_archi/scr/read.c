#include "read.h"
short compter_instructions (void){
	FILE* fichier = fopen ("fichier.txt", "r");
	if (!fichier){
		printf ("erreur");
		return 0;
	}
	int instruction, donnee, compte = 0;
	while (fscanf (fichier, "%x %x\n", &instruction, &donnee) != EOF){
		compte += 1;
	}
	fclose(fichier);
	return compte;
}


void lire_fichier (Programme* programme){
	FILE* fichier = fopen ("fichier.txt", "r");

	int instruction, donnee, i;
	for (i = 0; i < programme->nb_instructions; i++) {
		fscanf (fichier, "%x %x\n", &instruction, &donnee);
		programme->instructions[i] = instruction;
		programme->donnees[i] = donnee;
	}
	fclose(fichier);
	return;
}