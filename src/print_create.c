#include "print_create.h"

/**
  * @brief Print content of a text file
  * @param filename
  * @retval None
  */
void printContents(char* fileName)
{   
	// Provjera da l je text fajl unesen
    if(strstr(fileName, ".txt") == NULL)
    {
        printf("\nFile You Entered Isn't A Text File!\n\n");
		
        return;
    }

    FILE *pFile;
    pFile = fopen(fileName, "r");
    char line[MAX_LENGTH];

    if(pFile != NULL)
    {

        fseek(pFile, 0, SEEK_END); // premota na kraj fajla
		
        if(ftell(pFile) == 0) // provjerava da li je falj prazan
        {
            printf("\nFile %s Is Empty!\n\n",fileName);
            fclose(pFile);
			
            return;
        }
		
		fseek(pFile, 0, SEEK_SET); // premotava na pocetak

		// ispis sadrzaja fajla
		printf("\n************************************************************\n");
		printf("%s: \n", fileName);

		while(fgets(line, MAX_LENGTH, pFile) != NULL)
		{
			printf("   %s", line);
		}

		printf("\n************************************************************\n\n");
    }
    else
    {
        printf("\nThere Is No Text File With That Name!\n\n");
    }

    fclose(pFile);
}

/**
  * @brief Creates a FILE / DIR.
  * @param filename
  * @param fileType
  * @param whereToCreatFile
  * @retval None
  */
void createFile(char *filename, char *fileType, char *whereToCreatFile)
{
    setCurentUserAdress();
	
    // odlazi na dir. gdje trba napraviti
    if( whereToCreatFile && !goToDirectorie(whereToCreatFile))
    {
        printf("\nCan't Fined Your Directory!\n\n");
        return;
    }
	
    // jel direktorijum
    if(!strcmp(fileType, "-d"))
    {
         // zabranjujemo korisniku da napravi dir. sa imenom home
        if(strcmp(filename, "home") == 0)
        {
            printf("\nYou Can't Make A Directory Whit That Name!\n\n");
            return;
        }
		
        if(!mkdir(filename)) // pravi dir.
        {
             printf("\nYour Directory Was Created!\n\n");
        }
        else
        {
            printf("\nYour Directory Wasn't Created!\n\n");
        }
    }
	
    //ili je fajl
    else if (!strcmp(fileType, "-"))
    {
        // provjerava da li odgovarajuci format
        if(strstr(filename, ".") == NULL)
        {
            printf("\nIncorrect File Name Was Entered!\n\n");
            return;
        }

        FILE *fp;
        fp  = fopen (filename, "wb"); //pravi dat.
		
        if(fp != NULL) // napravljena
        {
            printf("\nYour File Was Created!\n\n");
        }
        else // nije nap.
        {
            printf("\nYour File Wasn't Created!\n\n");
        }
		
        fclose (fp);
    }
    else
    {
        printf("\nSome Thing Went Wrong! Your File Or Directory Wasn't Created!\n\n");
    }
	
    goBack();
}

/**
  * @brief Creates a User
  * @param userLine : userNAme password
  * @param userName
  * @retval 1 : OK, 0 fuck it
  */
int createUser(char *userLine, char *userName)
{
    FILE *pFile = fopen("userDatabase.txt", "a");
	
    if(pFile != NULL)
    {
        fprintf(pFile, "\n%s", userLine); // upisuje ime i lozinku
        
		if (!mkdir(userName)) // pravi dir. za korisnika
        {
            fclose(pFile);
            return 1;
        }
    }
    else
    {
        printf("\nSomething Went Wrong Can't Create User!\n\n");
        memset(userName, 0, MAX_LENGTH); // postalja ime na nulu
        fclose(pFile);
		
        return 0;
    }
}
