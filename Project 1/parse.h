/* 
 * @File:   parse.h
 * @authors Ashley Miller / Torrey Bettis
 * @date 8/24/2016
 * @info Course COP4634 Project 1
 */

#ifndef PARSE_H
#define PARSE_H

/* typedef for a pointer to a PARAM struct*/
typedef struct PARAM * ParamP;

/*
 * Creates a pointer to a new PARAM structure
 * @param: none
 * @return: PARAM pointer
 */
ParamP newParam();

/*
 * Starts the prompt 
 * @param: none
 * @return: PARAM structure
 */
void runPrompt(ParamP, char *);

/*
 * Parses the string input into tokens and stores the tokens
 * in the PARAM structure
 * @param: pointer to the PARAM structure
 * @return: 0 if errors, 1 if no parsing errors
 */
int  parseInput(ParamP , char []);

/*
 * Prints the values of the PARAM structure
 * @param: pointer to the PARAM structure
 * @return: nothing
 */
void printParams(ParamP);


#endif /* PARSE_H */
