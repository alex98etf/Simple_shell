#include "directories.h"


void where()
{
    char adress[MAX_LENGTH];
    getcwd(adress, MAX_LENGTH);
    printf("%s\n", strstr(adress,"\\home"));
}

void removeNewline(char* line)
{
    int len = strlen(line);
    if(line[len-1] == '\n')
    {
        line[len-1] = '\0';
    }
}

void setRootAdress()
{
    getcwd(rootAdress, MAX_LENGTH);
}

void setRootUserAdress()
{
    getcwd(rootUserAdress, MAX_LENGTH);
}

void setCurentUserAdress()
{
    getcwd(curentUserAdress, MAX_LENGTH);
}

void goBack()
{
    chdir(curentUserAdress);
}

int goToDirectorie(char* path)
{
    if(path == NULL || strcmp(path, "..") == 0)
    {
        return 0;
    }
	
    // vraca na pocetni dir.
    else if(strcmp(path, "\\home") == 0)
    {
        if(chdir(rootUserAdress) == 0)
        {
            return 1;
        }
    }
	
    // vraca na prijašnji dir.
    else if (strcmp(path, "\\back") == 0)
    {
        setCurentUserAdress();
        if(strcmp(curentUserAdress, rootUserAdress) != 0)
        {
            if (chdir("..") == 0)
            {
                return 1;
            }
        }
    }
	
    // premjesta se sa trenutnog dir. na path
    else if(chdir(path) == 0)
    {
        return 1;
    }
	
    // pokusava da na curentUserAdress doda path pa da tako promjeni dir.
    else
    {
        setCurentUserAdress();
        char* tmprAdress = (char*)malloc(strlen(curentUserAdress) + strlen(path) + 1);

        strcpy(tmprAdress, rootUserAdress);
        strcat(tmprAdress, path);

        if(chdir(tmprAdress) == 0)
        {
            return 1;
        }
        free(tmprAdress);
    }

    return 0;
}

void listDirectory(char *directory, int depth)
{
    DIR *folder;
    struct dirent *element;
    struct stat filestat;

    // odlazi na dir. koji se treba izlistat
    if(directory && !goToDirectorie(directory))
    {
        printf("\nCan't List Directory!\n\n");
        return;
    }

    folder = opendir(".");
	
    if(folder == NULL)
    {
        printf("\nCan't List Directory!\n\n");
        return;
    }
	
     // ispisuje sadrzaj direktorijuma
    while((element = readdir(folder)))
    {
        /* preskace . i .. */
        if(strcmp(element->d_name, ".") == 0 || strcmp(element->d_name, "..") == 0)
        {
            continue;
        }

        printf("%*s%s\n", depth*4, " ", element->d_name);

        /* ako neki element direktorijum rekurzivno ulazi u nega
        i ispisuje negov sadrzaj*/
        stat(element->d_name, &filestat);
        if( S_ISDIR(filestat.st_mode) )
        {
            listDirectory(element->d_name, depth+1);
        }
    }
    
	/* ako izlistava trenutni dir. da se ne vraca nazad kroz stablo */
    if(directory)
    {
        chdir("..");
    }
	
    closedir(folder);
}
