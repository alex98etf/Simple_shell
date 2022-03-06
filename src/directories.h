#ifndef DIRECTORIES_H_INCLUDED
#define DIRECTORIES_H_INCLUDED

#include "heder_files.h"

char rootAdress[MAX_LENGTH];

char rootUserAdress[MAX_LENGTH];

char curentUserAdress[MAX_LENGTH];


// for dirs.
void where();

int goToDirectorie(char *directory);

void goBack();

void listDirectory(char *directory,int depth);


// for address stuff
void setCurentUserAdress();

void setRootUserAdress();

void setRootAdress();


void removeNewline(char* line);

#endif // DIRECTORIES_H_INCLUDED
