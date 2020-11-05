#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printChains(char ** chains, int rows) {

    for(int i = 0; i < rows; i++) {
        printf("%s", chains[i]);
    }
    printf("\n");
}