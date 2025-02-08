#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T_MEMOIRE 5000
//transformer les instructions en language machine, comment les stocker dans la pile
//division par 0, overflow, pile vide et demande de pop 

int syntaxe(char mot[]){
    /*pour toutes les fonctions ne prennant que des entiers on vérifie 
    si l'argument est bien un entier via le code ascii de chaque caractère
    cette fonction renvoie 1 si tout est bon et 0 sinon*/
    int i=0;
    while (mot[i]!='\0'){
        int j = (int) mot[i];
        if(47>j || j>58){ // de 0 à 9
            return 0;
        }
        i++;
    }
    return 1;
}


int calcul_adr(char etiquette[][50],  char etiq[], int ligne){
    int adr;
    for (int i=0; i<5000; i++){
        if (strcmp(etiquette[i], etiq)==0){
            if (ligne <= i){// <= ou < a voir
                adr=i-ligne-1;
                break;
            }
            else{
                adr=65536-ligne;
                break;
            }
        }
    }
    return adr;
}

typedef struct Instr{
    char instruction[80];
    char argument[80];

} instr;


int etiquette_colle(char str[]){
    int i=0;
    while (str[i]!='\0'){
        if (str[i]==':'){
            return i;
        }
        i++;
    }
    return 1000;
}


int code_inst(char instr[]){
    // renvoie en decimale car je ne sais pas comment le renvoyer en hexa
    if (strcmp(instr, "pop") == 0){
        return 00; //inutile car renvoie uniquement 0 sans le 0 devant 
    }
    else if (strcmp(instr, "ipop") == 0){
        return 1;
    }
    else if (strcmp(instr, "push") == 0){
        return 2;
    }
    else if (strcmp(instr, "ipush") == 0){
        return 3;
    }
    else if (strcmp(instr, "push#") == 0){
        return 4;
    }
    else if (strcmp(instr, "jmp") == 0){
        return 5;
    }
    else if (strcmp(instr, "jnz") == 0){
        return 6;
    }
    else if (strcmp(instr, "call") == 0){
        return 7;
    }
    else if (strcmp(instr, "ret") == 0){
        return 8;
    }
    else if (strcmp(instr, "read") == 0){
        return 9;
    }
    else if (strcmp(instr, "write") == 0){
        return 10;
    }
    else if (strcmp(instr, "op") == 0){
        return 11;
    }
    else if (strcmp(instr, "rnd") == 0){
        return 12;
    }
    else if (strcmp(instr, "dup") == 0){
        return 13;
    }
    else if (strcmp(instr, "halt") == 0){
        return 99;
    }
    else{
        return 100; //s'il y a une erreur dans l'instruction
    }

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
        exit(1);
    }
    else {
        instr *inst = malloc(sizeof(instr));
        if (!inst){
            printf("probleme d'allocation memoire");
            return 0;
        }
        char buff[50];
        char *mot;
        int ligne=1;;
        char etiquette[5000][50];
        char tab[1000][9]; // taille reservée a la pile 
        char copie[50];
        char etiq[50];
        // si l'étiquette est collée a l'instruction à voir
        while (fgets(buff, 50, f)!=NULL) {// on verifie qu'il n'y a pas d'erreurs dans le fichier source 
            if (strcmp(buff, "\n")==0){
                printf("Attention, la ligne %d est vide.\n", ligne);
                continue;
            }
            buff[strcspn(buff, "\n")] = '\0'; // supprime le \n a la fin de la ligne 
            mot = strtok(buff, " ");
            if (mot[strlen(mot)-1]==':'){
                if (strlen(mot)==1){
                    printf("Erreur, etiquette manquante");
                    exit(1);
                }
                strncpy(etiq, mot, strlen(mot)-1);
                etiq[strlen(mot) - 1] = '\0';
                strcpy(etiquette[ligne], etiq);
                mot = strtok(NULL, " ");
                if (mot==NULL){
                    printf("Erreur, instruction manquante.\n");
                    exit(1);
                }
           }
           // si  l'étiquette est collée à l'instruction
           else{
            if (etiquette_colle(mot)!=1000){
                int i=etiquette_colle(mot);
                strncpy(etiq, mot, i); //etiquette recupere manque plus qu'à recup le mot
                strcpy(etiquette[ligne], etiq);
                i++;

                for(int j=i; j<strlen(mot); j++){
                    mot[j-i]= mot[j];
                }
                mot[strlen(mot)-i]='\0';//on recupère uniquement l'instruction
                strcpy(inst->instruction, copie);
                 
            }
           }
            if (mot==NULL){
                printf("Erreur, instruction manquante.\n");
                exit(1);
           }
           strcpy(inst->instruction, mot); 
           mot = strtok(NULL, " ");       
           if (mot!=NULL){
               strcpy(inst->argument, mot);
               mot = strtok(NULL, " ");
               if (mot!=NULL){
                printf("Erreur, les intructions attendent un seul ou aucun argument a la ligne %d\n", ligne);
                exit(1);
               }
           }
           else {
               strcpy(inst->argument, "NULL");
           }
           if (code_inst(inst->instruction)==100){
               printf("Erreur, instruction inconnue a la ligne %d", ligne);
               exit(1);
           }
           // marche pas si l'etiquette est apres le jmp ou autre
           else if (5<=code_inst(inst->instruction) && code_inst(inst->instruction)<=7){ // toutes les instructions qui pourraient nécissité un cacul d'adresse
               if (strcmp(inst->argument, "NULL")==0){ // si pas d'adresse ou d'étiquette
                   printf("Erreur, %s attend une adresse en argument.\n", inst->instruction);
                   exit(1);
               }
               if (syntaxe(inst->argument)!=0){
                int x=atoi(inst->argument);
                char machine[9];
                sprintf(machine, "%02x", code_inst(inst->instruction));  // Première partie
                strcat(machine, " ");  // Ajoute un espace
                sprintf(machine + strlen(machine), "%04x", x);
                strcpy(tab[ligne-1], machine);
               }
               else {
                char machine[9];
                sprintf(machine, "%02x", code_inst(inst->instruction));
                strcat(machine, " "); 
                strcat(machine, inst->argument);
                strcpy(tab[ligne-1], machine);
                //cacul_adr(etiquette, inst->argument, ligne);
               }
               
           }
           else if (code_inst(inst->instruction)==1 || code_inst(inst->instruction)==3 || code_inst(inst->instruction)==8 || code_inst(inst->instruction)==13 || code_inst(inst->instruction)==99){

               if (strcmp(inst->argument, "NULL")!=0){
                   printf("Erreur, %s n'attend pas d'argument a la ligne %d.", inst->instruction, ligne);    
               }
               else {
                   char machine[9];
                   sprintf(machine, "%02x", code_inst(inst->instruction));  // Première partie
                   strcat(machine, " ");  // Ajoute un espace
                   strcat(machine, "0000");
                   strcpy(tab[ligne-1], machine);
                   //mettre dans les tableau ou l'utiliser pour calculer les etiquettes?
               }
           }
           else {
               if (strcmp(inst->argument, "NULL")==0){
                printf("Erreur, %s attend un argument a la ligne %d.\n", inst->instruction, ligne);
                exit(1);
               }
                // on verifie que l'argument donné est bien un entier positif ecrit en décimal
               if (syntaxe(inst->argument)==0){
                    printf("Erreur, %s ne prend que des entiers positifs en argument a la ligne %d.\n", inst->instruction, ligne);
                    exit(1);
               }
               int x=atoi(inst->argument);
               if (code_inst(inst->instruction)==11){
                if (x<0 || x>15){ // on vérifie si l'argument de op est bien entre O et 15
                    printf("Erreur, %s attend un argument entre 0 et 15 compris a la ligne %d.\n", inst->instruction, ligne);
                    exit(1);
                }
               }
               char machine[9];
               sprintf(machine, "%02x", code_inst(inst->instruction));  // Première partie
               strcat(machine, " ");  // Ajoute un espace
               sprintf(machine + strlen(machine), "%04x", x);
               strcpy(tab[ligne-1], machine);
            }
               ligne ++;
            }
            for(int i=0; i<ligne; i++){
                char copie[9];
                strcpy(copie, tab[i]);
                char *mot=strtok(copie, " ");
                int y=atoi(copie);  // pas de problème avec l'hexa car compris entre 5 et 7 donc convertit direct en hexa décimal
                if (5<=y && y<=7){
                    mot=strtok(NULL, " ");
                    int adr=calcul_adr(etiquette, mot, i+1);
                    char machine[9];
                    sprintf(machine, "%02x", y);  // Première partie
                    strcat(machine, " ");  // Ajoute un espace
                    sprintf(machine + strlen(machine), "%04x", adr);
                    strcpy(tab[i], machine);
                }
                printf("%s\n", tab[i]);

            }
        if (strcmp(inst->instruction, "halt")!=0){
            printf("Attention, votre instruction de fin n'est pas halt, votre programme risque de ne pas s'arreter correctement.\n");
        }
    
        //on créé le nouveau fichier pour le language machine
        f_machine=fopen("hexa.txt", "a");
        if (!f_machine) {
            printf("Erreur d'allocation memoire, impossible de creer le fichier\n");
            fclose(f_machine);
            fclose(f);
            return 0;
        }
        for (int j = 0; j < ligne; j++) {
            fputs(tab[j], f_machine);
            fputc('\n', f_machine); 
        }
        fclose(f_machine);
        fclose(f);
        return 1;
    }
}




int main(void) {
    recup_fichier();
    return 1;
}

