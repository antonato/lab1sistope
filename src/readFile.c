#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/memory.h"

#define MAX 255

char ** readFile(int nChains, long int cursor, char* nameFile){
    // buffer
    int row = 4;
    long int cursor;

    FILE * file = fopen(nameFile, "r+"); //read plus write mode 

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
        cursor = ftell(file);
        printf("Cursor: %d \n", cursor);  
        i++;
    }

    fclose(file);
    return dnaChain;
}


int main(int argc, char const *argv[])
{
	readFile();
}