/* 
 * @File:   parse.h
 * @author Ashley Miller
 * @date 8/24/2016
 * @info Course COP4634
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
 * @return: nothing
 */
void parseInput(ParamP , char []);

/*
 * Prints the values of the PARAM structure
 * @param: pointer to the PARAM structure
 * @return: nothing
 */
void printParams(ParamP);


#endif /* PARSE_H */