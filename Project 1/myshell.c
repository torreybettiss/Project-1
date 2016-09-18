/* 
 * This program prompts the user for two input values to compute the average of the two values.
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

    return (EXIT_SUCCESS);
}

