#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Funcion que imprime las cadenas, permite debug.
*/
void printChains(char ** chains, int rows) {

    for(int i = 0; i < rows; i++) {
        printf("%s", chains[i]);
    }
    printf("\n");
}

/*
    Función que concatena dos strings y los separa con una coma
    Entrada: String original donde se quiere concatenar, elemento a añadir
    Salida: String con ambos elementos separados por coma
*/
char * concatenateString(char * string, char * element) {

    char * newString = malloc(strlen(string) + strlen(element) + 2); // +2 por la coma y null final
    strcpy(newString, string);
    strcat(newString, ",");
    strcat(newString, element);

    return newString;
}