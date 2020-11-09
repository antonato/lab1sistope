//Declaración de librerías

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include "../incl/fileManage.h"


//Declaración de funciones y variables

/*-------------------LÓGICA--------------------*/

/*
	Función que define si una cadena se encuentra en la línea    
	Entrada: 
			char* chain -> cadena a buscar
			char *line -> línea donde se buscará
    Salida: Si el resultado es 1 encontró una coincidencia, si es 0 es lo contrario
*/
short int result(char *chain, char *line){

	int lenC = strlen(chain);
	int lenL = strlen(line);

	for (int i = 0; i < lenL-(lenC-1); ++	i)
	{
		//busca la simitud con el primer caracter
		if (chain[0]==line[i])
		{
			int j; //si lo encuentra sigue buscando con el siguiente caracter
			for (j = 1; j < lenC; j++)
			{
				//si encuentra el siguiente caracter sigue adelante
				if (chain[j]==line[i+1])
				{
					i++;
				}
				else{ //si no lo encuentra corta el ciclo
					i = i+1;
					break;
				}
			} 
			if (j==lenC) //si recorrió toda la palabra es porque ha hecho match
			{
				return 1;
			}
		}
	}
	return 0; //de lo contrario retornará 0
}

/*
	Función que lee el archivo y pregunta por cada línea que deba revisar
	Entrada: 
			char* nameFile -> nombre del archivo
			char* chain -> cadena a buscar
			long int cursor -> posición del cursor
			int nChains -> cantidad de cadenas a revisar
			int id -> id del proceso
    Salida: Si el resultado es 1 encontró se creó el archivo correctamente, si es 0 es lo contrario
*/
int comparator(char* nameFile, char* chain, long int cursor, int nChains, int id){
	
	char ** lines =  readFile(nChains, nameFile, cursor);
	int len;
	//se agrega espacios separadores entre los resultados
	for (int i = 0; i < nChains; i++)
	{
		len = strlen(lines[i]);

		if (lines[i][len-1] == '\n')
		{
			lines[i][len-1] = ' ';
		}else{
			lines[i][len] = ' ';
			len++;
		}
		short int answer = result(chain, lines[i]);
		if (answer == 0){
			lines[i][len] = '0';
		}
		else if(answer == 1) {
			lines[i][len] = '1';
		}
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

	int final = writeFile(nChains, name, lines, len);
	if (final==0)
	{
		printf("Se ha creado el archivo %s, desde el proceso con id: %d\n", name, id);
		exit(-1);
	}
	
	return final;	
}

int main(int argc, char const *argv[])
{	
	char data[5];
	read(STDIN_FILENO, data, 100*sizeof(char));

	char * token = strtok(data, ",");
	char * name = token; // 0
	token = strtok(NULL, ",");
	char * nChainsSTR = token;
	int nChains = atoi(nChainsSTR); // 1
	token = strtok(NULL, ",");
	char * chain = token; // 2
	token = strtok(NULL, ",");
	char * idSTR = token;
	int id = atoi(idSTR);
	token = strtok(NULL, ",");
	char * cursorSTR = token;
	int cursor = atoi(cursorSTR);

	return comparator(name, chain, cursor, nChains, id);
}