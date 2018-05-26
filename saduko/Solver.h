/**
 * Solver Summary:
 *
 * This module is used to generate a Saduko game by using he randomize backtracking algorithm,
 *
 * array_cut    			- Returns minimize array with no Zeros.
 * posible_nums_row			- Return possible values to specific cell according to its row
 * posible_nums_column		- Return possible values to specific cell according to its column
 * posible_nums_Block		- Return possible values to specific cell according to its block
 * posible_nums				- Return possible values to specific cell according to its row, column and block
 * randmoize_backtracking	- Backtracking randomly  at the board to find legal value for all empty cells
 * deteministic_backtracking- Backtracking deterministically at the board to find legal value for all empty cells
 * clean_notAllowed			- Clean the list of not possible values for specific cell
 * find_first_open_cell		- Return the position (between 1 to 81) of first not fixed cell
 * copyBoard				- Return a pointer of the copy of the original board
 * copySolvedBoard			- Gets the game board after the initialization
 * isValidate				- Checks if the board is solvable
 * hint						- Gives a hint of a good placement value for a specific cell
 */

#ifndef SOLVER_H_
#define SOLVER_H_


int* array_cut(int size, int* nums, int table_size);

int * posiable_nums(Box **board, int row, int clmn ,int table_size,int block_size);

int randmoize_backtracking(Box **board, int table_size, int block_size);

int deterministic_backtracking(Box **board, int table_size, int block_size);

void clean_notAllowed(Box **board,int row,int clmn,int arrySize);

int* posible_nums_row(Box **board, int row, int height, int *ok_nums);

int* posible_nums_column(Box **board, int clmn, int height, int *ok_nums);

int* posible_nums_Block(Box **board, int block_row, int block_clmn,int *ok_nums, int block_size);

int find_first_open_cell(Box **board,int table_size);

Box** copyBoard(Box**board,int table_size);

void copySolvedBoard(Box**board,Box** solved,int table_size);

int isValidate(Box **board,Box **solved_board, int table_size, int block_size);

int hint(Move* user_command,Box** board);


#endif /* SOLVER_H_ */
