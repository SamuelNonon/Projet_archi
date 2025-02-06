#ifndef MEMOIRE
#define MEMOIRE

typedef struct adresse {
    int entier;
    struct adresse* suivante;
    int hauteur;    //necessaire ?? pourrait servir à connaitre hauteur pile et vérifier qu'on depasse pas 5000 adresses
} Adresse;





#endif