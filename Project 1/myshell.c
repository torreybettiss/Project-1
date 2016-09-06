/* 
 * This program prompts the user for two input values to compute the average of the two values.
 * 
 * @author Ashley Miller
 * @date 8/24/2016
 * @info Course COP4634
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

