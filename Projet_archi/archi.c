#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T_MEMOIRE 5000
//transformer les instructions en language machine, comment les stocker dans la pile
//division par 0, overflow, pile vide et demande de pop 

char *espace(char str[]) {
    // Récupère le premier mot avant un espace
    if (str[0]=' '){ // pas d'étiquette 
        int i = 0;
        while (str[i]==' '){
            i++;
        }
        int j=i; 
        while (str[j] != ' ' && str[j] != '\0') { 
            j++;
        }
        char *instruction = malloc(j + 1);
        if (!instruction) {
            printf("Erreur d'allocation mémoire\n");
            return NULL;
        }
        strncpy(instruction, str, j);
        instruction[j] = '\0'; 
        int x=0;
        while (instruction[i+x]!='\0'){
                instruction[x]=instruction[i+x];
                x++;
        }
        instruction[x]='\0';
        return instruction;
    }
    else { // s'il y a une étiquette 
        int i = 0;
        while (str[i] !=' ' && str[i] !='\0') { 
            i++;
        }
        char *instruction = malloc(i + 1);
        if (!instruction) {
            printf("Erreur d'allocation mémoire\n");
            return NULL;
        }
        strncpy(instruction, str, i);
        instruction[i] = '\0'; 
        return instruction;
    }
    
}


char *deci_hex(int decimal) {
    char *hex = malloc(5);
    if (!hex) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    sprintf(hex, "%04x", decimal);  // %04x pour que ce soit sur 4 octets et les lettres en minuscule 

    return hex;
}


void copier_chaine(char chaine[], char copie[]){
    int j=0;
    while (chaine[j]!='\0'){
        copie[j]=chaine[j];
        j+=1;
            }
    copie[j]='\0';
}


int nb_espaces(char str[]){// pas utile pour le moment mais on sait jamais 
    int i=0;
    int cpt=0;
    while (str[i]!='\0'){
        if (str[i]==' '){
            cpt+=1;
        }
        i++;
    }
    if (cpt==4){
        return 1;
    }
    return 0;
}


int etiquette(char chaine[]) {// si il y a une étiquette 1 sinon 0
    if (chaine[0]!=' '){
        return 1;
    }
    return 0;
}


int syntaxe(char mot[], int i){
    //pour toutes les fonctions ne prennant que des entiers on vérifie si l'argument est bien un entier via le code ascii de chaque caractère
    int j = (int) mot[i];
    if(47<j && j<58){ // de 0 à 9
        return 0;
    }
    return 1;
}


int est_vide(char mot[]){ // vérifier qu'une chaine de caractère est bien vide
    int i=0;
    while (mot[i]!='\0'){
        if (mot[i]!= ' '){
            return 0;
        }
        i++;
    }
    return 1;
}


char *convers_machine(char str[]) {
// convertit l'assembleur en language machine et renovie la chaine de caractère associée push 1000 -> 02 03e8
    char copie[50];
    strcpy(copie, str);
    char *motbis=strtok(copie, " "); 
    char *mot = strtok(str, " ");
    char *mach = malloc(8); 
    if (!mach) {
        printf("Erreur d'allocation mémoire");
        return NULL;
    }
    if (etiquette(str)){
        mot = strtok(NULL, " ");
    }
    if (strcmp(mot, "push") == 0) {
        mot = strtok(NULL, " ");
        int x= strlen(mot);
        mot[x-1]='\0';
        if (est_vide(mot)){ //si il n'y a pas d'arguments
            strcpy(mach, "NULL");
            return mach;
        }
        motbis=strtok(NULL, " ");
        if (motbis!=NULL){
            strcpy(mach, "NULL");
            return mach;
        }
        int i=0;
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot); // convertit la chaîne en entier
            char *hex = deci_hex(x); 
            if (hex) {
                sprintf(mach, "02 %s", hex); // concatène 02 avec la valeur hexadécimale
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "read") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "09 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "pop") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "00 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "ipop") == 0){
        strcpy(mach, "01 0000");
    }
    else if (strcmp(mot, "push#") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "04 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "ipush") == 0){
        strcpy(mach,"03 0000");
    }
    else if (strcmp(mot, "ret") == 0){
        strcpy(mach, "08 0000");
    }
    else if (strcmp(mot, "write") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot);
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "0a %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "op") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot);
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "0b %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "rnd") == 0){
        mot = strtok(NULL, " ");
        int i=0;
        int x= strlen(mot);
        mot[x-1]='\0'; // car le dernier caractere est un espace et renvoie donc un mauvais resultat 
        while (mot[i]!='\0'){
            if (syntaxe(mot, i)){
                strcpy(mach, "NULL");
                return mach;
            }
            i++;
        }
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "0c %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "dup") == 0){ 
        strcpy(mach,"0c 0000");
    }
    else if (strcmp(mot, "halt") == 0){
        strcpy(mach, "63 0000"); //(6*16 + 3 = 99)
    }
    else if (strcmp(mot, "jmp") == 0){////////////////////////////////////////////////////////////////calculer etiquette
        mot = strtok(NULL, " ");
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "05 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "jnz") == 0){
        mot = strtok(NULL, " ");
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "06 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else if (strcmp(mot, "call") == 0){
        mot = strtok(NULL, " ");
        if (mot) {
            int x = atoi(mot); 
            char *hex = deci_hex(x);
            if (hex) {
                sprintf(mach, "07 %s", hex); 
                free(hex); 
            } 
            else {
                strcpy(mach, "NULL");
            }
        } 
        else {
            strcpy(mach, "NULL");
        }
    }
    else {
        strcpy(mach, "NULL");
    }
    printf("%s\n", mach);
    return mach;
}


int recup_fichier(void) {
    short memoire[T_MEMOIRE];
    short *SP=memoire; // pointeur sur la première case de mémoire libre
    short *PC=memoire; // pointeur sur l'instruction à exécuter
    FILE *f=NULL;
    FILE *f_machine=NULL;
    f=fopen("pgm.txt", "r");
    if (!f) { //si on ne peut pas lire le fichier 
        printf("Impossible de lire le fichier\n");
        return 0;
    }
    else {
        char buff[50];
        int i=0;
        char *tab[1000]; // taille reservée a la pile 
        char cp[50];
        while (fgets(buff, 50, f)!=NULL) {// on verifie qu'il n'y a pas d'erreurs dans le fichier source 
            tab[i]=malloc(strlen(buff)+1); 
            if (!tab[i]){
                printf("Probleme d'allocation memoire");
                for (int j = 0; j < i; j++) {
                    free(tab[j]);
                }
                fclose(f);
                return 0;
            }
            strcpy(tab[i],buff);
            if(strcmp(convers_machine(buff), "NULL")==0){ // problème de syntaxe
                printf("Erreur de syntaxe dans le fichier source a la ligne %d, le fichier n'a pas pu etre cree.\n", i+1);
                for (int j = 0; j < i; j++) {
                    free(tab[j]);
                }
                fclose(f);
                return 0;
            }
            i+=1;
        }
        //on créé le nouveau fichier pour le language machine
        /*f_machine=fopen("hexa.txt", "a");
        if (!f_machine) {
            printf("Erreur d'allocation memoire, impossible de creer le fichier\n");
            for (int j = 0; j < i; j++) {
                free(tab[j]);
            }
            fclose(f_machine);
            fclose(f);
            return 0;
        }
        for (int j = 0; j < i; j++) {
            char* result = convers_machine(tab[j]);
            fputs(result, f_machine);
            fputc('\n', f_machine);
            free(tab[j]); // Libérer la mémoire allouée pour cette ligne
        }
        fclose(f_machine);*/
        fclose(f);
        return 1;
    }
}

int main(void) {
    recup_fichier();
    return 1;
}