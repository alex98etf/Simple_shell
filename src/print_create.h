#ifndef PRINT_CREATE_H_INCLUDED
#define PRINT_CREATE_H_INCLUDED

#include "heder_files.h"
#include "directories.h"

void printContents(char* fileName);

void createFile(char *filename,char *fileType,char *whereToCreatFile);

int createUser(char *userLine,char *userName);

#endif // PRINT_CREATE_H_INCLUDED
