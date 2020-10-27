//FECHA: 08-01-19, 11:09 AM


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

   return 0;

}