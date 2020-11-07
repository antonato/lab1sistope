#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/memory.h"

#define MAX 255

/*
	Función que lee un archivo
	Entrada: 
			char* nameFile -> nombre del archivo
			int row -> cantidad de cadenas a revisar
			long int cursorPos -> posición del cursor
    Salida: char ** -> Retorna las líneas leídas
*/
char ** readFile(int row, char* nameFile, long int cursorPos){

    FILE * file = fopen(nameFile, "r+"); //read plus write mode 
    
    if(file == NULL){
        printf("Archivo no encontrado, verifique ruta\n");
        exit(-1);
    }

    fseek(file, cursorPos, SEEK_CUR); //se setea el lugar del cursor

    // memoria para "row" filas de archivo
    int i;
    char ** dnaChain = (char **)malloc(sizeof(char *) * row);
    for(i = 0; i < row; i++){
        dnaChain[i] = (char *)malloc(sizeof(char) * MAX);
    }
    
    // lectura por lineas
    int j = 0;
    while(j < i && fgets(dnaChain[j], MAX, file)){
        j++;
    }

    fclose(file);
    return dnaChain;
}

/*
	Función que lee un archivo
	Entrada: 
			char* nameFile -> nombre del archivo
			int row -> cantidad de cadenas a revisar
            char** lines -> lineas a escribir
			long int cursorPos -> posición del cursor
    Salida: char ** -> retorna 1 si tiene problemas 0 si fue exitoso
*/
int writeFile(int row, char* nameFile, char ** lines, int len){

    FILE *file = fopen(nameFile, "w");
    if(file == NULL){
        printf("Problemas con la creación del archivo %s\n", nameFile);
        exit(1);
    }
    char no[] = "NO\n";
    char si[] = "SI\n";

    //se escriben las líneas y se agrega 'si' o 'no'
    for (int i = 0; i < row; i++)
    {
        if (lines[i][len] == '0'){
            lines[i][len] = ' ';
          	strcat(lines[i], no);

            // printf("--> %s", lines[i]);
            fputs(lines[i], file);
		}
		else{
            lines[i][len] = ' ';
           	strcat(lines[i], si);
            fputs(lines[i], file);
		}
    }
    
  	fclose (file);

    return 0;
}

int makefile(int nProcess, char* chain){
    FILE *final, *rest;
    char c;
   	
    char file1[30]="rc_";
   	char guion[] = "_";
   	char extension[] = ".txt"; 
    strcat(file1,chain);
    strcat(file1,extension);
    

    printf("Nombre 1: %s\n", file1);

    for (int i = 1; i <= nProcess; i++)
    {
        char file2[30]="rp_";
        strcat(file2,chain);
        char idst[3]; 
	    sprintf(idst, "%d", i);
        strcat(file2,guion);
        strcat(file2,idst);
        strcat(file2,extension);

        rest=fopen(file2, "r+");
        final=fopen(file1, "a");
        printf("Nombre parcial: %s\n", file2);

        while(!feof(rest))
        {
            fscanf(rest, "%c", &c);
            fprintf(final, "%c", c);
        }
        fclose(rest);
        fclose(final);
    }
        
    return 1;
}

int main(int argc, char const *argv[])
{
    makefile(3, "AGGAA");
    /* code */
    return 0;
}