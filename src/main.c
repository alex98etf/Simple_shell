#include "heder_files.h"
#include "commands.h"

void newPC();

int main()
{
    /* odlazi na dir. home\OOS*/
    if (!goToDirectorie("home\\OOS"))
    {
        newPC(); //ako nema home\OOS neka napravi i ode na dir.
    }
	
    setRootAdress();

    char line[MAX_LENGTH];

    printf("************************************************************\n\n");
    printf("                   OOS Simple Shell\n");
    printf("                                                   by Alex '20\n");
    printf("************************************************************\n\n");

    while(1)
    {
        printf("%s>>", userName);

        // cita liniju sa konzole i blaga provjera
        if(!fgets(line, MAX_LENGTH, stdin) || !strcmp(line, "\n") || !strcmp(line, "\t\n"))
		{
			printf("\n");
			continue;
		}
		
        removeNewline(line);  // uklanja \n na kraju line

        // izvrsava naredbu
        if(executeCommand(line) == 1)
        {
            break;
        }
		
        memset(line, 0, MAX_LENGTH);   //postavlja line na nula
    }

    printf("\nGoodbye\n");
	
    return 0;
}

/**
  * @brief Creates new dirs. of a new PC
  * @retval None
  */
void newPC()
{
    // pravi home dir. i ide na njega
    mkdir("home");
	goToDirectorie("home");
	
    // pravi OOS dir. i ide na njega
    mkdir("OOS");
	goToDirectorie("OOS");
	
    // pravi dat. za imena i lozinke korisnika
    FILE *pFile = fopen("userDatabase.txt", "w");
    fclose(pFile);
	
    printf("First You Need To Create A User Account, Type: login -n\n");
}
