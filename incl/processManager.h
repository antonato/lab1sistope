#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

    void checkIn(int argc, char ** argv, char ** iFlag, int * nFlag, int * cFlag, char ** pFlag, int * dFlag);
    void pipelining(char * nameFile, char * chain, int numberProcess, int sizeCursor, int linesPerProcess);
    int *linesPerProcess(int nProcess, int sizeFile);
#endif