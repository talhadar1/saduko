/*
 * This program is a Saduko game - Final project
 *
 * The program include's 4 modules:
 * 	1. Parser Module 	- Reads the user commands , parse them and send them to the Game module.
 * 	2. Game	Module	 	- Runs the game from initialization to completion.
 * 	3. Solver Module	- This module implements the Backtrack algorithms. that helps to generate the saduko puzzle and solve it.
 * 	3. Main_aux Module	- This module implements Game board memory allocation/deallocation methods.
 *

 * This game default table dimensions   - 9X9 cells. can be modify at Game.h file
 *
 *
 * Written by Tal Hadar 200443968  &   Matan Richker 201263563 at 20/05/18.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SPBufferset.h"
#include "Game.h"
#include "Main_aux.h"


int main(int argc, char **argv){
	Box **board;											/*Game board Pointer*/
	Box** solved_board = (Box**)malloc_board(Table_Size);	/*Solution board initialization*/
	if (argc==2){
		srand(atoi(argv[1]));}								/*Get the "SEED" provided to the program*/
	SP_BUFF_SET();
	/*RUN_GAME*/
	do {
		board = initialize_game(Table_Size, solved_board,Block_Size);}
	while (run_game(board, solved_board,Table_Size,Block_Size) == 0);
	/*GAME OVER*/
	free_board (board ,Table_Size);							/*deallocate Memory of Game board*/
	free_board (solved_board ,Table_Size);					/*deallocate Memory of Solution board*/
	return 0;
}/* END OF MAIN */

