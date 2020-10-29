#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/memory.h"

#define MAX 255

char ** readFile( /*some*/  ){
    // buffer
    int row = 2;

    FILE * file = fopen("../test", "r");

    if(file == NULL){
        printf("Archivo no encontrado, verifique ruta\n");
        exit(1);
    }

    // memoria para "row" filas de archivo
    int i;
    char ** dnaChain = (char **)malloc(sizeof(char *) * row);
    for(i = 0; i < row; i++){
        dnaChain[i] = (char *)malloc(sizeof(char) * MAX);
    }

    // lectura por lineas
    i = 0;
    while(fgets(dnaChain[i], MAX, file)){
        i++;
    }

    fclose(file);
    return dnaChain;
}
