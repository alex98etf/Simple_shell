#include "commands.h"

/**
  * @brief Executes User Command
  * @param line
  * @retval 1 : Exit, 0 Fuck it
  */
int executeCommand(char *line)
{
    // Uzimamo naredbu tj. prvu riječ do razmaka
    char *command = strtok(line," ");

    /* Provjeramo da li korisnik prijavljen */
    if (userName[0] == 0 && strcmp(command,"login") != 0 )
    {
        if(strcmp(command, "exit") == 0)
        {
            return 1;
        }
		
        printf("\nYou Need To Be Logged In Execute This Command!\n\n");
        return 0;
    }
	
    // trazi komandu koja je unesena
    short whichCommand = listOfCommand(command);

    switch (whichCommand)
    {
    case 0: // login naredba
        {
            if(userName[0] == 0)
            {
                char *isNewUser = strtok(NULL, " ");
                logInUser(isNewUser);
            }

            else
            {
                printf("\nYou Are Already Logged In!\n\n");
            }
            break;
        }
    case 1: // logout naredba
        {
            logOutUser();
            break;
        }
    case 2: // where naredba
        {
            printf("\n");
			where();
			printf("\n");
			
            break;
        }
    case 3: //go naredba
        {
            char *path = strtok(NULL, "");
			
            if(!path)
            {
                printf("\nYou Didn't Enter The Command Promptly!\n\n");
				
                return 0;
            }
            if(!goToDirectorie(path))
            {
                printf("\nCan't go to %s!\n\n",path);
                break;
            }

            printf("\n");
			
            break;
        }
    case 4: // create naredba
        {
            char *fileType = strtok(NULL, " ");
            char *fileName = strtok(NULL, "\\");
            char *path = strtok(NULL, "");
			
            if(!fileName || !fileType)
            {
                printf("\nYou Didn't Enter The Command Promptly!\n\n");
				
                return 0;
            }
			
            createFile(fileName, fileType, path);
			
            break;
        }
    case 5: // list naredba
        {
            char *path = strtok(NULL, "");
            printf("\n************************************************************\n");
            listDirectory(path, 0);
            printf("************************************************************\n\n");
			
            break;
        }
    case 6: // print naredba
        {
            char *fileName = strtok(NULL, "");
			
            if(!fileName)
            {
                printf("\nYou Didn't Enter The Command Promptly!\n\n");
				
				return 0;
            }
			
            printContents(fileName);
            break;
        }
    case 7: // find naredba
        {
            char *text = strtok(NULL, "\"");
            char *fileName = strtok(NULL, "");
			
            if(!text || !fileName)
            {
                printf("\nYou Didn't Enter The Command Promptly!\n\n");
				
                return 0;
            }
			
            findTextInFile(text,fileName);
			
            break;
        }
    case 8: // findDat naredba
        {
            char *fileName = strtok(NULL, "\\");
            char *path = strtok(NULL, "");
			
            if(!fileName)
            {
                printf("\nYou Didn't Enter The Command Promptly!\n\n");
				
                return 0;
            }
			
            findFileInDirectory(fileName, path);
			
            break;
        }
    case 9: // exit naredba
        {
            return 1;
            break;
        }
    case 10: // clear naredba
        {
            system("cls"); // "Čisti" ekran
			
            break;
        }

        default:
            printf("\nThere Is No Command Whit That Name!\n\n");
            break;
    }
	
    return 0;
}

/**
  * @brief Logs in as New User
  * @param isNewUser : if "-n" it crates a new user
  * @retval None
  */
void logInUser(char *isNewUser)
{
    char password[MAX_LENGTH];
    char *userLine;

    printf("\nUser Name: ");
	fgets(userName, MAX_LENGTH, stdin);
	removeNewline(userName);
	
    printf("Password: ");
	fgets(password, MAX_LENGTH, stdin);
	removeNewline(password);

    userLine = (char*)malloc(strlen(userName) + strlen(password)+ 2);
	
    strcpy(userLine, userName);
	strcat(userLine, " ");
	strcat(userLine, password);

    // pravi novog korisnika
    if(isNewUser && strcmp(isNewUser, "-n") == 0)
    {
        if(!createUser(userLine, userName))
            return;
    }
	
    // trazi korisnik
    else if (!findUser(userName, password))
    {
        memset(userName, 0, MAX_LENGTH); // ako nema korisnika
		
        return;
    }
	
    // postavlja tekuci dir. za korisnika
    if(!goToDirectorie(userName))
    {
        mkdir(userName);
        goToDirectorie(userName);
    }
	
    setRootUserAdress();
    printf("\n************************************************************\n");
    printf("Welcome %s\n", userName);
    printf("Your Current Directory Is "); where();
    printf("If You Want to Return To This Directory Type In: go \\home\n");
    printf("************************************************************\n\n");
	
    free(userLine);
}

/**
  * @brief Logs Out a User
  * @retval None
  */
void logOutUser()
{
    printf("\nBye %s!\n\n", userName);
    memset(userName, 0, MAX_LENGTH);
    chdir(rootAdress);
}

/**
  * @brief Logs in as New User
  * @param cmd : command
  * @retval Returns a number corisponding to command, or 33 if the command dose not exist
  */
short listOfCommand(char *cmd)
{
    short i;
    char whatCmd[11][10] = {"login", "logout", "where", "go", "create",
                            "list", "print", "find", "findDat", "exit", "clear"};
    for(i = 0; i < 11; i++)
    {
        if(strcmp(cmd, whatCmd[i]) == 0 )
        {
            return i;
        }
    }
	
    // Ako nema te komande onda vraća neku vrijednost da se osigura da ode u default
    return 33;
}
