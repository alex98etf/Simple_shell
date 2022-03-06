#include "searching_for_stuff.h"

/**
  * @brief Find Text In File
  * @param text
  * @param filename
  * @retval None
  */
void findTextInFile(char* text, char* fileName)
{
    // provjerava da li je tekst fajl
    if(strstr(fileName, ".txt") == NULL)
    {
        printf("\nFile You Entered Isn't A Text File!\n\n");
		
        return;
    }
	
    // preskace razmak na pocetku fileName-a
    fileName += sizeof(char);

    FILE *pFile;
    int whatLine = 0;
    pFile = fopen(fileName, "r");
    char line[MAX_LENGTH];

	if(pFile != NULL)
	{
		while(fgets(line, MAX_LENGTH, pFile) != NULL)
		{
			++whatLine;

			if( strstr(line,text) != NULL)
			{
				printf("\nThe Text You Entered Was Found on Line %d.\n\n",whatLine);
				break;
			}
		}

		if (feof(pFile))
		{
			printf("\nThe Text You Entered Wasn't Found!\n\n");
		}
	}
	
    else
	{
        printf("\nCan't Open The File!\n\n");
	}
	
    fclose(pFile);
}

/**
  * @brief Finds a File in Dir.
  * @param filename
  * @param directory
  * @retval None
  */
void findFileInDirectory(char *fileName, char *directory)
{
     if(strstr(fileName, ".") == NULL)
    {
        printf("\nIncorrect File Name Was Entered!\n\n");
		
        return;
    }

    setCurentUserAdress();
	
    if(directory && !goToDirectorie(directory))
    {
        printf("\nCan't Find Directory!\n\n");
        return;
    }

    FILE *pFile = fopen(fileName, "rb"); // otvara dat.

    if(pFile != NULL) // da li postoji dat.
    {
        printf("\nYore File %s Was Found!\n\n", fileName);
    }
    else
    {
        printf("\nFile Doesn't Exist!\n\n");
    }
	
    fclose(pFile);

    goBack();
}

/**
  * @brief Finds a User in the User Database
  * @param userName
  * @param password
  * @retval 1 : OK, 0 Fuck it
  */
int findUser(char *userName, char *password)
{
    FILE *pFile;
    char dName[MAX_LENGTH];
    char dPassword[MAX_LENGTH];

    pFile = fopen("userDatabase.txt", "r");

    if(pFile != NULL)
    {
        // cita liniju sa imenom i lozinkom korisnika
        while(fscanf(pFile, "%s %s", dName, dPassword) != EOF)
        {
            if(!strcmp(userName, dName)) // provjerava ime
            {
                if(!strcmp(password, dPassword)) // provjerava lozinku
                    {
                        fclose(pFile);
                        return 1;
                    }
                else
                    {
                        printf("\nYou Entered The Wrong Password, Try Again!\n\n");
                        fclose(pFile);
                        return 0;
                    }
            }
        }
    }
    else
	{
		 printf("Can't Find The User Database!\n\n");
	}

    fclose(pFile);
    printf("\nThere Is No User Whit That Name!\n\n");
	
    return 0;
}
