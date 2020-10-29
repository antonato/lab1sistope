#include <stdlib.h>

void freeMemory(char ** array, int dim){
    for(int i = 0; i < dim; i++){
        free(array[i]);
    }
    free(array);
}