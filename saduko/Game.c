/**
 * Game Summary:
 *
 * This module encapsulates the Saduko puzzle game and the Saduko board.
 * It will be used to store and manipulate the game status, validate, and set
 * moves, and so on.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Main_aux.h"
#include "Parser.h"
#include "Game.h"
#include "Solver.h"
char GameMode = 'i';
/**
 * valueExsists:
 * this method gets a value and array and returns if the  value is inside the array
 * @param arr
 * @param value
 * @return
 * '1' if value is inside the 'arr' array.
 *  else returns '0'
 */
int valueExsists(int* arr, int value) {
	int i, size = arr[0];
	for (i = 1; i <= size; ++i) {
		if (value == arr[i]) {
			return 1;
		}
	}
	return 0;
}

/**
 * print_board:
 * The method get board and print this board on the screen
 * @param board
 * @param table_size
 * @param block_size
 */

void print_board(Box **board, int table_size, int block_size) {
	int row, column, i;
	int block_clmns = block_size; /* block_clmns = Number of columns in block*/
	/*int block_rows = table_size / block_clmns;*//* block_rows = Number of rows in block*/
	for (i = 0; i < (4 * table_size + block_clmns + 1); i++) { /* Print Separator row*/
		printf("-");
	}
	printf("\n");
	for (row = 0; row < table_size; ++row) {
		for (column = 0; column < table_size; ++column) {
			if (column % block_clmns == 0) {
				printf("|");
			}
			if (board[row][column].value == 0) { /*empty cell for zero value*/
				printf("    ");
			} else {
				if (board[row][column].fixed == 1) { /*if the cell is Fixed */
					printf(".%2d ", board[row][column].value);
				} else {
					printf(" %2d ", board[row][column].value);
					/*	'*' for an erroneous cell when in Edit  mode or the "Mark errors" parameter is set to 1, or space otherwise.  */
				}
			}
		}
		printf("|\n");
		if (row % block_size == block_size - 1) {
			for (i = 0; i < (4 * table_size + block_clmns + 1); i++) { /* Print Separator row*/
				printf("-");
			}
			printf("\n");
		}
	}
}

/**
 * build_board:
 * Gets the 2 pointers for 2 boards  , and build a solved board using randomize backtracking method,
 * And clean random cells (the number of clean cells is in numOfcells)
 * @param board 		- the game board
 * @param numOfcells	- The number of cells to "clean"
 * @param solved_board	- The pointer for the solution of the game
 * @param table_size	- Const. (int) the default is '9'
 * @param block_size	- Const. (int) the default is '3'
 * @return
 * pointer for the game board (Box 2-dimensional array)
 */
Box **build_board(Box **board, int numOfcells, Box** solved_board,
		int table_size, int block_size) {
	int i;
	for (i = 0; i < table_size; ++i) {
		int j;
		for (j = 0; j < table_size; ++j) {
			int k;
			board[i][j].value = 0;
			board[i][j].fixed = 0;
			for (k = 0; k < table_size; ++k) {
				board[i][j].notAllowed[k] = 0;
			}
		}
	}
	randmoize_backtracking(board, table_size, block_size);
	copySolvedBoard(board, solved_board, table_size);
	starting_board(board, numOfcells, table_size);
	return board;
}

/**
 * initilaize_game:
 * asks the number of cells to fill,it will "loop" until a good input will enter by the user (number between 1-80)
 * Than it call's the build_board method to build a game board an a solution board
 *r
 * @param table_size 	- Const. (int) the default is '9'
 * @param solved_board 	- Pointer for the predefined solved board.
 * @param block_size	- Const. (int) the default is '3'
 * @return
 * pointer for the game board (Box 2-dimensional array)
 */
Box** initialize_game(int table_size, Box** solved_board, int block_size) {
	int cells;
	char numOfcells[MAX_STRING];
	char* token;
	Box** board = (Box**) malloc_board(Table_Size);
	do { /*Get user number of cell to fill*/
		printf("Please enter the number of cells to fill [0-%d]:\n",
				table_size * table_size - 1);
		if (fgets(numOfcells, MAX_STRING, stdin) == NULL) {
			printf("Exiting...");
			exit(0);
		}
		token = strtok(numOfcells, " \t\r\n");
		cells = atoi(token);
		if ((cells < table_size * table_size) && (cells > 0)) { /*check if the number is legal ,depends on the board size*/
			break;
		}
		printf(
				"Error: invalid number of cells to fill (should be between 0 and %d)\n",
				table_size * table_size - 1);
	} while (!((cells < table_size * table_size) && (cells > 0)));

	board = build_board(board, cells, solved_board, table_size, block_size);
	print_board(board, table_size, block_size);
	return board;

}

/**
 * starting_board:
 * this method clean's selected number of cells randomly from given game board
 * @param board 		- the game board
 * @param numOfcells	- The number of cells to "clean"
 * @param table_size	- Const. (int) the default is '9'
 */
void starting_board(Box **board, int numOfcells, int table_size) {
	int row, clmn, i, j, k;
	for (i = 0; i < table_size; ++i) {
		for (j = 0; j < table_size; ++j) {
			board[i][j].fixed = 0;
		}
	}
	for (k = 0; k < numOfcells; ++k) {
		do {
			clmn = rand() % table_size;
			row = rand() % table_size;
		} while (board[row][clmn].fixed == 1); /*if the random cell already empty - continue select cell to empty*/
		/* got to  a cell with value !=0 */
		board[row][clmn].fixed = 1;
	}
	for (i = 0; i < table_size; ++i) {
		for (j = 0; j < table_size; ++j) {
			if (board[i][j].fixed == 0) {
				board[i][j].value = 0;
			}
		}
	}

}

/**
 * set_cell:
 * This method try to set value to cell according to user choice,
 * if the placement  isn't legal for the selected cell or selected value, the method print error message to user
 *
 * @param board 		- the game board
 * @param user_move		- the user desired cell index's & value of placement
 * @param table_size 	- Const. (int) the default is '9'
 * @param block_size	- Const. (int) the default is '3'
 * @return
 * 1 - if cell is fixed or value is invalid  (nor between 0-9)
 * 0 - for good placement
 */
int set_cell(Box **board, Move* user_move, int table_size, int block_size) {
	int row = user_move->row - 1;
	int clmn = user_move->column - 1;
	int val = user_move->val;
	int * pos_nums;
	if (board[row][clmn].fixed == 1) {
		printf("Error: cell is fixed\n"); /*try to set value to fixed cell*/
	} else {
		if (val == 0 || val == board[row][clmn].value) {
			board[row][clmn].value = val;
			return 0;
		} else {
			pos_nums = posiable_nums(board, row, clmn, table_size, block_size);
			if (valueExsists(pos_nums, val) == 1) {
				board[row][clmn].value = val;
				free(pos_nums);
				return 0;
			}
			free(pos_nums);
		}
		printf("Error: value is invalid\n"); /*selected value is wrong*/
	}

	return 1;
}

/**
 * board_check:
 * This method check if the board full and solved, it runs on all the board cells and if no-one
 * of the cells equal to zero(No zero is in the board table!) than the board is solved.
 * Developer assumption: the only placement's of value's to cells are the legal placement's.
 *
 * @param board 		- the game board
 * @param table_size	- Const. (int) the default is '9'
 * @return
 * 1 - Solved board
 * 0 - Not-Solved board
 */
int board_check(Box **board, int table_size) {
	int i, j;
	for (i = 0; i < table_size; ++i) {
		for (j = 0; j < table_size; ++j) {
			if (board[i][j].value == 0) {
				return 0;
			}
		}
	}
	return 1;
}

void invalid_command() {
	printf("Error: invalid command\n");
}
void set_command(Move* user_command, Box **board, int table_size,
		int block_size, int board_status, int game_stat, int status) {
	if (board_status == 0) { /*check if board not solved*/
		status = set_cell(board, user_command, table_size, block_size);
		if (status == 0) { /*legal set*/
			print_board(board, table_size, block_size); /*cell is update print board*/
			board_status = board_check(board, table_size);
			if (board_status == 1) {
				printf("Puzzle solved successfully\n");
				/*after this print only exit or restart available*/
			}
		}
	} else {
		invalid_command();
	}
}

void validate_command(Box **board, Box **solved_board, int table_size, int block_size,int board_status, int game_stat) {
	if (board_status != 1) { /*check if board not solved*/
		game_stat = isValidate(board, solved_board, table_size, block_size);
		if (game_stat == 1) {
			printf("Validation passed: board is solvable\n");
		} else {
			printf("Validation failed: board is unsolvable\n");
		}
	} else {
		invalid_command();
	}
}

void hint_command (int board_status,Move *user_command,Box **solved_board){
	if (board_status != 1) { /*check if board not solved*/
		printf("Hint: set cell to %d\n",
				hint(user_command, solved_board));
	} else {
		invalid_command();
	}
}
char* print_mode(){
	if (GameMode == 'i'){
		return "Initiallize_mode";
	}
	else if (GameMode == 'e'){
		return "Edit Mode";
	}
	else if (GameMode == 's'){
		return "Solve Mode";
	}
return "Error";
}

/**
 * run_game:
 * This method run game according to command's from user until exit/restart command are given by the user
 * or EOF(End-Of-File) is reached.
 *
 * @param board 		- the game board
 * @param solved_board	- The pointer for the solution of the game
 * @param table_size	- Const. (int) the default is '9'
 * @param block_size	- Const. (int) the default is '3'
 * @return
 * 1 - for exit command or EOF
 * 0 - for restart command
 */
int run_game(Box **board, Box **solved_board, int table_size, int block_size) {
	int board_status = 0, game_stat = 0, status = 1;
	Move* user_command;
	do {
		user_command = move_input();
		if (user_command->comannd == 's') { /*SET COMANNED*/
			set_command(user_command, board, table_size, block_size,
					board_status, game_stat, status);
		} else if ((user_command->comannd == 'v')) { /*VALIDATE COMANNED*/
			validate_command(board,solved_board, table_size,block_size,board_status, game_stat);
		} else if ((user_command->comannd == 'h')) { /*HINT COMANNED*/
			hint_command (board_status,user_command,solved_board);
		} else if (user_command->comannd == 'r') { /*RESTART COMANNED*/
			free(user_command);
			free_board(board, table_size);
			return 0;
		} else if (user_command->comannd == 'e') { /*EXIT COMANNED*/
			printf("Exiting...");
			free(user_command);
			return 1;
		} else if ((user_command->comannd == 'S')) { /*Solve-Mode COMANNED*/
			printf("Solve-Mode COMANNED \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'E')) { /*Edit-Mode COMANNED*/
			printf("Edit-Mode COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'm')) { /*mark_errors-Mode COMANNED*/
			printf("mark_errors COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'g')) { /*generate COMANNED*/
			printf("generate COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'U')) { /*UNDO COMANNED*/
			printf("UNDO COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'R')) { /*REDO COMANNED*/
			printf("REDO COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'F')) { /*save COMANNED*/
			printf("Save COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'n')) { /*num_solutions COMANNED*/
			printf("num_solutions COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'a')) { /*autofill COMANNED*/
			printf("autofill COMANND \n");
			/*ENTER CODE HERE*/
		} else if ((user_command->comannd == 'M')) { /*print_current_mode COMANNED*/
				printf("Current_Mode: %s \n",print_mode());
			}
		free(user_command);
	} while (1);
	return 0;
}/*END OF RUN_GAME*/

/*new method's */

