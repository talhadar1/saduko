/**
 * Main_aux Summary:
 * This module implements Game board memory allocation/deallocation methods.
 *
 * malloc_board			- Allocate the requested memory for the game board and returns a pointer to it.
 * free_board			- Deallocates the memory previously allocated for the game_board.
 */

#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_
#include "Game.h"

Box** malloc_board (int table_Size);
void free_board (Box **board ,int table_Size);

#endif /* MAIN_AUX_H_ */
