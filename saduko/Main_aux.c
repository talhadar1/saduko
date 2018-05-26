/**
 * Main_aux.c
 * This module implements Game board memory allocation/deallocation methods.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Main_aux.h"
/**
 * malloc_board:
 * Allocate the requested memory for the game board and returns a pointer to it.
 * @param table_size
 * @return board 	-pointer of the board
 *
 */
Box** malloc_board (int table_size){
	int i;
	Box **board = (Box **) malloc( table_size * sizeof(Box));
	if (board == NULL) {
		printf("Error: <malloc> has failed\n");
		exit(0);
	}
	for (i = 0; i < table_size; i++) {
		board[i] = (Box *) malloc(table_size * sizeof(Box));
		if (board[i] == NULL) {
			printf("Error: <malloc> has failed\n");
			exit(0);
		}
	}
	return board;
}
/**
 * free_board:
 * Deallocates the memory previously allocated for the game_board.
 * @param board
 * @param table_Size
 */
void free_board (Box **board ,int table_Size){
	int i;
	for (i = 0; i < table_Size; i++) {
		free(board[i]);
		}
	free(board);
}
