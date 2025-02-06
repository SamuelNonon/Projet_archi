#include <stdio.h>

int convertir_hexa (char c){
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return 9999999;
}


int main (void){
    char hexa = "e";
    int res;
    res = convertir_hexa(hexa);
    printf ("%d ", res);
}