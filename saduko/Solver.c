/**
 * Solver.c
 *	a.	This module implements the Backtrack algorithms.
 *	b.	The user of this module is not aware of the
 *			algorithm behind the module, i.e. it solves the board and the actual
 *			implementation freely change without "breaking" the public interface
 *			of the module.
 *	c. contain's a solver method, and a puzzle
 *			generator method (which supplies a puzzle as well as a solution).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Main_aux.h"
#include "Parser.h"
#include "Game.h"
#include "Solver.h"

/**
 * array_cut:
 * this method remove zeros from array of possible value of cell
 *
 * @param size		- Size of the array
 * @param nums		- pointer for a given array of integers.
 * @param table_size- The dimensions of the table
 * @return pos_nums
 */
int* array_cut(int size, int* nums, int table_size) {
	int *pos_nums = (int *) calloc(size + 1, sizeof(int));
	int i, j = 1;
	if (pos_nums == NULL) {
		printf("Error: <calloc> has failed\n");
		exit(0);
	}
	pos_nums[0] = size;
	for (i = 0; i < table_size; ++i) {
		if (nums[i] != 0) {
			pos_nums[j] = nums[i];
			j++;
		}
	}
	free(nums); /*free int array nums which define in 'posible_nums' method*/
	return pos_nums;
}

/**
 * find_first_open_cell:
 * this method return the position (between 1 to 81) of first not fixed cell
 *
 * @param board 		- Pointer to the game board
 * @param table_size	- The dimensions of the table
 * @return
 */
int find_first_open_cell(Box **board, int table_size) {
	int i, j;
	for (i = 0; i < table_size; ++i) {
		for (j = 0; j < table_size; ++j) {
			if (board[i][j].value == 0) {
				return ((i * table_size) + (j + 1));
			}
		}
	}
	return 0;
}

/**
 * posible_nums_row:
 *this method return possible values to specific cell according to its row
 * @param board 		- Pointer to the game board
 * @param row			- The requested cell Row index
 * @param ok_nums		- Pointer to array of the Possible numbers to place in the given cell.
 * @return
 */
int* posible_nums_row(Box **board, int row, int height, int *ok_nums) {
	int i, temp;
	for (i = 0; i < height; i++) {
		temp = board[row][i].value;
		if (temp != 0) {
			if (ok_nums[temp - 1] != 0) {
				ok_nums[temp - 1] = 0;
			}
		}
	}
	return ok_nums;
}

/**
 * posible_nums_column:
 *this method return possible values to specific cell according to its column
 * @param board 		- Pointer to the game board
 * @param clmn			- The requested cell column index
 * @param height		- The dimensions of the table
 * @param ok_nums		- Pointer to array of the Possible numbers to place in the given cell.
 * @return
 */
int* posible_nums_column(Box **board, int clmn, int height, int *ok_nums) {
	int i, temp;
	for (i = 0; i < height; i++) {
		temp = board[i][clmn].value;
		if (temp != 0) {
			if (ok_nums[temp - 1] != 0) {
				ok_nums[temp - 1] = 0;
			}
		}
	}
	return ok_nums;
}

/**
 * posible_nums_Block:
 * this method return possible values to specific cell according to its block
 * @param board 		- Pointer to the game board
 * @param block_row * 	- The requested cell Row index
 * @param block_clmn	- The requested cell column index
 * @param ok_nums		- Pointer to array of the Possible numbers to place in the given cell.
 * @param block_size
 * @return ok_nums after cleaning the numbers that are not allowed at this block of cells.
 */
int* posible_nums_Block(Box **board, int block_row, int block_clmn,
		int *ok_nums, int block_size) {
	int i, j, temp;
	for (i = 0; i < block_size; i++) {
		for (j = 0; j < block_size; j++) {
			temp =
					board[block_row * block_size + i][block_clmn * block_size
							+ j].value;
			if (temp != 0) {
				ok_nums[temp - 1] = 0;
			}
		}
	}
	return ok_nums;
}

/**
 * posiable_nums:
 * this method return possible values to specific cell according to its row, column and block
 *
 * @param board			- The game board pointer
 * @param row			- The requested cell Row index
 * @param clmn			- The requested cell Column index
 * @param table_size	- The dimensions of the table
 * @param block_size	- The Dimensions of single "Block" at the given game table.
 * @return
 */
int * posiable_nums(Box **board, int row, int clmn, int table_size,
		int block_size) {
	int x, i, cnt = 0, temp;
	int block_row, block_clmn;
	int *ok_nums = (int *) calloc(table_size, sizeof(int)); /*Initialize array, size=10, first cell to size*/
	if (ok_nums == NULL) {
		printf("Error: <calloc> has failed\n");
		exit(0);
	}
	for (x = 0; x < table_size; x++) {
		ok_nums[x] = x + 1;
	}/*After  the 'for' ok_nums is = [1,2,3,4,5,6,7,8,9]  - (for table_size = 9) */

	/*delete neighbors from the same row */
	ok_nums = posible_nums_row(board, row, table_size, ok_nums);

	/*delete neighbors from the same column */
	ok_nums = posible_nums_column(board, clmn, table_size, ok_nums);

	/*get the Block index's */
	block_row = row / block_size;
	block_clmn = clmn / block_size;

	/*delete neighbors from the same block */
	ok_nums = posible_nums_Block(board, block_row, block_clmn, ok_nums,
			block_size);

	/*delete notAllowed - if we are in Backtracking*/
	for (i = 0; i < table_size; i++) {
		temp = board[row][clmn].notAllowed[i];
		if (temp == 1) {
			ok_nums[i] = 0;
		}
	}

	/* now all the numbers that we cleared will appear as '0' in 'nums' array */
	for (i = 0; i < table_size; ++i) {
		if (ok_nums[i] == 0) {
			cnt++; /*count all the zeros*/
		}
	}
	return (array_cut(table_size - cnt, ok_nums, table_size));
}/*END OF POSIABLE_NUMS*/

/**
 * clean_notAllowed:
 * clean the list of not possible values for specific cell
 * @param board			- The game board pointer
 * @param row			- The requested cell Row index
 * @param clmn			- The requested cell Column index
 * @param arrySize
 */
void clean_notAllowed(Box **board, int row, int clmn, int arrySize) {
	int k;
	for (k = 0; k < arrySize; ++k) {
		board[row][clmn].notAllowed[k] = 0;
	}
}

/**
 * randmoize_backtracking:
 * this method randomly backtracking the board to find legal value placement for all empty cells
 * if it succeed the board is solvable.
 * @param board 		- Pointer to the game board
 * @param table_size	- The dimensions of the table
 * @param block_size	- The Dimensions of single "Block" at the given game table.
 * @return				- "0" if the algorithm failed to solve the board: Board is unsolvable.
 * 						- "1" if the algorithm succeed to solve the board: Board is solvable
 */
int randmoize_backtracking(Box **board, int table_size, int block_size) {
	int val;
	int i = 0, j = 0, preval;
	int *nums;

	/* now the index's are at the first cell that is not fixed */
	while ((i < table_size) && (j < table_size)) {
		if (board[i][j].fixed == 1) { /*increase index's to next cell to validate*/
			if (j < table_size - 1) {
				j = j + 1;
			} else {
				j = 0;
				i = i + 1;
			}
			continue;
		}
		nums = posiable_nums(board, i, j, table_size, block_size); /* get the possible numbers to this cell*/
		if (nums[0] == 0) { /*backtracking-No possible values to put in the cell*/
			if (i == 0 && j == 0) {
				free(nums);
				return 0;
			} else { /*go to the previous cell*/
				clean_notAllowed(board, i, j, table_size);
				if (i == 0 && j == 0) {
					return 0;
				}
				j = j - 1;
				if (j < 0) {
					j = table_size - 1;
					i = i - 1;
				}
			}
			preval = board[i][j].value;
			board[i][j].value = 0;
			board[i][j].fixed = 0;
			board[i][j].notAllowed[preval - 1] = 1;
		} else { /* no need backtracking, choose random possible number*/
			/*print_board(board, table_size, block_size);*/
			if (nums[0] == 1) {
				val = nums[1];
			} else {
				val = nums[(rand() % nums[0]) + 1];
			}
			board[i][j].value = val;
			board[i][j].fixed = 1;
			if (j < table_size - 1) {
				j = j + 1;
			} else {
				j = 0;
				i = i + 1;
			}
		}
		free(nums); /*free int array nums which define in 'array_cut' method*/
	}
	return 1;
}
/*END OF RANDOMIZE_BACKTRACKING */

/**
 * deterministic_backtracking:
 * Backtracking deterministically at the board to find legal value for all empty cells
 * @param test_board 	- Pointer for the Game-Board
 * @param table_size	- The dimensions of the table
 * @param block_size	- The Dimensions of single "Block" at the given game table.
 * @return				- "0" if the algorithm failed to solve the board: Board is unsolvable.
 * 						- "1" if the algorithm succeed to solve the board: Board is solvable
 */
int deterministic_backtracking(Box **test_board, int table_size, int block_size) {
	int start_row = 0, start_clmn = 0, i = 0, j = 0, preval;
	int *nums;
	while ((i < table_size) && (j < table_size)) {
		if (test_board[i][j].fixed == 1) { /*increase index's to next cell to validate*/
			if (j < table_size - 1) {
				j = j + 1;
			} else {
				j = 0;
				i = i + 1;
			}
			/*i,j are index's of "NOT-FIXED" cell*/
		} else {
			nums = posiable_nums(test_board, i, j, table_size, block_size); /* get the possible numbers to this cell*/
			if (nums[0] == 0) { /*No possible values to put in the cell*/
				if ((i == start_row) && (j == start_clmn)) {
					free(nums);
					return 0; /*the board is unsolved*/
				} else {
					clean_notAllowed(test_board, i, j, table_size);
					do {
						j = j - 1;
						if (j < 0) {
							j = table_size - 1;
							i = i - 1;
						}
						if ((i == start_row) && (j == start_clmn)) {
							free(nums);
							return 0; /*the board is unsolved*/
						}
					} while (test_board[i][j].fixed == 1);
					preval = test_board[i][j].value;
					test_board[i][j].notAllowed[preval - 1] = 1;
					test_board[i][j].value = 0;

				}
			} else { /* no need backtracking, choose first possible number*/
				test_board[i][j].value = nums[1];
				if (j < table_size - 1) { /*Append index's to next cell*/
					j = j + 1;
				} else {
					j = 0;
					i = i + 1;
				}
			}
			free(nums); /*free int array nums which define in 'array_cut' method*/
		}
	}
	return 1;
}/*END OF DETERMENISTIC_BACKTRACKING*/

/**
 * copyBoard:
 * Allocate new space in the memory for the cloned board.
 * and return an  copy of the original board
 * the memory allocated for the cloned-board is freed in Validate() after the use.
 * @param board			- Pointer to game board
 * @param table_size	- The dimensions of the table
 * @return
 * cloned board
 */
Box** copyBoard(Box**board, int table_size) {
	int i, j;
	Box** clone_board = (Box**) malloc_board(Table_Size);
	for (i = 0; i < table_size; i++) {
		for (j = 0; j < table_size; j++) {
			clone_board[i][j].value = board[i][j].value;
			if (clone_board[i][j].value == 0) {
				clone_board[i][j].fixed = 0;
			} else {
				clone_board[i][j].fixed = 1;
			}
		}

	}
	return clone_board;
}

/**
 * copySolvedBoard:
 * Gets the game board after the initialization (the board is full!) and copy it.
 * This method can be used to copy board if we created 2 boards and set them as arguments.
 *
 * @param board 		- Pointer to the game board
 * @param solved 		- Pointer to the solved board
 * @param table_size	- The dimensions of the table
*/
void copySolvedBoard(Box **board, Box **solved, int table_size) {
	int i, j;
	for (i = 0; i < table_size; i++) {
		for (j = 0; j < table_size; j++) {
			solved[i][j].value = board[i][j].value;
			solved[i][j].fixed = board[i][j].fixed;
		}
	}
}

/**
 * hint:
 * return hint for a good placement value for a specific cell
 * @param user_command	- a structure the containing the user command to the program(row & column for a given cell).
 * @param board			- Pointer to the game board
 * @return
 */
int hint(Move* user_command, Box** board) {
	int row = user_command->row;
	int clmn = user_command->column;
	return board[row - 1][clmn - 1].value;
}

/**isValidate:
 * this method run's the deterministic backtracking method on current state of board to check if is validate
 * @param board 		- Pointer to the game board
 * @param table_size	-The dimensions of the table
 * @param block_size	-The Dimensions of single "Block" at the given game table.
 * @return
 */
int isValidate(Box **board, Box **solved_board, int table_size, int block_size) {
	Box **test_board = copyBoard(board, table_size);
	int validTable = 0;
	validTable = deterministic_backtracking(test_board, table_size, block_size);

	if (validTable == 1) { /* the board is solvable*/
		copySolvedBoard(test_board, solved_board, table_size); /*copy the update solution of the board*/
	}
	/*free the "help board" that created in copyBoard method */
	free_board(test_board, table_size);
	return validTable;
}

