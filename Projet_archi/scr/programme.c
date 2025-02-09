#include "programme.h"

Programme* creer_programme (short nb_instructions){
    Programme* res = malloc(sizeof(Programme));
    res->nb_instructions = nb_instructions;
    res->instructions = malloc(nb_instructions*sizeof(short));
    res->donnees = malloc(nb_instructions*sizeof(short));
    res->PC = 0;
    res->SP = 0;
    return res;
}


void supprimer_programme (Programme* programme){
    free (programme->instructions);
    free (programme->donnees);
    free (programme);
    return;
}


short selectionner_instruction (Programme* programme){
    short instruction = programme->instructions[programme->PC-1];
    if (instruction == 0){
        return pop (programme);
    }
    if (instruction == 1){
        return ipop (programme);
    }
    if (instruction == 2){
        return push (programme);
    }
    if (instruction == 3){
        return ipush (programme);
    }
    if (instruction == 4){
        return push_immediate (programme);
    }
    if (instruction == 5){
        return jmp (programme);
    }
    if (instruction == 6){
        return jnz (programme);
    }
    if (instruction == 7){
        return call (programme);
    }
    if (instruction == 8){
        return ret (programme);
    }
    if (instruction == 9){
        return read (programme);
    }
    if (instruction == 10){
        return write (programme);
    }
    if (instruction == 11){
        return op (programme);
    }
    if (instruction == 12){
        return rnd (programme);
    }
    if (instruction == 13){
        return dup (programme);
    }
    if (instruction == 99){
        return 2;
    }
}