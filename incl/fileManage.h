#ifndef READFILE_H
#define READFILE_H

    char ** readFile(int row, char* nameFile, long int cursor);
    int writeFile(int row, char* nameFile, char ** lines, int len);
    int makefile(int nProcess, char* chain, int flag);
    int lengthChain(char * nameFile);

#endif