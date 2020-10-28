/*
Laboratorio 1, Sistemas Operativos
Creadores: Antonina Arriagada, Francisco Núñez
Fecha de creación: 28 de Octubre, 2020
Última actualización: 28 de Octubre, 2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Declaración de funciones y variables


/*-------------------ARCHIVOS--------------------*/

//Funcion que leer el primer numero del txt
//Entrada: Dirección del txt
//Salida: Numero n
int leerN(char* direccion)
{	
	int largo = 0; 
	FILE *fd;

	fd = fopen(direccion,"r"); //modo: read text

	if(fd == NULL){

		printf("Error al leer archivo\n");
	}
	else
	{
		fscanf(fd, "%d", &largo);

		fclose(fd);
		return largo;
	}

}

int main(int argc, char const *argv[])
{
	printf("hola\n");
}