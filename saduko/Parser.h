/**
 * Parser Summary:
 * This module is used to read the the user inputs lines that represents saduko game commands,and interpret them.
 *
 * commmand_chack    	- Determines the user command
 * move_input			- Parse the user input line , and determines the user command
 */

#ifndef PARSER_H_
#define PARSER_H_
#define MAX_STRING 1024  /*maximum length of command line*/

/**
 * 'Move' is the structure of a single user command it contains:
 * 	1. column 	- the column of the cell the user entered.
 * 	2. row 		- the row of the cell the user entered.
 * 	3. val 		- the value of the cell the user entered.
 * 	4. command 	- the user command (as a char) the first letter of the command string.
 */
typedef struct Move {
	int column;
	int row;
	int val;
	char comannd;
}Move;

Move* move_input();
char commmand_check(char* input);

#endif /* PARSER_H_ */
