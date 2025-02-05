#include <stdio.h>

int convertir_hexa (char hexa[]){
    int res = 0;
    for (int i = 0; i < 4; i++){
        if (hexa[i] >= '0' && hexa[i] <= '9'){
            res = res * 16 + hexa[i] - '0';
            continue;
        }
        if (hexa[i] >= 'a' && hexa[i] <= 'f'){
            res = res * 16 + hexa[i] - 'a' + 10;
            continue;
        }
    }
    return res;
}


int main (void){
    char hexa[] = "03e8";
    int res;
    res = convertir_hexa(hexa);
    printf ("%d ", res);
}