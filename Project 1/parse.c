/*
 * @File:   parse.c
 * @author Ashley Miller
 * @date 8/24/2016
 * @info Course COP4634
 */
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
/* don’t test program with more than this many tokens for input */
#define MAXARGS 32

/*
 * Checks the buffer to see if user entered
 * exit, if so the program closes
 * @param: the input buffer
 * @return: nothing
 */
void checkExit(char []);

/*
 * Creates a pointer to a new PARAM structure
 * @param: none
 * @return: PARAM pointer
 */
 int checkNumInstances(ParamP );

/*
 * Creates a pointer to a new PARAM structure
 * @param: none
 * @return: PARAM pointer
 */
 int isIntCheck(ParamP );

 /*
  *
  */
 void initializeParam(ParamP );

void programCall(ParamP param);
void fileOut(ParamP param);
void pathFinder();

/* structure to hold input data */
struct PARAM
{
    char *inputRedirect; /* file name or NULL */
    char *outputRedirect; /* file name or NULL */
    int argumentCount; /* number of tokens in argument vector */
    char *argumentVector[MAXARGS]; /* array of strings */
};

/* a typedef so we don’t need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;


ParamP newParam()
{
    ParamP param = malloc(sizeof(Param_t));

    if(param == NULL)
    {
        printf("Parameter creation failed");
        return NULL;
    }

    initializeParam(param);

    return param;
}

void runPrompt(ParamP param, char * argv)
{
    char * prompt = "$$$ ";


    while(prompt)
    {
        char buffer[500];
        printf("%s", prompt);
        fgets(buffer, 500, stdin);
        checkExit(buffer);
        parseInput(param, buffer);

        if(argv != NULL && strcmp(argv, "[-Debug]") == 0)
        {
            printParams(param);
        }
        programCall(param);
    }
}

void parseInput(ParamP param, char buffer[])
{
    char * token;
    char delimiters[] = "[' '|'\t''\n']+]*";

    token = strtok(buffer, delimiters);

    while(token != NULL)
    {
        if(token[0] == '<' && token[1])
        {
            param->inputRedirect = &token[1];
        }
        else if(token[0] == '>')
        {
            param->outputRedirect = &token[1];
        }
        else
        {
            param->argumentVector[param->argumentCount] = token;
            param->argumentCount++;
        }

        token = strtok(NULL , delimiters);
    }

    if(checkNumInstances(param) == 0)
    {
        printf("To many instances requested.  Please enter 4 or less requests.\n");
        initializeParam(param);
        return;
    }

    if(isIntCheck(param) == 0)
    {
        printf("Second argument must be an integer.\n");
        initializeParam(param);
        return;
    }


}

void printParams(Param_t * param)
{
    int i;

    printf ("InputRedirect: [%s]\n", (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
    printf ("OutputRedirect: [%s]\n", (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
    printf ("ArgumentCount: [%d]\n", param->argumentCount);

    for (i = 0; i < param->argumentCount; i++)
    {
        printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
    }
}

void checkExit(char buffer[])
{
    if(strcmp(buffer, "exit\n") == 0)
    {
        exit(EXIT_SUCCESS) ;
    }
}

int checkNumInstances(ParamP param)
{
    if(param->argumentCount > 4)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int isIntCheck(ParamP param)
{
    int i = 0;
    char * temp = param->argumentVector[1];

    while(i < strlen(temp))
    {
        if(isdigit(temp[i]) == 0)
        {
            return 0;
        }

        i++;
    }

    return 1;
}

void initializeParam(ParamP param)
{
    int i = 0;

    param->inputRedirect = NULL;
    param->outputRedirect = NULL;
    param->argumentCount = 0;

    while(i < MAXARGS)
    {
        param->argumentVector[i] = NULL;
        i++;
    }
}
void programCall(ParamP param)
{
    int j;
    int k =0;
    int  status;
/*
    b = setenv("PATH", "/home/ARGONET/tlb76/Documents/p1/",0);
    char* fullPath = getenv( "PATH" );
    printf("The new path is %s and b is %d \n",fullPath, b);
*/
         pid_t pArray[param->argumentCount];  // Array to hold children program ID numbers
          for(j =0; j < param->argumentCount-1; j++)
           {
               pArray[j]=fork();    //Assigns child PID to array for wait call
               if(pArray[j]==0)     //If PID is 0, then child program, this will call exec function
                {
                    fileOut(param);
                   k= execlp("/home/ARGONET/tlb76/Documents/p1/prime", param->argumentVector[0],param->argumentVector[2],NULL);
                  //  k = execlp("/home/ARGONET/tlb76/Documents/p1/tester","tester", NULL);

                   if(k==-1)
                    {
                        printf("Please enter name of valid program. \n");
                          initializeParam(param);
                        break;
                       
                    }
                }

                wait(&status);      //Hold main program up, until all children are gone
            }

}

void fileOut(ParamP param)
{
    FILE *execOutput;
    execOutput = freopen(param->outputRedirect, "w", stdout);
    // fclose(execOutput);
     if(execOutput==NULL)
     {
         printf("No output file was opened. \n");
     }
}

void pathFinder(ParamP param)
{
  /*  
  char buffer [50];
  char* prefix = "/bin/";
  sprintf (buffer, prefix, param->argumentVector[0]);
  printf ("Path is [%s] \n",buffer);

DIR *dp;
  struct dirent *ep;

  dp = opendir ("./");
  if (dp != NULL)
    {
      while (ep = readdir (dp))
        puts (ep->d_name);
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  

    printf("PATH : %s\n", getenv("PATH"));
  printf("HOME : %s\n", getenv("HOME"));
  printf("ROOT : %s\n", getenv("ROOT"));

return 0;
*/
}

