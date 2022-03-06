#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "heder_files.h"
#include "directories.h"
#include "searching_for_stuff.h"
#include "print_create.h"

char userName[MAX_LENGTH];

short listOfCommand(char *cmd);

void logInUser(char *isNewUser);

void logOutUser();

int executeCommand(char *line);


#endif // COMMANDS_H_INCLUDED
