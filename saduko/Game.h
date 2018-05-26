/**
 * Game Summary:
 *
 * This module encapsulates the Saduko puzzle game and the Saduko board.
 * It will be used to store and manipulate the game status, validate, and set
 * moves, and so on.
 *
 * valueExsists			- Checks if value is inside an array
 * print_board			- Print the game board on the screen
 * build_board			- Build a game board and a solution board
 * initilaize_game  	- Initiate the game by asking the user for the number of cells to fill
 * set_cell 			- Set value to cell according to user choice,
 * board_check			- Check if the board is solved and the game is completed
 * run_game				- Run the game after the first initialization until finishing the game or restarting it
 */

#ifndef GAME_H_
#define GAME_H_
#define  Table_Size 9 /*Integer constant*/
#define  Block_Size 3 /*Integer constant*/

/**
 * 'Box' is the structure of a single Cell it contains:
 * 	1.	 value 	- the value of the cell
 * 	2.	 fixed 	- A flag:
 * 	 		fixed value = 1 : the cell is "fixed" , placement to this cell is not legal.
 * 			fixed value = 0	: the cell is "not-fixed" , placement to this cell is legal.
 * 	3. notAllowed - an array of integers used by the methods to determine which numbers are legal to
 * 					place in this cell.
 */

typedef struct Box {
	int value;
	int fixed;
	int notAllowed[9];
}Box;


Box** initialize_game(int table_size, Box** solved_board,int block_size);
Box **build_board(Box **board, int numOfcells, Box** solved_board, int table_size, int block_size);
void print_board(Box **board, int table_size, int block_size);
void starting_board(Box **board, int numOfcells, int table_size);
int run_game(Box **board, Box **solved_board, int table_size, int block_size);
int valueExsists(int* arr,int value);
int board_check(Box **board, int size);
#endif /* GAME_H_ */

