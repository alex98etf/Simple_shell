#ifndef SEARCHING_FOR_STUFF_H_INCLUDED
#define SEARCHING_FOR_STUFF_H_INCLUDED

#include "heder_files.h"
#include "directories.h"

void findFileInDirectory(char *fileName, char *directory);

void findTextInFile(char* text, char* fileName);

int findUser(char *userName, char *password);


#endif // SEARCHING_FOR_STUFF_H_INCLUDED
