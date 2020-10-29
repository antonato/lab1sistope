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
	return 0;
}

int coordinator(char* nameFile, int nProcess, int lenChain){
	return 0;
}

int main(int argc, char const *argv[])
{
	char test[30] = "AGAAAGGCATAAATATATG"; 
	char chain[30] = "AGAAAGGCATAAATATATG"; 
	short int answer = result(chain,test);
	printf("Respuesta Comparador: %d", answer);
}