/* 
 * @File:   parse.c
 * @authors Ashley Miller / Torrey Bettis
 * @date 8/24/2016
 * @info Course COP4634 Project 1
 */
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* donâ€™t test program with more than this many tokens for input */
#define MAXARGS 32

/*
 * Checks the buffer to see if user entered 
 * exit, if so the program closes
 * @param: the input buffer
 * @return: nothing
 */
void checkExit(char []);

/*
 * Checks to make sure the number of entries from the
 * buffer is not more than 4
 * @param: param structure
 * @return: 0 if more than 4, 1 if 4 or less
 */
 int checkNumInstances(ParamP );
 
/*
 * Checks to see if the second argument in the PARAM
 * argument vector is an integer
 * @param: the PARAM structure
 * @return: 0 if false, 1 if is an Integer
 */
 int isIntCheck(ParamP );
 
 /*
  * Initializes the PARAM structure
  * @param: param structure
  * @return: nothing
  */
 void initializeParam(ParamP );
 
 /*
  * Performs the actions defined by the user input
  * at the shell command prompt. Sets up input/output file operations
  * and executes the file determined by the user input.
  * @param: param structure
  * @return: nothing
  */
 void programCall(ParamP);
 
 /*
  * Takes the given input file of arguments and adds
  * the arguments to a buffer to be processed into
  * the PARAM structure.
  * @param: param structure
  * @return: 0 for fail, 1 for success
  */
 int getInput(ParamP);
 
 
/* structure to hold input data */
struct PARAM
{
    char *inputRedirect; /* file name or NULL */
    char *outputRedirect; /* file name or NULL */
    int argumentCount; /* number of tokens in argument vector */
    char *argumentVector[MAXARGS]; /* array of strings */
};

/* a typedef so we don't need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;


ParamP newParam()
{
    //Creating new PARAM structure
    ParamP param = malloc(sizeof(Param_t));
    
    //Check creation is success
    if(param == NULL)
    {
        printf("Parameter creation failed");
        return NULL;
    }
    
    //Initialize structure
    initializeParam(param);
    
    return param;
}

void runPrompt(ParamP param, char * argv)
{
    char * prompt = "$$$ ";
    
    //Runs the shell till the user enters "exit"
    while(prompt)
    {  
        char buffer[500];
        
        //Prints prompt for console
        printf("%s", prompt);
        
        //Put user input into buffer
        fgets(buffer, 500, stdin);
        
        //Checks if user entered "exit", if so ends program 
        checkExit(buffer);
        
        //Takes buffer entry and inserts arguments into the PARAM structure
        if(parseInput(param, buffer) != 0)
	{       
        	//If the user passed "[-Debug] at command line PARAM structure
        	//printed for the user to view
        	if(argv != NULL && strcmp(argv, "[-Debug]") == 0)
        	{
            	    printParams(param);
        	}
        
        	//Take PARAM structure values and perform necessary actions
        	programCall(param);
         
        	//Clear the PARAM structure for user to enter next command
        	initializeParam(param);
    	}
    }
}

int parseInput(ParamP param, char buffer[])
{
    char * token;
    char temp[50];
    char delimiters[] = "' '|'\t''\n'][";
    
    //Get first token from buffer
    token = strtok(buffer, delimiters);

    while(token != NULL)
    {
        //Test for < input, > output, or regular argument
        if(token[0] == '<' && token[1])
        {
            param->inputRedirect = &token[1];            
        }
        else if(token[0] == '>' && token[1])
        {
            param->outputRedirect = &token[1]; 
        }
        else if(token[0] != '.' && token[1] != '/' && param->argumentCount == 0)
        {
	    //If just file name is enterd without "./" before it we add it for the user
            strcpy(temp, "./");
            strcat(temp,token);
	    param->argumentVector[param->argumentCount] = temp;
            param->argumentCount++;
        }
        else
        {
            param->argumentVector[param->argumentCount] = token;
            param->argumentCount++;
        }
        
        //Getting next token
        token = strtok(NULL , delimiters);
    }
    
    //Check the total number 
    if(checkNumInstances(param) == 0)
    {
        printf("Must at least pass program to execute and instances as arguments.\n");
        initializeParam(param);
        return 0;
    }
    
    //Check for second argument in argument vector is an Integer
    if(isIntCheck(param) == 0)
    {
        printf("Second argument must be an integer.\n");
        initializeParam(param);
        return 0;
    }

    return 1;
}

void printParams(Param_t * param)
{
    int i;
    
    //Displaying the values in the PARAM structure to the console
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
    //Checks buffer to see if user entered "exit"
    if(strcmp(buffer, "exit\n") == 0)
    {
        exit(EXIT_SUCCESS) ;
    }
}


int checkNumInstances(ParamP param)
{
    //check to make sure at least 2 arguments (exec file and number of processes) is passed
    if(param->argumentCount < 2)
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
    
    //Checks each char if is Integer (returns 1), if not returns 0 
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
    
    //Initializing the values in the PARAM structure
    param->inputRedirect = NULL;
    param->outputRedirect = NULL;
    param->argumentCount = 0;
    
    //Setting values in argument array to NULL
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
    FILE* fp;
    long numProcesses;
    char * ptr;
   
    //Converting string value for number of processes to long for 
    //process evaluation. 
    numProcesses = strtol(param->argumentVector[1], &ptr, 10);

    //Array to hold children program ID numbers
    pid_t pArray[numProcesses];  
           
    for(j =0; j < numProcesses; j++)
    {
        //Assigns child PID to array for wait call
        pArray[j]=fork();    

        //If PID is 0, then child program, this will call exec function
        if(pArray[j]==0)     
        {
            //If there is an output file then open it
            if(param->outputRedirect != NULL)   
            {  
                //Opens and appends file
                fp = freopen(param->outputRedirect, "a", stdout);                     
            }  
        
            //If there is an input file then call getInput function
            if(param->inputRedirect != NULL)
            {   
                //Gets input data from file name passed in inputdirect
                //If it fails to find input file cancel and go back to prompt
                if(getInput(param) == 0)
                {
                    initializeParam(param);
                    return;
                }
            }  
            
            //Executing the program by name as the user specified
            k = execvp(param->argumentVector[0], param->argumentVector);
            
            //Closing file 
            fclose(fp);

            //Check to see if execlp() function failed if -1 is returned
            if(k == -1)
            {
                //If fail notify user and reinitialize PARAM structure
                printf("Please enter name of valid program. \n");
                initializeParam(param);
                break;
            }
        }           
    
        //Hold main program up, until all children are gone
        wait(&status);      
    }
}

int getInput(ParamP param) 
{   
    char* cBuffer;
    long fSize;
    FILE * rp = freopen(param->inputRedirect, "r", stdin);    
   
    //Check if file opened successfully 
    if(rp==NULL)
    {
        printf("Could not open input file. \n");//need to do something//start the prompt over???
        return 0;
    }
    else
    {
        //Getting end of file
        fseek(rp, 0, SEEK_END); 
        
        //Getting size of file, for buffer size
        fSize = ftell(rp); 
                
        cBuffer = (char*) malloc(fSize+2);
        
        //Going back to beginning of file
        rewind(rp);  
        
        //Reading file into cBuffer
        fread(cBuffer, fSize, 1, rp); 
        
        //Closing input file
        fclose(rp);  
        
         //Calling parse function
        parseInput(param, cBuffer);
    }
    
    return 1;
}

ParamP freeParam(ParamP param)
{
	free(param);
	param = NULL;
        return param;
}
