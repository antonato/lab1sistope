/*
Laboratorio 1, Sistemas Operativos
Creadores: Antonina Arriagada, Francisco Núñez
Fecha de creación: 28 de Octubre, 2020
Última actualización: 8 de Noviembre, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include "../incl/fileManage.h"
#include "../incl/utility.h"
#include "../incl/memory.h"
#include "../incl/processManager.h"

#define READ 0
#define WRITE 1


int main(int argc, char * argv[]){

    // flag numero procesos, flag cantidad lineas archivo, flag resultados por pantalla
    int nFlag = 0, cFlag = 0, dFlag = 0;
    char * iFlag = NULL; // flag nombre archivo
    char * pFlag = NULL; // flag cadena a buscar

    checkIn(argc, argv, &iFlag, &nFlag, &cFlag, &pFlag, &dFlag);

    // direccion del archivo y lectura  
    char path[3] = "../";
    strcat(path, iFlag);

    // tamaño del cursor
    int sizeCursor = lengthChain(path);
    int * lines = linesPerProcess(nFlag, cFlag);

    // coordinador
    pipelining(path, pFlag, nFlag, sizeCursor, lines);
    
    // merge de resultados
    makefile(nFlag, pFlag, dFlag);
    
    exit(-1);
    return 0;
}