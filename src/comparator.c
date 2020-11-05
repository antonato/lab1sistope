/*
Laboratorio 1, Sistemas Operativos
Creadores: Antonina Arriagada, Francisco Núñez
Fecha de creación: 28 de Octubre, 2020
Última actualización: 28 de Octubre, 2020
*/

//Declaración de librerías

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../incl/fileManage.h"


//Declaración de funciones y variables

/*-------------------LÓGICA--------------------*/

short int result(char *chain, char *line){

	int lenC = strlen(chain);
	int lenL = strlen(line);
	// printf("lenC: %d\n", lenC);
	// printf("lenL: %d\n", lenL);


	for (int i = 0; i < lenL-(lenC-1); ++	i)
	{
		// printf("%c", line[i]);
		if (chain[0]==line[i])
		{
			// printf("Encontre una similitud con %c \n", line[i]);
			int j;
			for (j = 1; j < lenC; j++)
			{
				if (chain[j]==line[i+1])
				{
					// printf("Encontre una similitud interna con %c \n", line[i+1]);
					i++;
				}
				else{
					i = i+1;
					break;
				}
			}
			if (j==lenC)
			{
				return 1;
			}
		}
	}
	return 0;
}


int comparator(char* nameFile, char* chain, long int cursor, int nChains, int id){
	
	char ** lines =  readFile(nChains, nameFile, cursor);
	int len = strlen(lines[0]);

	printf("line: %s \n", lines[0]);
	printf("line: %s \n", lines[1]);
 
	for (int i = 0; i < nChains; i++)
	{
		short int answer = result(chain, lines[i]);
		if (answer == 0){
			lines[i][len-1] = '0';
		}
		else if(answer == 1) {
			lines[i][len-1] = '1';
		}
		printf("i: %d line: %s \n", i,lines[i]);
	}

    char name[50] = "rp_";
	char idst[3]; 
	char guion[] = "_";
	char extension[] = ".txt"; 
	sprintf(idst, "%d", id);
	strcat(chain,guion);
	strcat(name,chain);
	strcat(name, idst);
	strcat(name, extension);

	printf("Escribiendo archivo: %s\n", name);
	return writeFile(nChains, name, lines, len);	
}

int main(int argc, char const *argv[])
{
	//argv[0]  
	//argv[1]  archivo a ocupar
	//argv[2]  posicion del cursor
	//argv[3]  cadena a encontrar
	//argv[4]  cuántas líneas debe hacer la comparación
	//argv[5]  número identificador
	
	int id = 1;
	char name[20] = "test.txt";
	int nChains = 2;
	int cursor = 21;
	char chain[30] = "AGGAA"; 

	int result = comparator(name, chain, cursor, nChains, id);
	printf("El resultado es exitoso");
	return 0;
}