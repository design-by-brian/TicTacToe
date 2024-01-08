#ifndef BOARD_DISPLAY_H
#define BOARD_DISPLAY_H

#include "LinkedList.h"
#include "TicTacToe.h"

void printBoard(int, int, char**);
int checkWinner(char**, int, int, int*); 
int playerMove(int*, LinkedList*, char**, char);
int quitGame(void);

#endif
