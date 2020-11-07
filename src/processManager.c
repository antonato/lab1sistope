#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include "../incl/processManager.h"

#define READ 0
#define WRITE 1

/*
    Función que revisa los parámetros de entrada mediante los flags ingresados por la terminal
    Entrada: Argumentos de entrada por terminal de la forma
             -> ./sucesion -i <nombre_archivo.txt> -n <numero procesos> -c <cantidad lineas archivos> -p <cadena a buscar> -d
    Salida: Si el algoritmo detecta un error en los flags se indicará por la salida estándar
*/
void checkIn(int argc, char ** argv, char ** iFlag, int * nFlag, int * cFlag, char ** pFlag, int * dFlag) {
    
    int c;
    if(argc < 10) {
        printf("Error al ingresar parametros de entrada, seguir la siguiente estructura\n");
        fprintf(stderr, "%s [-i <nombre_archivo.txt>] [-n <numero procesos>] [-c <cantidad lineas archivo>] [-p <cadena a buscar>] [-d]\n\n", argv[0]);
        exit(-1);
    }

    // retorna -1 cuando no hay más opciones a revisar
    while((c = getopt(argc, argv, "i:n:c:p:d")) != -1) {

        switch(c) {
            // mostrar por pantalla
            case 'd':
                *dFlag = 1;
                break;
            // archivo de entrada
            case 'i':
                *iFlag = optarg;
                if(strlen(*iFlag) <= 0){
                    printf("Nombre del archivo no es válido");
                    exit(-1);
                }
                break;
            // cantidad de procesos
            case 'n':
                sscanf(optarg, "%d", nFlag);
                if(*nFlag <= 0) {
                    printf("La cantidad de procesos no es valida\n");
                    exit(-1);
                }
                break;
            // cantidad lineas del archivo
            case 'c':
                sscanf(optarg, "%d", cFlag);
                if(*cFlag <= 0) {
                    printf("La cantidad de lineas del archivo no es valida\n");
                    exit(-1);
                }
                else if(*nFlag > *cFlag) {
                    printf("La cantidad de procesos es mayor a la cantidad de lineas del archivo\n");
                    exit(-1);
                }
                break;
            // cadena a buscar
            case 'p':
                *pFlag = optarg;
                if(strlen(*pFlag) < 4 || strlen(*pFlag) > 4){
                    printf("Cadena a buscar no es valida, ingrese una de largo cuatro\n");
                    exit(-1);
                }
                break;
            // faltan flags
            case '?':
                if(optopt == 'i'){
                    fprintf(stderr, "Se requiere argumento < -%c >\n", optopt);
                }
                else if(optopt == 'n'){
                    fprintf(stderr, "Se requiere argumento < -%c >\n", optopt);
                }
                else if(optopt == 'c'){
                    fprintf(stderr, "Se requiere argumento < -%c >\n", optopt);
                }
                else if(optopt == 'p'){
                    fprintf(stderr, "Se requiere argumento < -%c >\n", optopt);
                }
                else if(isprint(optopt)){
                    fprintf(stderr,"Opcion desconocida < -%c >\n",optopt);
                }
                else{
                    fprintf(stderr,"Opcion con caracter desconocido \\x%x\n",optopt);
                }
                exit(1);
            // 
            default:
                abort();
            break;
        }
    }
}

/*
    Función ...
    Entrada:
    Salida:
*/
void pipelining(char * nameFile, char * chain, int numberProcess, int sizeCursor, int linesPerProcess) {

    // pipe de comunicacion
    int pipes[2];
    pipe(pipes);
    int status;
    pid_t pid;
    // transformacion de valores a string para argumentos
    char lines[10];
    sprintf(lines, "%d", linesPerProcess);
    
    char id[5];
    char cursor[5];
    int actualCursor = 0;
    char * arguments[] = {"comparator", nameFile, lines, chain, id, cursor, NULL};

    int idProcess = 0;
    while(idProcess < numberProcess) { 
        // parseo a string para entregar id y cursor como argumento en execv
        sprintf(id, "%d", (idProcess+1));
        sprintf(cursor, "%d", actualCursor);

        pid = fork();
        // proceso hijo
        if(pid == 0){
            close(pipes[READ]);
            dup2(pipes[WRITE], STDIN_FILENO);
            execv(arguments[0], arguments);
        }
        // proceso padre
        else if(pid > 0){
            waitpid(pid, &status, 0);
        }
        // error
        else {
            fprintf(stderr, "Error al crear el proceso\n");
            exit(-1);
        }
        // siguiente proceso y cursor
        idProcess++;
        actualCursor = idProcess * linesPerProcess * sizeCursor;
    }

    //makefile(numberProcess, chain);
    printf("Proceso finalizado\n");

}

/*
    Función...
    Entrada:
    Salida:
*/
int *linesPerProcess(int nProcess, int sizeFile){

    int* result = (int*)malloc(sizeof(int)*2);
    
    if (sizeFile%nProcess==0)
    {
        result[0] = sizeFile/nProcess;
        result[1] = 0;
        return result;    
    }
    else
    {
        int i = sizeFile;
        int j = 0;
        while (i%nProcess!=0)
        {
            j++;
            i--;
            result[0] = i/nProcess;
            result[1] = j;
        }        
        return result;
    }
}

