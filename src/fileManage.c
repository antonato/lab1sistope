#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/memory.h"

#define MAX 255

char ** readFile(int row, char* nameFile, long int cursorPos){

    FILE * file = fopen(nameFile, "r+"); //read plus write mode 
    int cursor = fseek(file, cursorPos, SEEK_CUR);
    printf("Leyendo archivo: %s\n", nameFile);


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
    int j = 0;
    while(fgets(dnaChain[j], MAX, file) && j != i){
        cursor = ftell(file);
        j++;
    }
    fclose(file);
    return dnaChain;
}

int writeFile(int row, char* nameFile, char ** lines, int len){

	printf("Iniciando proceso \n");
	printf("Creando archivo %s\n", nameFile);
    FILE *file = fopen(nameFile, "w");

    if(file == NULL){
        printf("Archivo no encontrado, verifique ruta\n");
        exit(1);
    }
    char no[] = "NO\n";
    char si[] = "SI\n";


    for (int i = 0; i < row; i++)
    {
        if (lines[i][len-1] == '0'){
            lines[i][len-1] = ' ';
          	strcat(lines[i], no);
            fputs(lines[i], file);
		}
		else{
            lines[i][len-1] = ' ';
           	strcat(lines[i], si);
            fputs(lines[i], file);
		}
    }
    
  	fclose (file);

    return 1;
}