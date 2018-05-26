/**
 * Parser.c
 * This module is used to read the the user inputs lines that represents saduko game commands,and interpret them.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"

/**
 * commmand_chack:
 * gets the user input line ('input'-of type char*) ,parse it and determines the user command.
 *
 * @param input - the user first string at the command line.
 * @return
 * '0'	- if the command is not legal and otherwise:
 * 's'- for "set"
 * 'h'- for "hint"
 * 'v'- for "validate"
 * 'r'- for "restart"
 * 'e'- for "exit"
 */
char commmand_chack(char* input) {
	int rc = strcmp(input, "set"); /*SET COMMAND */
	if (rc == 0) {
		return 's';
	}
	rc = strcmp(input, "hint"); /*HINT COMMAND */
	if (rc == 0) {
		return 'h';
	}
	rc = strcmp(input, "validate"); /*VALIDATE COMMAND */
	if (rc == 0) {
		return 'v';
	}
	rc = strcmp(input, "restart"); /*RE-START COMMAND */
	if (rc == 0) {
		return 'r';
	}
	rc = strcmp(input, "exit"); /*EXIT COMMAND */
	if (rc == 0) {
		return 'e';
	}
	return '0';
}

/**
 * move_input:
 * This function gets the user move from the keyboard and enters it to 'Move' structure and returns it
 * @return
 * Move instance;
 */
Move* move_input() {
	char input[MAX_STRING];
	char* token;
	char cmd = '0';
	const char delimiter[] = " \t\r\n";
	Move* user_move = malloc(sizeof(Move));
	if(user_move==NULL){
		printf("Error: <malloc> has failed\n");
		exit(0);
	}
	/* initiate move */
	user_move->column = 0;
	user_move->row = 0;
	user_move->val = 0;

	do {
		if (fgets(input, MAX_STRING, stdin) == NULL) {
			/*printf("Error: <fgets> has failed\n");*/
			printf("Exiting...");
			exit(0);
		}
		token = strtok(input, delimiter);
		cmd = commmand_chack(token);
		if (cmd == '0') {
			printf("Error: invalid command\n");
		}

	} while (cmd == '0'); /* while user set invalid command*/

	user_move->comannd = cmd;
	token = strtok(NULL, delimiter);
	if (cmd == 'h' || cmd == 's') { /*get from user the row, column and value*/
		user_move->column = atoi(token);
		token = strtok(NULL, delimiter);
		user_move->row = atoi(token);
		if (cmd == 's') {
			token = strtok(NULL, delimiter);
			user_move->val = atoi(token);
		}
	}
	return user_move;
}/*END OF  MOVE_INPUT*/

