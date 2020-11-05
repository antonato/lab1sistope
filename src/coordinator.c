/*
Laboratorio 1, Sistemas Operativos
Creadores: Antonina Arriagada, Francisco Núñez
Fecha de creación: 28 de Octubre, 2020
Última actualización: 5 de Noviembre, 2020
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

void pipelining() {

    // file descriptor
    int fd[2];
    pipe(fd);

    int status;
    pid_t pid;

    char * arguments[] = {"test", iFlag, NULL};

    pid = fork();
    // proceso padre
    if(pid > 0) {
        close(fd[READ]);
        write(fd[WRITE], iFlag, 30*(sizeof(char)));
        printf("Soy el coordinador y mi pid es %i\n", getpid());
        waitpid(pid, &status, 0);
    }
    // el hijo
    else if(pid == 0) {
        close(fd[WRITE]);
        printf("I'm the son and my pid is: %i\n", getpid());
        printf("My father's pid would be: %i\n", getppid());
        dup2(fd[READ], STDIN_FILENO);

        execv(arguments[0], arguments);
    }
    else {
        fprintf(stderr, "Error al crear el proceso\n");
        exit(-1);
    }


}*/




int main(int argc, char * argv[]){
    
    system("clear");
    int nFlag = 0, cFlag = 0, dFlag = 0;
    char * iFlag = NULL;
    char * pFlag = NULL;

    checkIn(argc, argv, &iFlag, &nFlag, &cFlag, &pFlag, &dFlag);

    // direccion del archivo y lectura  
    char path[3] = "../";
    strcat(path, iFlag);
    char ** chains = readFile(cFlag, path, 0);
    //printChains(chains, cFlag);
    printf("Lectura finalizada\n");
    
    // Bloque pipeline
    /*
        Por c/ proceso hacer pipelinig y enviar:
            -> Posición del cursor  (comparator.c)
            -> Archivo a leer       (readFile.c)
            -> Largo de las cadenas (fijo)
            -> Número de procesos   (stdin)
    */
    
    //pipelining();
    
    // liberacion de memoria y salida
    freeMemory(chains, cFlag);
    exit(-1);

    return 0;
}