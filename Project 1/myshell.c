/* 
 * This program simulates a shell the user can use to execute
 * files in their directory. The user can also import arguments
 * through an input file and output program execution results
 * to an output file the create.
 * 
 * @authors Ashley Miller / Torrey Bettis
 * @date 8/24/2016
 * @info Course COP4634 Project 1
 */

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

/*
 * 
 */
int main(int argc, char** argv)
{ 
    ParamP param = newParam();
    runPrompt(param, argv[1]);
    freeParam(param);	

    return (EXIT_SUCCESS);
}

