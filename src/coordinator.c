#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

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
                break;
            // cadena a buscar
            case 'p':
                *pFlag = optarg;
                if(strlen(*pFlag) <= 0){
                    printf("Cadena a buscar no es valida\n");
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



int main(int argc, char * argv[]){
    
    system("clear");
    int nFlag = 0, cFlag = 0, dFlag = 0;
    char * iFlag = NULL;
    char * pFlag = NULL;

    checkIn(argc, argv, &iFlag, &nFlag, &cFlag, &pFlag, &dFlag);

    /*if(dFlag == 1){
    printf("iFlag: %s nFlag: %d cFlag: %d pFlag: %s dFlag: %d\n", iFlag, nFlag, cFlag, pFlag, dFlag);
    }*/

    printf("OK!\n");

    return 0;
}